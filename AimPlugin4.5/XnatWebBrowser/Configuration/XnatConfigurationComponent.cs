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
using Microsoft.Win32;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Configuration;

namespace XnatWebBrowser.Configuration
{
    [ExtensionPoint]
    public sealed class XnatConfigurationComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
    {
    }

    /// <summary>
    /// XnatConfigurationComponent class.
    /// </summary>
    [AssociateView(typeof(XnatConfigurationComponentViewExtensionPoint))]
    public class XnatConfigurationComponent : ConfigurationApplicationComponent
    {
        public static readonly string Path = "XNAT";

        private XnatSettings _settings;
        private string _xnatUrl;
        private string _downloadFolder;
        private int _downloadCheckInterval;

        /// <summary>
        /// Gets or sets the URL loaded by the Xnat Web Browser
        /// </summary>
        public string XnatUrl
        {
            get { return _xnatUrl; }
            set
            {
                if (_xnatUrl != value)
                {
                    _xnatUrl = value;
                    Modified = true;
                    NotifyPropertyChanged("XnatUrl");
                }
            }
        }

        /// <summary>
        /// Gets or sets the path where downloaded files are monitored to be
        /// automatically imported into the workstation
        /// </summary>
        public string DownloadFolder
        {
            get { return _downloadFolder; }
            set
            {
                if (_downloadFolder != value)
                {
                    _downloadFolder = value;
                    Modified = true;
                    NotifyPropertyChanged("DownloadFolder");
                }
            }
        }

        /// <summary>
        /// Gets or sets the time interval in seconds between checks for
        /// downloaded files to be automatically imported into the workstation
        /// </summary>
        public int DownloadCheckInterval
        {
            get { return _downloadCheckInterval; }
            set
            {
                if (_downloadCheckInterval != value)
                {
                    _downloadCheckInterval = value;
                    Modified = true;
                    NotifyPropertyChanged("DownloadCheckInterval");
                }
            }
        }

        /// <summary>
        /// Called by the host to initialize the application component.
        /// </summary>
        ///  <remarks>
        /// Override this method to implement custom initialization logic.  Overrides must be sure to call the base implementation.
        /// </remarks>
        public override void Start()
        {
            base.Start();

            _settings = XnatSettings.Default;
            _xnatUrl = _settings.XnatUrl;
            _downloadFolder = _settings.DownloadFolder;

            if (String.IsNullOrEmpty(_downloadFolder))
            {
                XnatSettings.Default.DownloadFolder = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) +
                                 "\\AIM XNAT Downloads";
                XnatSettings.Default.Save();
            }

            _downloadCheckInterval = _settings.DownloadCheckInterval;
            var value = Read();

        }

        public object Read()
        {
            return Registry.GetValue(@"HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer", "Download Directory",
                              new object());
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
            _settings.XnatUrl = _xnatUrl;
            _settings.DownloadFolder = _downloadFolder;
            _settings.DownloadCheckInterval = _downloadCheckInterval;
            _settings.Save();
        }
    }
}
