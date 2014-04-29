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

using System.Linq;
using System.Windows.Forms;
using System.Drawing;
using System.Collections.Generic;
using ClearCanvas.Desktop.View.WinForms;

namespace AIM.Annotation.View.WinForms
{
	/// <summary>
	/// Provides a Windows Forms user-interface for <see cref="AimAnnotationsListComponent"/>.
	/// </summary>
	public partial class AimAnnotationsListComponentControl : ApplicationComponentUserControl
	{
		private readonly AimAnnotationsListComponent _component;

		private readonly Dictionary<string, AimDetailsList> _availableAnnotationsBySeries = new Dictionary<string, AimDetailsList>();

		/// <summary>
		/// Constructor.
		/// </summary>
		public AimAnnotationsListComponentControl(AimAnnotationsListComponent component)
			: base(component)
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
			var availableAnnotationDetailsList = _component.AvailableAnnotationsDetails;
			if (availableAnnotationDetailsList != null)
			{
				var annotationDetailsList = availableAnnotationDetailsList.ToList();
				foreach (var annotationDetails in annotationDetailsList)
				{
					string seriesUid = annotationDetails.AnnotationSeriesUid;
					if (!_availableAnnotationsBySeries.ContainsKey(seriesUid))
						_availableAnnotationsBySeries.Add(seriesUid, new AimDetailsList());
					_availableAnnotationsBySeries[seriesUid].Add(annotationDetails);
				}
			}
		}

		private void LayoutTableContainer()
		{
			CleanTableContainer();

			if (_availableAnnotationsBySeries.Count > 0)
			{
				_labelNoAnnotationsAvailable.Visible = false;
				_tableLayoutPanel.Visible = true;

				int i = 0;
				foreach (string seriesUid in _availableAnnotationsBySeries.Keys)
				{
					BindingSource bindingSource = new BindingSource();
					bindingSource.DataSource = _component;

					AimDetailsListControl aimDetailsListControl = new AimDetailsListControl();
					aimDetailsListControl.SelectedAnnotationUid = _component.SelectedAnnotationUid;
					aimDetailsListControl.DataBindings.Add("SelectedAnnotationUid", bindingSource, "SelectedAnnotationUid", true, DataSourceUpdateMode.OnPropertyChanged);
					aimDetailsListControl.AvailableDetailsList = _availableAnnotationsBySeries[seriesUid];
					aimDetailsListControl.Dock = DockStyle.Top;
					aimDetailsListControl.ShowImageClicked += OnShowImageClicked;
					aimDetailsListControl.EditImageClicked += EditImageClicked;
					_tableLayoutPanel.RowStyles.Add(new RowStyle());
					GroupBox groupBox = new GroupBox();
					groupBox.Text = _component.GetSeriesCaption(seriesUid);
					groupBox.Dock = DockStyle.Top;
					groupBox.AutoSize = true;

					// Make the series group boxes stand out
					Font originalFont = aimDetailsListControl.Font;
					groupBox.Font = new Font(groupBox.Font.FontFamily, groupBox.Font.Size * 1.25f, FontStyle.Bold);
					aimDetailsListControl.Font = originalFont;
					groupBox.BackColor = Color.FromArgb(
						(int)(groupBox.BackColor.R * 0.75),
						(int)(groupBox.BackColor.G * 0.75),
						(int)(groupBox.BackColor.B * 0.75));

					groupBox.AutoSizeMode = AutoSizeMode.GrowAndShrink;
					_tableLayoutPanel.Controls.Add(groupBox, 0, i);
					groupBox.Controls.Add(aimDetailsListControl);
					groupBox.Padding = new Padding(0, 16, 0, 0);
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

		private void EditImageClicked(object sender, ShowAimAnnotationEventArg e)
		{
			_component.EditImageAnnotation(e.AimUid, false);
		}
	}
}
