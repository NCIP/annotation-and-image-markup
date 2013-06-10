#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace AIM.Annotation.View.WinForms
{
	/// <summary>
	/// LinkLabel control to display tooltip when hoovering over a part of the LinkLabel
	/// </summary>
	public class ToolTipLinkLabel : LinkLabel
	{
		private const int NUM_OF_TOOLTIP_CHAR = 3;

		private string _toolTipText;
		private bool _showToolTip;

		public event EventHandler ToolTipTextChanged;
		public event EventHandler ShowToolTipChanged;

		public ToolTipLinkLabel()
		{
			LinkArea = new LinkArea(0, 0);
		}

		[Category("Appearance"),
		 Description("ToolTip when hoovering over the label"),
		 Bindable(true)]
		public string ToolTipText
		{
			get { return _toolTipText; }
			set
			{
				if (_toolTipText != value)
				{
					_toolTipText = value;
					// Set link area to be at most NUM_OF_TOOLTIP_CHAR chars
					LinkArea = new LinkArea(0, string.IsNullOrEmpty(_toolTipText) ? 0 : Math.Min(NUM_OF_TOOLTIP_CHAR, _toolTipText.Length));
					if (ToolTipTextChanged != null)
						ToolTipTextChanged(this, EventArgs.Empty);
				}
			}
		}

		[Category("Appearance"),
		 Description("indicates if ToolTip should be shown"),
		 Bindable(true)]
		public bool ShowToolTip
		{
			get { return _showToolTip; }
			set
			{
				if (_showToolTip != value)
				{
					_showToolTip = value;
					if (ShowToolTipChanged != null)
						ShowToolTipChanged(this, EventArgs.Empty);
				}
			}
		}

		protected override void OnMouseMove(MouseEventArgs e)
		{
			ShowToolTip = PointInLink(e.X, e.Y) != null;

			base.OnMouseMove(e);

			if (ShowToolTip)
				OverrideCursor = Cursors.Help;
		}

		// Remove focus rect
		protected override bool ShowFocusCues
		{
			get { return false; }
		}
	}
}
