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
		private bool _resetTemplateAfterAnnotationCreation;
		private string _localTemplateStoreFolder;
		private bool _useCrosshairsInsteadOfArrowsForTextCallouts;
		private bool _alwaysPromptOnRestoringTemplateData;

		public bool SendNewXmlAnnotationsToGrid
		{
			get { return _sendNewXmlAnnotationsToGrid; }
			set
			{
				if (_sendNewXmlAnnotationsToGrid != value)
				{
					_sendNewXmlAnnotationsToGrid = value;
					this.Modified = true;
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
					this.Modified = true;
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
					this.Modified = true;
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
					this.Modified = true;
					NotifyPropertyChanged("LocalAnnotationStoreFolder");
				}
			}
		}

		public bool LocalAnnotationStoreFolderEnabled
		{
			get { return this.StoreXmlAnnotationsLocally && this.StoreXmlInSpecifiedFolder; }
		}

		[ValidationMethodFor("LocalAnnotationStoreFolder")]
		protected ValidationResult LocalAnnotationFolderValidation()
		{
			if (!this.StoreXmlAnnotationsLocally || this.StoreXmlInMyDocuments)
				return new ValidationResult(true, "");

			return new ValidationResult(System.IO.Directory.Exists(this.LocalAnnotationStoreFolder), "Local AIM storage folder does not exist");
		}

		public bool RequireUserInfo
		{
			get { return _requireUserInfo; }
			set
			{
				if (_requireUserInfo != value)
				{
					_requireUserInfo = value;
					this.Modified = true;
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
					this.Modified = true;
					NotifyPropertyChanged("RequireMarkupInAnnotation");
				}
			}
		}

		public bool ResetTemplateAfterAnnotationCreation
		{
			get { return _resetTemplateAfterAnnotationCreation; }
			set
			{
				if (_resetTemplateAfterAnnotationCreation != value)
				{
					_resetTemplateAfterAnnotationCreation = value;
					this.Modified = true;
					NotifyPropertyChanged("ResetTemplateAfterAnnotationCreation");
				}
			}
		}

		public bool UseCrosshairsInsteadOfArrowsForTextCallouts
		{
			get { return _useCrosshairsInsteadOfArrowsForTextCallouts; }
			set
			{
				if (_useCrosshairsInsteadOfArrowsForTextCallouts != value)
				{
					_useCrosshairsInsteadOfArrowsForTextCallouts = value;
					Modified = true;
					NotifyPropertyChanged("UseCrosshairsInsteadOfArrowsForTextCallouts");
				}
			}
		}

		public bool AlwaysPromptOnRestoringTemplateData
		{
			get { return _alwaysPromptOnRestoringTemplateData; }
			set
			{
				if (_alwaysPromptOnRestoringTemplateData != value)
				{
					_alwaysPromptOnRestoringTemplateData = value;
					Modified = true;
					NotifyPropertyChanged("AlwaysPromptOnRestoringTemplateData");
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
					this.Modified = true;
					NotifyPropertyChanged("LocalTemplatesStoreFolder");
				}
			}
		}

		[ValidationMethodFor("LocalTemplatesStoreFolder")]
		protected ValidationResult LocalTemplatesFolderValidation()
		{
			if (string.IsNullOrEmpty(this.LocalTemplatesStoreFolder))
				return new ValidationResult(true, "");

			return new ValidationResult(System.IO.Directory.Exists(this.LocalTemplatesStoreFolder), "Local AIM Templates storage folder does not exist");
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
			_resetTemplateAfterAnnotationCreation = _settings.ResetTemplateAfterAnnotationCreation;
			_useCrosshairsInsteadOfArrowsForTextCallouts = _settings.UseCrosshairsForTextCallouts;
			_localTemplateStoreFolder = _settings.LocalTemplatesFolder;
			_alwaysPromptOnRestoringTemplateData = _settings.AlwaysPromptOnRestoringTemplateData;
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
			_settings.ResetTemplateAfterAnnotationCreation = _resetTemplateAfterAnnotationCreation;
			_settings.LocalTemplatesFolder = System.IO.Directory.Exists(_localAnnotationStoreFolder) ? _localAnnotationStoreFolder : "";
			_settings.UseCrosshairsForTextCallouts = _useCrosshairsInsteadOfArrowsForTextCallouts;
			_settings.AlwaysPromptOnRestoringTemplateData = _alwaysPromptOnRestoringTemplateData;
			_settings.Save();
		}
	}
}
