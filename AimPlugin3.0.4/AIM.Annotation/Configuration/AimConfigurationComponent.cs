#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
