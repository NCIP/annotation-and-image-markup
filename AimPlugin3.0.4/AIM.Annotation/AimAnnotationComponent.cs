//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Validation;
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Network;
using ClearCanvas.Dicom.Network.Scu;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.RoiGraphics.Analyzers;
using ClearCanvas.ImageViewer.Services.LocalDataStore;
using ClearCanvas.ImageViewer.StudyManagement;
using ClearCanvas.ImageViewer.Services.ServerTree;

using AIM.Annotation.Configuration;
using aim_dotnet;
using AnatomicEntity = aim_dotnet.AnatomicEntity;
using ImagingObservation = aim_dotnet.ImagingObservation;
using Inference = aim_dotnet.Inference;

namespace AIM.Annotation
{
	[ExtensionPoint]
	public sealed class AimAnnotationComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	[AssociateView(typeof(AimAnnotationComponentViewExtensionPoint))]
	public class AimAnnotationComponent : ImageViewerToolComponent
	{
		private string _annotationName;
		private List<AnatomicEntity> _anatomicEntities;
		private List<ImagingObservation> _imagingObservations;
		private List<Inference> _inferences;
		private StandardCodeSequence _annotationTypeCode; // i.e. selected template code 

		private Template.TemplateContainer _loadedTemplateContainer;
		private bool _isAimTemplateValid;

		private Dictionary<string, string> _sopInstanceUidToAeTitle = new Dictionary<string, string>();
		private object _mapLock = new object();

		private ILocalDataStoreEventBroker _localDataStoreEventBroker;

		public event EventHandler AnnotationCreated;
		public event EventHandler AnnotationCreating;

		public static StandardCodeSequence NullCodeValue = new StandardCodeSequence("C47840", "Null", "NCIt");

		public AimAnnotationComponent(IDesktopWindow desktopWindow)
			: base(desktopWindow)
		{
			if (AvailableAnnotationTypes.Count > 0)
				_annotationTypeCode = AvailableAnnotationTypes[0];
			AnnotationName = CreateDefaultAnnotationName();
		}

		[ValidateNotNull(Message = "AnnotationTypeCannotBeNull")]
		public StandardCodeSequence AnnotationTypeCode
		{
			get { return _annotationTypeCode; }
			set
			{
				if (_annotationTypeCode != value)
				{
					if (_annotationTypeCode != null && _annotationTypeCode.Equals(value))
						return;

					_annotationTypeCode = value;

					NotifyPropertyChanged("SelectedAimTemplate");
					NotifyPropertyChanged("AimTemplateVisible");
				}
			}
		}

		public List<StandardCodeSequence> AvailableAnnotationTypes
		{
			get { return AvailableAimTemplates; }
		}

		public bool AimTemplateVisible
		{
			get
			{
				return AnnotationTypeCode == null ||
					   AvailableAimTemplates.Find(code => code.Equals(AnnotationTypeCode)) != null;
			}
		}

		[ValidateNotNull(Message = "AnnotationNameCannotBeNull")]
		public string AnnotationName
		{
			get { return _annotationName; }
			set
			{
				if (_annotationName != value)
				{
					_annotationName = value;

					NotifyPropertyChanged("AnnotationName");
					NotifyPropertyChanged("CreateAnnotationEnabled");
				}
			}
		}

		#region User Info
		public string UserName
		{
			get { return AimSettings.Default.UserName; }
			set
			{
				if (AimSettings.Default.UserName != value)
				{
					AimSettings.Default.UserName = value;
					AimSettings.Default.Save();
				}
			}
		}

		public string LoginName
		{
			get { return AimSettings.Default.UserLoginName; }
			set
			{
				if (AimSettings.Default.UserLoginName != value)
				{
					AimSettings.Default.UserLoginName = value;
					AimSettings.Default.Save();
				}
			}
		}

		public string RoleInTrial
		{
			get { return AimSettings.Default.UserRoleInTrial; }
			set
			{
				if (AimSettings.Default.UserRoleInTrial != value)
				{
					AimSettings.Default.UserRoleInTrial = value;
					AimSettings.Default.Save();
				}
			}
		}

