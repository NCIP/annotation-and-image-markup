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
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.View.WinForms
{
	public partial class AimDetailsControl : UserControl, INotifyPropertyChanged
	{
		private event EventHandler<ShowAimAnnotationEventArg> _showAnnotationClicked;
		private event EventHandler<ShowAimAnnotationEventArg> _editAnnotationClicked;

		private static readonly Color _labelColor = Color.FromKnownColor(KnownColor.ControlLight);

		private string _aimName;
		private string _aimUid;
		private string[] _aeList;
		private string[] _ioList;

		private static int cnt;
		private bool _isAnnotationSelected;

		public AimDetailsControl()
		{
			InitializeComponent();

			_linkShow.DataBindings.Add("Enabled", this, "IsLinkEnabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_linkEdit.DataBindings.Add("Enabled", this, "IsLinkEnabled", true, DataSourceUpdateMode.OnPropertyChanged);

			// AimName binding
			Binding aimNameBinding = new Binding("Text", this, "AimName", true);
			aimNameBinding.Format +=
				delegate(object sender, ConvertEventArgs e)
				{
					if (e.DesiredType == typeof(string))
					{
						e.Value = string.Format("Name: {0}", AimName);
						this._lblAimName.Font = new Font(_lblAimName.Font.FontFamily, _lblAimName.Font.Size,
														 _isAnnotationSelected ? FontStyle.Bold : FontStyle.Regular, _lblAimName.Font.Unit);

					}
				};
			_lblAimName.DataBindings.Add(aimNameBinding);
			_lblAimName.ShowToolTipChanged += new EventHandler(OnLblAimNameShowToolTipChanged);
		}

		void OnLblAimNameShowToolTipChanged(object sender, EventArgs e)
		{
			_toolTip.SetToolTip(_lblAimName, _lblAimName.ShowToolTip ? _lblAimName.ToolTipText : null);
		}

		internal event EventHandler<ShowAimAnnotationEventArg> ShowAimAnnotationClicked
		{
			add { _showAnnotationClicked += value; }
			remove { _showAnnotationClicked -= value; }
		}

		internal event EventHandler<ShowAimAnnotationEventArg> EditAimAnnotationClicked
		{
			add { _editAnnotationClicked += value; }
			remove { _editAnnotationClicked -= value; }
		}

		public string AimName
		{
			get { return _aimName; }
			internal set
			{
				if (_aimName == value)
					return;

				_aimName = value;
				this.NotifyPropertyChanged("AimName");
			}
		}

		public string ToolTipText
		{
			get { return _lblAimName.ToolTipText; }
			set { _lblAimName.ToolTipText = value; }
		}

		public string AimUid
		{
			get { return _aimUid; }
			internal set
			{
				if (_aimUid == value)
					return;

				_aimUid = value;
				this.NotifyPropertyChanged("AimUid");
				this.NotifyPropertyChanged("IsLinkEnabled");
			}
		}

		public bool IsLinkEnabled
		{
			get { return !string.IsNullOrEmpty(_aimUid); }
			internal set
			{
				// No-op
			}
		}

		public string[] AnnatomicEntities
		{
			get { return _aeList; }
			set
			{
				if (_aeList == value)
					return;

				_aeList = value;
				this.UpdateFlowPanel(_flowPanelAe, _aeList);
			}
		}

		public string[] ImagingObservations
		{
			get { return _ioList; }
			set
			{
				if (_ioList == value)
					return;

				_ioList = value;
				this.UpdateFlowPanel(_flowPanelIo, _ioList);
			}
		}

		public bool IsAnnotationSelected
		{
			get { return _isAnnotationSelected; }
			set
			{
				if (_isAnnotationSelected == value)
					return;

				_isAnnotationSelected = value;
				this.NotifyPropertyChanged("AimName");
			}
		}

		// Populates FlowLayoutPanel with given values
		private void UpdateFlowPanel(FlowLayoutPanel flowPanel, string[] listOfValues)
		{
			flowPanel.SuspendLayout();
			flowPanel.Controls.Clear();

			if (listOfValues != null)
			{
				foreach (string s in listOfValues)
				{
					Label label = new Label();
					label.AutoEllipsis = true;
					// Highlight every other row of labels
					if (flowPanel.Controls.Count != 0 && flowPanel.Controls[flowPanel.Controls.Count - 1].BackColor != _labelColor)
						label.BackColor = _labelColor;
					label.Size = new Size(flowPanel.ClientSize.Width - label.Margin.Horizontal, 17);
					label.TabIndex = flowPanel.Controls.Count;
					label.Text = s;
					label.TextAlign = ContentAlignment.MiddleLeft;

					flowPanel.Controls.Add(label);
				}
			}
			flowPanel.ResumeLayout();
		}

		protected void RemoveLabelFromFlowPanel(FlowLayoutPanel flowPanel)
		{
			if (flowPanel.Controls.Count > 0)
				flowPanel.Controls.RemoveAt(flowPanel.Controls.Count - 1);
			flowPanel.Update();
		}

		private void OnTableLayoutPanelSizeChanged(object sender, EventArgs e)
		{
			_linkShow.Location = new Point(_linkShow.Location.X, _tableLayoutPanel.Location.Y + _tableLayoutPanel.Size.Height + 8);
			_linkEdit.Location = new Point(_linkEdit.Location.X, _tableLayoutPanel.Location.Y + _tableLayoutPanel.Size.Height + 8);
		}

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion

		private void NotifyPropertyChanged(String info)
		{
			EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs(info));
		}

		private void OnFlowPanelAeClientSizeChanged(object sender, EventArgs e)
		{
			AdjustChildrenControlWidth(_flowPanelAe);
		}

		private void OnFlowPanelIoClientSizeChanged(object sender, EventArgs e)
		{
			AdjustChildrenControlWidth(_flowPanelIo);
		}

		private static void AdjustChildrenControlWidth(Control parent)
		{
			foreach (Control control in parent.Controls)
			{
				control.Width = parent.ClientSize.Width - control.Margin.Horizontal;
			}
		}

		private void OnOpenAnnotationLinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			EventsHelper.Fire(_showAnnotationClicked, this, new ShowAimAnnotationEventArg(_aimUid));
		}

		private void LinkShowLinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			EventsHelper.Fire(_showAnnotationClicked, this, new ShowAimAnnotationEventArg(_aimUid));
		}

		private void LinkEditLinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			EventsHelper.Fire(_editAnnotationClicked, this, new ShowAimAnnotationEventArg(_aimUid));
		}
	}

	internal class ShowAimAnnotationEventArg : EventArgs
	{
		public ShowAimAnnotationEventArg(string aimUid)
		{
			AimUid = aimUid;
		}

		public string AimUid { get; set; }
	}
}
