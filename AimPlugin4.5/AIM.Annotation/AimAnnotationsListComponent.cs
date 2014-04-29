#region License

// Copyright (c) 2007 - 2014, Northwestern University, Vladimir Kleper, Skip Talbot
// and Pattanasak Mongkolwat.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
//   Neither the name of the National Cancer Institute nor Northwestern University
//   nor the names of its contributors may be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

using System;
using System.Collections.Generic;
using System.Linq;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.StudyManagement;

using AIM.Annotation.AimManager;
using AIM.Annotation.Graphics;
using AIM.Annotation.Configuration;

namespace AIM.Annotation
{
	/// <summary>
	/// Extension point for views onto <see cref="AimAnnotationsListComponent"/>.
	/// </summary>
	[ExtensionPoint]
	public sealed class AimAnnotationsListComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	/// <summary>
	/// AimAnnotationsListComponent class.
	/// </summary>
	[AssociateView(typeof(AimAnnotationsListComponentViewExtensionPoint))]
	public class AimAnnotationsListComponent : ApplicationComponent
	{
		private readonly IDesktopWindow _desktopWindow;
		private IImageViewer _activeViewer;

		private string _selectedAnnotationUid;

		//private List<aim_dotnet.Annotation> _availableStudyAnnotations; // all annotations in the current study
		private List<IAimAnnotationInstance> _availableStudyAnnotations; // all annotations in the current study

		private bool _isImageViewerActive;
		private bool _isImageSelected;


		//public event EventHandler SelectedStudyChanged;
		public event EventHandler SelectedImageChanged;
		public event EventHandler SelectedAnnotationUidChanged;

		public event EventHandler AvailableAnnotationsChanged;

		/// <summary>
		/// Constructor.
		/// </summary>
		public AimAnnotationsListComponent(IDesktopWindow desktopWindow)
		{
			_desktopWindow = desktopWindow;
		}

		private List<IAimAnnotationInstance> AvailableAnnotations
		{
			get { return _availableStudyAnnotations; }
			set
			{
				if (_availableStudyAnnotations == value)
					return;

				_availableStudyAnnotations = value;

				EventsHelper.Fire(AvailableAnnotationsChanged, this, EventArgs.Empty);
				//NotifyPropertyChanged("AvailableAnnotations");
			}
		}

		public string SelectedAnnotationUid
		{
			get { return _selectedAnnotationUid; }
			set
			{
				if (_selectedAnnotationUid == value)
					return;

				_selectedAnnotationUid = value;

				EventsHelper.Fire(SelectedAnnotationUidChanged, this, EventArgs.Empty);
				//NotifyPropertyChanged("SelectedAnnotation");
			}
		}

		public bool IsImageViewerActive
		{
			get { return _isImageViewerActive; }
			set
			{
				if (_isImageViewerActive == value)
					return;

				_isImageViewerActive = value;
				NotifyPropertyChanged("IsImageViewerActive");
			}
		}

		public bool IsImageSelected
		{
			get { return _isImageSelected; }
			set
			{
				if (_isImageSelected == value)
					return;

				_isImageSelected = value;
				NotifyPropertyChanged("IsImageSelected");
			}
		}

		internal static IShelf Launch(IDesktopWindow desktopWindow)
		{
			AimAnnotationsListComponent component = new AimAnnotationsListComponent(desktopWindow);
			Shelf shelf = LaunchAsShelf(
				desktopWindow,
				component,
				"Available AIM Annotations",
				"AimAnnotations",
				ShelfDisplayHint.DockLeft | ShelfDisplayHint.DockAutoHide);

			return shelf;
		}

		private void SetImageViewer(Workspace workspace)
		{
			IImageViewer viewer = CastToImageViewer(workspace);
			if (viewer == _activeViewer)
				return;

			if (_activeViewer != null)
			{
				_activeViewer.EventBroker.ImageBoxSelected -= OnImageBoxSelected;
				_activeViewer.EventBroker.TileSelected -= OnTileSelected;
				_activeViewer.EventBroker.GraphicSelectionChanged -= OnGraphicSelectionChanged;
				_activeViewer.EventBroker.PresentationImageSelected -= OnPresentationImageSelected;
				//_activeViewer.EventBroker.DisplaySetChanged -= OnImageViewerDisplaySetChanged;
			}

			_activeViewer = viewer;

			if (_activeViewer != null)
			{
				_activeViewer.EventBroker.ImageBoxSelected += OnImageBoxSelected;
				_activeViewer.EventBroker.TileSelected += OnTileSelected;
				_activeViewer.EventBroker.GraphicSelectionChanged += OnGraphicSelectionChanged;
				_activeViewer.EventBroker.PresentationImageSelected += OnPresentationImageSelected;
				//_activeViewer.EventBroker.DisplaySetChanged += OnImageViewerDisplaySetChanged;
			}

			SetInitialSelections();
		}

