#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

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

			var scrollbarOffset = 0;
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

			var maxWidth = 0.0f;
			using (var ds = comboBox.CreateGraphics())
			{
				foreach (var item in comboBox.Items)
				{
					maxWidth = Math.Max(maxWidth, ds.MeasureString(comboBox.GetItemText(item), comboBox.Font).Width);
				}
			}

			var newWidth = (int)decimal.Round((decimal)maxWidth, 0) + scrollbarOffset;
			//If the width is bigger than the screen, ensure
			//we stay within the bounds of the screen
			if (newWidth > Screen.GetWorkingArea(comboBox).Width)
				newWidth = Screen.GetWorkingArea(comboBox).Width;

			// Don't let dropdown area to be outside of the screen
			if (comboBox.Parent != null)
			{
				var screenWidth = Screen.FromControl(comboBox).Bounds.Width;
				var pt = comboBox.Parent.PointToScreen(new Point(comboBox.Left + newWidth, comboBox.Bottom));
				if (pt.X > screenWidth)
					newWidth = Math.Max(comboBox.Bounds.Width, newWidth - (pt.X - screenWidth));
			}

			// Only change the width if the calculated width is larger that the current width
			return comboBox.Bounds.Width > newWidth ? comboBox.Bounds.Width : newWidth;
		}
	}
}
