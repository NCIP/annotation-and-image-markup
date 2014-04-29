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
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.AimManager.Aim3
{
	/// <summary>
	/// Formats Annotation into a HTML page for display in the Annotation Details control
	/// </summary>
	internal class AimHtmlFormatter
	{
		private static string AimHtmlDoc = "";
		private static string PlusImagePathName;
		private static string MinusImagePathName;

		private int _aeCount;
		private int _aecCount;
		private int _aecsCount;
		private int _ioCount;
		private int _iocCount;
		private int _iocsCount;
		private int _charqCount;
		private int _charqsCount;

		//internal static string GetAimHtml(aim_dotnet.Annotation annotation)
		internal static string GetAimHtml(Aim3AnnotationInstance annotationInstance)
		{
			var annotation = annotationInstance == null ? null : annotationInstance.AimAnnotation;

			if (annotation == null)
				return GetEmptyHtml();

			switch (annotation.AnnotationKind)
			{
				case aim_dotnet.AnnotationKind.AK_ImageAnnotation:
					return GetImageAnnotationHtml(annotation as aim_dotnet.ImageAnnotation);
				case aim_dotnet.AnnotationKind.AK_AnnotationOfAnnotation:
					return GetAnnotationOfAnnotationHtml(annotation as aim_dotnet.AnnotationOfAnnotation);
			}

			Platform.Log(LogLevel.Error, "Annotation Display Formatting (HTML): unknown annotation type");
			Debug.Assert(false, "Uknown Annotation Type");
			return "Unknown Annotation Type";
		}

		private static string GetImageAnnotationHtml(aim_dotnet.ImageAnnotation imageAnnotation)
		{
			StringBuilder sb = new StringBuilder();
			AimHtmlFormatter htmlFormatter = new AimHtmlFormatter();

			Color ctrlColor = Color.FromKnownColor(KnownColor.Control);
			Color fontColor = Color.FromKnownColor(KnownColor.WindowText);

			sb.Append(HtmlDocHeader);
			sb.AppendFormat("<body style=\"background-color: #{0}{1}{2};\" onload=\"setupPaths(['{3}', '{4}'])\">", 
				ctrlColor.R.ToString("X2"), ctrlColor.G.ToString("X2"), ctrlColor.B.ToString("X2"),
				MinusImagePathName, PlusImagePathName);
			sb.Append("<div id=\"main_content\">");
			sb.AppendFormat("<div><b>Name: {0}</b></div>", imageAnnotation.Name);
			sb.AppendFormat("<div>Number of Markups: {0}</div>", imageAnnotation.GeometricShapeCollection == null ? 0 : imageAnnotation.GeometricShapeCollection.Count(geoShape => geoShape != null));
			if (imageAnnotation.User != null)
				sb.AppendFormat("<div>Created by: {0}</div>", imageAnnotation.User.Name);
			sb.Append(htmlFormatter.GetAnatomicEntitiesHtml(imageAnnotation.AnatomyEntityCollection));
			sb.Append(htmlFormatter.GetImagingObservationHtml(imageAnnotation.ImagingObservationCollection));
			// TODO - append other sections
			sb.Append("</div>");
			sb.Append("</body>");
			sb.Append("</html>");

			return sb.ToString();
		}

		private static string GetAnnotationOfAnnotationHtml(aim_dotnet.AnnotationOfAnnotation annotationOfAnnotation)
		{
			throw new NotImplementedException();
		}

		private static string GetEmptyHtml()
		{
			StringBuilder sb = new StringBuilder();

			Color ctrlColor = Color.FromKnownColor(KnownColor.Control);
			Color fontColor = Color.FromKnownColor(KnownColor.WindowText);

			sb.Append(HtmlDocHeader);
			sb.AppendFormat("<body style=\"background-color: #{0}{1}{2};\">", 
				ctrlColor.R.ToString("X2"), ctrlColor.G.ToString("X2"), ctrlColor.B.ToString("X2"));
			//sb.AppendFormat("{0}", DateTime.Now.ToLongTimeString());
			sb.Append("</body>");
			sb.Append("</html>");

			return sb.ToString();
			
		}

		// Returns the start of HTML document, upto and including the opening <body> tag.
		// It should contain all styles and javascript for the page
		private static string HtmlDocHeader
		{
			get
			{
				if (string.IsNullOrEmpty(AimHtmlDoc))
				{
					lock (AimHtmlDoc)
					{
						if (string.IsNullOrEmpty(AimHtmlDoc))
						{
							ResourceResolver resolver = new ResourceResolver(typeof(AimHtmlFormatter).Assembly);
							try
							{
								using (Stream stream = resolver.OpenResource("Tools.AimHtmlDoc.html"))
								{
									using (StreamReader reader = new StreamReader(stream))
									{
										AimHtmlDoc = reader.ReadToEnd();
									}
								}

								using (Stream stream = resolver.OpenResource("Tools.minus_13x13.gif"))
								{
									using (System.Drawing.Image img = System.Drawing.Image.FromStream(stream))
									{
										MinusImagePathName = Path.GetTempFileName().Replace("\\", "/");
										img.Save(MinusImagePathName, System.Drawing.Imaging.ImageFormat.Gif);
									}
								}

								using (Stream stream = resolver.OpenResource("Tools.plus_13x13.gif"))
								{
									using (System.Drawing.Image img = System.Drawing.Image.FromStream(stream))
									{
										PlusImagePathName = Path.GetTempFileName().Replace("\\", "/");
										img.Save(PlusImagePathName, System.Drawing.Imaging.ImageFormat.Gif);
									}
								}
							}
							catch(Exception ex)
							{
								Platform.Log(LogLevel.Error, ex);
							}
						}
					}
				}

				return string.IsNullOrEmpty(AimHtmlDoc) ? "<html><body>" : AimHtmlDoc;
			}
		}

		private string GetAnatomicEntitiesHtml(List<aim_dotnet.AnatomicEntity> anatomicEntities)
		{
			StringBuilder sb = new StringBuilder();
			if (anatomicEntities != null)
			{
				foreach (aim_dotnet.AnatomicEntity anatomicEntity in anatomicEntities)
				{
					sb.Append(GetExpandableItemHtml(
						anatomicEntity.CodeMeaning,
						null,
						"ae_header",
						null,
						"ae_content",
						"ae",
						_aeCount++,
						GetAnatomicEntityCharacteristicsHtml(anatomicEntity.AnatomicEntityCharacteristicCollection)));
				}
			}
			return GetExpandableItemHtml(
				"Anatomic Entities",
				string.Format("({0})", anatomicEntities == null ? 0 : anatomicEntities.Count),
				"aes_header",
				"aes_summary",
				"aes_content",
				"aes",
				0,
				sb.ToString());
		}

		private string GetAnatomicEntityCharacteristicsHtml(List<aim_dotnet.AnatomicEntityCharacteristic> aeCharacteristics)
		{
			StringBuilder sb = new StringBuilder();
			if (aeCharacteristics != null)
			{
				foreach (aim_dotnet.AnatomicEntityCharacteristic aeCharacteristic in aeCharacteristics)
				{
					sb.Append(GetExpandableItemHtml(
						aeCharacteristic.CodeMeaning,
						null,
						"aec_header",
						null,
						"aec_content",
						"aec",
						_aecCount++,
						GetCharacteristicQuantificationsHtml(aeCharacteristic.CharacteristicQuantificationCollection)));
				}
			}
			return GetExpandableItemHtml(
				"Anatomic Entity Characteristics",
				string.Format("({0})", aeCharacteristics == null ? 0 : aeCharacteristics.Count),
				"aecs_header",
				"aecs_summary",
				"aecs_content",
				"aecs",
				_aecsCount++,
				sb.ToString());
		}

		private string GetImagingObservationHtml(List<aim_dotnet.ImagingObservation> imagingObservations)
		{
			StringBuilder sb = new StringBuilder();
			if (imagingObservations != null)
			{
				foreach (aim_dotnet.ImagingObservation imagingObservation in imagingObservations)
				{
					sb.Append(GetExpandableItemHtml(
						imagingObservation.CodeMeaning,
						null,
						"io_header",
						null,
						"io_content",
						"io",
						_ioCount++,
						GetImagingObservationCharacteristicsHtml(imagingObservation.ImagingObservationCharacteristicCollection)));
				}
			}
			return GetExpandableItemHtml(
				"Imaging Observations",
				string.Format("({0})", imagingObservations == null ? 0 : imagingObservations.Count),
				"ios_header",
				"ios_summary",
				"ios_content",
				"ios",
				0,
				sb.ToString());
		}

		private string GetImagingObservationCharacteristicsHtml(List<aim_dotnet.ImagingObservationCharacteristic> ioCharacteristics)
		{
			StringBuilder sb = new StringBuilder();
			if (ioCharacteristics != null)
			{
				foreach (aim_dotnet.ImagingObservationCharacteristic ioCharacteristic in ioCharacteristics)
				{
					sb.Append(GetExpandableItemHtml(
						ioCharacteristic.CodeMeaning,
						null,
						"ioc_header",
						null,
						"ioc_content",
						"ioc",
						_iocCount++,
						GetCharacteristicQuantificationsHtml(ioCharacteristic.CharacteristicQuantificationCollection)));
				}
			}
			return GetExpandableItemHtml(
				"Imaging Observation Characteristics",
				string.Format("({0})", ioCharacteristics == null ? 0 : ioCharacteristics.Count),
				"iocs_header",
				"iocs_summary",
				"iocs_content",
				"iocs",
				_iocsCount++,
				sb.ToString());
		}

		private string GetCharacteristicQuantificationsHtml(List<aim_dotnet.ICharacteristicQuantification> characteristicQuantificationCollection)
		{
			StringBuilder sb = new StringBuilder();
			if (characteristicQuantificationCollection != null)
			{
				foreach (aim_dotnet.ICharacteristicQuantification characteristicQuantification in characteristicQuantificationCollection)
				{
					sb.Append(GetExpandableItemHtml(
						characteristicQuantification.Name,
						null,
						"charq_header",
						null,
						"charq_content",
						"charq",
						_charqCount++,
						GetCharacteristicQuantificationHtml(characteristicQuantification)));
				}
			}
			return GetExpandableItemHtml(
				"Characteristic Quantifications",
				string.Format("({0})", characteristicQuantificationCollection == null ? 0 : characteristicQuantificationCollection.Count),
				"charqs_header",
				"charqs_summary",
				"charqs_content",
				"charqs",
				_charqsCount++,
				sb.ToString());
		}

		private string GetCharacteristicQuantificationHtml(aim_dotnet.ICharacteristicQuantification characteristicQuantification)
		{
			if (characteristicQuantification == null)
				return "";

			switch (characteristicQuantification.QuantificationType)
			{
				case aim_dotnet.CharacteristicQuantificationType.Numerical:
					aim_dotnet.Numerical numerical = (aim_dotnet.Numerical) characteristicQuantification;
					return numerical.Operator == aim_dotnet.ComparisonOperatorIdentifier.InvalidComparisonOperator ||
					       numerical.Operator == aim_dotnet.ComparisonOperatorIdentifier.None
					       	? string.Format("{0} {1}", numerical.Value, numerical.UcumString)
					       	: string.Format("{0} {1} {2}", OperatorToString(numerical.Operator, true), numerical.Value, numerical.UcumString);
				case aim_dotnet.CharacteristicQuantificationType.Quantile:
					aim_dotnet.Quantile quantile = (aim_dotnet.Quantile) characteristicQuantification;
					return string.Format("Quantile [{0}]", quantile.Bin);
				case aim_dotnet.CharacteristicQuantificationType.NonQuantifiable:
					aim_dotnet.NonQuantifiable nonQuantifiable = (aim_dotnet.NonQuantifiable) characteristicQuantification;
					return nonQuantifiable.CodeMeaning ?? "";
				case aim_dotnet.CharacteristicQuantificationType.Scale:
					aim_dotnet.Scale scale = (aim_dotnet.Scale) characteristicQuantification;
					return scale.Value ?? "";
				case aim_dotnet.CharacteristicQuantificationType.Interval:
					aim_dotnet.Interval interval = (aim_dotnet.Interval) characteristicQuantification;
					{
						string left = CombineOperatorAndValue(interval.MinOperator, interval.MinValue == double.MinValue ? "" : interval.MinValue.ToString(), true);
						string right = CombineOperatorAndValue(interval.MaxOperator, interval.MaxValue == double.MaxValue ? "" : interval.MaxValue.ToString(), string.IsNullOrEmpty(left));

						StringBuilder sb = new StringBuilder();
						sb.Append(left);
						if (!string.IsNullOrEmpty(left) && !string.IsNullOrEmpty(right))
							sb.Append(" and ");
						sb.Append(right);
						return sb.ToString();
					}
				default:
					Debug.Assert(false, "Unknown characteristic quantification type");
					break;
			}
			return "";
		}

		private string GetExpandableItemHtml(string headerText, string headerSummary, string headerClass, string headerSummaryClass,
			string contentClass, string idPrefix, int idCounter, string contentHtml)
		{
			if (string.IsNullOrEmpty(headerText) && string.IsNullOrEmpty(headerSummary) && 
				string.IsNullOrEmpty(headerClass) && string.IsNullOrEmpty(contentClass) && string.IsNullOrEmpty(contentHtml))
				return string.Empty;

			StringBuilder sb = new StringBuilder();

			bool hasContentData = !string.IsNullOrEmpty(contentHtml);
			bool hasIdPrefix = !string.IsNullOrEmpty(idPrefix);
			
			// Header
			sb.Append("<div");
			if(hasIdPrefix)
				sb.AppendFormat(" id=\"{0}{1}_header\"", idPrefix, idCounter);
			if (!string.IsNullOrEmpty(headerClass))
				sb.AppendFormat(" class=\"{0}\"", headerClass);
			sb.Append(">");

			// Make header expandable only when content will have an ID and there is anything in the header
			if(hasContentData && hasIdPrefix && (!string.IsNullOrEmpty(headerText) || !string.IsNullOrEmpty(headerSummary)))
				sb.AppendFormat(
					"<a><img class=\"expando\" src=\"{0}\" alt=\"-\" onmousedown=\"toggleDiv(this, '{1}{2}_content');\" title=\"Toggle\" /></a>",
					MinusImagePathName, idPrefix, idCounter);
			if (!string.IsNullOrEmpty(headerText))
				sb.Append(headerText);

			if (!string.IsNullOrEmpty(headerSummary))
			{
				sb.Append(" <span");
				if (!string.IsNullOrEmpty(headerSummaryClass))
					sb.AppendFormat(" class=\"{0}\"", headerSummaryClass);
				sb.AppendFormat(">{0}</span>", headerSummary);
			}
			sb.Append("</div>"); // end of header

			// Content
			if (hasContentData)
			{
				sb.AppendFormat("<div");
				if (hasIdPrefix)
					sb.AppendFormat(" id=\"{0}{1}_content\"", idPrefix, idCounter);
				if (!string.IsNullOrEmpty(contentClass))
					sb.AppendFormat(" class=\"{0}\"", contentClass);
				sb.Append(">");
				sb.Append(contentHtml);
				sb.Append("</div>");
			}

			return sb.ToString();
		}

		private static string OperatorToString(aim_dotnet.ComparisonOperatorIdentifier operatorIdentifier, bool capFirst)
		{
			switch(operatorIdentifier)
			{ 
				case aim_dotnet.ComparisonOperatorIdentifier.Equal:
					return capFirst ? "Equal to" : "equal to";
				case aim_dotnet.ComparisonOperatorIdentifier.NotEqual:
					return capFirst ? "Not equal to" : "not equal to";
				case aim_dotnet.ComparisonOperatorIdentifier.LessThan:
					return capFirst ? "Less than" : "less than";
				case aim_dotnet.ComparisonOperatorIdentifier.LessThanEqual:
					return capFirst ? "Less than or equal" : "less than or equal";
				case aim_dotnet.ComparisonOperatorIdentifier.GreaterThan:
					return capFirst ? "Greater than" : "greater than";
				case aim_dotnet.ComparisonOperatorIdentifier.GreaterThanEqual:
					return capFirst ? "Greater than or equal" : "greater than or equal";
				case aim_dotnet.ComparisonOperatorIdentifier.None:
					return capFirst ? "None" : "none";
				case aim_dotnet.ComparisonOperatorIdentifier.InvalidComparisonOperator:
					return capFirst ? "Invalid" : "invalid";
			}

			return string.Empty;
		}

		private static string CombineOperatorAndValue(aim_dotnet.ComparisonOperatorIdentifier operatorIdentifier, string aValue, bool capFirst)
		{
			aValue = aValue.Trim();
			if (operatorIdentifier == aim_dotnet.ComparisonOperatorIdentifier.None || 
				operatorIdentifier == aim_dotnet.ComparisonOperatorIdentifier.InvalidComparisonOperator)
				return string.IsNullOrEmpty(aValue) ? "" : aValue;

			if (string.IsNullOrEmpty(aValue))
				return OperatorToString(operatorIdentifier, capFirst);

			return string.Format("{0} {1}", OperatorToString(operatorIdentifier, capFirst), aValue);
		}
	}
}