		private static IImageViewer CastToImageViewer(Workspace workspace)
		{
			IImageViewer viewer = null;
			if (workspace != null)
				viewer = ImageViewerComponent.GetAsImageViewer(workspace);

			return viewer;
		}

		// Sets initial Available and Selected annotations
		private void SetInitialSelections()
		{
			SetAvailableAnnotations();
			SetSelectedAnnotation(_activeViewer != null && _activeViewer.SelectedPresentationImage != null
										   ? _activeViewer.SelectedPresentationImage.SelectedGraphic
										   : null);
			IsImageViewerActive = _activeViewer != null;

			EventsHelper.Fire(SelectedImageChanged, this, EventArgs.Empty);
		}

		private void OnImageBoxSelected(object sender, ImageBoxSelectedEventArgs e)
		{
			if (e.SelectedImageBox == null || e.SelectedImageBox.SelectedTile == null || e.SelectedImageBox.SelectedTile.PresentationImage == null)
				SetSelectedAnnotation(null);
			else
				SetSelectedAnnotation(e.SelectedImageBox.SelectedTile.PresentationImage.SelectedGraphic);
		}

		private void OnTileSelected(object sender, TileSelectedEventArgs e)
		{
			if (e.SelectedTile != null)
			{
				// NOTE: only do this if we have multiple tiles. For a 1x1 case, other events take care of 
				if (e.SelectedTile.ParentImageBox.Tiles.Count > 1)
					SetSelectedAnnotation(e.SelectedTile.PresentationImage == null ? null : e.SelectedTile.PresentationImage.SelectedGraphic);
			}
		}

		private void OnGraphicSelectionChanged(object sender, GraphicSelectionChangedEventArgs e)
		{
			SetSelectedAnnotation(e.SelectedGraphic);
		}

		private void OnPresentationImageSelected(object sender, PresentationImageSelectedEventArgs e)
		{
			SetSelectedAnnotation(e.SelectedPresentationImage == null ? null : e.SelectedPresentationImage.SelectedGraphic);
		}

		//private void OnImageViewerDisplaySetChanged(object sender, DisplaySetChangedEventArgs e)
		//{
		//    SetAvailableAnnotations();
		//}

		private void SetAvailableAnnotations()
		{
			if (_activeViewer == null)
			{
				AvailableAnnotations = null;
				return;
			}

			HashSet<string> studyUids = new HashSet<string>();
			foreach (IImageSet imageSet in _activeViewer.LogicalWorkspace.ImageSets)
			{
				foreach (IDisplaySet displaySet in imageSet.DisplaySets)
				{
					foreach (IPresentationImage image in displaySet.PresentationImages)
					{
						IImageSopProvider imageSop = image as IImageSopProvider;
						if (imageSop != null)
							studyUids.Add(imageSop.ImageSop.StudyInstanceUid);
					}
				}
			}

			// Load & sort annotations by name
			var allAnnotations = new List<IAimAnnotationInstance>();
			foreach (var studyUid in studyUids)
			{
				var allStudyAnnotations = AimManager.AimManager.Instance.LoadLocalAnnotationsForStudy(studyUid);
				if (allStudyAnnotations != null)
					foreach (var aimInstance in allStudyAnnotations)
					{
						allAnnotations.AddRange(aimInstance.AimAnnotations);
					}
			}

			// TODO - this sort is bogus, need to sort by annotation name
			AvailableAnnotations =
				allAnnotations.Any()
					? CollectionUtils.Sort(allAnnotations, (ann1, ann2) =>
														   string.Compare(ann1.ParentAimDocument.SeriesInstanceUid, ann2.ParentAimDocument.SeriesInstanceUid,
																		  StringComparison.InvariantCultureIgnoreCase))
					: null;
		}

