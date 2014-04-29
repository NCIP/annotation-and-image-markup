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

using System.Collections.Generic;
using System.Linq;
using ClearCanvas.Desktop.View.WinForms;

namespace AimDataService.View.WinForms
{
    public partial class AimDataServiceSearchCriteriaComponentControl : ApplicationComponentUserControl
    {
        private readonly AimDataServiceSearchCriteriaComponent _component;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="component"></param>
        public AimDataServiceSearchCriteriaComponentControl(AimDataServiceSearchCriteriaComponent component)
            : base(component)
        {
            InitializeComponent();

            ClearCanvasStyle.SetTitleBarStyle(_titleBar);

            // Hide Advanced Search Criteria controls for now
            _advancedSearchCriteriaListView.Visible = false;
            _advancedSearchCriteriaGroupBox.Visible = false;
            _searchCriteriaLabel.Visible = false;

            _component = component;
        }

        private void SearchButtonClick(object sender, System.EventArgs e)
        {
            _component.Search();
        }

        private void CancelButtonClick(object sender, System.EventArgs e)
        {
            _component.Cancel();
        }

        private void ResetButtonClick(object sender, System.EventArgs e)
        {
            _imagingPhysicalEntitiesTextField.Value = "";
            _imagingPhysicalEntityCharacteristicsTextField.Value = "";
            _imagingObservationsTextField.Value = "";
            _imagingObservationCharacteristicsTextField.Value = "";

            _studyInstanceUidTextField.Value = "";

            _patientIdTextField.Value = "";
            _patientNameTextField.Value = "";

            _imageAnnotationRadioButton.Checked = false;
            _annotationOfAnnotationRadioButton.Checked = false;
            _annotationNameTextField.Value = "";

            _userTextField.Value = "";
            _component.ResetSearchCriteria();
        }

        private void ImagingPhysicalEntitiesTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.AnatomicEntity = _imagingPhysicalEntitiesTextField.Value;
        }

        private void ImagingPhysicalEntityCharacteristicsTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.AnatomicEntityCharacteristic =
                _imagingPhysicalEntityCharacteristicsTextField.Value;
        }

        private void ImagingObservationsTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.ImagingObservationEntity = 
                _imagingObservationsTextField.Value;
        }

        private void ImagingObservationCharacteristicsTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.ImagingObservationEntityCharacteristic = 
                _imagingObservationCharacteristicsTextField.Value;
        }

        private void UserTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.Username = _userTextField.Value;
        }

        private void StudyInstanceUidTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.StudyInstanceUid = _studyInstanceUidTextField.Value;
        }

        private void PatientIdTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.PatientId = _patientIdTextField.Value;
        }

        private void PatientNameTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.PatientName = _patientNameTextField.Value;
        }

        private void AnnotationNameTextFieldValueChanged(object sender, System.EventArgs e)
        {
            _component.SearchCriteria.AnnotationName = _annotationNameTextField.Value;
        }

        /// <summary>
        /// Disabled - Search criteria not implemented on web service
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ImageAnnotationRadioButtonCheckedChanged(object sender, System.EventArgs e)
        {
        }

        /// <summary>
        /// Disabled - Search criteria not implemented on web service
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AnnotationOfAnnotationRadioButtonCheckedChanged(object sender, System.EventArgs e)
        {
        }

        /// <summary>
        /// Splits a string of comma separated values and returns the values in a collection
        /// </summary>
        /// <param name="value">Comma separated string</param>
        /// <returns>Collection of string values from a comma separated value string</returns>
        private IEnumerable<string> StringToCsvStringCollection(string value)
        {
            var values = new List<string>();

            if (!string.IsNullOrEmpty(value))
            {
                string[] strings = value.Split(',');
                values.AddRange(from csv in strings where !string.IsNullOrEmpty(csv.Trim()) select csv.Trim());
            }

            return values;
        }
    }
}