		public int NumberWithinRoleInTrial
		{
			get { return AimSettings.Default.UserNumberWitinRoleOfClinicalTrial; }
			set
			{
				AimSettings.Default.UserNumberWitinRoleOfClinicalTrial = value;
				AimSettings.Default.Save();
			}
		}
		#endregion User Info

		private string CreateDefaultAnnotationName()
		{
			var defaultName = "";
			var dateTime = DateTime.Now;
			var dateTimeStr = dateTime.ToString("yyyy-MM-dd HH:mm tt");
			var iImageSopProvider = ImageViewer.SelectedPresentationImage as IImageSopProvider;
			if (iImageSopProvider != null)
			{
				defaultName = iImageSopProvider.ImageSop.PatientId + "_" + AimSettings.Default.UserName + "_" + dateTimeStr;
			}
			return defaultName;
		}

		/// <summary>
		/// Validates an XML template against the v19 and v23 schemas, while converting
		/// v19 templates to v23 templates and returning the filename of the original
		/// template if not converted, or a new filename if the template was converted.
		/// </summary>
		/// <param name="templateFilename">The filename of the validated v23 template.  Empty
		/// if validation fails.</param>
		/// <returns></returns>
		private string ValidateAndConvertAimTemplate(string templateFilename)
		{
			var validated = false;
			Utilities.ValidationResult result;

			// Validate against v19 schema first
			try
			{
				result = Utilities.ValidateXML.Initialize(
					"AIM.Annotation.Template.AIMTemplate_v1rv19.xsd",
					"gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate",
					templateFilename);
				// Convert to v23 if v19 template validated
				if (result.Validated)
				{
					try
					{
						var newTemplateFilename = System.IO.Path.GetTempFileName();
						var mapper = new AimTemplateConverter.ConverterToAimTemplateV1Rv23();
						mapper.Run(templateFilename, newTemplateFilename);
						templateFilename = newTemplateFilename;
					}
					catch (Exception ex)
					{
						Platform.Log(LogLevel.Error, ex, "Failed to convert template file: {0} from v19 to v23", templateFilename);
					}
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to validate v19 template file: {0}", templateFilename);
			}

			// Validate against v23 template
			try
			{
				result = Utilities.ValidateXML.Initialize(
					"AIM.Annotation.Template.AIMTemplate_v1rv23.xsd",
					"gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate",
					templateFilename);
				validated = result.Validated;
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to validate v23 template file: {0}", templateFilename);
			}

			return validated ? templateFilename : string.Empty;
		}

		public Template.TemplateContainer LoadedTemplateDoc
		{
			get
			{
				if (_loadedTemplateContainer == null)
				{
					var templateDocPathName = AimSettings.Default.SelectedTemplatePathName ?? "";
					if (System.IO.File.Exists(templateDocPathName))
					{
						try
						{
							var template = ValidateAndConvertAimTemplate(templateDocPathName);

							if (!string.IsNullOrEmpty(template))
								using (var fs = System.IO.File.OpenRead(template))
								{
									_loadedTemplateContainer = Template.TemplateContainerSerializer.ReadStream(fs);
								}
						}
						catch (Exception ex)
						{
							Platform.Log(LogLevel.Error, ex, "Failed to open template file: {0}", templateDocPathName);
						}
					}
					if (_loadedTemplateContainer == null)
					{
						var resolver = new ResourceResolver(GetType().Assembly);
						try
						{
							using (var stream = resolver.OpenResource("Template.AIM_Template_v1rv18_TCGA_v5.xml"))
							{
								_loadedTemplateContainer = Template.TemplateContainerSerializer.ReadStream(stream);
							}
						}
						catch (Exception)
						{
							_loadedTemplateContainer = null;
						}
					}
				}
				return _loadedTemplateContainer;
			}
		}

		public Template.Template SelectedAimTemplate
		{
			get
			{
				return LoadedTemplateDoc == null
						? null
						: LoadedTemplateDoc.Template.Find(
							t =>
							t.CodeValue == AnnotationTypeCode.CodeValue &&
							t.CodeMeaning == AnnotationTypeCode.CodeMeaning &&
							t.CodingSchemeDesignator == AnnotationTypeCode.CodingSchemeDesignator &&
							t.CodingSchemeVersion == AnnotationTypeCode.CodingSchemeVersion);
			}
		}

		public List<StandardCodeSequence> AvailableAimTemplates
		{
			get
			{
				var retVal = new List<StandardCodeSequence>();
				if (LoadedTemplateDoc != null)
				{
					LoadedTemplateDoc.Template.ForEach(
						template =>
						retVal.Add(new StandardCodeSequence(
									template.CodeValue,
									template.CodeMeaning,
									template.CodingSchemeDesignator,
									template.CodingSchemeVersion))
						);
				}
				return retVal;
			}
		}

		public string SelectedAimTemplateDocument
		{
			get { return AimSettings.Default.SelectedTemplatePathName ?? ""; }
			set
			{
				if (AimSettings.Default.SelectedTemplatePathName != value &&
					AvailableAnnotationTypes.Count > 0)
				{
					AimSettings.Default.SelectedTemplatePathName = value;
					AimSettings.Default.Save();

					_loadedTemplateContainer = null;

					AnnotationTypeCode = AvailableAnnotationTypes[0];

					NotifyPropertyChanged("AvailableAnnotationTypes");
				}
			}
		}

		public string SelectedAimTemplateLocalFolder
		{
			get
			{
				return System.IO.File.Exists(AimSettings.Default.SelectedTemplatePathName ?? "")
						? System.IO.Path.GetFullPath(AimSettings.Default.SelectedTemplatePathName ?? "")
						: (string.IsNullOrEmpty(AimSettings.Default.LocalTemplatesFolder)
							? Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)
							: AimSettings.Default.LocalTemplatesFolder);
			}
		}

