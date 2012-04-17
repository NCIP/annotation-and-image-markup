#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

using System;
using System.Drawing;
using System.Collections.Generic;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Configuration;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;

using AIM.Annotation.Graphics;
using GeneralUtilities.Collections;

namespace AIM.Annotation.Configuration
{
	[ExtensionPoint]
	public sealed class AimMarkupColorComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView> { }

	[AssociateView(typeof(AimMarkupColorComponentViewExtensionPoint))]
	public class AimMarkupColorComponent : ConfigurationApplicationComponent
	{
		public static readonly string Path = "AIM/Markup";

		private AimSettings _settings;
		private Color _defaultMarkupColor;
		private XmlSerializableStringToColorDictionary _loginNameMarkupColorsOriginalSettings;
		private bool _useRandomDefaultMarkupColor;
		private readonly ObservableDictionary<string, UserMarkupProperties> _userMarkupPropertiesDictionary = new ObservableDictionary<string, UserMarkupProperties>();

		#region User Markup Properties class
		public class UserMarkupProperties
		{
			private readonly Color _originalColor;
			private readonly Color _newColor;
			private readonly bool _isDisplayed;
			private readonly bool _isReadFromSettings;

			public UserMarkupProperties(Color originalColor, Color newColor, bool isReadFromSettings, bool isDisplayed)
			{
				_originalColor = originalColor;
				_newColor = newColor;
				_isReadFromSettings = isReadFromSettings;
				_isDisplayed = isDisplayed;
			}

			public Color Color
			{
				get { return _newColor; }
			}

			public Color OriginalColor
			{
				get { return _originalColor; }
			}

			public bool IsReadFromSettings
			{
				get { return _isReadFromSettings; }
			}

			public bool IsDisplayed
			{
				get { return _isDisplayed; }
			}

			public bool HasColorChanges
			{
				get { return _originalColor != _newColor; }
			}
		}
		#endregion

		public Color DefaultMarkupColor
		{
			get { return _settings.DefaultMarkupColor; }
			set
			{
				if (_settings.DefaultMarkupColor != value)
				{
					_settings.DefaultMarkupColor = value;
					Modified = true;
					NotifyPropertyChanged("DefaultMarkupColor");

					UpdateDisplayedImages(null);
				}
			}
		}

		public bool UseRandomDefaultMarkupColor
		{
			get { return _settings.UseRandomDefaultMarkupColor; }
			set
			{
				if (_settings.UseRandomDefaultMarkupColor != value)
				{
					_settings.UseRandomDefaultMarkupColor = value;
					Modified = true;
					NotifyPropertyChanged("UseRandomDefaultMarkupColor");

					UpdateDisplayedImages(null);
				}
			}
		}

		public Color[] GetSavedColors()
		{
			var savedColors = new HashSet<Color>();
			foreach (var loginNameMarkupColor in AimSettings.Default.LoginNameMarkupColors)
			{
				savedColors.Add(loginNameMarkupColor.Value);
			}

			var colors = new Color[savedColors.Count];
			savedColors.CopyTo(colors);
			return colors;
		}

		public IDictionary<string, UserMarkupProperties> AvailableUserMarkupProperties
		{
			get { return _userMarkupPropertiesDictionary; }
		}

		public void AddLoginNameMarkupColor(out string loginName, out Color markupColor)
		{
			const string newuser = "newuser";
			var i = 0;
			while (_userMarkupPropertiesDictionary.ContainsKey(newuser + i))
				i++;
			loginName = newuser + i;
			markupColor = GetLoginNameMarkupColor(loginName);
			SetLoginNameMarkupColor(loginName, markupColor);
		}

		public UserMarkupProperties RemoveLoginNameMarkupColor(string loginName)
		{
			UserMarkupProperties newUserMarkupProperties = null;

			loginName = (loginName ?? "").ToLowerInvariant();
			if (_userMarkupPropertiesDictionary.ContainsKey(loginName))
			{
				var oldUserMarkupProperties = _userMarkupPropertiesDictionary[loginName];
				_userMarkupPropertiesDictionary.Remove(loginName);
				Modified = true;
			}

			return newUserMarkupProperties;
		}

