#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

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
		private event EventHandler<ShowAimAnnotationEventArg> _showImageClicked;

		public AimDetailsListControl()
		{
			InitializeComponent();
		}

		private List<aim_dotnet.Annotation> _availableAnnotations = new List<aim_dotnet.Annotation>();

		public List<aim_dotnet.Annotation> AvailableAnnotations
		{
			get { return null; }
			set
			{
				if (value == null || value.Count == 0)
					return;

				if (_availableAnnotations.Count == value.Count)
				{
					var same = true;
					for (var j = 0; j < value.Count; j++)
					{
						if (_availableAnnotations[j] != value[j])
						{
							same = false;
							break;
						}
					}
					if (same)
						return;
				}

				_availableAnnotations = new List<aim_dotnet.Annotation>(value.ToArray());

				SuspendLayout();
				_mainPanel.SuspendLayout();
				_mainPanel.Controls.Clear();

				var tableLayoutPanel = new TableLayoutPanel();
				tableLayoutPanel.AutoSize = true;
				tableLayoutPanel.AutoSizeMode = AutoSizeMode.GrowAndShrink;
				tableLayoutPanel.Dock = DockStyle.Top;
				_mainPanel.Controls.Add(tableLayoutPanel);
				tableLayoutPanel.CellBorderStyle = TableLayoutPanelCellBorderStyle.Inset;
				var i = 0;
				foreach (var annotation in value)
				{
					tableLayoutPanel.RowStyles.Add(new RowStyle());
					var control = AddDetailsControl();
					control.AimName = annotation.Name;
					control.AimUid = annotation.UniqueIdentifier;
					var aeList = new List<string>();
					if (annotation.AnatomyEntityCollection != null)
						CollectionUtils.ForEach(annotation.AnatomyEntityCollection, ae => aeList.Add(ae.CodeMeaning));
					var ioList = new List<string>();
					if (annotation.ImagingObservationCollection != null)
						CollectionUtils.ForEach(annotation.ImagingObservationCollection, io => ioList.Add(io.CodeMeaning));
					control.AnnatomicEntities = aeList.ToArray();
					control.ImagingObservations = ioList.ToArray();
					control.ToolTipText = ToolTipTextFromAimAnnotation(annotation);
					tableLayoutPanel.Controls.Add(control, 0, i);
					i++;
				}
				ResumeLayout(false);
				_mainPanel.ResumeLayout();
				PerformLayout();
			}
		}

		private string ToolTipTextFromAimAnnotation(aim_dotnet.Annotation annotation)
		{
			var toolTipText = String.Empty;
			toolTipText += annotation.Name + "\n";
			toolTipText += annotation.DateTime.ToString() + "\n";
			toolTipText += annotation.CodeValue + "\n";
			toolTipText += annotation.CodeMeaning += "\n";
			toolTipText += annotation.Comment;
			
			return toolTipText;
		}

		public aim_dotnet.Annotation SelectedAnnotation
		{
			get { return null; }
			set
			{
				foreach (var aimDetailsControl in AimDetailsControls)
				{
					aimDetailsControl.IsAnnotationSelected = value == null ? false : aimDetailsControl.AimUid == value.UniqueIdentifier;
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

		internal event EventHandler<ShowAimAnnotationEventArg> ShowImageClicked
		{
			add { _showImageClicked += value; }
			remove { _showImageClicked -= value; }
		}

		private AimDetailsControl AddDetailsControl()
		{
			var aimShortDetailsControl = new AimDetailsControl();
			aimShortDetailsControl.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			aimShortDetailsControl.AutoSize = true;
			aimShortDetailsControl.AutoSizeMode = AutoSizeMode.GrowAndShrink;
			aimShortDetailsControl.BackColor = SystemColors.Control;
			aimShortDetailsControl.Location = new Point(0, 0);
			aimShortDetailsControl.ShowAimAnnotationClicked += OnShowAimAnnotationClicked;

			return aimShortDetailsControl;
		}

		private void OnShowAimAnnotationClicked(object sender, ShowAimAnnotationEventArg e)
		{
			EventsHelper.Fire(_showImageClicked, this, new ShowAimAnnotationEventArg(e.AimUid));
		}

		private void OnPanelClientSizeChanged(object sender, EventArgs e)
		{
			_mainPanel.SuspendLayout();

			foreach (var control in AimDetailsControls)
				control.Width = control.Parent.ClientSize.Width;

			_mainPanel.ResumeLayout(true);
			_mainPanel.Update();
		}
	}
}
