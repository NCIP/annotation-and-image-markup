//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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
		private static readonly Color _labelColor = Color.FromKnownColor(KnownColor.ControlLight);
		private string _aimName;
		private string _aimUid;
		private string[] _aeList;
		private string[] _ioList;
		private bool _isAnnotationSelected;

		public AimDetailsControl()
		{
			InitializeComponent();

			_linkOpenImageAnnotation.DataBindings.Add("Enabled", this, "IsLinkEnabled", true, DataSourceUpdateMode.OnPropertyChanged);

			var aimNameBinding = new Binding("Text", this, "AimName", true);
			aimNameBinding.Format +=
				delegate(object sender, ConvertEventArgs e)
					{
						if (e.DesiredType == typeof (string))
						{
							e.Value = string.Format("Name: {0}", AimName);
							_lblAimName.Font = new Font(_lblAimName.Font.FontFamily, _lblAimName.Font.Size,
							                                 _isAnnotationSelected ? FontStyle.Bold : FontStyle.Regular, _lblAimName.Font.Unit);

						}
					};
			_lblAimName.DataBindings.Add(aimNameBinding);
			_lblAimName.ShowToolTipChanged += OnLblAimNameShowToolTipChanged;
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

		public string AimName
		{
			get { return _aimName; }
			internal set
			{
				if (_aimName == value)
					return;

				_aimName = value;
				NotifyPropertyChanged("AimName");
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
				NotifyPropertyChanged("AimUid");
				NotifyPropertyChanged("IsLinkEnabled");
			}
		}

		public bool IsLinkEnabled
		{
			get { return !string.IsNullOrEmpty(_aimUid); }
			internal set { }
		}

		public string[] AnnatomicEntities
		{
			get { return _aeList; }
			set
			{
				if (_aeList == value)
					return;

				_aeList = value;
				UpdateFlowPanel(_flowPanelAe, _aeList);
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
				UpdateFlowPanel(_flowPanelIo, _ioList);
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
				NotifyPropertyChanged("AimName");
			}
		}

		private void UpdateFlowPanel(FlowLayoutPanel flowPanel, string[] listOfValues)
		{
			flowPanel.SuspendLayout();
			flowPanel.Controls.Clear();

			if (listOfValues != null)
			{
				foreach (var s in listOfValues)
				{
					var label = new Label();
					label.AutoEllipsis = true;
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
			_linkOpenImageAnnotation.Location = new Point(_linkOpenImageAnnotation.Location.X, _tableLayoutPanel.Location.Y + _tableLayoutPanel.Size.Height + 8);
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
