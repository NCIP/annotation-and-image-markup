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
using System.Drawing;
using System.Windows.Forms;

namespace AIM.Annotation.View.WinForms
{
	internal class AimWinFormsUtil
	{
		// Calculates maximum required width of the dropdown portion for the ComboBox.
		// This is done in order not to cut off the longest dropdown item.
		public static int CalculateComboBoxDropdownWidth(ComboBox comboBox)
		{
			if (comboBox == null)
				return SystemInformation.VerticalScrollBarWidth;

			int scrollbarOffset = 0;

			if (comboBox.Items.Count > comboBox.MaxDropDownItems)
			{
				scrollbarOffset = SystemInformation.VerticalScrollBarWidth;
				try
				{
					scrollbarOffset += SystemInformation.HorizontalFocusThickness; // padding
				}
				catch (NotSupportedException)
				{
					scrollbarOffset += 2; // 2 pixels padding
				}
			}

			float maxWidth = 0.0f;
			using (System.Drawing.Graphics ds = comboBox.CreateGraphics())
			{
				foreach (object item in comboBox.Items)
				{
					maxWidth = Math.Max(maxWidth, ds.MeasureString(comboBox.GetItemText(item), comboBox.Font).Width);
				}
			}

			int newWidth = (int)decimal.Round((decimal)maxWidth, 0) + scrollbarOffset;

			//If the width is bigger than the screen, ensure
			//we stay within the bounds of the screen
			if (newWidth > Screen.GetWorkingArea(comboBox).Width)
			{
				newWidth = Screen.GetWorkingArea(comboBox).Width;
			}

			// Don't let dropdown area to be outside of the screen
			if (comboBox.Parent != null)
			{
				int screenWidth = Screen.FromControl(comboBox).Bounds.Width;
				Point pt = comboBox.Parent.PointToScreen(new Point(comboBox.Left + newWidth, comboBox.Bottom));
				if (pt.X > screenWidth)
					newWidth = Math.Max(comboBox.Bounds.Width, newWidth - (pt.X - screenWidth));
			}

			// Only change the width if the calculated width is larger that the current width
			return comboBox.Bounds.Width > newWidth ? comboBox.Bounds.Width : newWidth;
		}
	}
}
