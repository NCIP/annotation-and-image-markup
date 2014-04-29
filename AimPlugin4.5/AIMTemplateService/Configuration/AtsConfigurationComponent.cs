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

namespace AIMTemplateService.Configuration
{
	[ExtensionPoint]
	public sealed class AtsConfigurationComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	/// <summary>
	/// AtsConfigurationComponent class.
	/// </summary>
	[AssociateView(typeof(AtsConfigurationComponentViewExtensionPoint))]
	public class AtsConfigurationComponent : ConfigurationApplicationComponent
	{
		public static readonly string Path = "AIM Template Service";

		private AtsSettings _settings;
		private string _atsUrl;
	    private bool _autoImportTemplates;

		public string AtsUrl
		{
            get { return _atsUrl; }
			set
			{
				if (_atsUrl != value)
				{
                    _atsUrl = value;
					Modified = true;
					NotifyPropertyChanged("AtsUrl");
				}
			}
		}

	    public bool AutoImportTemplates
	    {
            get { return _autoImportTemplates; }
            set
            {
                if (_autoImportTemplates != value)
                {
                    _autoImportTemplates = value;
                    Modified = true;
                    NotifyPropertyChanged("AutoImportTemplates");
                }
            }
	    }

		public override void Start()
		{
			base.Start();

			_settings = AtsSettings.Default;
			_atsUrl = _settings.AtsUrl;
		    _autoImportTemplates = _settings.AutoImportTemplates;
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
		    _settings.AtsUrl = _atsUrl;
		    _settings.AutoImportTemplates = _autoImportTemplates;
			_settings.Save();
		}
	}
}
