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
			if (LoginNameMarkupColors == null)
				LoginNameMarkupColors = new XmlSerializableStringToColorDictionary();

			if (Parameters == null)
				Parameters = new XmlSerializableStringDictionary();
		}

		// Actual annotation store folder on the user system
		public string ActualAnnotationStoreFolder
		{
			get
			{
				return this.StoreXmlInMyDocuments
						? System.IO.Path.Combine(System.Environment.GetFolderPath(System.Environment.SpecialFolder.MyDocuments), "AIM Annotations")
						: this.LocalAnnotationsFolder;
			}
		}

		// Folder where all annotation queues are stored
		public string AnnotationQueuesFolder
		{
			get { return System.IO.Path.Combine(this.ActualAnnotationStoreFolder, "queue"); }
		}

		public Color GetAimGraphicColorForUser(string username)
		{
			Color color;

			if (this.LoginNameMarkupColors.ContainsKey(username))
			{
				color = this.LoginNameMarkupColors[username];
			}
			else
			{
				color = this.GetAimGraphicDefaultColorForUser(username);
			}

			return color;
		}

		public Color GetAimGraphicDefaultColorForUser(string username)
		{
			Color color;

			if (this.UseRandomDefaultMarkupColor)
				color = CreateColorFromStringHash(username);
			else
				color = this.DefaultMarkupColor;

			return color;
		}

		/// <summary>
		/// Selects a random, non-red color based on the hashcode of a string
		/// </summary>
		/// <param name="stringValue">A string to be used as a seed for the random color</param>
		/// <returns>A random color based on the input string</returns>
		public static Color CreateColorFromStringHash(string stringValue)
		{
			Color color = Color.Yellow;

			if (!string.IsNullOrEmpty(stringValue))
			{
				// Build random vector representing rgb color based on username
				int randSeed = stringValue.GetHashCode();
				System.Random rand = new System.Random(randSeed);
				Vector3D colorVector = new Vector3D((float)rand.NextDouble(), (float)rand.NextDouble(), (float)rand.NextDouble());

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

				//Create color from vector
				color = Color.FromArgb(255, (int)(colorVector.X * 255), (int)(colorVector.Y * 255), (int)(colorVector.Z * 255));
			}

			return color;
		}
	}
}
