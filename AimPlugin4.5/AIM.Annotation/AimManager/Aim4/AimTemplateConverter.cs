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
using System.Linq;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Dicom;
using ClearCanvas.ImageViewer.Mathematics;

using AIM.Annotation.Configuration;
using AIM.Annotation.TemplateTree;

using GeneralUtilities.Collections;

namespace AIM.Annotation.AimManager.Aim4
{
	internal class AimTemplateConverter
	{
		private const string COLLAPSED_VALID_TERM_CODING_SCHEME_DESIGNATOR = "AIM4-COMPAT";

		private static volatile AimTemplateConverter _instance;
		private static readonly object _syncRoot = new Object();

		public static AimTemplateConverter Instance
		{
			get
			{
				if (_instance == null)
				{
					lock (_syncRoot)
					{
						if (_instance == null)
							_instance = new AimTemplateConverter();
					}
				}
				return _instance;
			}
		}

		public static AimTemplateTree AimAnnotationToAimTemplateTree(Aim4AnnotationInstance annotationInstance, AimTemplateTree template)
		{
			if (annotationInstance == null || annotationInstance.AimAnnotationEntity == null)
				return null;

			var annotation = annotationInstance.AimAnnotationEntity;
			if (annotation.ImagingPhysicalEntityCollection != null)
			{
				foreach (var imgPhysEnt in annotation.ImagingPhysicalEntityCollection)
				{
					if (IsNullCodeList(imgPhysEnt.TypeCode))
						continue;

					AimTemplateTreeAnatomicEntityNode matchingTreeNode = FromImagingPhysicalEntity(imgPhysEnt, template);
					if (matchingTreeNode == null)
						return null;
				}
			}
			if (annotation.ImagingObservationEntityCollection != null)
			{
				foreach (var io in annotation.ImagingObservationEntityCollection)
				{
					if (IsNullCodeList(io.TypeCode))
						continue;

					AimTemplateTreeImagingObservationNode matchingTreeNode = FromImagingObservationEntity(io, template);
					if (matchingTreeNode == null)
						return null;
				}
			}
			if (annotation.CalculationEntityCollection != null)
			{
				//foreach (var calc in annotation.CalculationCollection)
				//{
				//    AimTemplateTreeCalculationNode matchingTreeNode =
				//        template.TemplateNodes.OfType<AimTemplateTreeCalculationNode>().FirstOrDefault(
				//            treeCalc => treeCalc.Label == calc.Description);
				//    if (matchingTreeNode != null)
				//    {
				//        AimTemplateTreeCalculationType matchingCalculationType =
				//            matchingTreeNode.CalculationTypes.FirstOrDefault(
				//                treeCalc => ToStandardCodeSequence(treeCalc).CodeValue == calc.CodeValue);
				//        if (matchingCalculationType != null)
				//        {
				//            matchingTreeNode.SelectedCalculationType = matchingCalculationType;
				//        }
				//        else
				//            return null;

				//        //if (matchingTreeNode.HasConfidence && calc..HasValue)
				//        //    matchingTreeNode.ConfidenceValue = calc.AnnotatorConfidence.Value;
				//    }
				//    else
				//        return null;
				//}
			}
			if (annotation.InferenceEntityCollection != null)
			{
				foreach (var inference in annotation.InferenceEntityCollection)
				{
					if (IsNullCodeList(inference.TypeCode))
						continue;

					foreach (var inferenceNode in template.TemplateNodes.OfType<AimTemplateTreeInferenceNode>())
					{
						AimTemplateTreeAllowedTerm matchingAllowedTerm =
							inferenceNode.AllowedTerms.FirstOrDefault(term => DoTheyMatch(term, inference.TypeCode));
						if (matchingAllowedTerm != null)
							matchingAllowedTerm.Selected = true;
					}
				}
			}
			template.Markup.Clear();
			if (annotation is aim4_dotnet.ImageAnnotation)
			{
				var imageAnnotation = (aim4_dotnet.ImageAnnotation)annotation;
				var annotationName = string.IsNullOrEmpty(imageAnnotation.Name) ? "" : imageAnnotation.Name;

				if (imageAnnotation.MarkupEntityCollection != null)
				{
					foreach (var markupEntity in imageAnnotation.MarkupEntityCollection)
					{
						if (markupEntity is aim4_dotnet.GeometricShapeEntity)
						{
							var markup = ToMarkup2D((aim4_dotnet.GeometricShapeEntity)markupEntity, annotationName);
							if (markup != null)
								template.Markup.Add(markup);
						} 
						else if (markupEntity is aim4_dotnet.TextAnnotationEntity)
						{
							var textAnnotationEntity = (aim4_dotnet.TextAnnotationEntity) markupEntity;
							if (textAnnotationEntity.GeometricShapeEntity != null)
							{
								var calloutText = AimHelpers.FormatPointCalloutText(annotationName, textAnnotationEntity.Text);
								aim4_dotnet.TwoDimensionGeometricShapeEntity geoShapeEntity = null;
								if (textAnnotationEntity.GeometricShapeEntity is aim4_dotnet.TwoDimensionGeometricShapeEntity)
								{
									var twoDGeoShape = (aim4_dotnet.TwoDimensionGeometricShapeEntity) textAnnotationEntity.GeometricShapeEntity;
									switch (twoDGeoShape.TwoDimensionSpatialCoordinateCollection.Count)
									{
										case 1:
											{
												var markup = new MarkupPoint();
												markup.Name = annotationName;
												markup.IncludeInAnnotation = twoDGeoShape.IncludeFlag;
												markup.Point = AsPointF(twoDGeoShape.TwoDimensionSpatialCoordinateCollection[0]);
												markup.CalloutText = calloutText;
												markup.CalloutLocation = new PointF(markup.Point.X, markup.Point.Y);
												SetMarkupImageReference(markup, twoDGeoShape);
												markup.UseCrosshair = AimSettings.Default.UseCrosshairsForTextCallouts;
												template.Markup.Add(markup);
											}
											break;
										case 2:
											{
												var markup = new MarkupPoint();
												markup.Name = annotationName;
												markup.IncludeInAnnotation = twoDGeoShape.IncludeFlag;
												markup.Point = AsPointF(twoDGeoShape.TwoDimensionSpatialCoordinateCollection[0]);
												markup.CalloutText = calloutText;
												markup.CalloutLocation = AsPointF(twoDGeoShape.TwoDimensionSpatialCoordinateCollection[1]);
												SetMarkupImageReference(markup, twoDGeoShape);
												markup.UseCrosshair = AimSettings.Default.UseCrosshairsForTextCallouts;
												template.Markup.Add(markup);
											}
											break;
										default:
											Platform.Log(LogLevel.Error, "TextAnnotation has [{0}] Connector Points", twoDGeoShape.TwoDimensionSpatialCoordinateCollection.Count);
											break;
									}
								}
								else if (textAnnotationEntity.GeometricShapeEntity is aim4_dotnet.ThreeDimensionGeometricShapeEntity)
								{
									// TODO: implement 2D markup conversion!
									// TODO: convert to the 2D ImageReferenceUid and referencedFrameNumber!

									var threeDGeoShape = (aim4_dotnet.ThreeDimensionGeometricShapeEntity) textAnnotationEntity.GeometricShapeEntity;
									switch (threeDGeoShape.ThreeDimensionSpatialCoordinateCollection.Count)
									{
										case 1:
											throw new NotImplementedException();
											break;
										case 2:
											throw new NotImplementedException();
											break;
										default:
											Platform.Log(LogLevel.Error, "TextAnnotation has [{0}] 3D Connector Points", threeDGeoShape.ThreeDimensionSpatialCoordinateCollection.Count);
											break;
									}
								}
							}
						}
						else
							Debug.Assert(false, "Unexpected markup type");
					}
				}
			}
			return template;
		}