		public List<AnatomicEntity> SelectedAnatomicEntities
		{
			get { return _anatomicEntities; }
			set
			{
				if (_anatomicEntities != value)
				{
					_anatomicEntities = (null == value || value.Count == 0) ? null : new List<AnatomicEntity>(value);

					NotifyPropertyChanged("SelectedAnatomicEntities");
					NotifyPropertyChanged("CreateAnnotationEnabled");
				}
			}
		}

		public List<ImagingObservation> SelectedImagingObservations
		{
			get { return _imagingObservations; }
			set
			{
				if (_imagingObservations != value)
				{
					_imagingObservations = (null == value || value.Count == 0) ? null : new List<ImagingObservation>(value);

					NotifyPropertyChanged("SelectedImagingObservations");
				}
			}
		}

		public List<Inference> SelectedInferences
		{
			get { return _inferences; }
			set
			{
				if (_inferences != value)
				{
					_inferences = null == value || value.Count == 0 ? null : new List<Inference>(value);

					NotifyPropertyChanged("SelectedInferences");
				}
			}
		}

		public bool AnnotationModuleEnabled
		{
			get { return ImageViewer != null && ImageViewer.SelectedPresentationImage != null; }
		}

		public bool CreateAnnotationEnabled
		{
			get
			{
				return !HasValidationErrors &&
				AnnotationModuleEnabled && AnnotationTypeCode != null
				&& !string.IsNullOrEmpty(_annotationName)
				&& (!AimTemplateVisible || (AimTemplateVisible && IsAimTemplateValid))
				&& HasValidUserData
				&& HasRequiredMakup;
			}
		}

		protected bool IsAnatomicEntityEmpty
		{
			get { return _anatomicEntities == null || _anatomicEntities.Count == 0; }
		}

		protected bool HasValidUserData
		{
			get { return !AimSettings.Default.RequireUserInfo || !string.IsNullOrEmpty(UserName) && !string.IsNullOrEmpty(LoginName); }
		}

