//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Collections.Generic;
using System.Windows.Forms;

using ClearCanvas.Desktop.View.WinForms;

namespace AIM.Annotation.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="AimAnnotationsListComponent"/>.
    /// </summary>
    public partial class AimAnnotationsListComponentControl : ApplicationComponentUserControl
    {
        private readonly AimAnnotationsListComponent _component;
		private Dictionary<string, List<aim_dotnet.Annotation>> _availableAnnotationsBySeries = new Dictionary<string, List<aim_dotnet.Annotation>>();

        /// <summary>
        /// Constructor.
        /// </summary>
        public AimAnnotationsListComponentControl(AimAnnotationsListComponent component)
            :base(component)
        {
			_component = component;
            InitializeComponent();

			BuildAnnotationsDictionary();
		
			LayoutTableContainer();
			_component.AvailableAnnotationsChanged += OnAvailableAnnotationsChanged;
        }

		private void OnAvailableAnnotationsChanged(object sender, System.EventArgs e)
		{
			BuildAnnotationsDictionary();
			LayoutTableContainer();
		}

		private void CleanTableContainer()
		{
			_tableLayoutPanel.Controls.Clear();
			_tableLayoutPanel.RowStyles.Clear();
		}

		private void BuildAnnotationsDictionary()
		{
			_availableAnnotationsBySeries.Clear();
			if (_component.AvailableAnnotations != null)
			{
				foreach (var annotation in _component.AvailableAnnotations)
				{
					var seriesUID = _component.GetSeriesUIDFromAimAnnotation(annotation);
					if (!_availableAnnotationsBySeries.ContainsKey(seriesUID))
						_availableAnnotationsBySeries.Add(seriesUID, new List<aim_dotnet.Annotation>());
					_availableAnnotationsBySeries[seriesUID].Add(annotation);
				}
			}
		}

		private void LayoutTableContainer()
		{
			CleanTableContainer();

			if (_component.AvailableAnnotations != null && _component.AvailableAnnotations.Count > 0)
			{
				_labelNoAnnotationsAvailable.Visible = false;
				_tableLayoutPanel.Visible = true;

				var i = 0;
				foreach (var seriesUID in _availableAnnotationsBySeries.Keys)
				{
					var bindingSource = new BindingSource();
					bindingSource.DataSource = _component;

					var series = _component.GetSeriesFromUID(seriesUID);
					var seriesText = series.SeriesNumber.ToString() + ": " + series.SeriesDescription;
					var aimDetailsListControl = new AimDetailsListControl();
					aimDetailsListControl.DataBindings.Add("SelectedAnnotation", bindingSource, "SelectedAnnotation", true, DataSourceUpdateMode.OnPropertyChanged);
					aimDetailsListControl.SelectedAnnotation = _component.SelectedAnnotation;
					aimDetailsListControl.AvailableAnnotations = _availableAnnotationsBySeries[seriesUID];
					aimDetailsListControl.Dock = DockStyle.Top;
					aimDetailsListControl.ShowImageClicked += new System.EventHandler<ShowAimAnnotationEventArg>(OnShowImageClicked);
					_tableLayoutPanel.RowStyles.Add(new RowStyle());
					var groupBox = new GroupBox();
					groupBox.Text = seriesText;
					groupBox.Dock = DockStyle.Top;
					groupBox.AutoSize = true;
					groupBox.AutoSizeMode = AutoSizeMode.GrowAndShrink;
					_tableLayoutPanel.Controls.Add(groupBox, 0, i);
					groupBox.Controls.Add(aimDetailsListControl);
					i++;
				}
			}
			else
			{
				_labelNoAnnotationsAvailable.Visible = true;
				_tableLayoutPanel.Visible = false;
			}
		}

		private void OnShowImageClicked(object sender, ShowAimAnnotationEventArg e)
		{
			_component.ShowImageWithAnnotation(e.AimUid);
		}
    }
}