		private static AimTemplateTreeAnatomicEntityNode FromImagingPhysicalEntity(aim4_dotnet.ImagingPhysicalEntity imagingPhysicalEntity, AimTemplateTree template)
		{
			AimTemplateTreeAnatomicEntityNode matchingTreeNode = null;

			if (imagingPhysicalEntity.QuestionTypeCode != null)
				matchingTreeNode = template.TemplateNodes.OfType<AimTemplateTreeAnatomicEntityNode>().FirstOrDefault(treeAe => DoTheyMatch(treeAe.QuestionType, imagingPhysicalEntity.QuestionTypeCode));
			else if (!String.IsNullOrEmpty(imagingPhysicalEntity.Label))
				matchingTreeNode = template.TemplateNodes.OfType<AimTemplateTreeAnatomicEntityNode>().FirstOrDefault(treeAe => String.Equals(imagingPhysicalEntity.Label, treeAe.Label));
			else
				matchingTreeNode = template.TemplateNodes.OfType<AimTemplateTreeAnatomicEntityNode>().FirstOrDefault(treeAe => treeAe.ItemNumber == imagingPhysicalEntity.QuestionIndex);

			if (matchingTreeNode != null)
			{
				AimTemplateTreeAllowedTerm matchingAllowedTerm = matchingTreeNode.AllowedTerms.FirstOrDefault(treeAe => DoTheyMatch(treeAe, imagingPhysicalEntity.TypeCode));
				if (matchingAllowedTerm != null)
					matchingAllowedTerm.Selected = true;
				else
					return null;

				if (matchingTreeNode.HasConfidence && imagingPhysicalEntity.AnnotatorConfidence.HasValue)
					matchingTreeNode.ConfidenceValue = imagingPhysicalEntity.AnnotatorConfidence.Value;
			}
			else
				return null;

			if (imagingPhysicalEntity.ImagingPhysicalEntityCharacteristicCollection != null)
			{
				foreach (var aec in imagingPhysicalEntity.ImagingPhysicalEntityCharacteristicCollection)
				{
					if (IsNullCodeList(aec.TypeCode))
						continue;

					AimTemplateTreeAnatomicEntityCharacteristicNode matchingAecTreeNode =
						FromImagingPhysicalEntityCharacteristic(aec, matchingTreeNode.AnatomicEntityCharacteristicTreeNodes);
					if (matchingAecTreeNode == null)
						return null;
				}
			}

			if (imagingPhysicalEntity.ImagingObservationCharacteristicCollection != null)
			{
				foreach (var ioc in imagingPhysicalEntity.ImagingObservationCharacteristicCollection)
				{
					if (IsNullCodeList(ioc.TypeCode))
						continue;

					AimTemplateTreeImagingObservationCharacteristicNode matchingIocTreeNode =
						FromImagingObservationCharacteristic(ioc, matchingTreeNode.ImagingObservationCharacteristicTreeNodes);
					if (matchingIocTreeNode == null)
						return null;
				}
			}

			return matchingTreeNode;
		}

		private static AimTemplateTreeAnatomicEntityCharacteristicNode FromImagingPhysicalEntityCharacteristic(aim4_dotnet.ImagingPhysicalEntityCharacteristic imgPhysEntityChar, List<AimTemplateTreeAnatomicEntityCharacteristicNode> treeAecList)
		{
			AimTemplateTreeAnatomicEntityCharacteristicNode matchingAecTreeNode = null;

			if (imgPhysEntityChar.QuestionTypeCode != null)
				matchingAecTreeNode = treeAecList.FirstOrDefault(treeAec => DoTheyMatch(treeAec.QuestionType, imgPhysEntityChar.QuestionTypeCode));
			else if (!String.IsNullOrEmpty(imgPhysEntityChar.Label))
				matchingAecTreeNode = treeAecList.FirstOrDefault(treeAec => String.Equals(imgPhysEntityChar.Label, treeAec.Label));
			else
				matchingAecTreeNode = treeAecList.FirstOrDefault(treeAe => treeAe.ItemNumber == imgPhysEntityChar.QuestionIndex);

			if (matchingAecTreeNode != null)
			{
				CharacteristicQuantificationAllowedTerm matchingAllowedTerm =
					matchingAecTreeNode.CharacteristicQuantificationAllowedTerms.FirstOrDefault(treeAec => DoTheyMatch(treeAec, imgPhysEntityChar.TypeCode));
				if (matchingAllowedTerm != null)
				{
					matchingAllowedTerm.Selected = true;

					foreach (var quantification in matchingAllowedTerm.CharacteristicQuantifications)
					{
						if (ReadBackCharacteristicQuantificationFromAnnotation(imgPhysEntityChar.CharacteristicQuantificationCollection, quantification) == null)
							return null;
					}
				}
				else
					return null;

				if (matchingAecTreeNode.HasConfidence && imgPhysEntityChar.AnnotatorConfidence.HasValue)
					matchingAecTreeNode.ConfidenceValue = imgPhysEntityChar.AnnotatorConfidence.Value;

			}
			else
				return null;

			return matchingAecTreeNode;
		}

		private static AimTemplateTreeImagingObservationNode FromImagingObservationEntity(aim4_dotnet.ImagingObservationEntity imagingObservationEntity, AimTemplateTree template)
		{
			AimTemplateTreeImagingObservationNode matchingTreeNode = null;

			if (imagingObservationEntity.QuestionTypeCode != null)
				matchingTreeNode = template.TemplateNodes.OfType<AimTemplateTreeImagingObservationNode>().FirstOrDefault(treeAe => DoTheyMatch(treeAe.QuestionType, imagingObservationEntity.QuestionTypeCode));
			else if (!String.IsNullOrEmpty(imagingObservationEntity.Label))
				matchingTreeNode = template.TemplateNodes.OfType<AimTemplateTreeImagingObservationNode>().FirstOrDefault(treeAe => String.Equals(imagingObservationEntity.Label, treeAe.Label));
			else
				matchingTreeNode = template.TemplateNodes.OfType<AimTemplateTreeImagingObservationNode>().FirstOrDefault(treeAe => treeAe.ItemNumber == imagingObservationEntity.QuestionIndex);
            
			if (matchingTreeNode != null)
			{
				AimTemplateTreeAllowedTerm matchingAllowedTerm =
					matchingTreeNode.AllowedTerms.FirstOrDefault(treeIo => DoTheyMatch(treeIo, imagingObservationEntity.TypeCode));
				if (matchingAllowedTerm != null)
					matchingAllowedTerm.Selected = true;
				else
					return null;

				if (matchingTreeNode.HasConfidence && imagingObservationEntity.AnnotatorConfidence.HasValue)
					matchingTreeNode.ConfidenceValue = imagingObservationEntity.AnnotatorConfidence.Value;
			}
			else
				return null;

			if (imagingObservationEntity.ImagingObservationCharacteristicCollection != null)
			{
				foreach (var ioc in imagingObservationEntity.ImagingObservationCharacteristicCollection)
				{
					if (IsNullCodeList(ioc.TypeCode))
						continue;

					AimTemplateTreeImagingObservationCharacteristicNode matchingIocTreeNode =
						FromImagingObservationCharacteristic(ioc, matchingTreeNode.ImagingObservationCharacteristicTreeNodes);
					if (matchingIocTreeNode == null)
						return null;
				}
			}

			return matchingTreeNode;
		}