		protected bool HasRequiredMakup
		{
			get { return !AimSettings.Default.RequireMarkupInAnnotation || AimHelpers.IsImageMarkupPresent(ImageViewer.SelectedPresentationImage); }
		}

		public bool IsAimTemplateValid
		{
			get { return _isAimTemplateValid; }
			set
			{
				if (_isAimTemplateValid != value)
				{
					_isAimTemplateValid = value;
					NotifyPropertyChanged("CreateAnnotationEnabled");
				}
			}
		}

		protected override void OnActiveImageViewerChanged(ActiveImageViewerChangedEventArgs e)
		{
			if (e.ActivatedImageViewer != null)
			{
				e.ActivatedImageViewer.EventBroker.TileSelected += OnTileSelected;
				e.ActivatedImageViewer.EventBroker.MouseCaptureChanged += OnMouseCaptureChanged;
				e.ActivatedImageViewer.EventBroker.GraphicSelectionChanged += OnGraphicSelectionChanged;
			}

			NotifyPropertyChanged("AnnotationModuleEnabled");
			NotifyPropertyChanged("CreateAnnotationEnabled");
			NotifyPropertyChanged("CalculationInfo");
		}

		protected override void OnActiveImageViewerChanging(ActiveImageViewerChangedEventArgs e)
		{
			if (e.DeactivatedImageViewer != null)
			{
				e.DeactivatedImageViewer.EventBroker.TileSelected -= OnTileSelected;
				e.DeactivatedImageViewer.EventBroker.MouseCaptureChanged -= OnMouseCaptureChanged;
				e.DeactivatedImageViewer.EventBroker.GraphicSelectionChanged -= OnGraphicSelectionChanged;
			}
		}

		private void OnTileSelected(object sender, TileSelectedEventArgs e)
		{
			NotifyPropertyChanged("AnnotationModuleEnabled");
			NotifyPropertyChanged("CreateAnnotationEnabled");
			NotifyPropertyChanged("CalculationInfo");
		}

		private void OnMouseCaptureChanged(object sender, ClearCanvas.ImageViewer.InputManagement.MouseCaptureChangedEventArgs e)
		{
			NotifyPropertyChanged("CalculationInfo");
		}

		private void OnGraphicSelectionChanged(object sender, GraphicSelectionChangedEventArgs e)
		{
			NotifyPropertyChanged("AnnotationModuleEnabled");
			NotifyPropertyChanged("CreateAnnotationEnabled");
		}

		#region Start/Stop methods
		public override void Start()
		{
			base.Start();

			_localDataStoreEventBroker = LocalDataStoreActivityMonitor.CreatEventBroker();
			_localDataStoreEventBroker.SopInstanceImported += OnSopInstanceImported;
			AimSettings.Default.PropertyChanged += OnAimSettingsChanged;

			try
			{
				// Create extension points that use this component
				var xp = new AimAnnotationExtensionPoint();
				foreach (var obj in xp.CreateExtensions())
				{
					var extension = (IAimAnnotationExtension)obj;
					extension.Component = this;
				}
			}
			catch (NotSupportedException)
			{
			}
		}

		public override void Stop()
		{
			AimSettings.Default.PropertyChanged -= OnAimSettingsChanged;
			_localDataStoreEventBroker.SopInstanceImported -= OnSopInstanceImported;
			_localDataStoreEventBroker.Dispose();

			base.Stop();
		}
		#endregion

		private void OnAimSettingsChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
		{
			NotifyPropertyChanged("CreateAnnotationEnabled");
		}

