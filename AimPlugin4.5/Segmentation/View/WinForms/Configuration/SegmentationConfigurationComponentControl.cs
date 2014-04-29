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
using Segmentation.Configuration;

namespace Segmentation.View.WinForms.Configuration
{
	public partial class SegmentationConfigurationComponentControl : UserControl
	{
		private readonly SegmentationConfigurationComponent _component;

		public SegmentationConfigurationComponentControl(SegmentationConfigurationComponent component)
		{
			_component = component;

			InitializeComponent();

			_chkShowConfirmationWhenCreatingNewSegmentations.DataBindings.Add("Checked", _component,
																			  "ShowSegmentationCreationDialog", false,
																			  DataSourceUpdateMode.OnPropertyChanged);
			_txtCategoryTypeModifierXmlConfigurationFileLocation.DataBindings.Add("Text", _component,
																				  "CategoryTypeModifierConfigurationFileLocation",
																				  true,
																				  DataSourceUpdateMode.OnPropertyChanged);
			_txtAnatomicRegionAndModifierXmlConfigurationFile.DataBindings.Add("Text", _component,
																			   "AnatomicRegionModifierConfigurationFileLocation",
																			   true,
																			   DataSourceUpdateMode.OnPropertyChanged);
		}

		private void OnBtnBrowseForCategoryConfigurationFileClick(object sender, EventArgs e)
		{
			var initialFile = _component.CategoryTypeModifierConfigurationFileLocation;
			if (!String.IsNullOrEmpty(initialFile))
			{
				var directory = System.IO.Path.GetDirectoryName(initialFile);
				if (System.IO.Directory.Exists(directory))
					_openFileDialog.InitialDirectory = directory;
			}
			if (_openFileDialog.ShowDialog() == DialogResult.OK)
			{
				_txtCategoryTypeModifierXmlConfigurationFileLocation.Text = _openFileDialog.FileName;
			}
		}

		private void OnBtnBrowseForAnatomicRegionConfigurationFileClick(object sender, EventArgs e)
		{
			var initialFile = _component.AnatomicRegionModifierConfigurationFileLocation;
			if (!String.IsNullOrEmpty(initialFile))
			{
				var directory = System.IO.Path.GetDirectoryName(initialFile);
				if (System.IO.Directory.Exists(directory))
					_openFileDialog.InitialDirectory = directory;
			}
			if (_openFileDialog.ShowDialog() == DialogResult.OK)
			{
				_txtAnatomicRegionAndModifierXmlConfigurationFile.Text = _openFileDialog.FileName;
			}
		}

		private void OnBtnExportDefaultConfigFilesClick(object sender, EventArgs e)
		{
			string defaltXmlFilesPath;
			if (string.IsNullOrEmpty(_folderBrowserDialog.SelectedPath) &&
				!string.IsNullOrEmpty(defaltXmlFilesPath = _component.GetDefaultXmlFilesPath()))
				_folderBrowserDialog.SelectedPath = defaltXmlFilesPath;
			if (_folderBrowserDialog.ShowDialog() == DialogResult.OK)
			{
				if (!_component.ExportDefaultConfigurationFiles(_folderBrowserDialog.SelectedPath))
				{
					MessageBox.Show(@"Failed to Export Configuration Files. See log for details.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				}
			}
		}
	}
}