		private static AimTemplateTreeImagingObservationCharacteristicNode FromImagingObservationCharacteristic(aim4_dotnet.ImagingObservationCharacteristic imagingObservationCharacteristic, List<AimTemplateTreeImagingObservationCharacteristicNode> treeIocList)
		{
			AimTemplateTreeImagingObservationCharacteristicNode matchingIocTreeNode = null;

			if (imagingObservationCharacteristic.QuestionTypeCode != null)
				matchingIocTreeNode = treeIocList.FirstOrDefault(treeIoc => DoTheyMatch(treeIoc.QuestionType, imagingObservationCharacteristic.QuestionTypeCode));
			else if (!String.IsNullOrEmpty(imagingObservationCharacteristic.Label))
				matchingIocTreeNode = treeIocList.FirstOrDefault(treeIoc => String.Equals(imagingObservationCharacteristic.Label, treeIoc.Label));
			else
				matchingIocTreeNode = treeIocList.FirstOrDefault(treeAe => treeAe.ItemNumber == imagingObservationCharacteristic.QuestionIndex);

			if (matchingIocTreeNode != null)
			{
				CharacteristicQuantificationAllowedTerm matchingAllowedTerm =
					matchingIocTreeNode.CharacteristicQuantificationAllowedTerms.FirstOrDefault(treeIoc => DoTheyMatch(treeIoc, imagingObservationCharacteristic.TypeCode));
				if (matchingAllowedTerm != null)
				{
					matchingAllowedTerm.Selected = true;

					foreach (var quantification in matchingAllowedTerm.CharacteristicQuantifications)
					{
						if (ReadBackCharacteristicQuantificationFromAnnotation(imagingObservationCharacteristic.CharacteristicQuantificationCollection, quantification) == null)
							return null;
					}
				}
				else
					return null;

				if (matchingIocTreeNode.HasConfidence && imagingObservationCharacteristic.AnnotatorConfidence.HasValue)
					matchingIocTreeNode.ConfidenceValue = imagingObservationCharacteristic.AnnotatorConfidence.Value;
			}
			else
				return null;

			return matchingIocTreeNode;
		}

		// TODO - use AimNativeConverter instead of this
		private static PointF AsPointF(aim4_dotnet.TwoDimensionSpatialCoordinate twoDimensionSpatialCoordinate)
		{
			Platform.CheckTrue(twoDimensionSpatialCoordinate != null, "Spatial Coordinate Exists");

			return new PointF((float)twoDimensionSpatialCoordinate.X, (float)twoDimensionSpatialCoordinate.Y);
		}

		/// <summary>
		/// Matches an AimTempalteTreeCharacteristicQuantification from to a characteristic quantification from aim4_dotnet.annotation
		/// ICharacteristicQuantification collection
		/// </summary>
		/// <param name="annotationCharacteristicQuantifications"></param>
		/// <param name="templateTreeCharacteristicQuantification"></param>
		/// <returns></returns>
		public static AimTemplateTreeCharacteristicQuantification ReadBackCharacteristicQuantificationFromAnnotation(List<aim4_dotnet.CharacteristicQuantification> annotationCharacteristicQuantifications, AimTemplateTreeCharacteristicQuantification templateTreeCharacteristicQuantification)
		{
			if (annotationCharacteristicQuantifications != null && annotationCharacteristicQuantifications.Count > 0)
			{
				aim4_dotnet.NonQuantifiable nonQuantifiable = annotationCharacteristicQuantifications.OfType<aim4_dotnet.NonQuantifiable>().FirstOrDefault();

				if (nonQuantifiable != null)
				{
					StandardCodedTerm matchingNonQuantifiable =
						templateTreeCharacteristicQuantification.NonQuantifiables.FirstOrDefault(
							nonQuant =>
							AimDotNetNonQuantifiableEqualsTemplateTreeNonQuantifiable(nonQuantifiable, nonQuant));
					if (matchingNonQuantifiable != null)
						templateTreeCharacteristicQuantification.SelectedNonQuantifiable = matchingNonQuantifiable;
				}
				else
				{
					if (templateTreeCharacteristicQuantification is AimTemplateTreeScaleQuantification)
					{
						var scaleQuantification = templateTreeCharacteristicQuantification as AimTemplateTreeScaleQuantification;

						aim4_dotnet.Scale matchingScale = annotationCharacteristicQuantifications.OfType<aim4_dotnet.Scale>().FirstOrDefault();

						if (matchingScale != null)
						{
							var matchingTreeScaleLevel = scaleQuantification.Scale.ScaleLevels.FirstOrDefault(
									scaleLevel =>
									AimDotNetScaleEqualsTemplateTreeScaleLevel(matchingScale, scaleLevel));

							scaleQuantification.SelectedScaleLevel = matchingTreeScaleLevel;
						}
						else
							return null;
					}

					if (templateTreeCharacteristicQuantification is AimTemplateTreeQuantileQuantification)
					{
						var quantileQuantification = templateTreeCharacteristicQuantification as AimTemplateTreeQuantileQuantification;

						var quantile = annotationCharacteristicQuantifications.OfType<aim4_dotnet.Quantile>().FirstOrDefault();

						if (quantile != null)
						{
							quantileQuantification.SelectedBin = quantile.SelectedBin;
							// TODO - add other bin attributes
						}
						else
							return null;
					}

					if (templateTreeCharacteristicQuantification is AimTemplateTreeIntervalQuantification)
					{
						var intervalQuantification = templateTreeCharacteristicQuantification as AimTemplateTreeIntervalQuantification;

						var matchingInterval = annotationCharacteristicQuantifications.OfType<aim4_dotnet.Interval>().FirstOrDefault();

						if (matchingInterval != null)
						{
							var matchingTreeInterval = intervalQuantification.Intervals.FirstOrDefault(
									interval =>
									AimDotNetIntervalEqualsTemplateTreeInterval(matchingInterval, interval));

							intervalQuantification.SelectedInterval = matchingTreeInterval;
						}
						else
							return null;
					}

					if (templateTreeCharacteristicQuantification is AimTemplateTreeNumericalQuantification)
					{
						var numericalQuantification = templateTreeCharacteristicQuantification as AimTemplateTreeNumericalQuantification;

						var matchingNumerical = annotationCharacteristicQuantifications.OfType<aim4_dotnet.Numerical>().FirstOrDefault();

						if (matchingNumerical != null)
						{
							var matchingTreeNumerical = numericalQuantification.Numericals.FirstOrDefault(
									numerical =>
									AimDotNetNumericalEqualsTemplateTreeNumerical(matchingNumerical, numerical));

							numericalQuantification.SelectedNumerical = matchingTreeNumerical;
						}
						else
							return null;
					}
				}
			}
			return templateTreeCharacteristicQuantification;
		}

