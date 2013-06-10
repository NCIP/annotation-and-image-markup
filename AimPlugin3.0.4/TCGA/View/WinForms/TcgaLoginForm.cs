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
using System.Runtime.InteropServices;
using System.Windows.Forms;

using ClearCanvas.Desktop.View.WinForms;

namespace TCGA.View.WinForms
{
	public partial class TcgaLoginForm : Form
	{
		#region External Imports
		[DllImport("Gdi32.dll", EntryPoint="CreateRoundRectRgn")]
		private static extern IntPtr CreateRoundRectRgn
		(
			int nLeftRect, // x-coordinate of upper-left corner
			int nTopRect, // y-coordinate of upper-left corner
			int nRightRect, // x-coordinate of lower-right corner
			int nBottomRect, // y-coordinate of lower-right corner
			int nWidthEllipse, // height of ellipse
			int nHeightEllipse // width of ellipse
		);
		#endregion

		private Point _refPoint;

		public TcgaLoginForm()
		{
			// Need to explicitely dismiss the splash screen here, as the login dialog is shown before the desktop window, which is normally
			// responsible for dismissing it.
#if !MONO
			SplashScreenManager.DismissSplashScreen(this);
#endif

			InitializeComponent();

			// Make rounded corners
			Region = Region.FromHrgn(CreateRoundRectRgn(0, 0, Width - 10, Height - 10, 20, 20));

			BackColor = Color.FromArgb(255, 184, 228, 242);

			UpdateButtonStates();
		}

		public string UserName
		{
			get { return _txtUserName.Text; }
			set { _txtUserName.Text = value; }
		}

		public string LoginName
		{
			get { return _txtLoginName.Text; }
			set { _txtLoginName.Text = value; }
		}

		public string RoleInTrial
		{
			get { return _cmbRoleInTrial.SelectedIndex > 0 ? _cmbRoleInTrial.SelectedItem.ToString() : string.Empty; }
			set
			{
				foreach (var item in _cmbRoleInTrial.Items)
				{
					if (item.ToString() == value)
					{
						_cmbRoleInTrial.SelectedItem = item;
						return;
					}
				}

				if (_cmbRoleInTrial.Items.Count > 0)
					_cmbRoleInTrial.SelectedIndex = 0;
			}
		}

		public int NumberWithinRoleOfClinicalTrial
		{
			get { return (int)_upDownNumberWithinRoleOfClinicalTrial.Value; }
			set
			{
				if (value < _upDownNumberWithinRoleOfClinicalTrial.Minimum)
					_upDownNumberWithinRoleOfClinicalTrial.Value = _upDownNumberWithinRoleOfClinicalTrial.Minimum;
				else
				{
					_upDownNumberWithinRoleOfClinicalTrial.Value = value;
				}
			}
		}

		private void OnLoginFormLoad(object sender, System.EventArgs e)
		{
			_txtUserName.Select();
		}

		private void OnLoginButtonClick(object sender, System.EventArgs e)
		{
			DialogResult = DialogResult.OK;
		}

		private void OnCancelButtonClick(object sender, System.EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
		}

		private void UpdateButtonStates()
		{
			bool ok = !string.IsNullOrEmpty(_txtUserName.Text) && !string.IsNullOrEmpty(_txtLoginName.Text) &&
			          _cmbRoleInTrial.SelectedIndex > 0 && _upDownNumberWithinRoleOfClinicalTrial.Value >= 0;
			_btnLogin.Enabled = ok;
		}

		private void _txtUserName_TextChanged(object sender, System.EventArgs e)
		{
			UpdateButtonStates();
		}

		private void _txtLoginName_TextChanged(object sender, System.EventArgs e)
		{
			UpdateButtonStates();
		}

		private void _cmbRoleInTrial_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			UpdateButtonStates();
		}

		private void _upDownNumberWithinRoleOfClinicalTrial_ValueChanged(object sender, System.EventArgs e)
		{
			UpdateButtonStates();
		}

		private void TcgaLoginForm_MouseDown(object sender, MouseEventArgs e)
		{
			_refPoint = new Point(e.X, e.Y);
		}

		private void TcgaLoginForm_MouseMove(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				Left += (e.X - _refPoint.X);
				Top += (e.Y - _refPoint.Y);
			}
		}
	}
}