		public Color GetLoginNameMarkupColor(string loginName)
		{
			var markupColor = _settings.DefaultMarkupColor;
			loginName = (loginName ?? "").Trim().ToLower();
			if (_userMarkupPropertiesDictionary.ContainsKey(loginName))
				markupColor = _userMarkupPropertiesDictionary[loginName].Color;
			else
			{
				if (_settings.UseRandomDefaultMarkupColor)
					markupColor = AimSettings.CreateColorFromStringHash(loginName);
			}

			return markupColor;
		}

		public void SetLoginNameMarkupColor(string loginName, Color color)
		{
			loginName = (loginName ?? "").Trim().ToLower();
			if (_userMarkupPropertiesDictionary.ContainsKey(loginName))
			{
				if (_userMarkupPropertiesDictionary[loginName].Color == color)
					return;

				var markupProperties = _userMarkupPropertiesDictionary[loginName];
				_userMarkupPropertiesDictionary[loginName] = new UserMarkupProperties(markupProperties.OriginalColor, color, markupProperties.IsReadFromSettings, markupProperties.IsDisplayed);
			}
			else
			{
				_userMarkupPropertiesDictionary[loginName] = new UserMarkupProperties(color, color, true, false);
			}

			Modified = true;
		}

		public void SetDefaultLoginNameMarkupColor(string loginName)
		{
			loginName = (loginName ?? "").Trim().ToLower();
			var color = _settings.GetAimGraphicDefaultColorForUser(loginName);
			SetLoginNameMarkupColor(loginName, color);
		}

		public void UpdateLoginName(string oldLoginName, string newLoginName)
		{
			Color color;
			oldLoginName = (oldLoginName ?? "").Trim().ToLower();
			if (_userMarkupPropertiesDictionary.ContainsKey(oldLoginName))
			{
				color = _userMarkupPropertiesDictionary[oldLoginName].Color;
				_userMarkupPropertiesDictionary.Remove(oldLoginName);
				Modified = true;
			}
			else
			{
				color = GetLoginNameMarkupColor(newLoginName);
			}
			SetLoginNameMarkupColor(newLoginName, color);
		}

		public override void Start()
		{
			base.Start();

			_settings = AimSettings.Default;
			_defaultMarkupColor = _settings.DefaultMarkupColor;
			_loginNameMarkupColorsOriginalSettings = new XmlSerializableStringToColorDictionary(_settings.LoginNameMarkupColors);
			_useRandomDefaultMarkupColor = _settings.UseRandomDefaultMarkupColor;

			InitUserMarkupProperties();
			_userMarkupPropertiesDictionary.ItemAdded += OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemChanged += OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemRemoved += OnUserMarkupPropertiesChanged;

			_settings.LoginNameMarkupColors = GetNewUserColorSettings();
		}

		public override void Save()
		{
			_settings.LoginNameMarkupColors = GetNewUserColorSettings(false);
			_settings.Save();
			_defaultMarkupColor = _settings.DefaultMarkupColor;
			_loginNameMarkupColorsOriginalSettings = new XmlSerializableStringToColorDictionary(_settings.LoginNameMarkupColors);
			_useRandomDefaultMarkupColor = _settings.UseRandomDefaultMarkupColor;

			_userMarkupPropertiesDictionary.ItemAdded -= OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemChanged -= OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemRemoved -= OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.Clear();
		}

		public override void Stop()
		{
			_settings.LoginNameMarkupColors = _loginNameMarkupColorsOriginalSettings;
			_settings.DefaultMarkupColor = _defaultMarkupColor;
			_settings.UseRandomDefaultMarkupColor = _useRandomDefaultMarkupColor;
			UpdateDisplayedImages(null);
			_settings = null;
			base.Stop();
		}

		private void InitUserMarkupProperties()
		{
			_userMarkupPropertiesDictionary.Clear();
			var displayedUserColors = GetDisplayedUsersAndMarkupColors();
			foreach (var originalUserSetting in _loginNameMarkupColorsOriginalSettings)
			{
				if (displayedUserColors.ContainsKey(originalUserSetting.Key))
				{
					_userMarkupPropertiesDictionary[originalUserSetting.Key] = new UserMarkupProperties(displayedUserColors[originalUserSetting.Key], displayedUserColors[originalUserSetting.Key], true, true);
					displayedUserColors.Remove(originalUserSetting.Key);
				}
				else
					_userMarkupPropertiesDictionary[originalUserSetting.Key] = new UserMarkupProperties(originalUserSetting.Value, originalUserSetting.Value, true, false);
			}
			foreach (var displayedUserColor in displayedUserColors)
			{
				_userMarkupPropertiesDictionary[displayedUserColor.Key] = new UserMarkupProperties(displayedUserColor.Value, displayedUserColor.Value, false, true);
			}
			displayedUserColors.Clear();
		}