		private void SetSelectedAnnotation(ISelectableGraphic graphic)
		{
			IAimGraphic aimGraphic = graphic == null || graphic.ParentGraphic == null
										? null
										: graphic.ParentGraphic as IAimGraphic;
			SelectedAnnotationUid = aimGraphic == null ? null : aimGraphic.AnnotationUid;
		}

		public AimDetailsList AvailableAnnotationsDetails
		{
			get
			{
				var detailsList = new AimDetailsList();
				if (AvailableAnnotations != null)
				{
					foreach (var availableAnnotation in AvailableAnnotations)
					{
						var dataProvider = AimManager.AimManager.GetDataProvider(availableAnnotation);
						var annotationDetails = dataProvider.AimAnnotationDetails;
						detailsList.Add(annotationDetails);
					}
				}
				return detailsList;
			}
		}

		/// <summary>
		/// Called by the host to initialize the application component.
		/// </summary>
		public override void Start()
		{
			_desktopWindow.Workspaces.ItemActivationChanged += OnActiveWorkspaceChanged;

			SetImageViewer(_desktopWindow.ActiveWorkspace);

			base.Start();
		}

		/// <summary>
		/// Called by the host when the application component is being terminated.
		/// </summary>
		public override void Stop()
		{
			_desktopWindow.Workspaces.ItemActivationChanged -= OnActiveWorkspaceChanged;

			SetImageViewer(null);

			base.Stop();
		}

		private void OnActiveWorkspaceChanged(object sender, ItemEventArgs<Workspace> e)
		{
			SetImageViewer(e.Item);

			// Hack to populate the component.
			// Problem is when component is up and running before ImageViewer,
			// ItemActivationChanged will fire before the study is loaded;
			// therefore, no images/annotations are available yet.
			if (_activeViewer != null && _activeViewer.PhysicalWorkspace != null)
				_activeViewer.PhysicalWorkspace.LayoutCompleted += OnPhysicalWorkspaceLayoutCompleted;
		}

		private void OnPhysicalWorkspaceLayoutCompleted(object sender, EventArgs e)
		{
			SetInitialSelections();

			// Unsubscribe. We only need this the first time around
			_activeViewer.PhysicalWorkspace.LayoutCompleted -= OnPhysicalWorkspaceLayoutCompleted;
		}

		public void EditImageAnnotation(string aimUid, bool preview)
		{
			if (_activeViewer == null)
				return;

			// Find Annotation
			IAimAnnotationInstance annotationToShow = AvailableAnnotations.FirstOrDefault(annotation => annotation.UniqueIdentifier == aimUid);

			if (annotationToShow == null)
			{
				_activeViewer.DesktopWindow.ShowMessageBox("Could not locate annotation (UID = " + aimUid + ").", MessageBoxActions.Ok);
				return;
			}

			// Don't try to restore saved template - we'll be overwriting it anyway
			bool oldRestoreTreeFlag = AimSettings.Default.RestoreSavedAimTemplateTree;
			AimSettings.Default.RestoreSavedAimTemplateTree = false;

			AimAnnotationTool.StartAimAnnotationTool(_activeViewer);

			// Restore the setting
			AimSettings.Default.RestoreSavedAimTemplateTree = oldRestoreTreeFlag;
			AimSettings.Default.Save();

			if (AimAnnotationComponent.GetActiveComponent() != null)
			{
				var component = AimAnnotationComponent.GetActiveComponent();
				component.Preview = preview;
				component.LoadAimTemplateTreeFromAnnotation(annotationToShow); // will open the image as well
			}
		}

