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
				(this.LoginName.Length < 1 || this.UserName.Length < 1))
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
