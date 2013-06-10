#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Dicom.DataStore;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;
using ClearCanvas.ImageViewer.Services.ServerTree;
using ClearCanvas.ImageViewer.StudyManagement;

namespace AIM.Annotation
{
	[MenuAction("show", "global-menus/MenuAnnotation/AIMAnnotationMenu", "Show")]
	[ButtonAction("show", "global-toolbars/ToolbarStandard/AIMAnnotationButton", "Show")]
	[Tooltip("show", "AIMAnnotationTooltip")]
	[IconSet("show", IconScheme.Colour, "Icons.AIMAnnotationToolSmall.png", "Icons.AIMAnnotationToolMedium.png", "Icons.AIMAnnotationToolLarge.png")]

	[EnabledStateObserver("show", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(ImageViewerToolExtensionPoint))]
	public class AimAnnotationTool : ImageViewerTool
	{
		private static readonly Dictionary<IDesktopWindow, IShelf> _shelves = new Dictionary<IDesktopWindow, IShelf>();
		private IDesktopWindow _desktopWindow;
		// List of retieved SR objects for each study
		private readonly Dictionary<string, StudyItemList> _studyAnnotations = new Dictionary<string, StudyItemList>();
		private readonly AimInstanceDictionary _annotationDictionary = new AimInstanceDictionary();

		public AimAnnotationTool()
		{
			_desktopWindow = null;
		}

		public override void Initialize()
		{
			base.Initialize();

			ImageViewer.EventBroker.DisplaySetChanged += OnDisplaySetChanged;
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				_annotationDictionary.Clear();
				ImageViewer.EventBroker.DisplaySetChanged -= OnDisplaySetChanged;
			}

			base.Dispose(disposing);
		}

		protected void InitializeAnnotationList(string studyInstanceUID)
		{
			if (_annotationDictionary.ContainsStudy(studyInstanceUID))
				return;

			var studyAnnotations = GetAnnotationsList(studyInstanceUID);
			if (studyAnnotations == null || studyAnnotations.Count == 0)
				return;

			using (var reader = DataAccessLayer.GetIDataStoreReader())
			{
				foreach (var studyItem in studyAnnotations)
				{
					var study = reader.GetStudy(studyItem.StudyInstanceUid) as ClearCanvas.Dicom.DataStore.Study;
					if (study != null)
					{
						var allSeries = study.GetSeries();
						foreach (var series in allSeries)
						{
							if (series != null && series.Modality == "SR")
							{
								var sopInstances = series.GetSopInstances();
								foreach (var sopInstance in sopInstances)
								{
									if (sopInstance != null)
									{
										var fileUri = sopInstance.GetLocationUri();
										if (fileUri.IsFile)
											_annotationDictionary.Add(study.StudyInstanceUid, series.SeriesInstanceUid, sopInstance.SopInstanceUid, fileUri.LocalDiskPath);
									}
								}
							}
						}
					}
				}
			}
		}

		protected StudyItemList GetAnnotationsList(string studyInstanceUID)
		{
			if (!_studyAnnotations.ContainsKey(studyInstanceUID))
			{
				try
				{
					_studyAnnotations[studyInstanceUID] = RetrieveAnnotationsForStudy(studyInstanceUID);
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex);
					_studyAnnotations[studyInstanceUID] = null;
				}
			}

