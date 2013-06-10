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
using ClearCanvas.Desktop;

using AIM.Annotation.Configuration;

namespace TCGA
{
	[ExtensionPoint]
	public class TcgaLoginDialogExtensionPoint : ExtensionPoint<ITcgaLoginDialog>
	{
	}

	[ExtensionOf(typeof(SessionManagerExtensionPoint))]
	public class TcgaSessionManager : ISessionManager
	{
		#region Implementation of ISessionManager

		public bool InitiateSession()
		{
			try
			{
				return Login();
			}
			catch (Exception e)
			{
				Application.ShowMessageBox(e.Message, MessageBoxActions.Ok);
				return false;
			}
		}

		public void TerminateSession()
		{
		}

		#endregion

		private bool Login()
		{
			using(var loginDialog = (ITcgaLoginDialog)(new TcgaLoginDialogExtensionPoint()).CreateExtension())
			{
				loginDialog.UserName = AimSettings.Default.UserName;
				loginDialog.LoginName = AimSettings.Default.UserLoginName;
				loginDialog.RoleInTrial = AimSettings.Default.UserRoleInTrial;
				loginDialog.NumberWithinRoleOfClinicalTrial = AimSettings.Default.UserNumberWitinRoleOfClinicalTrial;

				if(loginDialog.Show())
				{
					AimSettings.Default.UserName = loginDialog.UserName;
					AimSettings.Default.UserLoginName = loginDialog.LoginName;
					AimSettings.Default.UserRoleInTrial = loginDialog.RoleInTrial;
					AimSettings.Default.UserNumberWitinRoleOfClinicalTrial = loginDialog.NumberWithinRoleOfClinicalTrial;
					AimSettings.Default.Save();

					return true;
				}
			}

			return false;
		}
	}
}
