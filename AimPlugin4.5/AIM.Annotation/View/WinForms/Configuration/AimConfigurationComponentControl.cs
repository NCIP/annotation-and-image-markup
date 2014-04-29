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
using System.Windows.Forms;

using ClearCanvas.Desktop.View.WinForms;

using AIM.Annotation.Configuration;

namespace AIM.Annotation.View.WinForms.Configuration
{
	/// <summary>
	/// Provides a Windows Forms user-interface for <see cref="AimConfigurationComponent"/>.
	/// </summary>
	public partial class AimConfigurationComponentControl : ApplicationComponentUserControl
	{
		private readonly AimConfigurationComponent _component;

		/// <summary>
		/// Constructor.
		/// </summary>
		public AimConfigurationComponentControl(AimConfigurationComponent component)
			: base(component)
		{
			InitializeComponent();

			_component = component;

			_chkSendToGrid.DataBindings.Add("Checked", _component, "SendNewXmlAnnotationsToGrid", false, DataSourceUpdateMode.OnPropertyChanged);
			
			_chkStoreAnnotationsLocally.DataBindings.Add("Checked", _component, "StoreXmlAnnotationsLocally", false, DataSourceUpdateMode.OnPropertyChanged);
			
			_radStoreInMyDocuments.DataBindings.Add("Checked", _component, "StoreXmlInMyDocuments", false, DataSourceUpdateMode.OnPropertyChanged);
			_radStoreInMyDocuments.DataBindings.Add("Enabled", _component, "StoreXmlAnnotationsLocally", false, DataSourceUpdateMode.OnPropertyChanged);
			
			_radStoreInFolder.DataBindings.Add("Checked", _component, "StoreXmlInSpecifiedFolder", false, DataSourceUpdateMode.OnPropertyChanged);
			_radStoreInFolder.DataBindings.Add("Enabled", _component, "StoreXmlAnnotationsLocally", false, DataSourceUpdateMode.OnPropertyChanged);
			
			_txtLocalAnnotationsFolderLocation.DataBindings.Add("Text", _component, "LocalAnnotationStoreFolder", true, DataSourceUpdateMode.OnPropertyChanged);
			_txtLocalAnnotationsFolderLocation.DataBindings.Add("Enabled", _component, "LocalAnnotationStoreFolderEnabled", false, DataSourceUpdateMode.OnPropertyChanged);

			_btnBrowseForAnnotationsFolder.DataBindings.Add("Enabled", _component, "LocalAnnotationStoreFolderEnabled", false, DataSourceUpdateMode.OnPropertyChanged);

			base.ErrorProvider.SetIconAlignment(_btnBrowseForAnnotationsFolder, ErrorIconAlignment.BottomRight);

			_chkRequireUserInfo.DataBindings.Add("Checked", _component, "RequireUserInfo", false, DataSourceUpdateMode.OnPropertyChanged);

			_chkRequireMarkupInAnnotation.DataBindings.Add("Checked", _component, "RequireMarkupInAnnotation", false, DataSourceUpdateMode.OnPropertyChanged);

			_chkResetTemplateAfterAnnotationCreation.DataBindings.Add("Checked", _component,
																	  "ResetTemplateAfterAnnotationCreation", false,
																	  DataSourceUpdateMode.OnPropertyChanged);

			_chkUseCrosshairsInsteadOfArrowsForTextCallouts.DataBindings.Add("Checked", _component, "UseCrosshairsInsteadOfArrowsForTextCallouts", false, DataSourceUpdateMode.OnPropertyChanged);

			_chkAlwaysPromptOnRestoringTemplateData.DataBindings.Add(
				"Checked",
				_component,
				"AlwaysPromptOnRestoringTemplateData",
				false,
				DataSourceUpdateMode.OnPropertyChanged);

			_txtLocalTemplatesFolderLocation.DataBindings.Add("Text", _component, "LocalTemplatesStoreFolder", true, DataSourceUpdateMode.OnPropertyChanged);
		}

		private void _btnBrowseForAnnotationsFolder_Click(object sender, EventArgs e)
		{
			string initialFolder = _txtLocalAnnotationsFolderLocation.Text.Trim();
			this._folderBrowserDialog.SelectedPath = System.IO.Directory.Exists(initialFolder) ? initialFolder : string.Empty;

			if (this._folderBrowserDialog.ShowDialog() == DialogResult.OK)
			{
				_txtLocalAnnotationsFolderLocation.Text = this._folderBrowserDialog.SelectedPath;
			}
		}

		private void _btnBrowseForTemplatesFolder_Click(object sender, EventArgs e)
		{
			string initialFolder = _txtLocalTemplatesFolderLocation.Text.Trim();
			this._folderBrowserDialog.SelectedPath = System.IO.Directory.Exists(initialFolder) ? initialFolder : string.Empty;

			if (this._folderBrowserDialog.ShowDialog() == DialogResult.OK)
			{
				_txtLocalTemplatesFolderLocation.Text = this._folderBrowserDialog.SelectedPath;
			}
		}
	}
}
