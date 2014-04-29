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

using System.Windows.Forms;
using XnatWebBrowser.Configuration;
using ClearCanvas.Desktop.View.WinForms;

namespace XnatWebBrowser.View.WinForms.Configuration
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="XnatConfigurationComponent"/>.
    /// </summary>
    public partial class XnatConfigurationComponentControl : ApplicationComponentUserControl
    {
        private readonly XnatConfigurationComponent _component;

        public XnatConfigurationComponentControl(XnatConfigurationComponent component) :
            base(component)
        {
            InitializeComponent();

            _component = component;

            _xnatUrlTextBox.DataBindings.Add("Text", _component, "XnatUrl", true, DataSourceUpdateMode.OnPropertyChanged);
            _autoImportDownloadFolderTextBox.DataBindings.Add("Text", _component, "DownloadFolder", true, DataSourceUpdateMode.OnPropertyChanged);
            _downloadCheckIntervalNumericUpDown.DataBindings.Add("Value", _component, "DownloadCheckInterval", false,
                                                                 DataSourceUpdateMode.OnPropertyChanged);
        }

        private void AutoImportDownloadFolderButtonClick(object sender, System.EventArgs e)
        {
            string initialFolder = _autoImportDownloadFolderTextBox.Text.Trim();
            _folderBrowserDialog.SelectedPath = System.IO.Directory.Exists(initialFolder) ? initialFolder : string.Empty;
            _folderBrowserDialog.Description = "Select folder to monitor for XNAT downloads";

            if (_folderBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                _autoImportDownloadFolderTextBox.Text = _folderBrowserDialog.SelectedPath;
            }
        }
    }
}
