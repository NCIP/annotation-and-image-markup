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
using System.Windows.Forms;

namespace AIM.Annotation.View.WinForms
{
	/// <summary>
	/// LinkLabel control to display tooltip when hovering over a part of the LinkLabel
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
			this.LinkArea = new LinkArea(0, 0); // no link by default

			//this.OverrideCursor = Cursors.Help;
		}

		[Category("Appearance"),
		 Description("ToolTip when hovering over the label"),
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
					this.LinkArea = new LinkArea(0, string.IsNullOrEmpty(_toolTipText) ? 0 : Math.Min(NUM_OF_TOOLTIP_CHAR, _toolTipText.Length));
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
			ShowToolTip = this.PointInLink(e.X, e.Y) != null;

			base.OnMouseMove(e);

			if (ShowToolTip)
				this.OverrideCursor = Cursors.Help;
		}

		// Remove focus rectangle
		protected override bool ShowFocusCues
		{
			get { return false; }
		}
	}
}