		public string[] CalculationInfo
		{
			get
			{
				if (ImageViewer != null)
				{
					var overlayGraphicProvider = ImageViewer.SelectedPresentationImage as IOverlayGraphicsProvider;
					if (overlayGraphicProvider != null)
					{
						var sb = new StringBuilder();
						var lineFeed = Environment.NewLine + "    ";
						var roiCnt = 0;
						foreach (var graphic in overlayGraphicProvider.OverlayGraphics)
						{
							var currentRoiGraphic = graphic as RoiGraphic;
							if (currentRoiGraphic != null)
							{
								if (sb.Length > 0)
									sb.Append(Environment.NewLine);
								if (string.IsNullOrEmpty(currentRoiGraphic.Name))
									sb.AppendFormat("ROI #{0}:", ++roiCnt);
								else
									sb.AppendFormat("ROI #{0} ({1}):", ++roiCnt, currentRoiGraphic.Name);
								var roi = currentRoiGraphic.Roi;
								foreach (var analyzer in currentRoiGraphic.Callout.RoiAnalyzers)
								{
									if (analyzer.SupportsRoi(roi))
									{
										var text = analyzer.Analyze(roi, RoiAnalysisMode.Normal).Trim().Replace("\r\n", "{0}").Replace("\n", "{0}");
										sb.Append(lineFeed);
										sb.AppendFormat(text, lineFeed);
									}
								}
							}
						}

						var strRetVal = sb.ToString().Split(new[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries);
						sb.Length = 0;
						return strRetVal;
					}
				}

				return new string[0];
			}

			set { }
		}

		private void ResetAnnotationData()
		{
			SelectedImagingObservations = null;
			SelectedAnatomicEntities = null;
			SelectedInferences = null;
			AnnotationName = CreateDefaultAnnotationName();

			EventsHelper.Fire(AnnotationCreated, this, EventArgs.Empty);
		}

		private List<aim_dotnet.Annotation> CreateAnnotationsFromUserInput(out List<IGraphic> annotationsGraphic)
		{
			var aimContext = new AimAnnotationCreationContext(AnnotationKind.AK_ImageAnnotation, AnnotationTypeCode, AnnotationName);
			aimContext.SelectedAnatomicEntities = SelectedAnatomicEntities;
			aimContext.SelectedImagingObservations = SelectedImagingObservations;
			aimContext.SelectedInferences = SelectedInferences;
			aimContext.AnnotationUser = (!string.IsNullOrEmpty(UserName) && !string.IsNullOrEmpty(LoginName))
											?
												new User
													{
														Name = UserName,
														LoginName = LoginName,
														RoleInTrial = RoleInTrial,
														NumberWithinRoleOfClinicalTrial = NumberWithinRoleInTrial >= 0 ? NumberWithinRoleInTrial : -1
													}
											: null;
			aimContext.includeCalculations = true;
			aimContext.SOPImageUIDs = new List<string> { ((IImageSopProvider)ImageViewer.SelectedPresentationImage).ImageSop.SopInstanceUid };
			return AimHelpers.CreateAimAnnotations(ImageViewer.SelectedPresentationImage.ParentDisplaySet.PresentationImages, aimContext, out annotationsGraphic);
		}

		private List<IGraphic> _annotationGraphics;
		public List<IGraphic> AnnotationGraphics { get { return _annotationGraphics; } }

		public void CreateAnnotation()
		{
			if (!CreateAnnotationEnabled)
				return;

			if (base.HasValidationErrors)
			{
				Platform.Log(LogLevel.Info, "Cannot create annotation. Validation error(s): " + Validation.GetErrorsString(this));
				ShowValidation(true);
				return;
			}

			if (!LocalDataStoreActivityMonitor.IsConnected)
			{
				DesktopWindow.ShowMessageBox("Failed to save annotation. Not connected to the local data store. Is workstation service running?", MessageBoxActions.Ok);
				return;
			}

			// Get new annotations
			List<IGraphic> annotationsGraphic;
			var annotations = CreateAnnotationsFromUserInput(out annotationsGraphic);
			_annotationGraphics = annotationsGraphic;
			if (annotations.Count == 0)
			{
				Platform.Log(LogLevel.Warn, "CreateAnnotation resulted in no annotations being created");
				return;
			}

			EventsHelper.Fire(AnnotationCreating, this, EventArgs.Empty);

			var isAnyOperationPerformed = false;
			if (AimSettings.Default.StoreXmlAnnotationsLocally)
			{
				var destinationFolder = AimSettings.Default.ActualAnnotationStoreFolder;
				try
				{
					if (!System.IO.Directory.Exists(destinationFolder))
						System.IO.Directory.CreateDirectory(destinationFolder);

					var annFiles = AimHelpers.WriteXmlAnnotationsToFolder(annotations, destinationFolder);
					if (annotations.Count != annFiles.Length)
						Platform.Log(LogLevel.Error, "Only {0} annotations(s) out of {1} written to \"{0}\"", annFiles.Length, annotations.Count, destinationFolder);

					isAnyOperationPerformed = annFiles.Length > 0;
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to store annotations to local folder \"{0}\"", destinationFolder);
				}
			}

			if (AimSettings.Default.SendNewXmlAnnotationsToGrid)
			{
				if (SendAnnotationsToGrid(annotations))
					isAnyOperationPerformed = true;
				else
					Platform.Log(LogLevel.Error, "Failed to send annotations to the caGrid");
			}

			if (LocalDataStoreActivityMonitor.IsConnected)
				isAnyOperationPerformed = SendAnnotationsToLocalStorageAndPacs(annotations) || isAnyOperationPerformed;
			else
				DesktopWindow.ShowMessageBox("Failed to save annotation. Not connected to the local data store. Is workstation service running?", MessageBoxActions.Ok);

			if (isAnyOperationPerformed)
			{
				UpdateImagesWithProperAimGraphic(annotations, annotationsGraphic);

				// Reset all controls on the template
				//ResetAnnotationData();
			}
		}