		private XmlSerializableStringToColorDictionary GetNewUserColorSettings()
		{
			return GetNewUserColorSettings(true);
		}

		private XmlSerializableStringToColorDictionary GetNewUserColorSettings(bool includeDisplayedDefaultColor)
		{
			var newUserColorSettings = new XmlSerializableStringToColorDictionary();
			foreach (var userMarkupProperty in _userMarkupPropertiesDictionary)
			{
				if (includeDisplayedDefaultColor)
				{
					if (userMarkupProperty.Value.IsDisplayed || userMarkupProperty.Value.IsReadFromSettings || userMarkupProperty.Value.HasColorChanges)
						newUserColorSettings[userMarkupProperty.Key] = userMarkupProperty.Value.Color;
				}
				else
				{
					if (userMarkupProperty.Value.IsReadFromSettings || userMarkupProperty.Value.HasColorChanges ||
						(userMarkupProperty.Value.IsDisplayed && userMarkupProperty.Value.Color != DefaultMarkupColor))
						newUserColorSettings[userMarkupProperty.Key] = userMarkupProperty.Value.Color;
				}
			}

			return newUserColorSettings;
		}

		private void OnUserMarkupPropertiesChanged(object sender, DictionaryEventArgs<string, UserMarkupProperties> e)
		{
			_settings.LoginNameMarkupColors = GetNewUserColorSettings();
			if (!_userMarkupPropertiesDictionary.ContainsKey(e.Key))
				UpdateDisplayedImages(null);
			else if (_userMarkupPropertiesDictionary[e.Key].IsDisplayed)
				UpdateDisplayedImages(e.Key);
		}

		private static Dictionary<string, Color> GetDisplayedUsersAndMarkupColors()
		{
			var displayedUserColors = new Dictionary<string, Color>();
			var imageViewer = ImageViewerComponent.GetAsImageViewer(Application.ActiveDesktopWindow.ActiveWorkspace);
			if (imageViewer != null)
			{
				foreach (ImageBox imageBox in imageViewer.PhysicalWorkspace.ImageBoxes)
				{
					foreach (Tile tile in imageBox.Tiles)
					{
						var graphicsProvider = tile.PresentationImage as IOverlayGraphicsProvider;
						if (graphicsProvider != null)
						{
							foreach (var graphic in graphicsProvider.OverlayGraphics)
							{
								var aimGraphic = graphic as AimGraphic;
								if (aimGraphic != null)
								{
									if (!displayedUserColors.ContainsKey(aimGraphic.UserLoginName))
										displayedUserColors[aimGraphic.UserLoginName] = aimGraphic.Color;
								}
							}
						}
					}
				}
			}
			return displayedUserColors;
		}

		private static void UpdateDisplayedImages(string loginName)
		{
			foreach (var desktopWindow in Application.DesktopWindows)
			{
				foreach (var workspace in desktopWindow.Workspaces)
				{
					var imageViewer = ImageViewerComponent.GetAsImageViewer(workspace);
					if (imageViewer != null)
					{
						foreach (ImageBox imageBox in imageViewer.PhysicalWorkspace.ImageBoxes)
						{
							foreach (Tile tile in imageBox.Tiles)
							{
								var graphicsProvider = tile.PresentationImage as IOverlayGraphicsProvider;
								if (graphicsProvider != null)
								{
									foreach (var graphic in graphicsProvider.OverlayGraphics)
									{
										var aimGraphic = graphic as AimGraphic;
										if (aimGraphic != null &&
											(string.IsNullOrEmpty(loginName) || string.Equals(loginName, aimGraphic.UserLoginName, StringComparison.InvariantCultureIgnoreCase)))
										{
											tile.PresentationImage.Draw();
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
