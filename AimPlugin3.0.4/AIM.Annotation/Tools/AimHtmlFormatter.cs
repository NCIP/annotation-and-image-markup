#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.Tools
{
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

		public static string GetAimHtml(aim_dotnet.Annotation annotation)
		{
			if (annotation == null)
				return GetEmptyHtml();

			switch (annotation.AnnotationKind)
			{
				case aim_dotnet.AnnotationKind.AK_ImageAnnotation:
					return GetImageAnnotationHtml(annotation as aim_dotnet.ImageAnnotation);
				case aim_dotnet.AnnotationKind.AK_AnnotationOfAnnotation:
					return GetAnnotationOfAnnotationHtml(annotation as aim_dotnet.AnnotationOfAnnotation);
			}

			Debug.Assert(false, "Uknown Annotation Type");
			Platform.Log(LogLevel.Error, "Annotation Display Formatting (HTML): unknown annotation type");
			return "Unknown Annotation Type";
		}

		private static string GetImageAnnotationHtml(aim_dotnet.ImageAnnotation imageAnnotation)
		{
			var sb = new StringBuilder();
			var htmlFormatter = new AimHtmlFormatter();
			var ctrlColor = Color.FromKnownColor(KnownColor.Control);

			sb.Append(HtmlDocHeader);
			sb.AppendFormat("<body style=\"background-color: #{0}{1}{2};\" onload=\"setupPaths(['{3}', '{4}'])\">", 
				ctrlColor.R.ToString("X2"), ctrlColor.G.ToString("X2"), ctrlColor.B.ToString("X2"),
				MinusImagePathName, PlusImagePathName);
			sb.Append("<div id=\"main_content\">");
			sb.Append(htmlFormatter.GetAnatomicEntitiesHtml(imageAnnotation.AnatomyEntityCollection));
			sb.Append(htmlFormatter.GetImagingObservationHtml(imageAnnotation.ImagingObservationCollection));
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
			var sb = new StringBuilder();
			var ctrlColor = Color.FromKnownColor(KnownColor.Control);

			sb.Append(HtmlDocHeader);
			sb.AppendFormat("<body style=\"background-color: #{0}{1}{2};\">", 
				ctrlColor.R.ToString("X2"), ctrlColor.G.ToString("X2"), ctrlColor.B.ToString("X2"));
			sb.Append("</body>");
			sb.Append("</html>");

			return sb.ToString();
		}

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
							var resolver = new ResourceResolver(typeof(AimHtmlFormatter).Assembly);
							try
							{
								using (var stream = resolver.OpenResource("Tools.AimHtmlDoc.html"))
								{
									using (var reader = new StreamReader(stream))
									{
										AimHtmlDoc = reader.ReadToEnd();
									}
								}

								using (var stream = resolver.OpenResource("Tools.minus_13x13.gif"))
								{
									using (var img = Image.FromStream(stream))
									{
										MinusImagePathName = Path.GetTempFileName().Replace("\\", "/");
										img.Save(MinusImagePathName, System.Drawing.Imaging.ImageFormat.Gif);
									}
								}

								using (var stream = resolver.OpenResource("Tools.plus_13x13.gif"))
								{
									using (var img = Image.FromStream(stream))
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

				return AimHtmlDoc ?? "<html><body>";
			}
		}

		private string GetAnatomicEntitiesHtml(List<aim_dotnet.AnatomicEntity> anatomicEntities)
		{
			var sb = new StringBuilder();
			if (anatomicEntities != null)
			{
				foreach (var anatomicEntity in anatomicEntities)
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
			var sb = new StringBuilder();
			if (aeCharacteristics != null)
			{
				foreach (var aeCharacteristic in aeCharacteristics)
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
			var sb = new StringBuilder();
			if (imagingObservations != null)
			{
				foreach (var imagingObservation in imagingObservations)
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
			var sb = new StringBuilder();
			if (ioCharacteristics != null)
			{
				foreach (var ioCharacteristic in ioCharacteristics)
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
			var sb = new StringBuilder();
			if (characteristicQuantificationCollection != null)
			{
				foreach (var characteristicQuantification in characteristicQuantificationCollection)
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
					var numerical = (aim_dotnet.Numerical) characteristicQuantification;
					return numerical.Operator == aim_dotnet.ComparisonOperatorIdentifier.InvalidComparisonOperator ||
					       numerical.Operator == aim_dotnet.ComparisonOperatorIdentifier.None
					       	? string.Format("{0} {1}", numerical.Value, numerical.UcumString)
					       	: string.Format("{0} {1} {2}", OperatorToString(numerical.Operator, true), numerical.Value, numerical.UcumString);
				case aim_dotnet.CharacteristicQuantificationType.Quantile:
					var quantile = (aim_dotnet.Quantile) characteristicQuantification;
					return string.Format("Quantile [{0}]", quantile.Bin);
				case aim_dotnet.CharacteristicQuantificationType.NonQuantifiable:
					var nonQuantifiable = (aim_dotnet.NonQuantifiable) characteristicQuantification;
					return nonQuantifiable.CodeMeaning ?? "";
				case aim_dotnet.CharacteristicQuantificationType.Scale:
					var scale = (aim_dotnet.Scale) characteristicQuantification;
					return scale.Value ?? "";
				case aim_dotnet.CharacteristicQuantificationType.Interval:
					var interval = (aim_dotnet.Interval) characteristicQuantification;
					{
						var left = CombineOperatorAndValue(interval.MinOperator, interval.MinValue == double.MinValue ? "" : interval.MinValue.ToString(), true);
						var right = CombineOperatorAndValue(interval.MaxOperator, interval.MaxValue == double.MaxValue ? "" : interval.MaxValue.ToString(), string.IsNullOrEmpty(left));

						var sb = new StringBuilder();
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

			var sb = new StringBuilder();
			var hasContentData = !string.IsNullOrEmpty(contentHtml);
			var hasIdPrefix = !string.IsNullOrEmpty(idPrefix);
			
			sb.Append("<div");
			if(hasIdPrefix)
				sb.AppendFormat(" id=\"{0}{1}_header\"", idPrefix, idCounter);
			if (!string.IsNullOrEmpty(headerClass))
				sb.AppendFormat(" class=\"{0}\"", headerClass);
			sb.Append(">");

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
			sb.Append("</div>");

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