		private void UpdateImagesWithProperAimGraphic(List<aim_dotnet.Annotation> annotations, List<IGraphic> annotationsGraphic)
		{
			var hasChanges = false;
			if (annotationsGraphic != null)
			{
				foreach (var graphic in annotationsGraphic)
				{
					Debug.Assert(graphic.ParentPresentationImage == null || graphic.ParentPresentationImage == ImageViewer.SelectedPresentationImage);

					var currentOverlayGraphics = graphic.ParentPresentationImage as IOverlayGraphicsProvider;
					if (currentOverlayGraphics != null && currentOverlayGraphics.OverlayGraphics != null)
						hasChanges |= currentOverlayGraphics.OverlayGraphics.Remove(graphic);

				}
			}

			if (annotations != null)
			{
				foreach (var annotation in annotations)
				{
					hasChanges |= AimHelpers.ReadGraphicsFromAnnotation(annotation, ImageViewer.SelectedPresentationImage);
				}
			}

			if (hasChanges)
				ImageViewer.SelectedPresentationImage.Draw();
		}

		private bool SendAnnotationsToLocalStorageAndPacs(List<aim_dotnet.Annotation> annotations)
		{
			var model = new DcmModel();
			var instanceInfos = new Dictionary<string, string>();
			foreach (var annotation in annotations)
			{
				var tempFileName = System.IO.Path.GetTempFileName();
				try
				{
					model.WriteAnnotationToFile(annotation, tempFileName);
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, "Failed to save annotation to temp file.", ex);
					try
					{
						System.IO.File.Delete(tempFileName);
					}
					catch
					{
					}
					continue;
				}

				var annFile = new DicomFile(tempFileName);
				annFile.Load(DicomReadOptions.Default | DicomReadOptions.DoNotStorePixelDataInDataSet);
				var annSopInstanceUid = annFile.DataSet[DicomTags.SopInstanceUid].GetString(0, string.Empty);
				annFile = null;

				instanceInfos.Add(annSopInstanceUid, tempFileName);
			}
			model = null;

			if (instanceInfos.Count < 1)
				return false;

			var imageAeTitle = string.Empty;
			var imageSopProvider = ImageViewer.SelectedPresentationImage as IImageSopProvider;
			if (imageSopProvider != null)
			{
				var localSopDataSource = imageSopProvider.ImageSop.DataSource as ILocalSopDataSource; //NativeDicomObject as DicomFile;
				if (localSopDataSource != null)
					imageAeTitle = localSopDataSource.File.SourceApplicationEntityTitle.Trim("\n\r".ToCharArray());
			}

