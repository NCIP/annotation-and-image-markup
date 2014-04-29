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
					this.Modified = true;
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
					this.Modified = true;
					NotifyPropertyChanged("UseRandomDefaultMarkupColor");

					UpdateDisplayedImages(null);
				}
			}
		}

		public Color[] GetSavedColors()
		{
			HashSet<Color> savedColors = new HashSet<Color>();
			foreach (KeyValuePair<string, Color> loginNameMarkupColor in AimSettings.Default.LoginNameMarkupColors)
			{
				savedColors.Add(loginNameMarkupColor.Value);
			}

			Color[] colors = new Color[savedColors.Count];
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
			int i = 0;
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
				UserMarkupProperties oldUserMarkupProperties = _userMarkupPropertiesDictionary[loginName];

				_userMarkupPropertiesDictionary.Remove(loginName);

				this.Modified = true;
			}

			return newUserMarkupProperties;
		}

		public Color GetLoginNameMarkupColor(string loginName)
		{
			Color markupColor = _settings.DefaultMarkupColor;
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

				UserMarkupProperties markupProperties = _userMarkupPropertiesDictionary[loginName];
				_userMarkupPropertiesDictionary[loginName] = new UserMarkupProperties(markupProperties.OriginalColor, color, markupProperties.IsReadFromSettings, markupProperties.IsDisplayed);
			}
			else
			{
				_userMarkupPropertiesDictionary[loginName] = new UserMarkupProperties(color, color, true, false);
			}

			this.Modified = true;
		}

		public void SetDefaultLoginNameMarkupColor(string loginName)
		{
			loginName = (loginName ?? "").Trim().ToLower();

			Color color = _settings.GetAimGraphicDefaultColorForUser(loginName);
			this.SetLoginNameMarkupColor(loginName, color);
		}

		public void UpdateLoginName(string oldLoginName, string newLoginName)
		{
			Color color;

			oldLoginName = (oldLoginName ?? "").Trim().ToLower();
			if (_userMarkupPropertiesDictionary.ContainsKey(oldLoginName))
			{
				color = _userMarkupPropertiesDictionary[oldLoginName].Color;
				_userMarkupPropertiesDictionary.Remove(oldLoginName);
				this.Modified = true;
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

			// Preserve original values
			_settings = AimSettings.Default;
			_defaultMarkupColor = _settings.DefaultMarkupColor;
			_loginNameMarkupColorsOriginalSettings = new XmlSerializableStringToColorDictionary(_settings.LoginNameMarkupColors);
			_useRandomDefaultMarkupColor = _settings.UseRandomDefaultMarkupColor;

			InitUserMarkupProperties();
			_userMarkupPropertiesDictionary.ItemAdded += OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemChanged += OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemRemoved += OnUserMarkupPropertiesChanged;

			// Update color values to include default colors for displayed images
			_settings.LoginNameMarkupColors = GetNewUserColorSettings();
		}

		public override void Save()
		{
			_settings.LoginNameMarkupColors = GetNewUserColorSettings(false);
			_settings.Save();
			// Update with new default values
			_defaultMarkupColor = _settings.DefaultMarkupColor;
			_loginNameMarkupColorsOriginalSettings = new XmlSerializableStringToColorDictionary(_settings.LoginNameMarkupColors);
			_useRandomDefaultMarkupColor = _settings.UseRandomDefaultMarkupColor;

			_userMarkupPropertiesDictionary.ItemAdded -= OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemChanged -= OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.ItemRemoved -= OnUserMarkupPropertiesChanged;
			_userMarkupPropertiesDictionary.Clear();
		}

		/// <summary>
		/// Called by the host when the application component is being terminated.
		/// </summary>
		public override void Stop()
		{
			_settings.LoginNameMarkupColors = _loginNameMarkupColorsOriginalSettings; // this should reset dictionary to the last saved values
			_settings.DefaultMarkupColor = _defaultMarkupColor;
			_settings.UseRandomDefaultMarkupColor = _useRandomDefaultMarkupColor;
			UpdateDisplayedImages(null);
			_settings = null;
			base.Stop();
		}

		// Initializes dictionary of markup properties for each available (read from settings or displayed) user logins
		private void InitUserMarkupProperties()
		{
			_userMarkupPropertiesDictionary.Clear();

			Dictionary<string, Color> displayedUserColors = GetDisplayedUsersAndMarkupColors();

			foreach (KeyValuePair<string, Color> originalUserSetting in _loginNameMarkupColorsOriginalSettings)
			{
				if (displayedUserColors.ContainsKey(originalUserSetting.Key))
				{
					_userMarkupPropertiesDictionary[originalUserSetting.Key] = new UserMarkupProperties(displayedUserColors[originalUserSetting.Key], displayedUserColors[originalUserSetting.Key], true, true);
					displayedUserColors.Remove(originalUserSetting.Key);
				}
				else
					_userMarkupPropertiesDictionary[originalUserSetting.Key] = new UserMarkupProperties(originalUserSetting.Value, originalUserSetting.Value, true, false);
			}

			foreach (KeyValuePair<string, Color> displayedUserColor in displayedUserColors)
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
			XmlSerializableStringToColorDictionary newUserColorSettings = new XmlSerializableStringToColorDictionary();
			foreach (KeyValuePair<string, UserMarkupProperties> userMarkupProperty in _userMarkupPropertiesDictionary)
			{
				if (includeDisplayedDefaultColor)
				{
					if (userMarkupProperty.Value.IsDisplayed || userMarkupProperty.Value.IsReadFromSettings || userMarkupProperty.Value.HasColorChanges)
						newUserColorSettings[userMarkupProperty.Key] = userMarkupProperty.Value.Color;
				}
				else
				{
					// These are color values stored in AimSettings
					if (userMarkupProperty.Value.IsReadFromSettings || userMarkupProperty.Value.HasColorChanges ||
						(userMarkupProperty.Value.IsDisplayed && userMarkupProperty.Value.Color != this.DefaultMarkupColor))
						newUserColorSettings[userMarkupProperty.Key] = userMarkupProperty.Value.Color;
				}
			}

			return newUserColorSettings;
		}

		private void OnUserMarkupPropertiesChanged(object sender, DictionaryEventArgs<string, UserMarkupProperties> e)
		{
			// Trigger displayed colors update for the changed user login name
			_settings.LoginNameMarkupColors = this.GetNewUserColorSettings();
			if (!_userMarkupPropertiesDictionary.ContainsKey(e.Key))
				UpdateDisplayedImages(null);
			else if (_userMarkupPropertiesDictionary[e.Key].IsDisplayed)
				UpdateDisplayedImages(e.Key);
		}

		// Returns currently displayed annotations' colors and associated user names
		private static Dictionary<string, Color> GetDisplayedUsersAndMarkupColors()
		{
			Dictionary<string, Color> displayedUserColors = new Dictionary<string, Color>();

			IImageViewer imageViewer = ImageViewerComponent.GetAsImageViewer(Application.ActiveDesktopWindow.ActiveWorkspace);

			if (imageViewer != null)
			{
				foreach (ImageBox imageBox in imageViewer.PhysicalWorkspace.ImageBoxes)
				{
					foreach (Tile tile in imageBox.Tiles)
					{
						IOverlayGraphicsProvider graphicsProvider = tile.PresentationImage as IOverlayGraphicsProvider;
						if (graphicsProvider != null)
						{
							foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
							{
								AimGraphic aimGraphic = graphic as AimGraphic;
								if (aimGraphic != null)// && String.Equals(loginName, aimGraphic.UserLoginName, StringComparison.InvariantCultureIgnoreCase))
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

		// Forces re-draw of displayed images if they have AIMGraphic
		private static void UpdateDisplayedImages(string loginName)
		{
			foreach (DesktopWindow desktopWindow in Application.DesktopWindows)
			{
				foreach (Workspace workspace in desktopWindow.Workspaces)
				{
					IImageViewer imageViewer = ImageViewerComponent.GetAsImageViewer(workspace);

					if (imageViewer != null)
					{
						foreach (ImageBox imageBox in imageViewer.PhysicalWorkspace.ImageBoxes)
						{
							foreach (Tile tile in imageBox.Tiles)
							{
								IOverlayGraphicsProvider graphicsProvider = tile.PresentationImage as IOverlayGraphicsProvider;
								if (graphicsProvider != null)
								{
									foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
									{
										AimGraphic aimGraphic = graphic as AimGraphic;
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
