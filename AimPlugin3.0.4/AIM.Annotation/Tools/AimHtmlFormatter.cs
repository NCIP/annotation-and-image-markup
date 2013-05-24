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
