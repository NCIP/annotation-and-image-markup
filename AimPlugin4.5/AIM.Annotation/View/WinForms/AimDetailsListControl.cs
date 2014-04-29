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
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.View.WinForms
{
	/// <summary>
	/// Control that shows details for multiple AIM annotations by
	/// aggregating AimDetailsControls.
	/// </summary>
	public partial class AimDetailsListControl : UserControl
	{
		internal event EventHandler<ShowAimAnnotationEventArg> ShowImageClicked;
		internal event EventHandler<ShowAimAnnotationEventArg> EditImageClicked;

		private AimDetailsList _availableDetailsList = new AimDetailsList();

		public AimDetailsListControl()
		{
			InitializeComponent();
		}

		public AimDetailsList AvailableDetailsList
		{
			get { return null; }
			set
			{
				if (value == null || value.Count == 0)
					return;

				// check if no change occurred?
				if (_availableDetailsList.Count == value.Count)
				{
					bool same = true;
					for (int j = 0; j < value.Count; j++)
					{
						if (_availableDetailsList[j] == null || !_availableDetailsList[j].Equals(value[j]))
						{
							same = false;
							break;
						}
					}
					if (same)
						return;
				}

				_availableDetailsList = value;

				this.SuspendLayout();
				_mainPanel.SuspendLayout();
				_mainPanel.Controls.Clear();

				TableLayoutPanel tableLayoutPanel = new TableLayoutPanel();
				tableLayoutPanel.AutoSize = true;
				tableLayoutPanel.AutoSizeMode = AutoSizeMode.GrowAndShrink;
				tableLayoutPanel.Dock = DockStyle.Top;
				_mainPanel.Controls.Add(tableLayoutPanel);
				tableLayoutPanel.CellBorderStyle = TableLayoutPanelCellBorderStyle.Inset;
				int i = 0;
				foreach (var annotationDetails in _availableDetailsList)
				{
					tableLayoutPanel.RowStyles.Add(new RowStyle());

					AimDetailsControl control = AddDetailsControl();
					control.AimName = annotationDetails.Name;
					control.AimUid = annotationDetails.AnnotationUid;
					var aeList = new List<string>();
					if (annotationDetails.AnatomicEntities != null)
						CollectionUtils.ForEach(annotationDetails.AnatomicEntities, ae => aeList.Add(ae.StandardCodeSequence.CodeMeaning));
					var ioList = new List<string>();
					if (annotationDetails.ImagingObservations != null)
						CollectionUtils.ForEach(annotationDetails.ImagingObservations, io => ioList.Add(io.StandardCodeSequence.CodeMeaning));
					control.AnnatomicEntities = aeList.ToArray();
					control.ImagingObservations = ioList.ToArray();
					control.ToolTipText = annotationDetails.ToolTipText;
					tableLayoutPanel.Controls.Add(control, 0, i);
					i++;
				}
				_mainPanel.ResumeLayout(false);
				this.ResumeLayout(false);
				this.PerformLayout();
			}
		}

		// Data binding method
		public string SelectedAnnotationUid
		{
			get { return null; }
			set
			{
				foreach (AimDetailsControl aimDetailsControl in AimDetailsControls)
				{
					aimDetailsControl.IsAnnotationSelected = !string.IsNullOrEmpty(value) && aimDetailsControl.AimUid == value;
				}
			}
		}

		private IEnumerable<AimDetailsControl> AimDetailsControls
		{
			get
			{
				if (_mainPanel.Controls.Count > 0 && _mainPanel.Controls[0] is TableLayoutPanel)
					foreach (Control control in _mainPanel.Controls[0].Controls)
						if (control is AimDetailsControl)
							yield return (AimDetailsControl)control;
			}
		}

		// Creates and configures new AimDetailsControl
		private AimDetailsControl AddDetailsControl()
		{
			AimDetailsControl aimShortDetailsControl = new AimDetailsControl();
			aimShortDetailsControl.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			aimShortDetailsControl.AutoSize = true;
			aimShortDetailsControl.AutoSizeMode = AutoSizeMode.GrowAndShrink;
			aimShortDetailsControl.BackColor = SystemColors.Control;
			aimShortDetailsControl.Location = new Point(0, 0);
			aimShortDetailsControl.ShowAimAnnotationClicked += OnShowAimAnnotationClicked;
			aimShortDetailsControl.EditAimAnnotationClicked += OnEditAimAnnotationClicked;

			return aimShortDetailsControl;
		}

		private void OnShowAimAnnotationClicked(object sender, ShowAimAnnotationEventArg e)
		{
			EventsHelper.Fire(ShowImageClicked, this, new ShowAimAnnotationEventArg(e.AimUid));
		}

		private void OnEditAimAnnotationClicked(object sender, ShowAimAnnotationEventArg e)
		{
			EventsHelper.Fire(EditImageClicked, this, new ShowAimAnnotationEventArg(e.AimUid));
		}

		private void OnPanelClientSizeChanged(object sender, EventArgs e)
		{
			_mainPanel.SuspendLayout();

			foreach (AimDetailsControl control in AimDetailsControls)
				control.Width = control.Parent.ClientSize.Width;

			_mainPanel.ResumeLayout(false);
			_mainPanel.PerformLayout();
		}
	}
}