		public static bool AimDotNetScaleEqualsTemplateTreeScaleLevel(aim4_dotnet.Scale a, TemplateTree.ScaleLevel b)
		{
			return a.Value == b.Value;
		}

		public static bool AimDotNetNonQuantifiableEqualsTemplateTreeNonQuantifiable(aim4_dotnet.NonQuantifiable a, TemplateTree.StandardCodedTerm b)
		{
			return a.TypeCode != null &&
				   String.Equals(a.TypeCode.CodeValue, b.CodeValue) &&
				   String.Equals(a.TypeCode.CodeMeaning, b.CodeMeaning) &&
				   String.Equals(a.TypeCode.CodingSchemeDesignator, b.CodingSchemeDesignator) &&
				   StringEquals(a.TypeCode.CodingSchemeVersion, b.CodingSchemeVersion);
		}

		/// <summary>
		/// Does a string equals comparison where null and String.Empty are equivalent.
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		private static bool StringEquals(string a, string b)
		{
			return string.Equals(a ?? string.Empty, b ?? string.Empty);
		}

		public static bool AimDotNetIntervalEqualsTemplateTreeInterval(aim4_dotnet.Interval a, TemplateTree.Interval b)
		{
			return
				a.MinValue == b.MinValue &&
				a.MaxValue == b.MaxValue &&
				a.MinOperator == ToAimComparisonOperator(b.MinOperator) &&
				a.MaxOperator == ToAimComparisonOperator(b.MaxOperator) &&
				a.UcumString == b.UcumString;
		}

		public static bool AimDotNetNumericalEqualsTemplateTreeNumerical(aim4_dotnet.Numerical a, TemplateTree.Numerical b)
		{
			return
				a.Value == b.Value &&
				a.UcumString == b.UcumString &&
				a.Operator == ToAimComparisonOperator(b.Operator);
		}

		public static IMarkup ToMarkup2D(aim4_dotnet.GeometricShapeEntity geometricShape, string markupText)
		{
			if (geometricShape == null)
				return null;

			if (geometricShape is aim4_dotnet.TwoDimensionPoint)
			{
				var point = (aim4_dotnet.TwoDimensionPoint)geometricShape;

				var markup = new MarkupPoint();
				markup.Name = markupText;
				markup.IncludeInAnnotation = point.IncludeFlag;
				markup.Point = AsPointF(point.Center);
				markup.CalloutText = string.Empty; // markupText;
				markup.CalloutLocation = markup.Point - new SizeF(30, 30);
				SetMarkupImageReference(markup, point);

				return markup;
			}
			if (geometricShape is aim4_dotnet.TwoDimensionCircle)
			{
				var circle = (aim4_dotnet.TwoDimensionCircle)geometricShape;

				PointF centerPt = AsPointF(circle.Center);
				PointF radiusPt = AsPointF(circle.RadiusPoint);
				double radiusLength = Vector.Distance(centerPt, radiusPt);

				var markup = new MarkupEllipse();
				markup.Name = markupText;
				markup.IncludeInAnnotation = circle.IncludeFlag;
				markup.TopLeft = new PointF((float)(centerPt.X - radiusLength), (float)(centerPt.Y - radiusLength));
				markup.BottomRight = new PointF((float)(centerPt.X + radiusLength), (float)(centerPt.Y + radiusLength));
				markup.CalloutLocation = markup.TopLeft - new SizeF(30, 30);
				SetMarkupImageReference(markup, circle);

				return markup;
			}
			if (geometricShape is aim4_dotnet.TwoDimensionEllipse)
			{
				var ellipse = (aim4_dotnet.TwoDimensionEllipse)geometricShape;

				Debug.Assert(ellipse.TwoDimensionSpatialCoordinateCollection.Count == 4, "Ellipse must have four points");
				var firstMajorAxisPt = AsPointF(ellipse.TwoDimensionSpatialCoordinateCollection[0]);
				var secondMajorAxisPt = AsPointF(ellipse.TwoDimensionSpatialCoordinateCollection[1]);
				var firstMinorAxisPt = AsPointF(ellipse.TwoDimensionSpatialCoordinateCollection[2]);
				var secondMinorAxisPt = AsPointF(ellipse.TwoDimensionSpatialCoordinateCollection[3]);

				var markup = new MarkupEllipse();
				markup.Name = markupText;
				markup.IncludeInAnnotation = ellipse.IncludeFlag;
				markup.TopLeft = new PointF(firstMajorAxisPt.X, firstMinorAxisPt.Y);
				markup.BottomRight = new PointF(secondMajorAxisPt.X, secondMinorAxisPt.Y);
				markup.CalloutLocation = markup.TopLeft - new SizeF(30, 30);
				SetMarkupImageReference(markup, ellipse);

				return markup;
			}
			if (geometricShape is aim4_dotnet.TwoDimensionPolyline)
			{
				var polyline = (aim4_dotnet.TwoDimensionPolyline)geometricShape;

				// Check if this is a non-rotated rectangle
				if (polyline.TwoDimensionSpatialCoordinateCollection.Count == 4)
				{
					PointF twoDPoint1 = AsPointF(polyline.TwoDimensionSpatialCoordinateCollection[0]);
					PointF twoDPoint2 = AsPointF(polyline.TwoDimensionSpatialCoordinateCollection[1]);
					PointF twoDPoint3 = AsPointF(polyline.TwoDimensionSpatialCoordinateCollection[2]);
					PointF twoDPoint4 = AsPointF(polyline.TwoDimensionSpatialCoordinateCollection[3]);
					// If it's a rectangle with sides parallel to the axes
					if ((twoDPoint1.X == twoDPoint2.X && twoDPoint2.Y == twoDPoint3.Y && twoDPoint3.X == twoDPoint4.X && twoDPoint4.Y == twoDPoint1.Y) ||
						(twoDPoint1.Y == twoDPoint2.Y && twoDPoint2.X == twoDPoint3.X && twoDPoint3.Y == twoDPoint4.Y && twoDPoint4.X == twoDPoint1.X))
					{
						var markupRectangle = new MarkupRectangle();
						markupRectangle.TopLeft = twoDPoint1;
						markupRectangle.BottomRight = twoDPoint3;
						markupRectangle.Name = markupText;
						markupRectangle.IncludeInAnnotation = polyline.IncludeFlag;
						markupRectangle.CalloutLocation = markupRectangle.TopLeft - new SizeF(30, 30);
						SetMarkupImageReference(markupRectangle, polyline);

						return markupRectangle;
					}
				}

				var points = new List<PointF>();
				foreach (var spatialCoordinate in polyline.TwoDimensionSpatialCoordinateCollection)
					if (spatialCoordinate != null)
						points.Add(AsPointF(spatialCoordinate));

				var markup = new MarkupPolygonal();
				markup.Vertices = points;
				markup.Name = markupText;
				markup.IncludeInAnnotation = polyline.IncludeFlag;
				markup.CalloutLocation = markup.Vertices[0] - new SizeF(30, 30);
				SetMarkupImageReference(markup, polyline);

				return markup;
			}
			if (geometricShape is aim4_dotnet.TwoDimensionMultiPoint)
			{
				var multiPoint = (aim4_dotnet.TwoDimensionMultiPoint)geometricShape;

				IMarkup markup;
				switch (multiPoint.TwoDimensionSpatialCoordinateCollection.Count)
				{
					case 2:
						{
							// Line
							var markupLinear = new MarkupLinear();
							markupLinear.Vertices = new List<PointF>(2);
							markupLinear.Vertices.Add(AsPointF(multiPoint.TwoDimensionSpatialCoordinateCollection[0]));
							markupLinear.Vertices.Add(AsPointF(multiPoint.TwoDimensionSpatialCoordinateCollection[1]));
							markupLinear.CalloutLocation = markupLinear.Vertices[0] - new SizeF(30, 30);
							markup = markupLinear;
						}
						break;
					case 3:
						{
							// Protractor
							var markupProtractor = new MarkupProtractor();
							markupProtractor.Points = new List<PointF>(3);
							markupProtractor.Points.Add(AsPointF(multiPoint.TwoDimensionSpatialCoordinateCollection[0]));
							markupProtractor.Points.Add(AsPointF(multiPoint.TwoDimensionSpatialCoordinateCollection[1]));
							markupProtractor.Points.Add(AsPointF(multiPoint.TwoDimensionSpatialCoordinateCollection[2]));
							markupProtractor.CalloutLocation = markupProtractor.Points[0] - new SizeF(30, 30);
							markup = markupProtractor;
						}
						break;
					default:
						throw new NotImplementedException("Reading non-linear or non-triangular MultiPoint shape is not implemented");
				}

				markup.Name = markupText;
				markup.IncludeInAnnotation = multiPoint.IncludeFlag;
				SetMarkupImageReference(markup, multiPoint);
				return markup;
			}

			// TODO - 3D GeoShapes Conversions

			throw new NotImplementedException();
			return null;
		}

