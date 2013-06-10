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
