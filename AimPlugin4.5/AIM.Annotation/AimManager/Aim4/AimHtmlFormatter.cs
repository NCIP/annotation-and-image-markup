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

namespace AIM.Annotation.AimManager.Aim4
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

		//internal static string GetAimHtml(aim4_dotnet.AnnotationEntity annotation, aim4_dotnet.User aimUserInfo)
		internal static string GetAimHtml(Aim4AnnotationInstance annotationInstance)
		{
			var annotation = annotationInstance == null ? null : annotationInstance.AimAnnotationEntity;
			if (annotation == null)
				return GetEmptyHtml();

			aim4_dotnet.User aimUserInfo = null;
			if (annotationInstance.ParentAimDocument is Aim4DocumentInstance)
				aimUserInfo = ((Aim4DocumentInstance) annotationInstance.ParentAimDocument).AnnotationCollection.User;

			if (annotation is aim4_dotnet.ImageAnnotation)
				return GetImageAnnotationHtml((aim4_dotnet.ImageAnnotation)annotation, aimUserInfo);
			if (annotation is aim4_dotnet.AnnotationOfAnnotation)
				return GetAnnotationOfAnnotationHtml((aim4_dotnet.AnnotationOfAnnotation)annotation, aimUserInfo);
			

			Platform.Log(LogLevel.Error, "Annotation Display Formatting (HTML): unknown annotation type");
			Debug.Assert(false, "Uknown Annotation Type");
			return "Unknown Annotation Type";
		}

		private static string GetImageAnnotationHtml(aim4_dotnet.ImageAnnotation imageAnnotation, aim4_dotnet.User aimUserInfo)
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
			sb.AppendFormat("<div>Number of Geometric Shapes: {0}</div>", imageAnnotation.MarkupEntityCollection == null ? 0 : imageAnnotation.MarkupEntityCollection.Count(geoShape => geoShape is aim4_dotnet.GeometricShapeEntity));
			sb.AppendFormat("<div>Number of Text Annotations: {0}</div>", imageAnnotation.MarkupEntityCollection == null ? 0 : imageAnnotation.MarkupEntityCollection.Count(geoShape => geoShape is aim4_dotnet.TextAnnotationEntity));
			if (aimUserInfo != null)
				sb.AppendFormat("<div>Created by: {0}</div>", aimUserInfo.Name);
			sb.Append(htmlFormatter.GetImagingPhysicalEntitiesHtml(imageAnnotation.ImagingPhysicalEntityCollection));
			sb.Append(htmlFormatter.GetImagingObservationHtml(imageAnnotation.ImagingObservationEntityCollection));
			// TODO - append other sections
			sb.Append("</div>");
			sb.Append("</body>");
			sb.Append("</html>");

			return sb.ToString();
		}

		private static string GetAnnotationOfAnnotationHtml(aim4_dotnet.AnnotationOfAnnotation annotationOfAnnotation, aim4_dotnet.User aimUserInfo)
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

		private string GetImagingPhysicalEntitiesHtml(List<aim4_dotnet.ImagingPhysicalEntity> imagingPhysicalEntities)
		{
			StringBuilder sb = new StringBuilder();
			if (imagingPhysicalEntities != null)
			{
				foreach (var imagingPhysicalEntity in imagingPhysicalEntities)
				{
					sb.Append(GetExpandableItemHtml(
						CodeListToString(imagingPhysicalEntity.TypeCode, "Anatomic Entity"),
						null,
						"ae_header",
						null,
						"ae_content",
						"ae",
						_aeCount++,
						GetImagingPhysicalEntityCharacteristicsHtml(imagingPhysicalEntity.ImagingPhysicalEntityCharacteristicCollection),
						GetImagingObservationCharacteristicsHtml(imagingPhysicalEntity.ImagingObservationCharacteristicCollection)));
				}
			}
			return GetExpandableItemHtml(
				"Anatomic Entities",
				string.Format("({0})", imagingPhysicalEntities == null ? 0 : imagingPhysicalEntities.Count),
				"aes_header",
				"aes_summary",
				"aes_content",
				"aes",
				0,
				sb.ToString());
		}

		private string GetImagingPhysicalEntityCharacteristicsHtml(List<aim4_dotnet.ImagingPhysicalEntityCharacteristic> imagingPhysicalEntityChars)
		{
			StringBuilder sb = new StringBuilder();
			if (imagingPhysicalEntityChars != null)
			{
				foreach (var imagingPhysEntityChar in imagingPhysicalEntityChars)
				{
					sb.Append(GetExpandableItemHtml(
						CodeListToString(imagingPhysEntityChar.TypeCode, "Anatomic Entity Characteristic"),
						null,
						"aec_header",
						null,
						"aec_content",
						"aec",
						_aecCount++,
						GetCharacteristicQuantificationsHtml(imagingPhysEntityChar.CharacteristicQuantificationCollection)));
				}
			}
			return GetExpandableItemHtml(
				"Anatomic Entity Characteristics",
				string.Format("({0})", imagingPhysicalEntityChars == null ? 0 : imagingPhysicalEntityChars.Count),
				"aecs_header",
				"aecs_summary",
				"aecs_content",
				"aecs",
				_aecsCount++,
				sb.ToString());
		}

		private string GetImagingObservationHtml(List<aim4_dotnet.ImagingObservationEntity> imagingObservations)
		{
			StringBuilder sb = new StringBuilder();
			if (imagingObservations != null)
			{
				foreach (aim4_dotnet.ImagingObservationEntity imagingObservation in imagingObservations)
				{
					sb.Append(GetExpandableItemHtml(
						CodeListToString(imagingObservation.TypeCode, "Imaging Observation Entity"),
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

		private string GetImagingObservationCharacteristicsHtml(List<aim4_dotnet.ImagingObservationCharacteristic> ioCharacteristics)
		{
			StringBuilder sb = new StringBuilder();
			if (ioCharacteristics != null)
			{
				foreach (aim4_dotnet.ImagingObservationCharacteristic ioCharacteristic in ioCharacteristics)
				{
					sb.Append(GetExpandableItemHtml(
						CodeListToString(ioCharacteristic.TypeCode, "Imaging Observation Characteristic"),
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

		private string GetCharacteristicQuantificationsHtml(List<aim4_dotnet.CharacteristicQuantification> characteristicQuantificationCollection)
		{
			StringBuilder sb = new StringBuilder();
			if (characteristicQuantificationCollection != null)
			{
				foreach (var characteristicQuantification in characteristicQuantificationCollection)
				{
					sb.Append(GetExpandableItemHtml(
						characteristicQuantification.ValueLabel,
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

		private string GetCharacteristicQuantificationHtml(aim4_dotnet.CharacteristicQuantification characteristicQuantification)
		{
			if (characteristicQuantification == null)
				return "";

			switch (characteristicQuantification.QuantificationType)
			{
				case aim4_dotnet.CharacteristicQuantificationType.Numerical:
					aim4_dotnet.Numerical numerical = (aim4_dotnet.Numerical) characteristicQuantification;
					return numerical.Operator == aim4_dotnet.ComparisonOperatorIdentifier.InvalidComparisonOperator ||
					       numerical.Operator == aim4_dotnet.ComparisonOperatorIdentifier.None
					       	? string.Format("{0} {1}", numerical.Value, numerical.UcumString)
					       	: string.Format("{0} {1} {2}", OperatorToString(numerical.Operator, true), numerical.Value, numerical.UcumString);
				case aim4_dotnet.CharacteristicQuantificationType.Quantile:
					aim4_dotnet.Quantile quantile = (aim4_dotnet.Quantile) characteristicQuantification;
					return string.Format("Quantile [{0}] of [{1}", quantile.SelectedBin, quantile.Bins);
				case aim4_dotnet.CharacteristicQuantificationType.NonQuantifiable:
					aim4_dotnet.NonQuantifiable nonQuantifiable = (aim4_dotnet.NonQuantifiable) characteristicQuantification;
					return nonQuantifiable.TypeCode == null ? "" : nonQuantifiable.TypeCode.CodeMeaning;
				case aim4_dotnet.CharacteristicQuantificationType.Scale:
					aim4_dotnet.Scale scale = (aim4_dotnet.Scale) characteristicQuantification;
					return scale.Value ?? "";
				case aim4_dotnet.CharacteristicQuantificationType.Interval:
					aim4_dotnet.Interval interval = (aim4_dotnet.Interval) characteristicQuantification;
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
			string contentClass, string idPrefix, int idCounter, params string[] contentHtml)
		{
			bool hasContentData = contentHtml != null && contentHtml.Any(item => !string.IsNullOrEmpty(item));

			if (string.IsNullOrEmpty(headerText) && string.IsNullOrEmpty(headerSummary) && 
				string.IsNullOrEmpty(headerClass) && string.IsNullOrEmpty(contentClass) && !hasContentData)
				return string.Empty;

			StringBuilder sb = new StringBuilder();

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
				foreach (var innerHtml in contentHtml.Where(innerHtml => !string.IsNullOrEmpty(innerHtml)))
					sb.Append(innerHtml);
				sb.Append("</div>");
			}

			return sb.ToString();
		}

		private static string OperatorToString(aim4_dotnet.ComparisonOperatorIdentifier operatorIdentifier, bool capFirst)
		{
			switch(operatorIdentifier)
			{ 
				case aim4_dotnet.ComparisonOperatorIdentifier.Equal:
					return capFirst ? "Equal to" : "equal to";
				case aim4_dotnet.ComparisonOperatorIdentifier.NotEqual:
					return capFirst ? "Not equal to" : "not equal to";
				case aim4_dotnet.ComparisonOperatorIdentifier.LessThan:
					return capFirst ? "Less than" : "less than";
				case aim4_dotnet.ComparisonOperatorIdentifier.LessThanEqual:
					return capFirst ? "Less than or equal" : "less than or equal";
				case aim4_dotnet.ComparisonOperatorIdentifier.GreaterThan:
					return capFirst ? "Greater than" : "greater than";
				case aim4_dotnet.ComparisonOperatorIdentifier.GreaterThanEqual:
					return capFirst ? "Greater than or equal" : "greater than or equal";
				case aim4_dotnet.ComparisonOperatorIdentifier.None:
					return capFirst ? "None" : "none";
				case aim4_dotnet.ComparisonOperatorIdentifier.InvalidComparisonOperator:
					return capFirst ? "Invalid" : "invalid";
			}

			return string.Empty;
		}

		private static string CombineOperatorAndValue(aim4_dotnet.ComparisonOperatorIdentifier operatorIdentifier, string aValue, bool capFirst)
		{
			aValue = aValue.Trim();
			if (operatorIdentifier == aim4_dotnet.ComparisonOperatorIdentifier.None || 
				operatorIdentifier == aim4_dotnet.ComparisonOperatorIdentifier.InvalidComparisonOperator)
				return string.IsNullOrEmpty(aValue) ? "" : aValue;

			if (string.IsNullOrEmpty(aValue))
				return OperatorToString(operatorIdentifier, capFirst);

			return string.Format("{0} {1}", OperatorToString(operatorIdentifier, capFirst), aValue);
		}

		private static string CodeListToString(List<aim4_dotnet.iso_21090.CD> codes, string defaulValue)
		{
			if (codes == null)
				return defaulValue;

			var sb = new StringBuilder();
			foreach (var code in codes)
			{
				var realCode = GeneralUtilities.StringUtils.NullIfTrimed(code.CodeMeaning);
				if (realCode == null)
					continue;

				if (sb.Length == 0)
					sb.Append(realCode);
				else
					sb.AppendFormat(" {0}", realCode);
			}

			return sb.Length > 0 ? sb.ToString() : defaulValue;
		}
	}
}