		// Retrieves SOP Instance UID and Referenced Frame Number from the coordinate
		private static void SetMarkupImageReference(IMarkup markup, aim4_dotnet.TwoDimensionGeometricShapeEntity geoShape)
		{
			if (geoShape != null)
			{
				Debug.Assert(geoShape.ReferencedFrameNumber > 0, "Referenced Frame Number must be positive");
				markup.PresentationImageUid = geoShape.ImageReferenceUid.Uid;
				markup.FrameNumber = geoShape.ReferencedFrameNumber.HasValue ? geoShape.ReferencedFrameNumber.Value : 1;
			}
		}

		public static List<aim4_dotnet.InferenceEntity> ToSelectedInferencesList(AimTemplateTreeInferenceNode node)
		{
			var inferences = new List<aim4_dotnet.InferenceEntity>();
			bool isValid = node.Valid;

			double? confidence = null;
			if (node.HasConfidence)
				confidence = node.ConfidenceValue;

			foreach (var term in node.SelectedAllowedTerms)
			{
				inferences.Add(
					new aim4_dotnet.InferenceEntity
						{
							UniqueIdentifier = NewUid,
							TypeCode = ToNativeCodeList(term),
							QuestionTypeCode = ToNativeCodeList(node.QuestionType),
							QuestionIndex = node.ItemNumber,
							AnnotatorConfidence = confidence,
							ImageEvidence = true,
							Label = node.Label,
							IsPresent = true
						});
			}

			return inferences;
		}

		public static List<aim4_dotnet.ImagingObservationEntity> ToSelectedImagingObservationList(AimTemplateTreeImagingObservationNode node)
		{
			var imagingObservations = new List<aim4_dotnet.ImagingObservationEntity>();
			bool isValid = node.Valid;
			foreach (var term in node.SelectedAllowedTerms)
			{
				//var imagingObservation = ToImagingObservation(ToStandardCodeSequence(term), node.Label);
				var imagingObservation = new aim4_dotnet.ImagingObservationEntity
					{
						UniqueIdentifier = NewUid,
						TypeCode = ToNativeCodeList(term),
						QuestionTypeCode = ToNativeCodeList(node.QuestionType),
						QuestionIndex = node.ItemNumber,
						Label = node.Label,
						IsPresent = true
					};

				if (node.HasConfidence)
					imagingObservation.AnnotatorConfidence = node.ConfidenceValue;

				//node
				var selectedImagingObservationCharacteristics = SelectedImagingObservationCharacteristicsDictionary(node);

				// Sort characteristics first according to their ItemNumber
				List<int> imagingObservationCharacteristicIndices =
					CollectionUtils.Sort(selectedImagingObservationCharacteristics.Keys, (i1, i2) => i1.CompareTo(i2));
				foreach (int characteristicIndex in imagingObservationCharacteristicIndices)
				{
					// Find definition of the selected characteristic in the component
					int index = characteristicIndex;
					AimTemplateTreeImagingObservationCharacteristicNode templateImagingObservationCharacteristic =
						CollectionUtils.SelectFirst(node.ImagingObservationCharacteristicTreeNodes, item => item.ItemNumber == index);
					isValid = templateImagingObservationCharacteristic != null &&
							  selectedImagingObservationCharacteristics[characteristicIndex].Count >=
							  Math.Min(templateImagingObservationCharacteristic.CharacteristicQuantificationAllowedTerms.Count, templateImagingObservationCharacteristic.MinCardinality) &&
							  selectedImagingObservationCharacteristics[characteristicIndex].Count <= templateImagingObservationCharacteristic.MaxCardinality;
					if (!isValid)
						break;

					// Put all Anatomic Entity Characteristics into a single collection
					imagingObservation.ImagingObservationCharacteristicCollection =
						CollectionUtils.Concat<aim4_dotnet.ImagingObservationCharacteristic>(
							imagingObservation.ImagingObservationCharacteristicCollection ?? new List<aim4_dotnet.ImagingObservationCharacteristic>(),
							selectedImagingObservationCharacteristics[characteristicIndex]
							);
				}
				if (!isValid)
					break;

				imagingObservations.Add(imagingObservation);
			}
			return imagingObservations;
		}

		public static List<aim4_dotnet.ImagingPhysicalEntity> ToSelectedAnatomicEntitiesList(AimTemplateTreeAnatomicEntityNode node)
		{
			var selectedImagingPhysicalEntities = new List<aim4_dotnet.ImagingPhysicalEntity>();
			bool isValid = node.Valid;
			foreach (var term in node.SelectedAllowedTerms)
			{
				var imagingPhysicalEntity = new aim4_dotnet.ImagingPhysicalEntity
					{
						UniqueIdentifier = NewUid,
						TypeCode = ToNativeCodeList(term),
						QuestionTypeCode = ToNativeCodeList(node.QuestionType),
						QuestionIndex = node.ItemNumber,
						Label = node.Label,
						IsPresent = true
					};

				if (node.HasConfidence)
					imagingPhysicalEntity.AnnotatorConfidence = null; // node.ConfidenceValue;

				//node
				var selectedImagingPhysicalEntityCharacteristics = SelectedAnatomicEntityCharacteristicsDictionary(node);

				// Sort characteristics first according to their ItemNumber
				List<int> anatomicEntityCharacteristicIndices =
					CollectionUtils.Sort(selectedImagingPhysicalEntityCharacteristics.Keys, (i1, i2) => i1.CompareTo(i2));
				foreach (int characteristicIndex in anatomicEntityCharacteristicIndices)
				{
					// Find definition of the selected characteristic in the component
					int index = characteristicIndex;
					AimTemplateTreeAnatomicEntityCharacteristicNode templateAnatomicEntityCharacteristic =
						CollectionUtils.SelectFirst(node.AnatomicEntityCharacteristicTreeNodes,
													item => item.ItemNumber == index);
					isValid = templateAnatomicEntityCharacteristic != null &&
							  selectedImagingPhysicalEntityCharacteristics[characteristicIndex].Count >=
							  Math.Min(templateAnatomicEntityCharacteristic.CharacteristicQuantificationAllowedTerms.Count, templateAnatomicEntityCharacteristic.MinCardinality) &&
							  selectedImagingPhysicalEntityCharacteristics[characteristicIndex].Count <= templateAnatomicEntityCharacteristic.MaxCardinality;
					if (!isValid)
						break;

					// Put all Anatomic Entity Characteristics into a single collection
					imagingPhysicalEntity.ImagingPhysicalEntityCharacteristicCollection =
						CollectionUtils.Concat<aim4_dotnet.ImagingPhysicalEntityCharacteristic>(
							imagingPhysicalEntity.ImagingPhysicalEntityCharacteristicCollection ?? new List<aim4_dotnet.ImagingPhysicalEntityCharacteristic>(),
							selectedImagingPhysicalEntityCharacteristics[characteristicIndex]
							);
				}
				if (!isValid)
					break;

				selectedImagingPhysicalEntities.Add(imagingPhysicalEntity);
			}
			return selectedImagingPhysicalEntities;
		}