			return _studyAnnotations[studyInstanceUID];
		}

		private static StudyItemList RetrieveAnnotationsForStudy(string studyInstanceUID)
		{
			var queryParams = new QueryParameters();
			queryParams.Add("PatientsName", "");
			queryParams.Add("ReferringPhysiciansName", "");
			queryParams.Add("PatientId", "");
			queryParams.Add("AccessionNumber", "");
			queryParams.Add("StudyDescription", "");
			queryParams.Add("ModalitiesInStudy", "SR");
			queryParams.Add("StudyDate", "");
			queryParams.Add("StudyInstanceUid", studyInstanceUID);

			var serverTree = new ServerTree();
			var failedServerInfo = new List<KeyValuePair<string, Exception>>();
			var localDataStoreList = new List<IServerTreeNode>();
			localDataStoreList.Add(serverTree.RootNode.LocalDataStoreNode);

			return Query(queryParams, failedServerInfo, localDataStoreList);
		}

		private static StudyItemList Query(QueryParameters queryParams, List<KeyValuePair<string, Exception>> failedServerInfo, List<IServerTreeNode> servers)
		{
			var aggregateStudyItemList = new StudyItemList();
			foreach (var serverNode in servers)
			{
				try
				{
					StudyItemList serverStudyItemList;
					if (serverNode.IsLocalDataStore)
					{
						serverStudyItemList = ImageViewerComponent.FindStudy(queryParams, null, "DICOM_LOCAL");
					}
					else if (serverNode.IsServer)
					{
						var server = (Server)serverNode;
						var ae = new ApplicationEntity(
							server.Host,
							server.AETitle,
							server.Name,
							server.Port,
							server.IsStreaming,
							server.HeaderServicePort,
							server.WadoServicePort);

						serverStudyItemList = ImageViewerComponent.FindStudy(queryParams, ae, "DICOM_REMOTE");
					}
					else
					{
						throw new Exception("Server is not queryable");
					}

					aggregateStudyItemList.AddRange(serverStudyItemList);
				}
				catch (Exception e)
				{
					failedServerInfo.Add(new KeyValuePair<string, Exception>(serverNode.Name, e));
				}
			}

			return aggregateStudyItemList;
		}

		public void Show()
		{
			if (_shelves.ContainsKey(Context.DesktopWindow))
			{
				_shelves[Context.DesktopWindow].Activate();
			}
			else
			{
				BlockingOperation.Run(delegate
										{
											_desktopWindow = Context.DesktopWindow;
											var aimComponent = new AimAnnotationComponent(Context.DesktopWindow);
											var shelf = ApplicationComponent.LaunchAsShelf(
												_desktopWindow,
												aimComponent,
												SR.TitleAIMCreater,
												"AIM Annotation",
												ShelfDisplayHint.DockRight | ShelfDisplayHint.DockAutoHide);

											shelf.Closed += OnShelfClosed;
											_shelves[_desktopWindow] = shelf;
										});
			}
		}

		private void OnShelfClosed(object sender, ClosedEventArgs e)
		{
			_shelves[_desktopWindow].Closed -= OnShelfClosed;
			_shelves.Remove(_desktopWindow);
			_desktopWindow = null;
		}

		private void OnDisplaySetChanged(object sender, DisplaySetChangedEventArgs e)
		{
			if (e.NewDisplaySet != null && e.NewDisplaySet.Visible)
			{
				var uidCnt = new Dictionary<string, int>();
				foreach (var img in e.NewDisplaySet.PresentationImages)
				{
					var imageSopPrivider = img as IImageSopProvider;
					if (imageSopPrivider != null)
					{
						var studyInstanceUID = imageSopPrivider.ImageSop.StudyInstanceUid;
						if (uidCnt.ContainsKey(studyInstanceUID))
							uidCnt[studyInstanceUID] += 1;
						else
							uidCnt[studyInstanceUID] = 1;
					}
				}

				var annotationList = new List<aim_dotnet.Annotation>();
				var dcmModel = new aim_dotnet.DcmModel();
				foreach (var studyInstanceUID in uidCnt.Keys)
				{
					InitializeAnnotationList(studyInstanceUID);
					var annotationSopsInfo = _annotationDictionary[studyInstanceUID];
					if (annotationSopsInfo == null)
						continue;

					foreach (var information in annotationSopsInfo)
					{
						try
						{
							annotationList.AddRange(dcmModel.ReadAnnotationsFromFile(information.InstanceFileName));
						}
						catch (Exception ex)
						{
							Platform.Log(LogLevel.Error, ex);
						}
					}
				}

				foreach (var annotation in annotationList)
				{
					foreach (var img in e.NewDisplaySet.PresentationImages)
					{
						AimHelpers.ReadGraphicsFromAnnotation(annotation, img);
					}
				}
			}
		}
	}
}
