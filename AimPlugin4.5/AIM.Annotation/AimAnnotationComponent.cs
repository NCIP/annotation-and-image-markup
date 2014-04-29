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
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Xml;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Validation;
using ClearCanvas.Dicom;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Common.ServerDirectory;
using ClearCanvas.ImageViewer.Configuration;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.RoiGraphics.Analyzers;
using ClearCanvas.ImageViewer.StudyManagement;

using AIM.Annotation.Configuration;
using AIM.Annotation.Graphics;
using AIM.Annotation.TemplateTree;
using AIM.Annotation.TemplateTree.Utilities;

using GeneralUtilities.Collections;
using Segmentation.Graphics;

namespace AIM.Annotation
{
	/// <summary>
	/// Extension point for views onto <see cref="AimAnnotationComponent"/>.
	/// </summary>
	[ExtensionPoint]
	public sealed class AimAnnotationComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	/// <summary>
	/// AIMAnnotationComponent class.
	/// </summary>
	[AssociateView(typeof(AimAnnotationComponentViewExtensionPoint))]
	public class AimAnnotationComponent : ImageViewerToolComponent
	{
		private bool _preview;
		private string _annotationStatus;
		private bool _embeddedForAts;

		private Template.TemplateContainer _loadedTemplateContainer;

		private AimManager.IAimActivityMonitor _aimActivityMonitor;

		public event EventHandler AnnotationCreating;

		// Default value for when an answer for a question is not required
		public static StandardCodeSequence NullCodeValue = new StandardCodeSequence("C47840", "Null", "NCIt");

		private static AimAnnotationComponent Instance { get; set; }

		public event EventHandler TemplateTreeSet;
		private AimTemplateTree _currentAimTemplateTree;

		// Fired when markup is added/removed from AIM Template Tree
		public event EventHandler AimTemplateTreeMarkupChanged;

		// TODO - Remove. Create Annotation should use TemplateTree directly
		public ReadOnlyCollection<IGraphic> SelectedGraphics
		{
			get
			{
				if (ImageViewer != null && AimTemplateTree != null)
				{
					var overlayGraphicProvider = ImageViewer.SelectedPresentationImage as IOverlayGraphicsProvider;
					if (overlayGraphicProvider != null && overlayGraphicProvider.OverlayGraphics.Count != 0)
					{
						return new ReadOnlyCollection<IGraphic>(
							overlayGraphicProvider.OverlayGraphics.Where(
								graphic =>
								graphic is SegFrameImageGraphic || // Unconditionally select Segmentation graphic
								AimTemplateTree.Markup.FirstOrDefault(
									markup => markup != null && markup.IncludeInAnnotation && markup.GraphicHashcode == graphic.GetHashCode()) != null).ToList());
					}
				}
				return new ReadOnlyCollection<IGraphic>(new List<IGraphic>());
			}
		}

		/// <summary>
		/// Constructor.
		/// </summary>
		private AimAnnotationComponent(IDesktopWindow desktopWindow)
			: base(desktopWindow)
		{
			if (AvailableAnnotationTypes.Count > 0)
				AnnotationTypeCode = AvailableAnnotationTypes[0];
		}

		public static AimAnnotationComponent GetActiveComponent()
		{
			if (Instance != null && Instance.IsStarted)
				return Instance;
			return null;
		}

		public static AimAnnotationComponent Create(IDesktopWindow desktopWindow, bool embeddedForAimTemplateService)
		{
			if (embeddedForAimTemplateService)
				return new AimAnnotationComponent(desktopWindow) { _embeddedForAts = true };
			if (Instance == null || !Instance.IsStarted)
				Instance = new AimAnnotationComponent(desktopWindow);
			return Instance;
		}

		void AimTemplateTreeNodeValueChanged(object sender, EventArgs e)
		{
			NotifyPropertyChanged("CreateAnnotationEnabled");
		}

		void AimTemplateTreeStatusChanged(object sender, StatusChangedEventArgs e)
		{
			if (e.MessageType == StatusChangedEventArgs.MessageTypes.Error)
			{
				ImageViewer.DesktopWindow.ShowMessageBox(e.Message, MessageBoxActions.Ok);
			}
			else
				AnnotationStatus = e.Message;
		}

		[ValidateNotNull(Message = "AnnotationTypeCannotBeNull")]
		public TemplateTree.StandardCodeSequence AnnotationTypeCode
		{
			get
			{
				if (AimTemplateTree != null && AimTemplateTree.StandardCodeSequence != null)
					return AimTemplateTree.StandardCodeSequence;
				return null;
			}
			set
			{
				if (_aimTemplateTrees.ContainsKey(value))
					AimTemplateTree = _aimTemplateTrees[value];
				else if (value == null)
					AimTemplateTree = null;
			}
		}

		public List<TemplateTree.StandardCodeSequence> AvailableAnnotationTypes
		{
			get { return AvailableAimTemplates; }
		}

		public bool AimTemplateVisible
		{
			get
			{
				return AnnotationTypeCode == null || AvailableAimTemplates.Find(code => code.Equals(AnnotationTypeCode)) != null;
			}
		}

		/// <summary>
		/// Gets or sets whether the AIM Template is being previewed (for use by ATS Web Browser and AIM Details List)
		/// </summary>
		public bool Preview
		{
			get { return _preview || _embeddedForAts; }
			set
			{
				if (_preview != value)
				{
					_preview = value;
					NotifyPropertyChanged("Preview");
					NotifyPropertyChanged("AnnotationModuleEnabled");
				}
			}
		}