		public void ShowImageWithAnnotation(string aimUid)
		{
			if (_activeViewer == null)
				return;

			// Find Annotation
			IAimAnnotationInstance annotationToShow = AvailableAnnotations.FirstOrDefault(annotation => annotation.UniqueIdentifier == aimUid);

			if (annotationToShow == null)
			{
				_activeViewer.DesktopWindow.ShowMessageBox("Could not locate annotation (UID = " + aimUid + ").", MessageBoxActions.Ok);
				return;
			}

			string studyInstanceUid;
			string seriesInstanceUid;
			string sopInstanceUid = null;
			int frameNumber = 1;

			if (annotationToShow is IAimImageAnnotationInstace)
			{
				var imageAnnotationToShow = (IAimImageAnnotationInstace) annotationToShow;
				studyInstanceUid = imageAnnotationToShow.ImageStudyUid;
				seriesInstanceUid = imageAnnotationToShow.ImageSeriesUid;
				sopInstanceUid = imageAnnotationToShow.FirstImageSopInstanceUid;
				frameNumber = imageAnnotationToShow.FirstFrameNumber;
			}
			else
			{
				studyInstanceUid = annotationToShow.ParentAimDocument.StudyInstanceUid;
				seriesInstanceUid = annotationToShow.ParentAimDocument.SeriesInstanceUid;
			}

			if (studyInstanceUid == null || seriesInstanceUid == null)
			{
				_activeViewer.DesktopWindow.ShowMessageBox("Error reading image information (annotation UID = " + aimUid + ").", MessageBoxActions.Ok);
				return;
			}

			// Search displayed images first
			foreach (IImageBox imageBox in _activeViewer.PhysicalWorkspace.ImageBoxes)
			{
				if (imageBox.DisplaySet == null || imageBox.DisplaySet.PresentationImages == null || imageBox.DisplaySet.PresentationImages.Count == 0)
					continue;

				IImageSopProvider imageSopProvider = imageBox.DisplaySet.PresentationImages[0] as IImageSopProvider;
				if (imageSopProvider == null)
					continue;

				if (imageSopProvider.ImageSop.StudyInstanceUid == studyInstanceUid &&
				    imageSopProvider.ImageSop.SeriesInstanceUid == seriesInstanceUid)
				{
					foreach (IPresentationImage presentationImage in imageBox.DisplaySet.PresentationImages)
					{
						imageSopProvider = presentationImage as IImageSopProvider;
						if (imageSopProvider == null)
							continue;
						// Note: will select the first image if there is no SOP Instance UID
						if (sopInstanceUid == null ||
							(imageSopProvider.ImageSop.SopInstanceUid == sopInstanceUid && imageSopProvider.Frame.FrameNumber == frameNumber))
						{
							try
							{
								// Unselect selected in a different image box
								if (!imageBox.Selected)
									UnselectCurrentGraphics(_activeViewer.PhysicalWorkspace.SelectedImageBox);

								imageBox.TopLeftPresentationImage = presentationImage;
								imageBox.Tiles[0].Select();
								SelectAimGraphic(presentationImage, aimUid);
								imageBox.Draw();

								return;
							}
							catch (Exception ex)
							{
								ExceptionHandler.Report(ex, _desktopWindow);
							}
						}
					}
				}
			}

			// Search other available images
			foreach (IImageSet imageSet in _activeViewer.LogicalWorkspace.ImageSets)
			{
				foreach (IDisplaySet displaySet in imageSet.DisplaySets)
				{
					if (displaySet.PresentationImages.Count > 0)
					{
						IImageSopProvider imageSopProvider = displaySet.PresentationImages[0] as IImageSopProvider;
						if (imageSopProvider == null)
							continue;

						if (imageSopProvider.ImageSop.StudyInstanceUid == studyInstanceUid &&
							imageSopProvider.ImageSop.SeriesInstanceUid == seriesInstanceUid)
						{
							foreach (IPresentationImage presentationImage in displaySet.PresentationImages)
							{
								imageSopProvider = presentationImage as IImageSopProvider;
								if (imageSopProvider == null)
									continue;
								// Note: will select the first image if there is no SOP Instance UID
								if (sopInstanceUid == null ||
									(imageSopProvider.ImageSop.SopInstanceUid == sopInstanceUid && imageSopProvider.Frame.FrameNumber == frameNumber))
								{
									try
									{
										IImageBox targetImageBox = _activeViewer.PhysicalWorkspace.SelectedImageBox ??
										                           (_activeViewer.PhysicalWorkspace.ImageBoxes.Count > 0 ? _activeViewer.PhysicalWorkspace.ImageBoxes[0] : null);
										if (targetImageBox == null)
										{
											_activeViewer.DesktopWindow.ShowMessageBox("Failed to find available display", MessageBoxActions.Ok);
											Platform.Log(LogLevel.Error, "Failed to locate a target ImageBox to display requested annotation (aimUID=" + aimUid + ").");
											return;
										}

										IDisplaySet targetDisplaySet = displaySet.CreateFreshCopy();
										IPresentationImage targetPresentationImage = FindRequiredImage(targetDisplaySet.PresentationImages,
										                                                               studyInstanceUid, seriesInstanceUid,
										                                                               sopInstanceUid, frameNumber);
										if (targetPresentationImage == null)
										{
											_activeViewer.DesktopWindow.ShowMessageBox("Failed to find required image", MessageBoxActions.Ok);
											Platform.Log(LogLevel.Error, "Failed to locate a target ImageBox to display requested annotation (aimUID=" + aimUid + ").");
											return;
										}

										// Unselect selected in a different image box
										if (!targetImageBox.Selected)
											UnselectCurrentGraphics(_activeViewer.PhysicalWorkspace.SelectedImageBox);

										targetImageBox.DisplaySet = targetDisplaySet;
										targetImageBox.TopLeftPresentationImage = targetPresentationImage;
										targetImageBox.Tiles[0].Select();
										SelectAimGraphic(targetPresentationImage, aimUid);
										targetImageBox.Draw();

										return;
									}
									catch (Exception ex)
									{
										ExceptionHandler.Report(ex, _desktopWindow);
									}
								}
							}
						}
					}
				}
			}
		}