		public static List<aim4_dotnet.CharacteristicQuantification> ToCharacteristicQuantifications(CharacteristicQuantificationAllowedTerm allowedTerm)
		{
			var selectedQuantifications = new List<aim4_dotnet.CharacteristicQuantification>();

			foreach (var characteristicQuantification in allowedTerm.CharacteristicQuantifications)
			{
				double? confidence = null;
				if (characteristicQuantification.HasConfidence)
					confidence = characteristicQuantification.ConfidenceValue;

				// NonQuantifiable
				if (characteristicQuantification.SelectedNonQuantifiable != null)
				{
					var codeSequence = characteristicQuantification.SelectedNonQuantifiable;
					selectedQuantifications.Add(
						new aim4_dotnet.NonQuantifiable
							{
								Label = characteristicQuantification.Name,
								TypeCode = ToNativeCode(codeSequence),
								CharacteristicQuantificationIndex = characteristicQuantification.CharacteristicQuantificationIndex,
								AnnotatorConfidence = confidence
							}
						);
				}
				else
				{
					if (characteristicQuantification is AimTemplateTreeNumericalQuantification)
					{
						var numericalQuantification = (AimTemplateTreeNumericalQuantification)characteristicQuantification;
						if (numericalQuantification.SelectedNumerical != null)
							selectedQuantifications.Add(
								new aim4_dotnet.Numerical
									{
										Label = characteristicQuantification.Name,
										Value = numericalQuantification.SelectedNumerical.Value.Value,
										Operator = ToAimComparisonOperator(numericalQuantification.SelectedNumerical.Value.Operator),
										UcumString = numericalQuantification.SelectedNumerical.Value.UcumString,
										CharacteristicQuantificationIndex = characteristicQuantification.CharacteristicQuantificationIndex,
										AnnotatorConfidence = confidence
									});
					}
					else if (characteristicQuantification is AimTemplateTreeQuantileQuantification)
					{
						var quantileQuantification = (AimTemplateTreeQuantileQuantification)characteristicQuantification;
						if (quantileQuantification.SelectedBin != null)
							selectedQuantifications.Add(
								new aim4_dotnet.Quantile
									{
										Label = characteristicQuantification.Name,
										Bins = quantileQuantification.Quantile.Bins,
										SelectedBin = quantileQuantification.SelectedBin.Value,
										MinValue = quantileQuantification.Quantile.MinValue,
										MaxValue = quantileQuantification.Quantile.MaxValue,
										CharacteristicQuantificationIndex = characteristicQuantification.CharacteristicQuantificationIndex,
										AnnotatorConfidence = confidence
									});
					}
					else if (characteristicQuantification is AimTemplateTreeScaleQuantification)
					{
						var scaleQuantification = (AimTemplateTreeScaleQuantification)characteristicQuantification;
						if (scaleQuantification.SelectedScaleLevel != null)
							selectedQuantifications.Add(
								new aim4_dotnet.Scale
									{
										Label = characteristicQuantification.Name,
										Value = scaleQuantification.SelectedScaleLevel.Value.Value,
										ValueDescription = scaleQuantification.SelectedScaleLevel.Value.ValueDescription,
										Comment = scaleQuantification.SelectedScaleLevel.Value.ValueLabel,
										CharacteristicQuantificationIndex = characteristicQuantification.CharacteristicQuantificationIndex,
										AnnotatorConfidence = confidence
									});
					}
					else if (characteristicQuantification is AimTemplateTreeIntervalQuantification)
					{
						var intervalQuantification = (AimTemplateTreeIntervalQuantification)characteristicQuantification;
						if (intervalQuantification.SelectedInterval != null)
							selectedQuantifications.Add(
								new aim4_dotnet.Interval
									{
										Label = characteristicQuantification.Name,
										MinValue = intervalQuantification.SelectedInterval.Value.MinValue,
										MaxValue = intervalQuantification.SelectedInterval.Value.MaxValue,
										MinOperator = ToAimComparisonOperator(intervalQuantification.SelectedInterval.Value.MinOperator),
										MaxOperator = ToAimComparisonOperator(intervalQuantification.SelectedInterval.Value.MaxOperator),
										UcumString = intervalQuantification.SelectedInterval.Value.UcumString,
										CharacteristicQuantificationIndex = characteristicQuantification.CharacteristicQuantificationIndex,
										AnnotatorConfidence = confidence
									});
					}
					else
						Debug.Assert(false, "Unexpected Template Tree Quantification Type");
				}
			}

			return selectedQuantifications;
		}

		public static aim4_dotnet.ComparisonOperatorIdentifier ToAimComparisonOperator(ComparisonOperator comparisonOperator)
		{
			var aimOperator = aim4_dotnet.ComparisonOperatorIdentifier.None;

			switch (comparisonOperator)
			{
				case ComparisonOperator.Equal:
					aimOperator = aim4_dotnet.ComparisonOperatorIdentifier.Equal;
					break;
				case ComparisonOperator.GreaterThan:
					aimOperator = aim4_dotnet.ComparisonOperatorIdentifier.GreaterThan;
					break;
				case ComparisonOperator.GreaterThanEqual:
					aimOperator = aim4_dotnet.ComparisonOperatorIdentifier.GreaterThanEqual;
					break;
				case ComparisonOperator.LessThan:
					aimOperator = aim4_dotnet.ComparisonOperatorIdentifier.LessThan;
					break;
				case ComparisonOperator.LessThanEqual:
					aimOperator = aim4_dotnet.ComparisonOperatorIdentifier.LessThanEqual;
					break;
				case ComparisonOperator.NotEqual:
					aimOperator = aim4_dotnet.ComparisonOperatorIdentifier.NotEqual;
					break;
			}

			return aimOperator;
		}

