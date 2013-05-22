//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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

			ErrorProvider.SetIconAlignment(_btnBrowseForAnnotationsFolder, ErrorIconAlignment.BottomRight);

			_chkRequireUserInfo.DataBindings.Add("Checked", _component, "RequireUserInfo", false, DataSourceUpdateMode.OnPropertyChanged);

			_chkRequireMarkupInAnnotation.DataBindings.Add("Checked", _component, "RequireMarkupInAnnotation", false, DataSourceUpdateMode.OnPropertyChanged);

			_txtLocalTemplatesFolderLocation.DataBindings.Add("Text", _component, "LocalTemplatesStoreFolder", true, DataSourceUpdateMode.OnPropertyChanged);
		}

		private void _btnBrowseForAnnotationsFolder_Click(object sender, EventArgs e)
		{
			var initialFolder = _txtLocalAnnotationsFolderLocation.Text.Trim();
			_folderBrowserDialog.SelectedPath = System.IO.Directory.Exists(initialFolder) ? initialFolder : string.Empty;

			if (_folderBrowserDialog.ShowDialog() == DialogResult.OK)
			{
				_txtLocalAnnotationsFolderLocation.Text = _folderBrowserDialog.SelectedPath;
			}
		}

		private void _btnBrowseForTemplatesFolder_Click(object sender, EventArgs e)
		{
			var initialFolder = _txtLocalTemplatesFolderLocation.Text.Trim();
			_folderBrowserDialog.SelectedPath = System.IO.Directory.Exists(initialFolder) ? initialFolder : string.Empty;

			if (_folderBrowserDialog.ShowDialog() == DialogResult.OK)
			{
				_txtLocalTemplatesFolderLocation.Text = _folderBrowserDialog.SelectedPath;
			}
		}
	}
}
