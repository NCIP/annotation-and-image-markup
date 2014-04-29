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

namespace SearchComponent.View.WinForms
{
	/// <summary>
	/// Provides a Windows Forms user-interface for <see cref="NBIASearchCriteriaComponent"/>.
	/// </summary>
	public partial class NBIASearchCriteriaComponentControl : ApplicationComponentUserControl
	{
		private NBIASearchCriteriaComponent _component;

		/// <summary>
		/// Constructor.
		/// </summary>
		public NBIASearchCriteriaComponentControl(NBIASearchCriteriaComponent component)
			: base(component)
		{
			_component = component;
			InitializeComponent();

			ClearCanvasStyle.SetTitleBarStyle(_titleBar);

			_modality.SetAvailableModalities(_component.AvailableSearchModalities);
			_modality.DataBindings.Add("CheckedModalities", component, "SearchModalities", true, DataSourceUpdateMode.OnPropertyChanged);
			_modality.DataBindings.Add("Enabled", component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_patientID.DataBindings.Add("Value", _component, "PatientId", true, DataSourceUpdateMode.OnPropertyChanged);
			_patientID.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_patientsName.DataBindings.Add("Value", _component, "PatientsName", true, DataSourceUpdateMode.OnPropertyChanged);
			_patientsName.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_patientsSex.DataBindings.Add("Value", _component, "PatientsSex", true, DataSourceUpdateMode.OnPropertyChanged);
			_patientsSex.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
	
			_project.DataBindings.Add("Value", _component, "Project", true, DataSourceUpdateMode.OnPropertyChanged);
			_project.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			// Not used fields
			//_protocolId.DataBindings.Add("Value", _component, "ProtocolId", true, DataSourceUpdateMode.OnPropertyChanged);
			//_protocolId.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			//_protocolName.DataBindings.Add("Value", _component, "ProtocolName", true, DataSourceUpdateMode.OnPropertyChanged);
			//_protocolName.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			//_siteName.DataBindings.Add("Value", _component, "SiteName", true, DataSourceUpdateMode.OnPropertyChanged);
			//_siteName.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			//_siteId.DataBindings.Add("Value", _component, "SiteId", true, DataSourceUpdateMode.OnPropertyChanged);
			//_siteId.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			
			_sliceThickness.DataBindings.Add("Value", _component, "SliceThickness", true, DataSourceUpdateMode.OnPropertyChanged);
			_sliceThickness.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			
			_studyInstanceUid.DataBindings.Add("Value", _component, "StudyInstanceUid", true, DataSourceUpdateMode.OnPropertyChanged);
			_studyInstanceUid.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			
			_patientsBirthDate.DataBindings.Add("Value", _component, "PatientsBirthDate", true, DataSourceUpdateMode.OnPropertyChanged);
			_patientsBirthDate.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_searchButton.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_cancelButton.DataBindings.Add("Enabled", _component, "CancelEnabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_resetButton.DataBindings.Add("Enabled", _component, "ResetEnabled", true, DataSourceUpdateMode.OnPropertyChanged);
		}

		private void _searchButton_Click(object sender, EventArgs e)
		{
			_component.Search();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			_component.Cancel();
		}

		private void _resetButton_Click(object sender, EventArgs e)
		{
			_component.Reset();
		}
	}
}