		/// <summary>
		/// Gets or sets the text displayed on the template control's status bar
		/// </summary>
		public string AnnotationStatus
		{
			get { return _annotationStatus; }
			set
			{
				if (_annotationStatus != value)
				{
					_annotationStatus = value;
					NotifyPropertyChanged("AnnotationStatus");
				}
			}
		}

		[ValidateNotNull(Message = "AnnotationNameCannotBeNull")]
		public string AnnotationName
		{
			get
			{
				if (AimTemplateTree != null)
					return AimTemplateTree.AnnotationName;
				return String.Empty;
			}
			set
			{
				if (AimTemplateTree != null)
				{
					if (AimTemplateTree.AnnotationName != value)
					{
						AimTemplateTree.AnnotationName = value;

						NotifyPropertyChanged("AnnotationName");
						NotifyPropertyChanged("CreateAnnotationEnabled");
					}

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
					AimTemplateTree.UserInfo.Name = value;
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
					AimTemplateTree.UserInfo.LoginName = value;
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
					AimTemplateTree.UserInfo.RoleInTrial = value;
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
				AimTemplateTree.UserInfo.NumberWithinRoleOfClinicalTrial = value;
			}
		}
		#endregion User Info

		private string CreateDefaultAnnotationName()
		{
			string defaultName = "";
			DateTime dateTime = DateTime.Now;
			string dateTimeStr = dateTime.ToString("yyyy-MM-dd HH:mm:ss tt");
			if (ImageViewer != null)
			{
				var iImageSopProvider = ImageViewer.SelectedPresentationImage as IImageSopProvider;
				if (iImageSopProvider == null)
				{
					// Try harder to get an image: check for currently displayed images
					var imageBox = ImageViewer.PhysicalWorkspace.ImageBoxes.FirstOrDefault(imgBox => imgBox.TopLeftPresentationImage != null);
					if (imageBox != null)
						iImageSopProvider = imageBox.TopLeftPresentationImage as IImageSopProvider;
				}
				if (iImageSopProvider != null)
				{
					defaultName = iImageSopProvider.ImageSop.PatientId + "_" + AimSettings.Default.UserName + "_" + dateTimeStr;
				}
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
			bool validated = false;
			Utilities.ValidationResult result;

			// Validate against v1rv19 schema first
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
						string newTemplateFilename = System.IO.Path.GetTempFileName();
						var mapper = new AimTemplateConverter.ConverterToAimTemplateV1Rv23();
						mapper.Run(templateFilename, newTemplateFilename);
						templateFilename = newTemplateFilename;
					}
					catch (Exception ex)
					{
						Platform.Log(LogLevel.Error, ex, "Failed to convert template file: {0} from v1rv19 to v1rv23", templateFilename);
					}
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to validate v19 template file: {0}", templateFilename);
			}

			// Validate against v1rv23 template and convert to v2rv13 if it validates
			try
			{
				result = Utilities.ValidateXML.Initialize(
					"AIM.Annotation.Template.AIMTemplate_v1rv23.xsd",
					"gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate",
					templateFilename);
				if (result.Validated)
				{
					try
					{
						string newTemplateFilename = System.IO.Path.GetTempFileName();
						var mapper =
							new MappingAimTemplate_v1rv23_v2rv13.MappingAimTemplate_v1rv23_v2rv13MapToAIMTemplate_v2rv13();
						mapper.Run(templateFilename, newTemplateFilename);
						templateFilename = newTemplateFilename;
					}
					catch (Exception ex)
					{
						Platform.Log(LogLevel.Error, ex, "Failed to convert template file: {0} from v1rv23 to v2v13", templateFilename);
					}
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to validate v1rv23 template file: {0}", templateFilename);
			}

			// Validate against v2rv13 template
			try
			{
				result = Utilities.ValidateXML.Initialize(
					"AIM.Annotation.Template.AIMTemplate_v2rv13.xsd",
					"gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate",
					templateFilename);
				validated = result.Validated;
				validated = true;
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to validate v2rv13 template file: {0}", templateFilename);
			}

			if (!validated)
				ImageViewer.DesktopWindow.ShowMessageBox("Failed to validate template.", MessageBoxActions.Ok);
			return validated ? templateFilename : string.Empty;
		}

		private readonly ObservableDictionary<TemplateTree.StandardCodeSequence, AimTemplateTree> _aimTemplateTrees = new ObservableDictionary<TemplateTree.StandardCodeSequence, AimTemplateTree>();
		public ObservableDictionary<TemplateTree.StandardCodeSequence, AimTemplateTree> AimTemplateTrees { get { return _aimTemplateTrees; } }

		private void OpenAimTemplateTreeContainerFromFile(string filename)
		{
			try
			{
				var serializer = new AimTemplateTreeSerializer();
				_aimTemplateTrees.Clear();
				var aimTemplateTrees = serializer.DeserializeAimTemplateTreeFromTemplate(filename);
				if (aimTemplateTrees != null)
				{
					foreach (var key in aimTemplateTrees.Keys)
					{
						if (AimTemplateTree == null)
							AnnotationTypeCode = key;
						_aimTemplateTrees.Add(key, aimTemplateTrees[key]);
					}
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to deserialize template tree: {0}", filename);
				ImageViewer.DesktopWindow.ShowMessageBox("File did not contain any valid AIM Templates.", MessageBoxActions.Ok);
			}
		}

		public void LoadAimTemplateTreeFromAnnotation(AimManager.IAimAnnotationInstance annotation)
		{
		}

		public AimTemplateTree AimTemplateTree
		{
			get { return _currentAimTemplateTree; }

			private set
			{
				if (_currentAimTemplateTree == value)
					return;

				if (_currentAimTemplateTree != null)
				{
					_currentAimTemplateTree.AimTemplateTreeNodeValueChanged -= AimTemplateTreeNodeValueChanged;
					_currentAimTemplateTree.AimTemplateTreeStatusChanged -= AimTemplateTreeStatusChanged;
					_currentAimTemplateTree.Reset();
				}

				_currentAimTemplateTree = value;

				if (_currentAimTemplateTree == null)
				{
					EventsHelper.Fire(TemplateTreeSet, this, EventArgs.Empty);
					EventsHelper.Fire(AimTemplateTreeMarkupChanged, this, EventArgs.Empty);
				}
				else
				{
					_currentAimTemplateTree.UserInfo = new UserInfo
						{
							Name = UserName,
							LoginName = LoginName,
							RoleInTrial = RoleInTrial,
							NumberWithinRoleOfClinicalTrial = NumberWithinRoleInTrial
						};

					UpdateGraphicsFromTemplateMarkup();

					if (string.IsNullOrEmpty(_currentAimTemplateTree.AnnotationName))
						_currentAimTemplateTree.AnnotationName = CreateDefaultAnnotationName();

					EventsHelper.Fire(TemplateTreeSet, this, EventArgs.Empty);

					_currentAimTemplateTree.AimTemplateTreeNodeValueChanged += AimTemplateTreeNodeValueChanged;
					_currentAimTemplateTree.AimTemplateTreeStatusChanged += AimTemplateTreeStatusChanged;
				}
			}
		}

		public Template.TemplateContainer LoadedTemplateDoc
		{
			get
			{
				if (_loadedTemplateContainer == null)
				{
					// Load on first use
					string templateDocPathName = AimSettings.Default.SelectedTemplatePathName ?? "";

					SelectedAimTemplateDocument = templateDocPathName;
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

		public List<TemplateTree.StandardCodeSequence> AvailableAimTemplates
		{
			get
			{
				var retVal = new List<TemplateTree.StandardCodeSequence>();

				if ((_aimTemplateTrees != null && _aimTemplateTrees.Count > 0) || LoadedTemplateDoc != null)
					if (_aimTemplateTrees != null)
						retVal.AddRange(_aimTemplateTrees.Keys);
				return retVal;
			}
		}

		private string _loadedTemplateDocument = String.Empty;

		public string SelectedAimTemplateDocument
		{
			get { return AimSettings.Default.SelectedTemplatePathName ?? ""; }
			set
			{
				if (File.Exists(value) && value != _loadedTemplateDocument)
				{
					try
					{
						string template = ValidateAndConvertAimTemplate(value);

						if (!String.IsNullOrEmpty(template))
						{
							OpenAimTemplateTreeContainerFromFile(template);
							if (_aimTemplateTrees.Count > 0)
							{
								if (!Preview)
								{
									AimSettings.Default.SelectedTemplatePathName = value;
									AimSettings.Default.Save();
								}

								_loadedTemplateContainer = null;
								_loadedTemplateDocument = value;

								AnnotationTypeCode = AvailableAnnotationTypes[0]; // Will select template tree

								NotifyPropertyChanged("AvailableAnnotationTypes");
							}
						}
						else
							return;
					}

					catch (Exception ex)
					{
						Platform.Log(LogLevel.Error, ex, "Failed to open template file: {0}", value);
					}
				}
			}
		}

		// Returns directory for the Open Template Document dialog
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

		// Returns True if the whole annotation module should be enabled, False - if not
		public bool AnnotationModuleEnabled
		{
			get { return ImageViewer != null && ImageViewer.SelectedPresentationImage != null; }
		}

		// Return True if Create Annotation button should be enabled, False - if not
		public bool CreateAnnotationEnabled
		{
			get
			{
				return
					IsStarted
					&& !Preview
					&& !HasValidationErrors
					&& AnnotationModuleEnabled && AnnotationTypeCode != null
					&& !string.IsNullOrEmpty(AnnotationName)
					&& (!AimTemplateVisible || (AimTemplateVisible && IsAimTemplateTreeValid))
					&& HasValidUserData
					&& HasRequiredMarkup;
			}
		}

		public bool ResetButtonEnabled
		{
			get
			{
				return
					IsStarted
					&& ImageViewer != null
					&& AimTemplateTree != null;
			}
		}

		public bool UserInfoButtonEnabled
		{
			get
			{
				return
					IsStarted
					&& !Preview
					&& ImageViewer != null
					&& AimTemplateTree != null;
			}
		}

		protected bool HasValidUserData
		{
			get { return !AimSettings.Default.RequireUserInfo || !string.IsNullOrEmpty(UserName) && !string.IsNullOrEmpty(LoginName); }
		}

		protected bool HasRequiredMarkup
		{
			get { return !AimSettings.Default.RequireMarkupInAnnotation || (AimTemplateTree != null && AimTemplateTree.Markup != null && AimTemplateTree.Markup.Count(item => item.IncludeInAnnotation) > 0); }
		}

		// Flag that sets validity for AIM Template Tree data
		public bool IsAimTemplateTreeValid
		{
			get
			{
				return AimTemplateTree.ValidForImageAnnotationCreation();
			}
		}

		protected override void OnActiveImageViewerChanged(ActiveImageViewerChangedEventArgs e)
		{
			// Add update event handlers
			if (e.ActivatedImageViewer != null)
			{
				UpdateImageViewerEventSubscriptions(e.ActivatedImageViewer, true);

				AnnotationName = CreateDefaultAnnotationName();
			}
			else
			{
				AnnotationName = String.Empty;
			}

			NotifyPropertyChanged("AnnotationModuleEnabled");
			NotifyPropertyChanged("CreateAnnotationEnabled");
			NotifyPropertyChanged("CalculationInfo");
		}

		protected override void OnActiveImageViewerChanging(ActiveImageViewerChangedEventArgs e)
		{
			// Remove update event handlers
			if (e.DeactivatedImageViewer != null)
			{
				UpdateImageViewerEventSubscriptions(e.DeactivatedImageViewer, false);
			}
		}

		/// <summary>
		/// Changes event subscription on the given <see cref="IImageViewer"/>
		/// </summary>
		/// <param name="imageViewer">ImageViewer to add or remove events from</param>
		/// <param name="subscribe"><code>true</code> - add event subscription, <code>false</code> - remove event subscription</param>
		private void UpdateImageViewerEventSubscriptions(IImageViewer imageViewer, bool subscribe)
		{
			if (imageViewer != null)
			{
				if (subscribe)
				{
					imageViewer.EventBroker.TileSelected += OnTileSelected;
					imageViewer.EventBroker.MouseCaptureChanged += OnMouseCaptureChanged;
					imageViewer.EventBroker.GraphicSelectionChanged += OnGraphicSelectionChanged;
					imageViewer.EventBroker.PresentationImageSelected += OnPresentationImageSelected;
				}
				else
				{
					imageViewer.EventBroker.TileSelected -= OnTileSelected;
					imageViewer.EventBroker.MouseCaptureChanged -= OnMouseCaptureChanged;
					imageViewer.EventBroker.GraphicSelectionChanged -= OnGraphicSelectionChanged;
					imageViewer.EventBroker.PresentationImageSelected -= OnPresentationImageSelected;
				}
			}
		}

		protected void OnPresentationImageSelected(object sender, PresentationImageSelectedEventArgs e)
		{
			UpdateTemplateTreeMarkup(false);

			// With open template, first opened study may need to set AnnotationName
			if (string.IsNullOrEmpty(AnnotationName))
				AnnotationName = CreateDefaultAnnotationName();

			//NotifyPropertyChanged("AnnotationModuleEnabled");
			NotifyPropertyChanged("CreateAnnotationEnabled");
			NotifyPropertyChanged("CalculationInfo");
		}

		private void OnTileSelected(object sender, TileSelectedEventArgs e)
		{
			// NOTE: When PresentationImage is present, markup will be updated in the OnPresentationImageSelected event
			if (e.SelectedTile.PresentationImage == null)
				UpdateTemplateTreeMarkup(false);
			NotifyPropertyChanged("AnnotationModuleEnabled");
			NotifyPropertyChanged("CreateAnnotationEnabled");
			NotifyPropertyChanged("CalculationInfo");
		}

		private void OnMouseCaptureChanged(object sender, ClearCanvas.ImageViewer.InputManagement.MouseCaptureChangedEventArgs e)
		{
			UpdateTemplateTreeMarkup(false);
			NotifyPropertyChanged("CreateAnnotationEnabled");
			NotifyPropertyChanged("CalculationInfo");
		}

		private void OnGraphicSelectionChanged(object sender, GraphicSelectionChangedEventArgs e)
		{
			UpdateTemplateTreeMarkup(false);
			NotifyPropertyChanged("AnnotationModuleEnabled");
			NotifyPropertyChanged("CreateAnnotationEnabled");
			//NotifyPropertyChanged("CalculationInfo");
		}

		#region Start/Stop methods
		/// <summary>
		/// Called by the host to initialize the application component.
		/// </summary>
		public override void Start()
		{
			base.Start();

			_aimActivityMonitor = AimManager.AimActivityMonitor.Create();

			AimSettings.Default.PropertyChanged += OnAimSettingsChanged;

			try
			{
				// Create extension points that use this component
				AimAnnotationExtensionPoint xp = new AimAnnotationExtensionPoint();
				foreach (object obj in xp.CreateExtensions())
				{
					IAimAnnotationExtension extension = (IAimAnnotationExtension)obj;
					extension.Component = this;
				}
			}
			catch (NotSupportedException)
			{
			}

			UpdateTemplateTreeMarkup(false);
		}

		/// <summary>
		/// Called by the host when the application component is being terminated.
		/// </summary>
		public override void Stop()
		{
			AimSettings.Default.PropertyChanged -= OnAimSettingsChanged;

			_aimActivityMonitor.Dispose();
			_aimActivityMonitor = null;

			UpdateImageViewerEventSubscriptions(ImageViewer, false);

			Instance = null;

			base.Stop();
		}
		#endregion

		private void OnAimSettingsChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
		{
			NotifyPropertyChanged("CreateAnnotationEnabled");
		}

		private void UpdateTemplateTreeMarkup(bool alwaysFireMarkupChangeEvent)
		{
			if (AimTemplateTree != null && !Preview)
			{
				bool isChanged = false; // this helps minimize number of change events when no real change occurs
				if (ImageViewer != null)
				{
					var overlayGraphicProvider = ImageViewer.SelectedPresentationImage as IOverlayGraphicsProvider;
					if (overlayGraphicProvider != null && overlayGraphicProvider.OverlayGraphics.Count != 0)
					{
						// Remove all markup that does not correspond to the current presentation image markup
						var originalMarkupCount = AimTemplateTree.Markup.Count;
						CollectionUtils.Remove(AimTemplateTree.Markup, item => overlayGraphicProvider.OverlayGraphics.Count(graphics => item.GraphicHashcode != 0 && graphics.GetHashCode() == item.GraphicHashcode) == 0);
						isChanged = originalMarkupCount != AimTemplateTree.Markup.Count;

						// Add/update markup
						foreach (var graphic in overlayGraphicProvider.OverlayGraphics)
						{
							IMarkup existingMarkup = AimTemplateTree.Markup.FirstOrDefault(markup => graphic != null && markup.GraphicHashcode == graphic.GetHashCode());
							if (existingMarkup == null)
							{
								// Add new markup if graphic:
								// 1. is not in the markup collection already and
								// 2. is visible and
								// 3. is NOT IAimGraphic, or if it IS IAimGraphic and belongs to the Precedent Annotation
								if (graphic.Visible && 
									(!(graphic is IAimGraphic) ||
								    ((IAimGraphic) graphic).AnnotationUid.Equals(AimTemplateTree.PrecedentReferencedAnnotationUid, StringComparison.InvariantCultureIgnoreCase)))
								{
									var newMarkup = AimTemplateTreeGraphicsHelpers.GraphicToIMarkup(graphic);
									if (newMarkup != null)
									{
										newMarkup.IncludeInAnnotation = true;
										AimTemplateTree.Markup.Add(newMarkup);
										isChanged = true;
									}
								}
							}
							else
							{
								// Replace existing
								// Reason to replace existing markup is that its content can change
								var newMarkup = AimTemplateTreeGraphicsHelpers.GraphicToIMarkup(graphic);
								if (newMarkup != null)
								{
									newMarkup.IncludeInAnnotation = existingMarkup.IncludeInAnnotation;
									AimTemplateTree.Markup[AimTemplateTree.Markup.IndexOf(existingMarkup)] = newMarkup;
									isChanged = true;
								}
								else
								{
									AimTemplateTree.Markup.Remove(existingMarkup);
									Platform.Log(LogLevel.Debug, "Failed to create markup from graphic [{0}]. Could be a hidden graphic or an error.", graphic.GetType().Name);
									//Platform.Log(LogLevel.Error, "Failed to create replacement markup. Template Tree will have invalid markup data");
								}
							}
						}
					}
					else
					{
						if (AimTemplateTree.Markup.Count > 0)
						{
							AimTemplateTree.Markup.Clear();
							isChanged = true;
						}
					}
				}
				else
				{
					if (AimTemplateTree.Markup.Count > 0)
					{
						AimTemplateTree.Markup.Clear();
						isChanged = true;
					}
				}

				if (isChanged || alwaysFireMarkupChangeEvent)
				{
					Platform.Log(LogLevel.Debug, "TemplateTree Markup collection updated [{0}]", AimTemplateTree.Markup.Count);
					EventsHelper.Fire(AimTemplateTreeMarkupChanged, this, EventArgs.Empty);
				}
			}
		}

		private void UpdateGraphicsFromTemplateMarkup()
		{
			if (ImageViewer != null && AimTemplateTree != null)
			{
				var firstMarkup = AimTemplateTree.Markup.FirstOrDefault();
				if (firstMarkup != null)
				{
					// Hold a local reference to the current markup
					var storedMarkup = new List<IMarkup>(AimTemplateTree.Markup);

					// Ensure that required image is visible
					var presentationImage = AimGraphicHelpers.SelectImage(ImageViewer, firstMarkup.PresentationImageUid, firstMarkup.FrameNumber);

					if (presentationImage == null)
						return; // image stored in the Template Tree is not found

					// Get existing markup on the image
					var graphicsProvider = presentationImage as IOverlayGraphicsProvider;
					var existingMarkup = GetAllNonAimGraphics(graphicsProvider, true)
						.ConvertAll(AimTemplateTreeGraphicsHelpers.GraphicToIMarkup)
						.Where(markup => markup != null).ToList();

					// Filter out existing identical markup
					var newMarkup = new List<IMarkup>();
					foreach (var markup in storedMarkup)
					{
						var existingItem = existingMarkup.FirstOrDefault(item => markup.Equals(item));
						if (existingItem == null)
							newMarkup.Add(markup);
						else
						{
							// Most current values come from the existing graphic
							markup.GraphicHashcode = existingItem.GraphicHashcode;
							markup.CalloutLocation = existingItem.CalloutLocation;
							markup.CaptionText = existingItem.CaptionText;
						}
					}

					// Insert dummy markup so that text callout generation works.
					if (newMarkup.Count > 0)
					{
						var graphics = AimTemplateTreeGraphicsHelpers.PopulateImageViewerWithSavedMarkup(newMarkup, ImageViewer);
					}

					// Select the first available graphic
					if (graphicsProvider != null)
					{
						foreach (var overlayGraphic in graphicsProvider.OverlayGraphics)
						{
							var existingItem = existingMarkup.FirstOrDefault(item => item.GraphicHashcode == overlayGraphic.GetHashCode());
							if (existingItem != null)
							{
								var isSelected = false;
								var decoratorGraphic = overlayGraphic as IDecoratorGraphic;
								if (decoratorGraphic != null)
								{
									presentationImage.SelectedGraphic = decoratorGraphic.DecoratedGraphic as ISelectableGraphic;
									presentationImage.FocussedGraphic = decoratorGraphic.DecoratedGraphic as IFocussableGraphic;
									if (presentationImage.SelectedGraphic != null)
									{
										presentationImage.SelectedGraphic.Selected = true;
										isSelected = true;
									}
								}
								else if (overlayGraphic is ISelectableGraphic)
								{
									presentationImage.SelectedGraphic = (ISelectableGraphic)overlayGraphic;
									presentationImage.FocussedGraphic = overlayGraphic as IFocussableGraphic;
									presentationImage.SelectedGraphic.Selected = true;
								}
								if (isSelected)
									break;
							}
						}
					}
				}
			}
		}

		public void SelectMarkup(IMarkup markup, bool select)
		{
			markup.IncludeInAnnotation = select;

			NotifyPropertyChanged("CreateAnnotationEnabled");
		}

		private List<IGraphic> GetAllNonAimGraphics(IOverlayGraphicsProvider graphicsProvider, bool includePrecedentAimGraphic)
		{
			if (graphicsProvider == null)
				return new List<IGraphic>();

			return graphicsProvider.OverlayGraphics.Where(graphic =>
														  !(graphic is IAimGraphic) ||
														  (includePrecedentAimGraphic &&
														   ((IAimGraphic)graphic).AnnotationUid.Equals(AimTemplateTree.PrecedentReferencedAnnotationUid,
																										StringComparison.InvariantCultureIgnoreCase))).ToList();
		}

		public string[] CalculationInfo
		{
			get
			{
				if (ImageViewer != null)
				{
					IOverlayGraphicsProvider overlayGraphicProvider = ImageViewer.SelectedPresentationImage as IOverlayGraphicsProvider;
					if (overlayGraphicProvider != null)
					{
						StringBuilder sb = new StringBuilder();
						string lineFeed = Environment.NewLine + "    ";

						int roiCnt = 0;
						foreach (IGraphic graphic in overlayGraphicProvider.OverlayGraphics)
						{
							RoiGraphic currentRoiGraphic = graphic as RoiGraphic;
							if (currentRoiGraphic != null)
							{
								if (sb.Length > 0)
									sb.Append(Environment.NewLine);
								if (string.IsNullOrEmpty(currentRoiGraphic.Name))
									sb.AppendFormat("ROI #{0}:", ++roiCnt);
								else
									sb.AppendFormat("ROI #{0} ({1}):", ++roiCnt, currentRoiGraphic.Name);
								Roi roi = currentRoiGraphic.Roi;
								foreach (IRoiAnalyzer analyzer in currentRoiGraphic.Callout.RoiAnalyzers)
								{
									if (analyzer.SupportsRoi(roi))
									{
										var analizerResult = analyzer.Analyze(roi, RoiAnalysisMode.Normal);
										sb.Append(analizerResult.Name);
										sb.Append(analizerResult.SerializedAsString());
									}
								}
							}
						}

						string[] strRetVal = sb.ToString().Split(new[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries);
						sb.Length = 0;
						return strRetVal;
					}
				}

				return new string[0];
			}

			set { }
		}

		// Creates AIM Annotation(s) based on user template/image selection and our internal preferences
		// Returns a list of the created annotations and a list of IGraphic elements used to create the annotations.
		// The list of graphic elements is used later to replace these elements with AimGraphics
		private List<AimManager.IAimObjectReference> CreateAnnotationsFromUserInputTree(out List<IGraphic> annotationsGraphic)
		{
			Debug.Assert(ImageViewer != null);

			int nextSeriesNumber =
				((IImageSopProvider)ImageViewer.SelectedPresentationImage).ImageSop.ParentSeries.ParentStudy.Series.Max(series => series.SeriesNumber) + 1;

			var aimContext = new AimAnnotationCreationContext(AimAnnotationCreationContext.AnnotationKind.ImageAnnotation, AnnotationTypeCode,
															  AimTemplateTree, nextSeriesNumber);
			aimContext.IncludeCalculations = true;
			// !!! Create annotation for the current image/frame only !!!
			aimContext.SopInstanceUidAndFrameNumbers.Add(((IImageSopProvider)ImageViewer.SelectedPresentationImage).ImageSop.SopInstanceUid,
														 new HashSet<int>
				                                             {
					                                             ((IImageSopProvider) ImageViewer.SelectedPresentationImage).Frame.FrameNumber
				                                             });
			aimContext.AnnotationComment = StringUtilities.Combine(new[]
				{
					string.IsNullOrEmpty(AimTemplateTree.SelectedTemplateContainerUid)
						? null
						: "AimTemplateContainerUid=" + AimTemplateTree.SelectedTemplateContainerUid,
					string.IsNullOrEmpty(AimTemplateTree.SelectedTemplateUid) ? null : "AimTemplateUid=" + AimTemplateTree.SelectedTemplateUid
				}, ",");

			return AimManager.AimManager.Instance.CreateAimAnnotations(ImageViewer.SelectedPresentationImage.ParentDisplaySet.PresentationImages,
																	   aimContext, SelectedGraphics, out annotationsGraphic);
		}

		public void CreateAnnotationFromTemplateTree()
		{
			if (!CreateAnnotationEnabled)
				return;

			if (base.HasValidationErrors)
			{
				Platform.Log(LogLevel.Info, "Cannot create annotation. Validation error(s): " + Validation.GetErrorsString(this));
				ShowValidation(true);
				return;
			}

			// We should bail out here even we only want to store it locally and/or to the grid.
			// There will be no way for us to display the new annotation back to the user after we remove the original markup.
			if (!_aimActivityMonitor.IsConnected)
			{
				DesktopWindow.ShowMessageBox("Failed to save annotation. Not connected to the local data store. Is workstation service running?", MessageBoxActions.Ok);
				return;
			}

			// Get new annotations
			List<IGraphic> annotationsGraphic = null;
			List<AimManager.IAimObjectReference> annotations = null;

			try
			{
				annotations = CreateAnnotationsFromUserInputTree(out annotationsGraphic);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Error creating annotation from AIM Template Tree.", AimTemplateTree);
				DesktopWindow.ShowMessageBox("Error creating annotation from AIM Template Tree.  Template may be invalid.", MessageBoxActions.Ok);
			}

			if (annotations == null || annotations.Count == 0)
			{
				Platform.Log(LogLevel.Warn, "CreateAnnotation resulted in no annotations being created");
				return;
			}

			EventsHelper.Fire(AnnotationCreating, this, EventArgs.Empty);

			AnnotationStatus = "Annotation Created: " + AnnotationName;

			bool isAnyOperationPerformed = false;

			// Save AIM XML Annotations locally
			if (AimSettings.Default.StoreXmlAnnotationsLocally)
			{
				string destinationFolder = AimSettings.Default.ActualAnnotationStoreFolder;
				try
				{
					if (!System.IO.Directory.Exists(destinationFolder))
						System.IO.Directory.CreateDirectory(destinationFolder);

					string[] annFiles = AimManager.AimManager.Instance.WriteXmlAnnotationsToFolder(annotations, destinationFolder);
					//string[] annFiles = AimHelpers.WriteXmlAnnotationsToFolder(annotations, destinationFolder);
					if (annotations.Count != annFiles.Length)
						Platform.Log(LogLevel.Error, "Only {0} annotations(s) out of {1} written to \"{2}\"", annFiles.Length, annotations.Count, destinationFolder);

					isAnyOperationPerformed = annFiles.Length > 0 || isAnyOperationPerformed;
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to store annotations to local folder \"{0}\"", destinationFolder);
				}
			}

			// Send annotations to the Grid
			if (AimSettings.Default.SendNewXmlAnnotationsToGrid)
			{
				if (SendAnnotationsToGrid(annotations))
					; // isAnyOperationPerformed = true; // This does not really tell us if data service succeeded or failed in sending annotations
				else
					Platform.Log(LogLevel.Error, "Failed to send annotations to the data service");
			}

			if (_aimActivityMonitor.IsConnected)
			{
				isAnyOperationPerformed = SendAnnotationsToLocalStorageAndPacs(annotations) || isAnyOperationPerformed;
				// Remove all IGraphic used to create annotations. We'll add them back as AimGraphic when local data store import completes
				if (isAnyOperationPerformed && annotationsGraphic != null)
					RemoveNonAimGraphicsFromImages(annotationsGraphic);
			}
			else
				DesktopWindow.ShowMessageBox("Failed to save annotation. Not connected to the local data store. Is workstation service running?", MessageBoxActions.Ok);

			if (AimSettings.Default.ResetTemplateAfterAnnotationCreation)
				AimTemplateTree.Reset();
			AnnotationName = CreateDefaultAnnotationName();

			UpdateTemplateTreeMarkup(true);
		}

		// Helper. Removes given IGraphic from their images
		private void RemoveNonAimGraphicsFromImages(List<IGraphic> annotationsGraphic)
		{
			bool hasChanges = false;
			if (annotationsGraphic != null)
			{
				foreach (IGraphic graphic in annotationsGraphic)
				{
					// Don't remove existing AIM Graphic
					if (graphic is AimGraphic)
						continue;

					// For now, we should be creating annotations only for the current image
					// Other code that reads annotations back depends on 
					// Otherwise we either need to keep track of images from which we delete graphics (could be different from the images for the annotations?)
					// or to pass in a list of images.
					Debug.Assert(graphic.ParentPresentationImage == null || graphic.ParentPresentationImage == ImageViewer.SelectedPresentationImage);

					var currentOverlayGraphics = graphic.ParentPresentationImage as IOverlayGraphicsProvider;
					if (currentOverlayGraphics != null && currentOverlayGraphics.OverlayGraphics != null)
						hasChanges |= currentOverlayGraphics.OverlayGraphics.Remove(graphic);
				}
			}

			if (hasChanges)
				ImageViewer.SelectedPresentationImage.Draw();
		}

		private bool SendAnnotationsToLocalStorageAndPacs(List<AimManager.IAimObjectReference> annotations)
		{
			var tempAnnFileNames = new List<string>();
			// 0. Save each annotation to a temp DICOM file
			try
			{
				AimManager.AimManager.Instance.WriteDicomAnnotationsToTempFiles(annotations, tempAnnFileNames.Add);
			}
			catch (AimManager.AimManagerException ae)
			{
				Platform.Log(LogLevel.Error, ae, "Failed to save annotations");
				DesktopWindow.ShowMessageBox("Failed to save annotations", "Annotation Import Error", MessageBoxActions.Ok);
			}

			if (tempAnnFileNames.Count < 1)
				return false; // Save failed

			var imageSopProvider = ImageViewer.SelectedPresentationImage as IImageSopProvider;
			var sopDataSource = imageSopProvider == null ? null : imageSopProvider.ImageSop.DataSource;
			if (sopDataSource == null)
			{
				Platform.Log(LogLevel.Error, "Failed to send AIM Annotation to data store. [Could not find image SOP DataSource]");
				DesktopWindow.ShowMessageBox("Failed to store annotations", "Annotation Import Error", MessageBoxActions.Ok);
				return false;
			}

			// 1. Publish new annotations to local data store and original study server if known

			// NOTE: This is what KeyImagePublisher does as well
			var dicomPublishingHelper = new DicomPublishingHelper();
			//dicomPublishingHelper.OriginServer = ServerDirectory.GetLocalServer();
			dicomPublishingHelper.OriginServer = ServerDirectory.GetRemoteServersByAETitle(sopDataSource[DicomTags.SourceApplicationEntityTitle].ToString()).FirstOrDefault();
			dicomPublishingHelper.SourceServer = sopDataSource.Server ?? ServerDirectory.GetLocalServer(); // GetLocalServer() allows to import annotations created for locally opened files

			// TODO: copy DicomPublishingHelper() into AimDicomFilePublisher and change the copy to allow for publishing SOPs to local data store even when the parent Study does not exist locally

			foreach (var tempAnnFileName in tempAnnFileNames)
			{
				var annFile = new DicomFile(tempAnnFileName);
				annFile.Load(DicomReadOptions.Default | DicomReadOptions.DoNotStorePixelDataInDataSet);
				string annSopInstanceUid = annFile.DataSet[DicomTags.SopInstanceUid].GetString(0, string.Empty);
				dicomPublishingHelper.Files.Add(annFile);
			}

			try
			{
				return dicomPublishingHelper.Publish();
			}
			catch(Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to store annotations");
				DesktopWindow.ShowMessageBox("Failed to store your annotation(s).", "Annotation Import Error", MessageBoxActions.Ok);
			}

			// 2. Displaying back newly imported annotations is done in the AimAnnotationMonitorTool

			return false;
		}

		public void ResetAimTemplateTree()
		{
			if (AimTemplateTree != null)
			{
				AimTemplateTree.Reset();
				Preview = false;
				AnnotationName = CreateDefaultAnnotationName();
				UpdateTemplateTreeMarkup(true);
			}
		}

		#region caGrid Operations
		private bool SendAnnotationsToGrid(List<AimManager.IAimObjectReference> annotations)
		{
			if (annotations == null || annotations.Count == 0)
				return true;

			Dictionary<string, string> xmlAnnotations = AimManager.AimManager.Instance.WriteXmlAnnotationsToString(annotations);

			// Send Annotations to AIM Service
			if (xmlAnnotations.Count > 0)
			{
				BackgroundTask task = null;
				try
				{
					var sendAnnotationsUserState = new SendAnnotationsUserState
													   {
														   XmlAnnotations = xmlAnnotations,
														   SynchronizationContext = SynchronizationContext.Current
													   };

					task = new BackgroundTask(BackgroundSendAnnotationsToAimService, false, sendAnnotationsUserState);
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

		private class SendAnnotationsUserState
		{
			public Dictionary<string, string> XmlAnnotations { get; set; }
			public SynchronizationContext SynchronizationContext { get; set; }
		}

		private void BackgroundSendAnnotationsToAimService(IBackgroundTaskContext context)
		{
			bool sent = false;
			var sendAnnotationsUserState = context.UserState as SendAnnotationsUserState;
			Dictionary<string, string> xmlAnnotations = sendAnnotationsUserState.XmlAnnotations;
			if (xmlAnnotations != null && xmlAnnotations.Count > 0)
			{
				AimDataServiceExtensionPoint xp = new AimDataServiceExtensionPoint();
				foreach (IAimDataService aimDataService in xp.CreateExtensions())
				{
					if (aimDataService.AimVersion == AimManager.AimManager.DefaultAimVersion)
					{
						if (!sent)
						{
							try
							{
								aimDataService.SynchronizationContext = sendAnnotationsUserState.SynchronizationContext;
								var progress = new BackgroundTaskProgress(20, string.Format("Sending {0} annotation(s) to AIM data service.", xmlAnnotations.Count));
								context.ReportProgress(progress);

								aimDataService.SendAnnotations(new List<string>(xmlAnnotations.Values));
							}
							catch (Exception ex)
							{
								// Assume that storing all annotations failed
								SaveAnnotationsToQueue(xmlAnnotations, aimDataService.ServiceUrl);

								// Error logged above where it is reported to the user
								context.Error(ex);
								return;
							}
							sent = true;
						}
						else
						{
							Platform.Log(LogLevel.Info, "There is more than one IAimDataService extensions for the current AIM version. Ignoring extras [{0}]",
										 aimDataService.GetType().Name);
							Debug.Assert(false, "There is more than one IAimDataService extensions for the current AIM version");
						}
					}
				}
			}
			if (sent)
				context.Complete();
			else
				context.Error(new Exception("Failed to find AIM Data Service implementation for the current version of AIM"));
		}

		private void SaveAnnotationsToQueue(Dictionary<string, string> xmlAnnotations, string serverUrl)
		{
			// 1. Figure out queue name based on the serverUrl
			int hashCode = 0;
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
						AimSettings.Default.SendQueuesNames = new XmlSerializableStringDictionary();
					hashCode = uri.AbsoluteUri.GetHashCode();
					folderName = hashCode.ToString("X8");
					AimSettings.Default.SendQueuesNames[uri.AbsoluteUri] = folderName;
					AimSettings.Default.Save();
				}
			}
			else
			{
				//folderName = System.IO.Path.GetRandomFileName();
				folderName = "invalid_server";
			}

			// Default value: My Documents/My Annotations/queue/<folder name>
			string folderPath = System.IO.Path.Combine(AimSettings.Default.AnnotationQueuesFolder, folderName);

			// 2. Write all annotations to that folder
			try
			{
				if (!System.IO.Directory.Exists(folderPath))
					System.IO.Directory.CreateDirectory(folderPath);

				foreach (KeyValuePair<string, string> xmlAnnotation in xmlAnnotations)
				{
					string fileName = string.IsNullOrEmpty(xmlAnnotation.Key)
										  ? System.IO.Path.GetFileNameWithoutExtension(System.IO.Path.GetRandomFileName())
										  : xmlAnnotation.Key;
					XmlDocument xmlDoc = new XmlDocument();
					xmlDoc.LoadXml(xmlAnnotation.Value);
					xmlDoc.Save(string.Format("{0}.xml", System.IO.Path.Combine(folderPath, fileName)));

					Platform.Log(LogLevel.Info, "Added annotation to the queue: {0}", fileName);
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to queue annotation(s) for subsequent Data Service submission.");
			}
		}
		#endregion
	}
}
