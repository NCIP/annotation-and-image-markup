#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

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
