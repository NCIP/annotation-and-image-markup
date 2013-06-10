#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;

using ClearCanvas.Common;

namespace TCGA.View.WinForms
{
	[ExtensionOf(typeof(TcgaLoginDialogExtensionPoint))]
	public class TcgaLoginDialog : ITcgaLoginDialog
	{
		private readonly TcgaLoginForm _loginForm = new TcgaLoginForm();

		#region Implementation of IDisposable

		public void Dispose()
		{
		}

		#endregion

		#region Implementation of ITcgaLoginDialog

		public bool Show()
		{
			System.Windows.Forms.Application.EnableVisualStyles();

			return _loginForm.ShowDialog() == System.Windows.Forms.DialogResult.OK;
		}

		public string UserName
		{
			get { return _loginForm.UserName; }
			set { _loginForm.UserName = value; }
		}

		public string LoginName
		{
			get { return _loginForm.LoginName; }
			set { _loginForm.LoginName = value; }
		}

		public string RoleInTrial
		{
			get { return _loginForm.RoleInTrial; }
			set { _loginForm.RoleInTrial = value; }
		}

		public int NumberWithinRoleOfClinicalTrial
		{
			get { return _loginForm.NumberWithinRoleOfClinicalTrial; }
			set { _loginForm.NumberWithinRoleOfClinicalTrial = value; }
		}

		#endregion
	}
}