			using (var localClient = new LocalDataStoreServiceClient())
			{
				try
				{
					localClient.Open();
					var request = new FileImportRequest();
					request.BadFileBehaviour = BadFileBehaviour.Delete;
					request.FileImportBehaviour = FileImportBehaviour.Move;
					var filePaths = new List<string>();
					foreach (var instanceInfo in instanceInfos)
					{
						var annSopInstanceUid = instanceInfo.Key;
						var tempFileName = instanceInfo.Value;
						filePaths.Add(tempFileName);
						if (!string.IsNullOrEmpty(imageAeTitle))
						{
							lock (_mapLock)
								_sopInstanceUidToAeTitle.Add(annSopInstanceUid, imageAeTitle);
						}
					}
					request.FilePaths = filePaths.ToArray();
					request.IsBackground = true;
					request.Recursive = false;
					localClient.Import(request);
					localClient.Close();
				}
				catch (Exception ex)
				{
					localClient.Abort();
					Platform.Log(LogLevel.Error, ex);
					DesktopWindow.ShowMessageBox("Failed to store your annotation(s).", "Annotation Import Error", MessageBoxActions.Ok);
					return false;
				}
			}
			return true;
		}

		private Server FindAETitle(ServerGroup serverGroup, string aeTitle)
		{
			foreach (var server in serverGroup.ChildServers)
			{
				if (server.AETitle == aeTitle)
					return server;
			}

			foreach (var childeServerGroup in serverGroup.ChildGroups)
			{
				var server = FindAETitle(childeServerGroup, aeTitle);
				if (server != null)
					return server;
			}

			return null;
		}

        // Called when a SOP Instance is imported into the local datastore
		private void OnSopInstanceImported(object sender, ItemEventArgs<ImportedSopInstanceInformation> e)
		{
			if (_sopInstanceUidToAeTitle.ContainsKey(e.Item.SopInstanceUid))
			{
				var destinationAeTitle = _sopInstanceUidToAeTitle[e.Item.SopInstanceUid];
				var destinationServer = FindAETitle(new ServerTree().RootNode.ServerGroupNode, destinationAeTitle);
				if (destinationServer == null)
				{
					Platform.Log(LogLevel.Error, "Study " + e.Item.SopInstanceUid + " cannot be send to server. Failed to find server infromation for AE Title " + destinationAeTitle + ".");
				}
				else
				{
					var storageScu = new StorageScu(ServerTree.GetClientAETitle(), destinationServer.AETitle, destinationServer.Host, destinationServer.Port);
					storageScu.ImageStoreCompleted += OnStoreEachInstanceCompleted;
					storageScu.AddFile(e.Item.SopInstanceFileName);
					storageScu.BeginSend(OnAnnotationSendComplete, storageScu);
				}
				lock (_mapLock)
					_sopInstanceUidToAeTitle.Remove(e.Item.SopInstanceUid);
			}
		}

		private void OnStoreEachInstanceCompleted(object sender, StorageInstance e)
		{
			if (e.SendStatus.Status != DicomState.Success)
				Platform.Log(LogLevel.Error, "Failed to send annotation to server. Status: " + e.SendStatus.Description);
		}

		private void OnAnnotationSendComplete(IAsyncResult ar)
		{
			var storageScu = (StorageScu)ar.AsyncState;
			if (storageScu.TotalSubOperations - storageScu.SuccessSubOperations > 0)
				Platform.Log(LogLevel.Error, "Not all annotations could be stored to server.");
			storageScu.Dispose();
		}