		public static Dictionary<int, List<aim4_dotnet.ImagingPhysicalEntityCharacteristic>> SelectedAnatomicEntityCharacteristicsDictionary(AimTemplateTreeAnatomicEntityNode anatomicEntity)
		{
			return anatomicEntity.SelectedAnatomicEntityCharacteristicTreeNodes.ToDictionary(aec => aec.ItemNumber,
				aec => new List<aim4_dotnet.ImagingPhysicalEntityCharacteristic>(SelectedAnatomicEntityCharacteristics(aec)));
		}

		public static Dictionary<int, List<aim4_dotnet.ImagingObservationCharacteristic>> SelectedImagingObservationCharacteristicsDictionary(AimTemplateTreeImagingObservationNode imagingObservation)
		{
			return imagingObservation.SelectedImagingObservationCharacteristicTreeNodes.ToDictionary(ioc => ioc.ItemNumber,
				ioc => new List<aim4_dotnet.ImagingObservationCharacteristic>(SelectedImagingObservationCharacteristics(ioc)));
		}

		public static List<aim4_dotnet.ImagingPhysicalEntityCharacteristic> SelectedAnatomicEntityCharacteristics(AimTemplateTreeAnatomicEntityCharacteristicNode node)
		{
			var imagingPhysicalEntityCharacteristics = new List<aim4_dotnet.ImagingPhysicalEntityCharacteristic>();

			if (node.SelectedCharacteristicQuantificationAllowedTerms.IsNullOrEmpty())
			{
				// Provide default NULL answer when answers are optional
				if (node.MinCardinality == 0)
				{
					imagingPhysicalEntityCharacteristics.Add(
						new aim4_dotnet.ImagingPhysicalEntityCharacteristic
							{
								TypeCode = new List<aim4_dotnet.iso_21090.CD>
										{
											new aim4_dotnet.iso_21090.CD(
												AimAnnotationComponent.NullCodeValue.CodeValue,
												AimAnnotationComponent.NullCodeValue.CodeMeaning,
												AimAnnotationComponent.NullCodeValue.CodingSchemeDesignator,
												AimAnnotationComponent.NullCodeValue.CodingSchemeVersion)
										},
								QuestionTypeCode = ToNativeCodeList(node.QuestionType),
								QuestionIndex = node.ItemNumber,
								Label = node.Label
							});
				}
			}
			else
			{
				foreach (var validTerm in node.SelectedCharacteristicQuantificationAllowedTerms)
				{
					if (validTerm == null)
						continue;

					double? confidence = null;
					if (node.HasConfidence)
						confidence = node.ConfidenceValue;

					if (validTerm.CharacteristicQuantifications != null && validTerm.CharacteristicQuantifications.All(quantification => quantification.Valid))
					{
						imagingPhysicalEntityCharacteristics.Add(
							new aim4_dotnet.ImagingPhysicalEntityCharacteristic
							{
								TypeCode = ToNativeCodeList(validTerm),
								QuestionTypeCode = ToNativeCodeList(node.QuestionType),
								QuestionIndex = node.ItemNumber,
								Label = node.Label,
								AnnotatorConfidence = confidence,
								CharacteristicQuantificationCollection = ToCharacteristicQuantifications(validTerm)
							});

					}
					else
					{
						imagingPhysicalEntityCharacteristics.Add(
							new aim4_dotnet.ImagingPhysicalEntityCharacteristic
								{
									TypeCode = ToNativeCodeList(validTerm),
									QuestionTypeCode = ToNativeCodeList(node.QuestionType),
									QuestionIndex = node.ItemNumber,
									Label = node.Label,
									AnnotatorConfidence = confidence
								});
					}
				}
			}

			return imagingPhysicalEntityCharacteristics;
		}

		public static List<aim4_dotnet.ImagingObservationCharacteristic> SelectedImagingObservationCharacteristics(AimTemplateTreeImagingObservationCharacteristicNode node)
		{
			var imagingObservationCharacteristics = new List<aim4_dotnet.ImagingObservationCharacteristic>();

			if (node.SelectedCharacteristicQuantificationAllowedTerms.IsNullOrEmpty())
			{
				// Provide default NULL answer when answers are optional
				if (node.MinCardinality == 0)
				{
					imagingObservationCharacteristics.Add(
						new aim4_dotnet.ImagingObservationCharacteristic
						{
							TypeCode = new List<aim4_dotnet.iso_21090.CD>
										{
											new aim4_dotnet.iso_21090.CD(
												AimAnnotationComponent.NullCodeValue.CodeValue,
												AimAnnotationComponent.NullCodeValue.CodeMeaning,
												AimAnnotationComponent.NullCodeValue.CodingSchemeDesignator,
												AimAnnotationComponent.NullCodeValue.CodingSchemeVersion)
										},
							QuestionTypeCode = ToNativeCodeList(node.QuestionType),
							QuestionIndex = node.ItemNumber,
							Label = node.Label
						});
				}
			}
			else
			{
				foreach (var validTerm in node.SelectedCharacteristicQuantificationAllowedTerms)
				{
					double? confidence = null;
					if (node.HasConfidence)
						confidence = node.ConfidenceValue;

					if (validTerm.CharacteristicQuantifications != null && validTerm.CharacteristicQuantifications.All(quantification => quantification.Valid))
					{

						imagingObservationCharacteristics.Add(
							new aim4_dotnet.ImagingObservationCharacteristic
							{
								TypeCode = ToNativeCodeList(validTerm),
								QuestionTypeCode = ToNativeCodeList(node.QuestionType),
								QuestionIndex = node.ItemNumber,
								Label = node.Label,
								AnnotatorConfidence = confidence,
								CharacteristicQuantificationCollection = ToCharacteristicQuantifications(validTerm)
							});
							
					}
					else
					{
						imagingObservationCharacteristics.Add(
							new aim4_dotnet.ImagingObservationCharacteristic
								{
									TypeCode = ToNativeCodeList(validTerm),
									QuestionTypeCode = ToNativeCodeList(node.QuestionType),
									QuestionIndex = node.ItemNumber,
									Label = node.Label,
									AnnotatorConfidence = confidence
								});
							
					}
				}
			}

			return imagingObservationCharacteristics;
		}

		private static aim4_dotnet.iso_21090.II NewUid
		{
			get { return new aim4_dotnet.iso_21090.II(DicomUid.GenerateUid().UID); }
		}

		public static TemplateTree.StandardCodeSequence ToStandardCodeSequence(aim4_dotnet.iso_21090.CD code)
		{
			return code == null ? null : new TemplateTree.StandardCodeSequence(code.CodeValue, code.CodeMeaning, code.CodingSchemeDesignator, code.CodingSchemeVersion);
		}

		public static TemplateTree.StandardValidTerm ToStandardValidTerm(List<aim4_dotnet.iso_21090.CD> codes)
		{
			if (codes.IsNullOrEmpty())
				return null;

			var firstCode = codes.First();
			return new TemplateTree.StandardValidTerm(
				ToStandardCodeSequence(firstCode),
				new List<TemplateTree.StandardValidTerm>
					{
						ToStandardValidTerm(codes.Where(code => !Equals(code, firstCode)).ToList())
					});
		}

		private static List<aim4_dotnet.iso_21090.CD> ToNativeCodeList(TemplateTree.StandardValidTerm standardValidTerm)
		{
			if (standardValidTerm == null || standardValidTerm.StandardCodeSequence == null)
				return null;

			var codeList = ToNativeCodeList(standardValidTerm.StandardCodeSequence);

			foreach (var validTerm in standardValidTerm.StandardValidTerms)
			{
				if (validTerm == null)
					continue;
				var subCodeList = ToNativeCodeList(validTerm);
				if (subCodeList != null)
					codeList.AddRange(subCodeList);
			}

			return codeList;
		}

