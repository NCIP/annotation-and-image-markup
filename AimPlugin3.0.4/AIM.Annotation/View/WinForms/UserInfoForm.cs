//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Windows.Forms;

namespace AIM.Annotation.View.WinForms
{
	public partial class FormUserInfo : Form
	{
		private bool _saveCalled;

		public FormUserInfo(string userName, string loginName, string roleInTrial, int numberWithinRoleInTrial)
		{
			InitializeComponent();

			_tboxUserName.Text = userName;
			_tboxLoginName.Text = loginName;
			foreach (string item in _cmbRoleInTrial.Items)
			{
				if (item == roleInTrial)
				{
					_cmbRoleInTrial.SelectedItem = item;
					break;
				}
			}
			// Select helper text if no selection is present
			if (_cmbRoleInTrial.SelectedIndex == -1)
				_cmbRoleInTrial.SelectedIndex = 0;
			_updownNumberWithinRoleInTrial.Value = numberWithinRoleInTrial;
		}

		public string UserName
		{
			get { return _tboxUserName.Text.Trim(); }
		}

		public string LoginName
		{
			get { return _tboxLoginName.Text.Trim(); }
		}

		public string RoleInTrial
		{
			get { return _cmbRoleInTrial.SelectedIndex < 1 ? null : _cmbRoleInTrial.SelectedItem.ToString(); }
		}

		public int NumberWithinRoleInTrial
		{
			get { return (int)_updownNumberWithinRoleInTrial.Value; }
		}

		private void FormUserInfo_FormClosing(object sender, FormClosingEventArgs e)
		{
			// Don't allow saving with missing values
			if (_saveCalled &&
				(LoginName.Length < 1 || UserName.Length < 1))
			{
				e.Cancel = true;
				_saveCalled = false;
			}
		}

		private void btnSave_Click(object sender, EventArgs e)
		{
			_saveCalled = true;
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			_saveCalled = false;
		}
	}
}
