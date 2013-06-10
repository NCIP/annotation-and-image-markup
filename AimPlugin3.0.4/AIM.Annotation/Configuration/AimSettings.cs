#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L


#endregion

using System.Configuration;
using System.Drawing;

using ClearCanvas.Desktop;
using ClearCanvas.ImageViewer.Mathematics;
using GeneralUtilities.Collections;

namespace AIM.Annotation.Configuration
{
	[SettingsGroupDescription("AIM Settings")]
	[SettingsProvider(typeof(ClearCanvas.Common.Configuration.StandardSettingsProvider))]
	public sealed partial class AimSettings
	{
		private AimSettings()
		{
			ApplicationSettingsRegistry.Instance.RegisterInstance(this);
            if (LoginNameMarkupColors == null)
                LoginNameMarkupColors = new XmlSerializableStringToColorDictionary();

			if (Parameters == null)
				Parameters = new XmlSerializableStringDictionary();
		}

		public string ActualAnnotationStoreFolder
		{
			get
			{
				return StoreXmlInMyDocuments
				       	? System.IO.Path.Combine(System.Environment.GetFolderPath(System.Environment.SpecialFolder.MyDocuments), "AIM Annotations")
				       	: LocalAnnotationsFolder;
			}
		}

		public string AnnotationQueuesFolder
		{
			get { return System.IO.Path.Combine(ActualAnnotationStoreFolder, "queue"); }
		}

		public Color GetAimGraphicColorForUser(string username)
		{
			Color color;
			if (LoginNameMarkupColors.ContainsKey(username))
			{
				color = LoginNameMarkupColors[username];
			}
			else
			{
				color = GetAimGraphicDefaultColorForUser(username);
			}

			return color;
		}

		public Color GetAimGraphicDefaultColorForUser(string username)
		{
			Color color;
			if (UseRandomDefaultMarkupColor)
				color = CreateColorFromStringHash(username);
			else
				color = DefaultMarkupColor;

			return color;
		}

		/// <summary>
		/// Selects a random, non-red color based on the hashcode of a string
		/// </summary>
		/// <param name="stringValue">A string to be used as a seed for the random color</param>
		/// <returns>A random color based on the input string</returns>
		public static Color CreateColorFromStringHash(string stringValue)
		{
			var color = Color.Yellow;
			if (!string.IsNullOrEmpty(stringValue))
			{
				// Build random vector representing rgb color based on username
				var randSeed = stringValue.GetHashCode();
				var rand = new System.Random(randSeed);
				var colorVector = new Vector3D((float)rand.NextDouble(), (float)rand.NextDouble(), (float)rand.NextDouble());

				// Keep the color (vector) from being too close to red (x) so it doesn't conflict with the selection color
				if (colorVector.Y > colorVector.Z)
				{
					if (colorVector.X > colorVector.Y)
						colorVector = new Vector3D(colorVector.Z, colorVector.Y, colorVector.Z);
				}
				else if (colorVector.Z > colorVector.Y)
				{
					if (colorVector.X > colorVector.Z)
						colorVector = new Vector3D(colorVector.Y, colorVector.Y, colorVector.Z);
				}

				// Make sure color isn't too dark
				if (colorVector.Magnitude < 1f)
					colorVector *= (1f / colorVector.Magnitude);

				// Make sure color components stay within bounds
				if (colorVector.X > 1)
					colorVector = new Vector3D(1f, colorVector.Y, colorVector.Z);
				if (colorVector.Y > 1)
					colorVector = new Vector3D(colorVector.X, 1f, colorVector.Z);
				if (colorVector.Z > 1)
					colorVector = new Vector3D(colorVector.X, colorVector.Y, 1f);

				color = Color.FromArgb(255, (int)(colorVector.X * 255), (int)(colorVector.Y * 255), (int)(colorVector.Z * 255));
			}

			return color;
		}
	}
}