		private bool SendAnnotationsToGrid(List<aim_dotnet.Annotation> annotations)
		{
			if (annotations == null || annotations.Count == 0)
				return true;

			var xmlAnnotations = new Dictionary<string, string>();
			var xmlModel = new XmlModel();
			foreach (var annotation in annotations)
			{
				try
				{
					xmlAnnotations.Add(annotation.UniqueIdentifier, xmlModel.WriteAnnotationToXmlString(annotation));
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to convert annotation to xml.");
				}
			}
			xmlModel = null;

			// Send Annotations to AIM Service
			if (xmlAnnotations.Count > 0)
			{
				BackgroundTask task = null;
				try
				{
					task = new BackgroundTask(BackgroundSendAnnotationsToAimService, false, xmlAnnotations);
					ProgressDialog.Show(task, DesktopWindow, true);
					return true;
				}
				catch (Exception e)
				{
					Platform.Log(LogLevel.Error, e, "Failed to send annotation(s) to the AIM data service");
					DesktopWindow.ShowMessageBox("Failed to send annotation(s) to the AIM data service. See log for details.", MessageBoxActions.Ok);
				}
				finally
				{
					if (task != null)
						task.Dispose();
				}
			}

			return false;
		}

		private void BackgroundSendAnnotationsToAimService(IBackgroundTaskContext context)
		{
			var xmlAnnotations = context.UserState as Dictionary<string, string>;
			try
			{
				if (xmlAnnotations != null && xmlAnnotations.Count > 0)
				{
					var progress = new BackgroundTaskProgress(20, string.Format("Sending {0} annotation(s) to AIM data service.", xmlAnnotations.Count));
					context.ReportProgress(progress);
					AIMTCGAService.AIMTCGASubmit.sendAIMTCGAAnnotation(new List<string>(xmlAnnotations.Values).ToArray());
				}
				context.Complete();
			}
			catch (Exception ex)
			{
				SaveAnnotationsToQueue(xmlAnnotations, AIMTCGAService.AIMTCGASubmit.ServiceUrl);
				context.Error(ex);
			}
		}

		private void SaveAnnotationsToQueue(Dictionary<string, string> xmlAnnotations, string serverUrl)
		{
			Uri uri;
			string folderName;
			if (!string.IsNullOrEmpty(serverUrl) && Uri.TryCreate(serverUrl, UriKind.RelativeOrAbsolute, out uri))
			{
				if (AimSettings.Default.SendQueuesNames != null && AimSettings.Default.SendQueuesNames.ContainsKey(uri.AbsoluteUri))
				{
					Debug.Assert(!string.IsNullOrEmpty(AimSettings.Default.SendQueuesNames[uri.AbsoluteUri]));
					folderName = AimSettings.Default.SendQueuesNames[uri.AbsoluteUri];
				}
				else
				{
					if (AimSettings.Default.SendQueuesNames == null)
						AimSettings.Default.SendQueuesNames = new GeneralUtilities.Collections.XmlSerializableStringDictionary();
					var hashCode = uri.AbsoluteUri.GetHashCode();
					folderName = hashCode.ToString("X8");
					AimSettings.Default.SendQueuesNames[uri.AbsoluteUri] = folderName;
					AimSettings.Default.Save();
				}
			}
			else
			{
				folderName = "invalid_server";
			}

			var folderPath = System.IO.Path.Combine(AimSettings.Default.AnnotationQueuesFolder, folderName);
			try
			{
				if (!System.IO.Directory.Exists(folderPath))
					System.IO.Directory.CreateDirectory(folderPath);

				foreach (var xmlAnnotation in xmlAnnotations)
				{
					var fileName = string.IsNullOrEmpty(xmlAnnotation.Key) ? System.IO.Path.GetRandomFileName() : xmlAnnotation.Key;
					var xmlDoc = new System.Xml.XmlDocument();
					xmlDoc.LoadXml(xmlAnnotation.Value);
					xmlDoc.Save(System.IO.Path.ChangeExtension(System.IO.Path.Combine(folderPath, fileName), "xml"));

					Platform.Log(LogLevel.Info, "Added annotation to the queue: {0}", fileName);
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to queue annotaion(s) for subsequent Data Service submission.");
			}
		}
	}
}
