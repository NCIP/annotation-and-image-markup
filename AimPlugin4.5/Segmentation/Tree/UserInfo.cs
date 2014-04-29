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
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using ClearCanvas.Common;

namespace Segmentation.Tree
{
	/// <summary>
	/// Represents a user's name and login 
	/// </summary>
	public class UserInfo
	{
		/// <summary>
		/// Gets or sets the user's name
		/// </summary>
		[DataMember]
		public string Name { get; set; }

		/// <summary>
		/// Gets or sets the user's login name
		/// </summary>
		[DataMember]
		public string LoginName { get; set; }

		public static System.Drawing.Color DefaultGraphicColor
		{
			get { return System.Drawing.Color.Yellow; }
		}

		/// <summary>
		/// Gets <see cref="UserInfo"/> for the currently logged in user
		/// </summary>
		/// <returns><see cref="UserInfo"/> object with values for the currently logged in user or null</returns>
		public static UserInfo GetCurrentUserInfo()
		{
			try
			{
				var aimAssembly = PluginManager.Instance.Plugins.FirstOrDefault(item => item.Assembly.Name == "AIM.Annotation");
				if (aimAssembly != null)
				{
					var aimSettingsType = aimAssembly.Assembly.Resolve().GetType("AIM.Annotation.Configuration.AimSettings");
					if (aimSettingsType != null)
					{
						var aimDefaultSettingsProp = aimSettingsType.GetProperty("Default", BindingFlags.Public | BindingFlags.Static | BindingFlags.FlattenHierarchy);
						var userNameProp = aimSettingsType.GetProperty("UserName", BindingFlags.Instance | BindingFlags.Public);
						var userLoginNameProp = aimSettingsType.GetProperty("UserLoginName", BindingFlags.Instance | BindingFlags.Public);

						if (aimDefaultSettingsProp != null)
						{
							var aimSettings = aimDefaultSettingsProp.GetValue(null, null);
							if (aimSettings != null)
							{
								var userName = userNameProp == null ? null : userNameProp.GetValue(aimSettings, null).ToString();
								var userLoginName = userLoginNameProp == null ? null : userLoginNameProp.GetValue(aimSettings, null).ToString();
								if (!string.IsNullOrEmpty(userName) && !string.IsNullOrEmpty(userLoginName))
									return new UserInfo { Name = userName, LoginName = userLoginName };
							}
						}
					}
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Error getting current User Info via reflection");
			}

			return null;
		}

		/// <summary>
		/// Gets specified user color for new graphics or default value
		/// </summary>
		/// <param name="userLoginName">User login name to get the graphic's color for or null to get the color for the currently logged in user</param>
		/// <returns>specified graphic's color for the user or default color value</returns>
		public static System.Drawing.Color GetGraphicColorForUser(string userLoginName = null)
		{
			try
			{
				var aimAssembly = PluginManager.Instance.Plugins.FirstOrDefault(item => item.Assembly.Name == "AIM.Annotation");
				if (aimAssembly != null)
				{
					var aimSettingsType = aimAssembly.Assembly.Resolve().GetType("AIM.Annotation.Configuration.AimSettings");
					if (aimSettingsType != null)
					{
						var aimDefaultSettingsProp = aimSettingsType.GetProperty("Default", BindingFlags.Public | BindingFlags.Static | BindingFlags.FlattenHierarchy);
						if (aimDefaultSettingsProp != null)
						{
							var aimSettings = aimDefaultSettingsProp.GetValue(null, null);
							if (aimSettings != null)
							{
								// Get current UserLoginName
								if (userLoginName == null)
								{
									var userLoginNameProp = aimSettingsType.GetProperty("UserLoginName", BindingFlags.Instance | BindingFlags.Public);
									if (userLoginNameProp != null)
										userLoginName = userLoginNameProp.GetValue(aimSettings, null).ToString();
								}
								var getAimGraphicColorForUserMethod = aimSettingsType.GetMethod("GetAimGraphicColorForUser", BindingFlags.Instance | BindingFlags.Public);
								if (getAimGraphicColorForUserMethod != null)
									return (System.Drawing.Color)getAimGraphicColorForUserMethod.Invoke(aimSettings, new[] { (object)userLoginName });
							}
						}
					}
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Error getting graphic color for userLoginName ({0}) via reflection", userLoginName);
			}

			return DefaultGraphicColor;
		}
	}
}
