//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Configuration;
using ClearCanvas.Desktop.Validation;

namespace AIM.Annotation.Configuration
{
	[ExtensionPoint]
	public sealed class AimConfigurationComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	/// <summary>
	/// AimConfigurationComponent class.
	/// </summary>
	[AssociateView(typeof(AimConfigurationComponentViewExtensionPoint))]
	public class AimConfigurationComponent : ConfigurationApplicationComponent
	{
		public static readonly string Path = "AIM";

		private AimSettings _settings;
		private bool _sendNewXmlAnnotationsToGrid;
		private bool _storeXmlAnnotationsLocally;
		private bool _storeXmlInMyDocuments;
		private string _localAnnotationStoreFolder;
		private bool _requireUserInfo;
		private bool _requireMarkupInAnnotation;
		private string _localTemplateStoreFolder;

		public bool SendNewXmlAnnotationsToGrid
		{
			get { return _sendNewXmlAnnotationsToGrid; }
			set
			{
				if (_sendNewXmlAnnotationsToGrid != value)
				{
					_sendNewXmlAnnotationsToGrid = value;
					Modified = true;
					NotifyPropertyChanged("SendNewXmlAnnotationsToGrid");
				}
			}
		}

		public bool StoreXmlAnnotationsLocally
		{
			get { return _storeXmlAnnotationsLocally; }
			set
			{
				if (_storeXmlAnnotationsLocally != value)
				{
					_storeXmlAnnotationsLocally = value;
					Modified = true;
					NotifyPropertyChanged("StoreXmlAnnotationsLocally");
				}
			}
		}

		public bool StoreXmlInMyDocuments
		{
			get { return _storeXmlInMyDocuments; }
			set
			{
				if (_storeXmlInMyDocuments != value)
				{
					_storeXmlInMyDocuments = value;
					Modified = true;
					NotifyPropertyChanged("StoreXmlInMyDocuments");
					NotifyPropertyChanged("StoreXmlInSpecifiedFolder");
				}
			}
		}

		public bool StoreXmlInSpecifiedFolder
		{
			get { return !StoreXmlInMyDocuments; }
			set { StoreXmlInMyDocuments = !value; }
		}

		public string LocalAnnotationStoreFolder
		{
			get { return _localAnnotationStoreFolder; }
			set
			{
				if (_localAnnotationStoreFolder != value)
				{
					_localAnnotationStoreFolder = value;
					Modified = true;
					NotifyPropertyChanged("LocalAnnotationStoreFolder");
				}
			}
		}

		public bool LocalAnnotationStoreFolderEnabled
		{
			get { return StoreXmlAnnotationsLocally && StoreXmlInSpecifiedFolder; }
		}

		[ValidationMethodFor("LocalAnnotationStoreFolder")]
		protected ValidationResult LocalAnnotationFolderValidation()
		{
			if (!StoreXmlAnnotationsLocally || StoreXmlInMyDocuments)
				return new ValidationResult(true, "");

			return new ValidationResult(System.IO.Directory.Exists(LocalAnnotationStoreFolder), "Local AIM storage folder does not exist");
		}

		public bool RequireUserInfo
		{
			get { return _requireUserInfo; }
			set
			{
				if (_requireUserInfo != value)
				{
					_requireUserInfo = value;
					Modified = true;
					NotifyPropertyChanged("RequireUserInfo");
				}
			}
		}

		public bool RequireMarkupInAnnotation
		{
			get { return _requireMarkupInAnnotation; }
			set
			{
				if (_requireMarkupInAnnotation != value)
				{
					_requireMarkupInAnnotation = value;
					Modified = true;
					NotifyPropertyChanged("RequireMarkupInAnnotation");
				}
			}
		}


		public string LocalTemplatesStoreFolder
		{
			get { return _localTemplateStoreFolder; }
			set
			{
				if (_localTemplateStoreFolder != value)
				{
					_localTemplateStoreFolder = value;
					Modified = true;
					NotifyPropertyChanged("LocalTemplatesStoreFolder");
				}
			}
		}

		[ValidationMethodFor("LocalTemplatesStoreFolder")]
		protected ValidationResult LocalTemplatesFolderValidation()
		{
			if (string.IsNullOrEmpty(LocalTemplatesStoreFolder))
				return new ValidationResult(true, "");

			return new ValidationResult(System.IO.Directory.Exists(LocalTemplatesStoreFolder), "Local AIM Templates storage folder does not exist");
		}

		public override void Start()
		{
			base.Start();

			_settings = AimSettings.Default;
			_sendNewXmlAnnotationsToGrid = _settings.SendNewXmlAnnotationsToGrid;
			_storeXmlAnnotationsLocally = _settings.StoreXmlAnnotationsLocally;
			_storeXmlInMyDocuments = _settings.StoreXmlInMyDocuments;
			_localAnnotationStoreFolder = _settings.LocalAnnotationsFolder;
			_requireUserInfo = _settings.RequireUserInfo;
			_requireMarkupInAnnotation = _settings.RequireMarkupInAnnotation;
			_localTemplateStoreFolder = _settings.LocalTemplatesFolder;
		}

		/// <summary>
		/// Called by the host when the application component is being terminated.
		/// </summary>
		public override void Stop()
		{
			_settings = null;

			base.Stop();
		}

		public override void Save()
		{
			_settings.SendNewXmlAnnotationsToGrid = _sendNewXmlAnnotationsToGrid;
			_settings.StoreXmlAnnotationsLocally = _storeXmlAnnotationsLocally;
			_settings.StoreXmlInMyDocuments = _storeXmlInMyDocuments;
			_settings.LocalAnnotationsFolder = System.IO.Directory.Exists(_localAnnotationStoreFolder) ? _localAnnotationStoreFolder : "";
			_settings.RequireUserInfo = _requireUserInfo;
			_settings.RequireMarkupInAnnotation = _requireMarkupInAnnotation;
			_settings.LocalTemplatesFolder = _localTemplateStoreFolder;
			_settings.Save();
		}
	}
}