		private static List<aim4_dotnet.iso_21090.CD> ToNativeCodeList(TemplateTree.StandardCodeSequence standardCodeSequence)
		{
			if (standardCodeSequence == null)
				return null;

			var codeList = new List<aim4_dotnet.iso_21090.CD>
				{
					new aim4_dotnet.iso_21090.CD
						{
							CodeMeaning = standardCodeSequence.CodeMeaning,
							CodeValue = standardCodeSequence.CodeValue,
							CodingSchemeDesignator = standardCodeSequence.CodingSchemeDesignator,
							CodingSchemeVersion = standardCodeSequence.CodingSchemeVersion
						}
				};

			return codeList;
		}

		private static aim4_dotnet.iso_21090.CD ToNativeCode(TemplateTree.StandardCodeSequence standardCodeSequence)
		{
			if (standardCodeSequence == null)
				return null;

			return new aim4_dotnet.iso_21090.CD
				{
					CodeMeaning = standardCodeSequence.CodeMeaning,
					CodeValue = standardCodeSequence.CodeValue,
					CodingSchemeDesignator = standardCodeSequence.CodingSchemeDesignator,
					CodingSchemeVersion = standardCodeSequence.CodingSchemeVersion
				};
		}

		private static bool IsNullCodeList(List<aim4_dotnet.iso_21090.CD> codeList)
		{
			if (codeList.IsNullOrEmpty())
				return false;

			return AimTemplateTreeUtilities.IsNullCodeSequence(ToStandardCodeSequence(codeList.First()));
		}

		/// <summary>
		/// Determines whether there is a path in the standardValidTerm tree that matches the given codeList
		/// </summary>
		/// <param name="standardValidTerm">Tempalate's StandardValidTerm to compare</param>
		/// <param name="codeList">code array to compare</param>
		/// <returns><code>true</code> if <paramref name="codeList"/> is a complete match to a path in the <paramref name="standardValidTerm"/>; false - if does not match</returns>
		private static bool DoTheyMatch(TemplateTree.StandardValidTerm standardValidTerm, List<aim4_dotnet.iso_21090.CD> codeList)
		{
			if (standardValidTerm == null)
				return codeList.IsNullOrEmpty();

			if (codeList.IsNullOrEmpty())
				return false;

			if (DoTheyMatch(standardValidTerm.StandardCodeSequence, codeList[0]))
			{
				if (standardValidTerm.StandardValidTerms.IsNullOrEmpty())
					return codeList.Count == 1;

				if (codeList.Count == 1)
					return false;

				// Recursively check whether a child StandardValidTerm matches the rest of the codes in the list
				var reducedCodeList = codeList.GetRange(1, codeList.Count - 1);
				return standardValidTerm.StandardValidTerms.Any(validTerm => DoTheyMatch(validTerm, reducedCodeList));
			}

			return false;
		}

		private static bool DoTheyMatch(TemplateTree.StandardCodeSequence standardCodeSequence, aim4_dotnet.iso_21090.CD code)
		{
			if (standardCodeSequence == null)
				return code == null;

			if (code == null)
				return false;

			return string.Equals(standardCodeSequence.CodeMeaning, code.CodeMeaning) &&
				   string.Equals(standardCodeSequence.CodeValue, code.CodeValue) &&
				   string.Equals(standardCodeSequence.CodingSchemeDesignator, code.CodingSchemeDesignator) &&
				   StringEquals(standardCodeSequence.CodingSchemeVersion, code.CodingSchemeVersion);
		}

		private static readonly char[] HEX_DIGIT = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		/// <summary>
		/// Create 8 char alphanumeric string from a given string
		/// of alphanumerical <paramref name="val"/> string
		/// </summary>
		public static string ToHex(string val)
		{
			int valToInt = val.GetHashCode();
			char[] ch8 = new char[8];
			for (int i = 8; --i >= 0; valToInt >>= 4)
			{
				ch8[i] = HEX_DIGIT[valToInt & 0xf];
			}
			return new string(ch8);
		}

		/// <summary>
		/// Recursively flattens a hierarchy of valid terms into a single StandardCodeSequence
		/// by concatenating the codeValue and codeMeaning fields.
		/// </summary>
		/// <param name="standardValidTerm"></param>
		/// <returns></returns>
		private static TemplateTree.StandardCodeSequence CollapseStandardValidTerm(TemplateTree.StandardValidTerm standardValidTerm)
		{
			string codeValue = standardValidTerm.StandardCodeSequence.CodeValue;
			string codingSchemeDesignator = standardValidTerm.StandardCodeSequence.CodingSchemeDesignator;
			string codingSchemeVersion = standardValidTerm.StandardCodeSequence.CodingSchemeVersion;
			string codeMeaning = standardValidTerm.StandardCodeSequence.CodeMeaning;
			const string delimiter = ", ";

			if (standardValidTerm.StandardValidTerms.Count > 0)
				codingSchemeDesignator = COLLAPSED_VALID_TERM_CODING_SCHEME_DESIGNATOR;

			foreach (TemplateTree.StandardValidTerm childStandardValidTerm in standardValidTerm.StandardValidTerms)
			{
				TemplateTree.StandardCodeSequence standardCodeSequence = CollapseStandardValidTerm(childStandardValidTerm);
				if (!string.IsNullOrEmpty(standardCodeSequence.CodeValue))
					codeValue += delimiter + standardCodeSequence.CodeValue;
				if (!string.IsNullOrEmpty(standardCodeSequence.CodeMeaning))
					codeMeaning += delimiter + standardCodeSequence.CodeMeaning;
			}

			return new TemplateTree.StandardCodeSequence(codeValue, codeMeaning, codingSchemeDesignator, codingSchemeVersion);
		}

		/// <summary>
		/// Returns a StandardCodeSequence from a recursively collapsed or flattened StandardValidTerm.
		/// </summary>
		/// <param name="standardValidTerm"></param>
		/// <returns></returns>
		public static TemplateTree.StandardCodeSequence ToStandardCodeSequence(TemplateTree.StandardValidTerm standardValidTerm)
		{
			const int codeValueLength = 16;
			const int codeMeaningLength = 64;

			TemplateTree.StandardCodeSequence standardCodeSequence = CollapseStandardValidTerm(standardValidTerm);

			string codeValue = standardCodeSequence.CodeValue;
			string codeMeaning = standardCodeSequence.CodeMeaning;
			string codingSchemeDesignator = standardCodeSequence.CodingSchemeDesignator;
			string codingSchemeVersion = standardCodeSequence.CodingSchemeVersion;

			if (standardValidTerm.StandardValidTerms.Count > 0)
			{
				codeValue = ToHex(codeValue);
				if (codeValue.Length > codeValueLength)
					codeValue = codeValue.Substring(0, codeValueLength);
				if (codeMeaning.Length > codeMeaningLength)
					codeMeaning = codeMeaning.Substring(0, codeMeaningLength);
			}

			return new TemplateTree.StandardCodeSequence(
				codeValue,
				codeMeaning,
				codingSchemeDesignator,
				codingSchemeVersion);
		}
	}
}
