#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

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
            :base(component)
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
