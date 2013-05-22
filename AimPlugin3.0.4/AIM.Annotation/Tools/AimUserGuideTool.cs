//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Diagnostics;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tools;

using AIM.Annotation.Configuration;

namespace AIM.Annotation.Tools
{
	[MenuAction("showAimUserGuide", "global-menus/MenuHelp/MenuAimUserGuide", "ShowOnlineAimUserGuide")]
	[GroupHint("showAimUserGuide", "Application.Help.AimUserGuide")]

	[ExtensionOf(typeof(DesktopToolExtensionPoint))]
	public class AimUserGuideTool : Tool<IDesktopToolContext>
	{
		public void ShowOnlineAimUserGuide()
		{
			Execute(AimSettings.Default.AimUserGuidePath, SR.AimUsersGuideNotFound);
		}

		private void Execute(string filename, string errorMessage)
		{
			var showMessageBox = string.IsNullOrEmpty(filename);
			if (!showMessageBox)
			{
				try
				{
					var info = new ProcessStartInfo();
					info.WorkingDirectory = Platform.InstallDirectory;
					info.FileName = filename;
					Process.Start(info);
				}
				catch (Exception e)
				{
					showMessageBox = true;
					Platform.Log(LogLevel.Warn, e, "Failed to launch '{0}'.", filename);
				}
			}

			if (showMessageBox)
				Context.DesktopWindow.ShowMessageBox(errorMessage, MessageBoxActions.Ok);
		}
	}
}