		private IPresentationImage FindRequiredImage(PresentationImageCollection images, string studyInstanceUid, string seriesInstanceUid, string sopInstanceUid, int frameNumber)
		{
			return CollectionUtils.SelectFirst(
				images, image =>
							{
								IImageSopProvider
									imageSopProvider = image as IImageSopProvider;
								return imageSopProvider != null && imageSopProvider.ImageSop.StudyInstanceUid == studyInstanceUid &&
									   imageSopProvider.ImageSop.SeriesInstanceUid == seriesInstanceUid && imageSopProvider.ImageSop.SopInstanceUid == sopInstanceUid &&
									   imageSopProvider.Frame.FrameNumber == frameNumber;
							});
		}

		private void UnselectCurrentGraphics(IImageBox imageBox)
		{
			if (imageBox == null)
				return;

			if (imageBox.TopLeftPresentationImage != null)
			{
				imageBox.TopLeftPresentationImage.SelectedGraphic = null;
				imageBox.Draw();
			}
		}

		// makes requested Graphic object selected
		private void SelectAimGraphic(IPresentationImage presentationImage, string aimUid)
		{
			IOverlayGraphicsProvider imageGraphicsProvider = presentationImage as IOverlayGraphicsProvider;
			if (imageGraphicsProvider != null)
			{
				bool isFound = false;
				foreach (IGraphic graphic in imageGraphicsProvider.OverlayGraphics)
				{
					IAimGraphic aimGraphic = graphic as IAimGraphic;
					if (aimGraphic != null && aimGraphic.AnnotationUid == aimUid)
					{
						IDecoratorGraphic decoratorGraphic = aimGraphic as IDecoratorGraphic;
						if (decoratorGraphic != null)
						{
							presentationImage.SelectedGraphic = decoratorGraphic.DecoratedGraphic as ISelectableGraphic;
							presentationImage.FocussedGraphic = decoratorGraphic.DecoratedGraphic as IFocussableGraphic;
							if (presentationImage.SelectedGraphic != null)
							{
								presentationImage.SelectedGraphic.Selected = true;
								isFound = true;
							}
							break;
						}
					}
				}
				if (!isFound)
				{
					// Unselect current selection
					if (presentationImage.SelectedGraphic != null)
						presentationImage.SelectedGraphic.Selected = false;
					presentationImage.SelectedGraphic = null;
					presentationImage.FocussedGraphic = null;
				}
			}
		}

		public string GetSeriesCaption(string seriesUid)
		{
			if (_activeViewer == null)
				return null;

			var series = _activeViewer.StudyTree.GetSeries(seriesUid);
			return string.Format("{0} {1}{2}{3}: {4}",
				series.ParentStudy.ParentPatient.PatientsName,
				series.ParentStudy.StudyDate, 
				Environment.NewLine,
				series.SeriesNumber,
				series.SeriesDescription);
		}
	}
}
