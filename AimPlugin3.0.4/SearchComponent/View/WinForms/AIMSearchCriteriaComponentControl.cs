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

using System.Collections.Generic;
using System.Windows.Forms;
using ClearCanvas.Desktop.View.WinForms;

namespace SearchComponent.View.WinForms
{
    public partial class AIMSearchCriteriaComponentControl : ApplicationComponentUserControl
    {
        private AIMSearchCriteriaComponent _component;

		public AIMSearchCriteriaComponentControl(AIMSearchCriteriaComponent component)
            :base(component)
        {
			_component = component;
            InitializeComponent();

            ClearCanvasStyle.SetTitleBarStyle(_titleBar);

			_anatomicEntities.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_anatomicEntities.ValueChanged += OnAnatomicEntitiesValueChanged;

			_imagingObservations.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_imagingObservations.ValueChanged += OnImagingObservationsValueChanged;

			_anatomicEntityCharacteristics.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_anatomicEntityCharacteristics.ValueChanged += OnAnatomicEntityCharacteristicsValueChanged;

			_imagingObservationCharacteristics.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_imagingObservationCharacteristics.ValueChanged += OnImagingObservationCharacteristicsValueChanged;

			_studyInstanceUid.DataBindings.Add("Value", _component, "StudyInstanceUid", true, DataSourceUpdateMode.OnPropertyChanged);
			_studyInstanceUid.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_user.DataBindings.Add("Value", _component, "User", true, DataSourceUpdateMode.OnPropertyChanged);
			_user.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_imageAnnotation.DataBindings.Add("Checked", _component, "ImageAnnotation", true, DataSourceUpdateMode.OnPropertyChanged);
			_imageAnnotation.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_annotationOfAnnotation.DataBindings.Add("Checked", _component, "AnnotationOfAnnotation", true, DataSourceUpdateMode.OnPropertyChanged);
			_annotationOfAnnotation.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_searchButton.DataBindings.Add("Enabled", _component, "Enabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_cancelButton.DataBindings.Add("Enabled", _component, "CancelEnabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_resetButton.DataBindings.Add("Enabled", _component, "ResetEnabled", true, DataSourceUpdateMode.OnPropertyChanged);

			_imageAnnotation.Click += delegate { _component.ImageAnnotation = true; };
			_annotationOfAnnotation.Click += delegate { _component.AnnotationOfAnnotation = true; };
		}

		void OnImagingObservationCharacteristicsValueChanged(object sender, System.EventArgs e)
		{
			_component.ImagingObservationCharacteristics.Clear();
			foreach (ImagingObservationCharacteristic characteristic in GetImagingObservationCharacteristics())
				_component.ImagingObservationCharacteristics.Add(characteristic);
		}

		void OnAnatomicEntityCharacteristicsValueChanged(object sender, System.EventArgs e)
		{
			_component.AnatomicEntityCharacteristics.Clear();
			foreach (AnatomicEntityCharacteristic characteristic in GetAnatomicEntityCharacteristics())
				_component.AnatomicEntityCharacteristics.Add(characteristic);
		}

		void OnImagingObservationsValueChanged(object sender, System.EventArgs e)
		{
			_component.ImagingObservations.Clear();
			foreach (ImagingObservation observation in GetImagingObservations())
				_component.ImagingObservations.Add(observation);
		}

		void OnAnatomicEntitiesValueChanged(object sender, System.EventArgs e)
		{
			_component.AnatomicEntities.Clear();
			foreach (AnatomicEntity entity in GetAnatomicEntities())
				_component.AnatomicEntities.Add(entity);
		}

		private void OnSearch(object sender, System.EventArgs e)
		{
			_component.Search();
		}

		private void OnCancel(object sender, System.EventArgs e)
		{
			_component.Cancel();
		}

		private void OnReset(object sender, System.EventArgs e)
		{
			_anatomicEntities.Value = string.Empty;
			_anatomicEntityCharacteristics.Value = string.Empty;
			_imagingObservations.Value = string.Empty;
			_imagingObservationCharacteristics.Value = string.Empty;
			_component.Reset();
			_user.Update();
			_user.PerformLayout();
			_studyInstanceUid.Update();
			_studyInstanceUid.PerformLayout();
		}

		private List<AnatomicEntity> GetAnatomicEntities()
		{
			List<AnatomicEntity> anatomicEntities = new List<AnatomicEntity>();
			foreach (string codeMeaning in AddFieldValuesToList(_anatomicEntities))
			{
				AnatomicEntity entity = new AnatomicEntity();
				entity.CodeMeaning = codeMeaning;
				anatomicEntities.Add(entity);
			}
			return anatomicEntities;
		}

		private List<AnatomicEntityCharacteristic> GetAnatomicEntityCharacteristics()
		{
			List<AnatomicEntityCharacteristic> values = new List<AnatomicEntityCharacteristic>();
			foreach (string codeMeaning in AddFieldValuesToList(_anatomicEntityCharacteristics))
			{
				AnatomicEntityCharacteristic value = new AnatomicEntityCharacteristic();
				value.CodeMeaning = codeMeaning;
				values.Add(value);
			}
			return values;
		}

		private List<ImagingObservation> GetImagingObservations()
		{
			List<ImagingObservation> imagingObservations = new List<ImagingObservation>();
			foreach (string codeMeaning in AddFieldValuesToList(_imagingObservations))
			{
				ImagingObservation observation = new ImagingObservation();
				observation.CodeMeaning = codeMeaning;
				imagingObservations.Add(observation);
			}
			return imagingObservations;
		}

		private List<ImagingObservationCharacteristic> GetImagingObservationCharacteristics()
		{
			List<ImagingObservationCharacteristic> values = new List<ImagingObservationCharacteristic>();
			foreach (string codeMeaning in AddFieldValuesToList(_imagingObservationCharacteristics))
			{
				ImagingObservationCharacteristic value = new ImagingObservationCharacteristic();
				value.CodeMeaning = codeMeaning;
				values.Add(value);
			}
			return values;
		}

		private List<string> AddFieldValuesToList(TextField textField)
		{
			List<string> values = new List<string>();

			if (!string.IsNullOrEmpty(textField.Value))
			{
				string[] strings = textField.Value.Split(',');
				foreach (string value in strings)
				{
					if (!string.IsNullOrEmpty(value))
						values.Add(value.Trim());
				}
			}

			return values;
		}
    }
}
