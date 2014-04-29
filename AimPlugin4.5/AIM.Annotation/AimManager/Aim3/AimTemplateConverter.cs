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
using System.Text;
using AIM.Annotation.Configuration;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.ImageViewer.Mathematics;

namespace AIM.Annotation.AimManager.Aim3
{
    internal static class AimTemplateConverter
    {
        private const string COLLAPSED_VALID_TERM_CODING_SCHEME_DESIGNATOR = "AIM3-COMPAT";

        public static TemplateTree.AimTemplateTree AimAnnotationToAimTemplateTree(Aim3AnnotationInstance annotationInstance, TemplateTree.AimTemplateTree template)
        {
            if (annotationInstance == null || annotationInstance.AimAnnotation == null)
                return null;

            var annotation = annotationInstance.AimAnnotation;
            if (annotation.AnatomyEntityCollection != null)
            {
                foreach (var ae in annotation.AnatomyEntityCollection)
                {
                    if (IsNullCodeSequence(ToStandardCodeSequence(ae)))
                        continue;

                    TemplateTree.AimTemplateTreeAnatomicEntityNode matchingTreeNode =
                        template.TemplateNodes.OfType<TemplateTree.AimTemplateTreeAnatomicEntityNode>().FirstOrDefault(treeAe => treeAe.Label == ae.Label);
                    if (matchingTreeNode != null)
                    {
                        TemplateTree.AimTemplateTreeAllowedTerm matchingAllowedTerm =
                            matchingTreeNode.AllowedTerms.FirstOrDefault(treeAe => ToStandardCodeSequence(treeAe).CodeValue == ae.CodeValue);
                        if (matchingAllowedTerm != null)
                        {
                            matchingAllowedTerm.Selected = true;
                        }
                        else
                            return null;

                        if (matchingTreeNode.HasConfidence && ae.AnnotatorConfidence.HasValue)
                            matchingTreeNode.ConfidenceValue = ae.AnnotatorConfidence.Value;
                    }
                    else
                        return null;

                    if (ae.AnatomicEntityCharacteristicCollection != null)
                    {
                        foreach (var aec in ae.AnatomicEntityCharacteristicCollection)
                        {
                            if (IsNullCodeSequence(ToStandardCodeSequence(aec)))
                                continue;

                            TemplateTree.AimTemplateTreeAnatomicEntityCharacteristicNode matchingAecTreeNode =
                                matchingTreeNode.AnatomicEntityCharacteristicTreeNodes.FirstOrDefault(treeAec => treeAec.Label == aec.Label);
                            if (matchingAecTreeNode != null)
                            {
                                TemplateTree.CharacteristicQuantificationAllowedTerm matchingAllowedTerm =
                                    matchingAecTreeNode.CharacteristicQuantificationAllowedTerms.FirstOrDefault(treeAec => ToStandardCodeSequence(treeAec).CodeValue == aec.CodeValue);
                                if (matchingAllowedTerm != null)
                                {
                                    matchingAllowedTerm.Selected = true;

                                    foreach (var quantification in matchingAllowedTerm.CharacteristicQuantifications)
                                    {
                                        if (ReadBackCharacteristicQuantificationFromAnnotation(aec.CharacteristicQuantificationCollection, quantification) == null)
                                            return null;
                                    }
                                }
                                else
                                    return null;

                                if (matchingAecTreeNode.HasConfidence && aec.AnnotatorConfidence.HasValue)
                                    matchingAecTreeNode.ConfidenceValue = aec.AnnotatorConfidence.Value;

                            }
                            else
                                return null;
                        }
                    }

                }
            }
            if (annotation.ImagingObservationCollection != null)
            {
                foreach (var io in annotation.ImagingObservationCollection)
                {
                    if (IsNullCodeSequence(ToStandardCodeSequence(io)))
                        continue;

                    TemplateTree.AimTemplateTreeImagingObservationNode matchingTreeNode =
                        template.TemplateNodes.OfType<TemplateTree.AimTemplateTreeImagingObservationNode>().FirstOrDefault(
                            treeIo => treeIo.Label == io.Label);
                    if (matchingTreeNode != null)
                    {
                        TemplateTree.AimTemplateTreeAllowedTerm matchingAllowedTerm =
                            matchingTreeNode.AllowedTerms.FirstOrDefault(
                                treeIo => ToStandardCodeSequence(treeIo).CodeValue == io.CodeValue);
                        if (matchingAllowedTerm != null)
                        {
                            matchingAllowedTerm.Selected = true;
                        }
                        else
                            return null;

                        if (matchingTreeNode.HasConfidence && io.AnnotatorConfidence.HasValue)
                            matchingTreeNode.ConfidenceValue = io.AnnotatorConfidence.Value;
                    }
                    else
                        return null;

                    if (io.ImagingObservationCharacteristicCollection != null)
                    {
                        foreach (var ioc in io.ImagingObservationCharacteristicCollection)
                        {
                            if (IsNullCodeSequence(ToStandardCodeSequence(ioc)))
                                continue;

                            TemplateTree.AimTemplateTreeImagingObservationCharacteristicNode matchingIocTreeNode =
                                matchingTreeNode.ImagingObservationCharacteristicTreeNodes.FirstOrDefault(
                                    treeIoc => treeIoc.Label == ioc.Label);
                            if (matchingIocTreeNode != null)
                            {
                                TemplateTree.CharacteristicQuantificationAllowedTerm matchingAllowedTerm =
                                    matchingIocTreeNode.CharacteristicQuantificationAllowedTerms.FirstOrDefault(
                                        treeIoc => ToStandardCodeSequence(treeIoc).CodeValue == ioc.CodeValue);
                                if (matchingAllowedTerm != null)
                                {
                                    matchingAllowedTerm.Selected = true;

                                    foreach (var quantification in matchingAllowedTerm.CharacteristicQuantifications)
                                    {
                                        if (ReadBackCharacteristicQuantificationFromAnnotation(ioc.CharacteristicQuantificationCollection, quantification) == null)
                                            return null;
                                    }
                                }
                                else
                                    return null;

                                if (matchingIocTreeNode.HasConfidence && ioc.AnnotatorConfidence.HasValue)
                                    matchingIocTreeNode.ConfidenceValue = ioc.AnnotatorConfidence.Value;

                            }
                            else
                                return null;
                        }
                    }
                }
            }
            if (annotation.CalculationCollection != null)
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
            if (annotation.InferenceCollection != null)
            {
                foreach (var inference in annotation.InferenceCollection)
                {
                    if (IsNullCodeSequence(ToStandardCodeSequence(inference)))
                        continue;

                    foreach (var inferenceNode in template.TemplateNodes.OfType<TemplateTree.AimTemplateTreeInferenceNode>())
                    {
                        TemplateTree.AimTemplateTreeAllowedTerm matchingAllowedTerm =
                            inferenceNode.AllowedTerms.FirstOrDefault(
                                term => ToStandardCodeSequence(term).CodeValue == inference.CodeValue);
                        if (matchingAllowedTerm != null)
                            matchingAllowedTerm.Selected = true;
                    }
                }
            }
            template.Markup.Clear();
            if (annotation is aim_dotnet.ImageAnnotation)
            {
                var imageAnnotation = (aim_dotnet.ImageAnnotation)annotation;
                var annotationName = string.IsNullOrEmpty(imageAnnotation.Name) ? "" : imageAnnotation.Name;

                if (imageAnnotation.GeometricShapeCollection != null)
                {
                    foreach (var geometricShape in imageAnnotation.GeometricShapeCollection)
                    {
                        var markup = ToMarkup(geometricShape, annotationName);
                        if (markup != null)
                            template.Markup.Add(markup);
                    }
                }
                if (imageAnnotation.TextAnnotationCollection != null)
                {
                    foreach (var textAnnotation in imageAnnotation.TextAnnotationCollection)
                    {
                        if (textAnnotation.ConnectorPoints != null && textAnnotation.ConnectorPoints.SpatialCoordinateCollection != null)
                        {
                            var calloutText = AimHelpers.FormatPointCalloutText(annotationName, textAnnotation.Text);
                            switch (textAnnotation.ConnectorPoints.SpatialCoordinateCollection.Count)
                            {
                                case 1:
                                    {
                                        var markup = new TemplateTree.MarkupPoint();
                                        markup.Name = annotationName;
                                        markup.IncludeInAnnotation = textAnnotation.ConnectorPoints.IsIncludeFlag;
                                        markup.Point = AimNativeConverter.AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
                                        markup.CalloutText = calloutText;
                                        markup.CalloutLocation = new PointF(markup.Point.X, markup.Point.Y);
                                        SetMarkupImageReference(markup, textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
                                        markup.UseCrosshair = AimSettings.Default.UseCrosshairsForTextCallouts;
                                        template.Markup.Add(markup);
                                    }
                                    break;
                                case 2:
                                    {
                                        var markup = new TemplateTree.MarkupPoint();
                                        markup.Name = annotationName;
                                        markup.IncludeInAnnotation = textAnnotation.ConnectorPoints.IsIncludeFlag;
                                        markup.Point = AimNativeConverter.AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
                                        markup.CalloutText = calloutText;
                                        markup.CalloutLocation = AimNativeConverter.AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[1]);
                                        SetMarkupImageReference(markup, textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
                                        markup.UseCrosshair = AimSettings.Default.UseCrosshairsForTextCallouts;
                                        template.Markup.Add(markup);
                                    }
                                    break;
                                default:
                                    Platform.Log(LogLevel.Error, "TextAnnotation has [{0}] Connector Points", textAnnotation.ConnectorPoints.SpatialCoordinateCollection.Count);
                                    break;
                            }
                        }
                    }
                }
            }
            return template;
        }

        /// <summary>
        /// Matches an AimTempalteTreeCharacteristicQuantification from to a characteristic quantification from aim_dotnet.annotation
        /// ICharacteristicQuantification collection
        /// </summary>
        /// <param name="annotationCharacteristicQuantifications"></param>
        /// <param name="templateTreeCharacteristicQuantification"></param>
        /// <returns></returns>
        public static TemplateTree.AimTemplateTreeCharacteristicQuantification ReadBackCharacteristicQuantificationFromAnnotation(List<aim_dotnet.ICharacteristicQuantification> annotationCharacteristicQuantifications, TemplateTree.AimTemplateTreeCharacteristicQuantification templateTreeCharacteristicQuantification)
        {
            if (annotationCharacteristicQuantifications != null && annotationCharacteristicQuantifications.Count > 0)
            {
                aim_dotnet.NonQuantifiable nonQuantifiable =
                    annotationCharacteristicQuantifications.OfType
                        <aim_dotnet.NonQuantifiable>().FirstOrDefault();

                if (nonQuantifiable != null)
                {
                    TemplateTree.StandardCodedTerm matchingNonQuantifiable =
                        templateTreeCharacteristicQuantification.NonQuantifiables.FirstOrDefault(
                            nonQuant =>
                            AimDotNetNonQuantifiableEqualsTemplateTreeNonQuantifiable(
                                nonQuantifiable, nonQuant));
                    if (matchingNonQuantifiable != null)
                        templateTreeCharacteristicQuantification.SelectedNonQuantifiable =
                            matchingNonQuantifiable;
                }
                else
                {
                    if (templateTreeCharacteristicQuantification is TemplateTree.AimTemplateTreeScaleQuantification)
                    {
                        var scaleQuantification = templateTreeCharacteristicQuantification as TemplateTree.AimTemplateTreeScaleQuantification;

                        aim_dotnet.Scale matchingScale =
                            annotationCharacteristicQuantifications.OfType
                                <aim_dotnet.Scale>()
                                .FirstOrDefault();

                        if (matchingScale != null)
                        {

                            TemplateTree.ScaleLevel matchingTreeScaleLevel =
                                scaleQuantification.Scale.ScaleLevels.FirstOrDefault(
                                    scaleLevel =>
                                    AimDotNetScaleEqualsTemplateTreeScaleLevel(
                                        matchingScale,
                                        scaleLevel));

                            scaleQuantification.SelectedScaleLevel = matchingTreeScaleLevel;
                        }
                        else
                            return null;
                    }

                    if (templateTreeCharacteristicQuantification is TemplateTree.AimTemplateTreeQuantileQuantification)
                    {
                        var quantileQuantification = templateTreeCharacteristicQuantification as TemplateTree.AimTemplateTreeQuantileQuantification;

                        var quantile = annotationCharacteristicQuantifications.OfType
                            <aim_dotnet.Quantile>().FirstOrDefault();

                        if (quantile != null)
                            quantileQuantification.SelectedBin = quantile.Bin;
                        else
                            return null;
                    }

                    if (templateTreeCharacteristicQuantification is TemplateTree.AimTemplateTreeIntervalQuantification)
                    {
                        var intervalQuantification = templateTreeCharacteristicQuantification as TemplateTree.AimTemplateTreeIntervalQuantification;

                        aim_dotnet.Interval matchingInterval =
                            annotationCharacteristicQuantifications.OfType
                                <aim_dotnet.Interval>().
                                FirstOrDefault();

                        if (matchingInterval != null)
                        {

                            TemplateTree.Interval matchingTreeInterval =
                                intervalQuantification.Intervals.FirstOrDefault(
                                    interval =>
                                    AimDotNetIntervalEqualsTemplateTreeInterval(
                                        matchingInterval,
                                        interval));

                            intervalQuantification.SelectedInterval = matchingTreeInterval;
                        }
                        else
                            return null;
                    }

                    if (templateTreeCharacteristicQuantification is TemplateTree.AimTemplateTreeNumericalQuantification)
                    {
                        var numericalQuantification = templateTreeCharacteristicQuantification as TemplateTree.AimTemplateTreeNumericalQuantification;

                        aim_dotnet.Numerical matchingNumerical =
                            annotationCharacteristicQuantifications.OfType
                                <aim_dotnet.Numerical>().
                                FirstOrDefault();

                        if (matchingNumerical != null)
                        {
                            TemplateTree.Numerical matchingTreeNumerical =
                                numericalQuantification.Numericals.FirstOrDefault(
                                    numerical =>
                                    AimDotNetNumericalEqualsTemplateTreeNumerical(
                                        matchingNumerical,
                                        numerical));

                            numericalQuantification.SelectedNumerical =
                                matchingTreeNumerical;
                        }
                        else
                            return null;
                    }
                }
            }
            return templateTreeCharacteristicQuantification;
        }

        public static bool AimDotNetScaleEqualsTemplateTreeScaleLevel(aim_dotnet.Scale a, TemplateTree.ScaleLevel b)
        {
            return a.Value == b.Value;
        }

        public static bool AimDotNetNonQuantifiableEqualsTemplateTreeNonQuantifiable(aim_dotnet.NonQuantifiable a, TemplateTree.StandardCodedTerm b)
        {
            return String.Equals(a.CodeValue, b.CodeValue) &&
                String.Equals(a.CodeMeaning, b.CodeMeaning) &&
                StringEquals(a.CodingSchemeVersion, b.CodingSchemeVersion) &&
                String.Equals(a.CodingSchemeDesignator, b.CodingSchemeDesignator);
        }

        /// <summary>
        /// Does a string equals comparison where null and String.Empty are equivalent.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static bool StringEquals(string a, string b)
        {
            if (String.IsNullOrEmpty(a) && String.IsNullOrEmpty(b))
                return true;
            return String.Equals(a, b);
        }

        public static bool AimDotNetIntervalEqualsTemplateTreeInterval(aim_dotnet.Interval a, TemplateTree.Interval b)
        {
            return
                a.MinValue == b.MinValue &&
                a.MaxValue == b.MaxValue &&
                a.MinOperator == ToAimComparisonOperator(b.MinOperator) &&
                a.MaxOperator == ToAimComparisonOperator(b.MaxOperator) &&
                a.UcumString == b.UcumString;
        }

        public static bool AimDotNetNumericalEqualsTemplateTreeNumerical(aim_dotnet.Numerical a, TemplateTree.Numerical b)
        {
            return
                a.Value == b.Value &&
                a.UcumString == b.UcumString &&
                a.Operator == ToAimComparisonOperator(b.Operator);
        }

        public static TemplateTree.IMarkup ToMarkup(aim_dotnet.IGeometricShape geometricShape, string markupText)
        {
            if (geometricShape == null)
                return null;

            if (geometricShape is aim_dotnet.Point)
            {
                var point = (aim_dotnet.Point)geometricShape;

                var markup = new TemplateTree.MarkupPoint();
                markup.Name = markupText;
                markup.IncludeInAnnotation = point.IsIncludeFlag;
                markup.Point = AimNativeConverter.AsPointF(point.Center);
                markup.CalloutText = string.Empty; // markupText;
                markup.CalloutLocation = markup.Point - new SizeF(30, 30);
                SetMarkupImageReference(markup, point.Center);

                return markup;
            }
            if (geometricShape is aim_dotnet.Circle)
            {
                var circle = (aim_dotnet.Circle)geometricShape;

                PointF centerPt = AimNativeConverter.AsPointF(circle.Center);
                PointF radiusPt = AimNativeConverter.AsPointF(circle.RadiusPoint);
                double radiusLength = Vector.Distance(centerPt, radiusPt);

                var markup = new TemplateTree.MarkupEllipse();
                markup.Name = markupText;
                markup.IncludeInAnnotation = circle.IsIncludeFlag;
                markup.TopLeft = new PointF((float)(centerPt.X - radiusLength), (float)(centerPt.Y - radiusLength));
                markup.BottomRight = new PointF((float)(centerPt.X + radiusLength), (float)(centerPt.Y + radiusLength));
                markup.CalloutLocation = markup.TopLeft - new SizeF(30, 30);
                SetMarkupImageReference(markup, circle.Center);

                return markup;
            }
            if (geometricShape is aim_dotnet.Ellipse)
            {
                var ellipse = (aim_dotnet.Ellipse)geometricShape;

                Debug.Assert(ellipse.EllipseCollection.Count == 4, "Ellipse must have four points");
                var firstMajorAxisPt = AimNativeConverter.AsPointF(ellipse.EllipseCollection[0]);
                var secondMajorAxisPt = AimNativeConverter.AsPointF(ellipse.EllipseCollection[1]);
                var firstMinorAxisPt = AimNativeConverter.AsPointF(ellipse.EllipseCollection[2]);
                var secondMinorAxisPt = AimNativeConverter.AsPointF(ellipse.EllipseCollection[3]);

                var markup = new TemplateTree.MarkupEllipse();
                markup.Name = markupText;
                markup.IncludeInAnnotation = ellipse.IsIncludeFlag;
                markup.TopLeft = new PointF(firstMajorAxisPt.X, firstMinorAxisPt.Y);
                markup.BottomRight = new PointF(secondMajorAxisPt.X, secondMinorAxisPt.Y);
                markup.CalloutLocation = markup.TopLeft - new SizeF(30, 30);
                SetMarkupImageReference(markup, ellipse.EllipseCollection[0]);

                return markup;
            }
            if (geometricShape is aim_dotnet.Polyline)
            {
                var polyline = (aim_dotnet.Polyline)geometricShape;

                // Check if this is a non-rotated rectangle
                if (polyline.SpatialCoordinateCollection.Count == 4)
                {
                    PointF twoDPoint1 = AimNativeConverter.AsPointF(polyline.SpatialCoordinateCollection[0]);
                    PointF twoDPoint2 = AimNativeConverter.AsPointF(polyline.SpatialCoordinateCollection[1]);
                    PointF twoDPoint3 = AimNativeConverter.AsPointF(polyline.SpatialCoordinateCollection[2]);
                    PointF twoDPoint4 = AimNativeConverter.AsPointF(polyline.SpatialCoordinateCollection[3]);
                    // If it's a rectangle with sides parallel to the axes
                    if ((twoDPoint1.X == twoDPoint2.X && twoDPoint2.Y == twoDPoint3.Y && twoDPoint3.X == twoDPoint4.X && twoDPoint4.Y == twoDPoint1.Y) ||
                        (twoDPoint1.Y == twoDPoint2.Y && twoDPoint2.X == twoDPoint3.X && twoDPoint3.Y == twoDPoint4.Y && twoDPoint4.X == twoDPoint1.X))
                    {
                        var markupRectangle = new TemplateTree.MarkupRectangle();
                        markupRectangle.TopLeft = twoDPoint1;
                        markupRectangle.BottomRight = twoDPoint3;
                        markupRectangle.Name = markupText;
                        markupRectangle.IncludeInAnnotation = polyline.IsIncludeFlag;
                        markupRectangle.CalloutLocation = markupRectangle.TopLeft - new SizeF(30, 30);
                        SetMarkupImageReference(markupRectangle, polyline.SpatialCoordinateCollection[0]);

                        return markupRectangle;
                    }
                }

                var points = new List<PointF>();
                foreach (var spatialCoordinate in polyline.SpatialCoordinateCollection)
                    if (spatialCoordinate is aim_dotnet.TwoDimensionSpatialCoordinate)
                        points.Add(AimNativeConverter.AsPointF(spatialCoordinate));

                var markup = new TemplateTree.MarkupPolygonal();
                markup.Vertices = points;
                markup.Name = markupText;
                markup.IncludeInAnnotation = polyline.IsIncludeFlag;
                markup.CalloutLocation = markup.Vertices[0] - new SizeF(30, 30);
                SetMarkupImageReference(markup, polyline.SpatialCoordinateCollection[0]);

                return markup;
            }
            if (geometricShape is aim_dotnet.MultiPoint)
            {
                var multiPoint = (aim_dotnet.MultiPoint)geometricShape;

                TemplateTree.IMarkup markup;
                switch (multiPoint.SpatialCoordinateCollection.Count)
                {
                    case 2:
                        {
                            // Line
                            var markupLinear = new TemplateTree.MarkupLinear();
                            markupLinear.Vertices = new List<PointF>(2);
                            markupLinear.Vertices.Add(AimNativeConverter.AsPointF(multiPoint.SpatialCoordinateCollection[0]));
                            markupLinear.Vertices.Add(AimNativeConverter.AsPointF(multiPoint.SpatialCoordinateCollection[1]));
                            markupLinear.CalloutLocation = markupLinear.Vertices[0] - new SizeF(30, 30);
                            markup = markupLinear;
                        }
                        break;
                    case 3:
                        {
                            // Protractor
                            var markupProtractor = new TemplateTree.MarkupProtractor();
                            markupProtractor.Points = new List<PointF>(3);
                            markupProtractor.Points.Add(AimNativeConverter.AsPointF(multiPoint.SpatialCoordinateCollection[0]));
                            markupProtractor.Points.Add(AimNativeConverter.AsPointF(multiPoint.SpatialCoordinateCollection[1]));
                            markupProtractor.Points.Add(AimNativeConverter.AsPointF(multiPoint.SpatialCoordinateCollection[2]));
                            markupProtractor.CalloutLocation = markupProtractor.Points[0] - new SizeF(30, 30);
                            markup = markupProtractor;
                        }
                        break;
                    default:
                        throw new NotImplementedException("Reading non-linear or non-triangular MultiPoint shape is not implemented");
                }

                markup.Name = markupText;
                markup.IncludeInAnnotation = multiPoint.IsIncludeFlag;
                SetMarkupImageReference(markup, multiPoint.SpatialCoordinateCollection[0]);
                return markup;
            }

            throw new NotImplementedException();
            return null;
        }

        // Retrieves SOP Instance UID and Referenced Frame Number from the coordinate
        private static void SetMarkupImageReference(TemplateTree.IMarkup markup, aim_dotnet.ISpatialCoordinate spatialCoordinate)
        {
            if (spatialCoordinate.CoordinateType == aim_dotnet.SpatialCoordinateType.SPATIAL_COORD_2D)
            {
                var twoDSpatialCoord = spatialCoordinate as aim_dotnet.TwoDimensionSpatialCoordinate;
                if (twoDSpatialCoord != null)
                {
                    Debug.Assert(twoDSpatialCoord.ReferencedFrameNumber > 0, "Referenced Frame Number must be positive");
                    markup.PresentationImageUid = twoDSpatialCoord.ImageReferenceUID;
                    markup.FrameNumber = twoDSpatialCoord.ReferencedFrameNumber;
                }
            }
            else
            {
                Debug.Assert(false, "Setting image references is not implemented for 3D");
            }
        }

        public static List<aim_dotnet.Inference> ToSelectedInferencesList(TemplateTree.AimTemplateTreeInferenceNode node)
        {
            var inferences = new List<aim_dotnet.Inference>();
            bool isValid = node.Valid;

            double? confidence = null;
            if (node.HasConfidence)
                confidence = node.ConfidenceValue;

            foreach (var term in node.SelectedAllowedTerms)
            {
                var standardCodeSequence = ToStandardCodeSequence(term);
                inferences.Add(
                    new aim_dotnet.Inference()
                        {
                            AnnotatorConfidence = confidence,
                            CodeMeaning = standardCodeSequence.CodeMeaning,
                            CodeValue = standardCodeSequence.CodeValue,
                            CodingSchemeDesignator = standardCodeSequence.CodingSchemeDesignator,
                            CodingSchemeVersion = standardCodeSequence.CodingSchemeVersion
                        });
            }
            foreach (var inference in inferences)
                inference.ImageEvidence = true;
            return inferences;
        }

        public static List<aim_dotnet.ImagingObservation> ToSelectedImagingObservationList(TemplateTree.AimTemplateTreeImagingObservationNode node)
        {
            var imagingObservations = new List<aim_dotnet.ImagingObservation>();
            bool isValid = node.Valid;
            foreach (var term in node.SelectedAllowedTerms)
            {
                var imagingObservation = ToImagingObservation(ToStandardCodeSequence(term), node.Label);

                if (node.HasConfidence)
                {
                    imagingObservation.AnnotatorConfidence = node.ConfidenceValue;
                }

                //node
                var selectedImagingObservationCharacteristics = SelectedImagingObservationCharacteristicsDictionary(node);

                // Sort characteristics first according to their ItemNumber
                List<int> imagingObservationCharacteristicIndices =
                    CollectionUtils.Sort(selectedImagingObservationCharacteristics.Keys, (i1, i2) => i1.CompareTo(i2));
                foreach (int characteristicIndex in imagingObservationCharacteristicIndices)
                {
                    // Find definition of the selected characteristic in the component
                    int index = characteristicIndex;
                    TemplateTree.AimTemplateTreeImagingObservationCharacteristicNode templateImagingObservationCharacteristic =
                        CollectionUtils.SelectFirst(node.ImagingObservationCharacteristicTreeNodes,
                                                    item => item.ItemNumber == index);
                    isValid = templateImagingObservationCharacteristic != null &&
                              selectedImagingObservationCharacteristics[characteristicIndex].Count >=
                              Math.Min(templateImagingObservationCharacteristic.CharacteristicQuantificationAllowedTerms.Count, templateImagingObservationCharacteristic.MinCardinality) &&
                              selectedImagingObservationCharacteristics[characteristicIndex].Count <= templateImagingObservationCharacteristic.MaxCardinality;
                    if (!isValid)
                        break;

                    // Put all Anatomic Entity Characteristics into a single collection
                    imagingObservation.ImagingObservationCharacteristicCollection =
                        CollectionUtils.Concat<aim_dotnet.ImagingObservationCharacteristic>(
                            imagingObservation.ImagingObservationCharacteristicCollection ?? new List<aim_dotnet.ImagingObservationCharacteristic>(),
                            selectedImagingObservationCharacteristics[characteristicIndex]
                            );
                }
                if (!isValid)
                    break;

                imagingObservations.Add(imagingObservation);
            }
            return imagingObservations;
        }

        public static List<aim_dotnet.AnatomicEntity> ToSelectedAnatomicEntitiesList(TemplateTree.AimTemplateTreeAnatomicEntityNode node)
        {
            var selectedAnatomicEntities = new List<aim_dotnet.AnatomicEntity>();
            bool isValid = node.Valid;
            foreach (var term in node.SelectedAllowedTerms)
            {
                string label = node.Label;
                if (node.QuestionType != null)
                    label = node.QuestionType.StandardCodeSequence.CodeMeaning;

                var anatomicEntity = ToAnatomicEntity(ToStandardCodeSequence(term), label);

                if (node.HasConfidence)
                {
                    anatomicEntity.AnnotatorConfidence = node.ConfidenceValue;
                }

                //node
                var selectedAnatomicEntityCharacteristics = SelectedAnatomicEntityCharacteristicsDictionary(node);

                // Sort characteristics first according to their ItemNumber
                List<int> anatomicEntityCharacteristicIndices =
                    CollectionUtils.Sort(selectedAnatomicEntityCharacteristics.Keys, (i1, i2) => i1.CompareTo(i2));
                foreach (int characteristicIndex in anatomicEntityCharacteristicIndices)
                {
                    // Find definition of the selected characteristic in the component
                    int index = characteristicIndex;
                    TemplateTree.AimTemplateTreeAnatomicEntityCharacteristicNode templateAnatomicEntityCharacteristic =
                        CollectionUtils.SelectFirst(node.AnatomicEntityCharacteristicTreeNodes,
                                                    item => item.ItemNumber == index);
                    isValid = templateAnatomicEntityCharacteristic != null &&
                              selectedAnatomicEntityCharacteristics[characteristicIndex].Count >=
                              Math.Min(templateAnatomicEntityCharacteristic.CharacteristicQuantificationAllowedTerms.Count, templateAnatomicEntityCharacteristic.MinCardinality) &&
                              selectedAnatomicEntityCharacteristics[characteristicIndex].Count <= templateAnatomicEntityCharacteristic.MaxCardinality;
                    if (!isValid)
                        break;

                    // Put all Anatomic Entity Characteristics into a single collection
                    anatomicEntity.AnatomicEntityCharacteristicCollection =
                        CollectionUtils.Concat<aim_dotnet.AnatomicEntityCharacteristic>(
                            anatomicEntity.AnatomicEntityCharacteristicCollection ?? new List<aim_dotnet.AnatomicEntityCharacteristic>(),
                            selectedAnatomicEntityCharacteristics[characteristicIndex]
                            );
                }
                if (!isValid)
                    break;

                selectedAnatomicEntities.Add(anatomicEntity);
            }
            return selectedAnatomicEntities;
        }

        public static Dictionary<StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>> SelectedCharacteristicQuantifcations()
        {
            return new Dictionary<StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>>();
        }

        public static List<aim_dotnet.ICharacteristicQuantification> ToCharacteristicQuantifications(
            TemplateTree.CharacteristicQuantificationAllowedTerm allowedTerm)
        {
            var selectedQuantifications = new List<aim_dotnet.ICharacteristicQuantification>();

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
                        new aim_dotnet.NonQuantifiable
                            {
                                Name = characteristicQuantification.Name,
                                CodeValue = codeSequence.CodeValue,
                                CodeMeaning = codeSequence.CodeMeaning,
                                CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
                                CodingSchemeVersion = codeSequence.CodingSchemeVersion,
                                AnnotatorConfidence = confidence
                            }
                        );
                }
                else
                {
                    if (characteristicQuantification is TemplateTree.AimTemplateTreeNumericalQuantification)
                    {
                        var numericalQuantification = (TemplateTree.AimTemplateTreeNumericalQuantification)characteristicQuantification;
                        if (numericalQuantification.SelectedNumerical != null)
                            selectedQuantifications.Add(
                                new aim_dotnet.Numerical
                                    {
                                        Name = characteristicQuantification.Name,
                                        Value = numericalQuantification.SelectedNumerical.Value.Value,
                                        Operator =
                                            ToAimComparisonOperator(
                                            numericalQuantification.SelectedNumerical.Value.Operator),
                                        UcumString = numericalQuantification.SelectedNumerical.Value.UcumString,
                                        AnnotatorConfidence = confidence
                                    });
                    }
                    if (characteristicQuantification is TemplateTree.AimTemplateTreeQuantileQuantification)
                    {
                        var quantileQuantification = (TemplateTree.AimTemplateTreeQuantileQuantification)characteristicQuantification;
                        if (quantileQuantification.SelectedBin != null)
                            selectedQuantifications.Add(
                                new aim_dotnet.Quantile
                                    {
                                        Name = characteristicQuantification.Name,
                                        Bin = quantileQuantification.SelectedBin.Value,
                                        AnnotatorConfidence = confidence
                                    });
                    }
                    if (characteristicQuantification is TemplateTree.AimTemplateTreeScaleQuantification)
                    {
                        var scaleQuantification = (TemplateTree.AimTemplateTreeScaleQuantification) characteristicQuantification;
                        if (scaleQuantification.SelectedScaleLevel != null)
                            selectedQuantifications.Add(
                                new aim_dotnet.Scale
                                    {
                                        Name = characteristicQuantification.Name,
                                        Value = scaleQuantification.SelectedScaleLevel.Value.Value,
                                        Description = scaleQuantification.SelectedScaleLevel.Value.ValueDescription,
                                        Comment = scaleQuantification.SelectedScaleLevel.Value.ValueLabel,
                                        AnnotatorConfidence = confidence
                                    });
                    }
                    if (characteristicQuantification is TemplateTree.AimTemplateTreeIntervalQuantification)
                    {
                        var intervalQuantification = (TemplateTree.AimTemplateTreeIntervalQuantification) characteristicQuantification;
                        if (intervalQuantification.SelectedInterval != null)
                            selectedQuantifications.Add(
                                new aim_dotnet.Interval
                                    {
                                        Name = characteristicQuantification.Name,
                                        MinValue = intervalQuantification.SelectedInterval.Value.MinValue,
                                        MaxValue = intervalQuantification.SelectedInterval.Value.MaxValue,
                                        MinOperator =
                                            ToAimComparisonOperator(
                                            intervalQuantification.SelectedInterval.Value.MinOperator),
                                        MaxOperator =
                                            ToAimComparisonOperator(
                                            intervalQuantification.SelectedInterval.Value.MaxOperator),
                                        UcumString = intervalQuantification.SelectedInterval.Value.UcumString,
                                        AnnotatorConfidence = confidence
                                    });
                    }
                }
            }

            return selectedQuantifications;
        }

        public static aim_dotnet.ComparisonOperatorIdentifier ToAimComparisonOperator(TemplateTree.ComparisonOperator comparisonOperator)
        {
            var aimOperator = aim_dotnet.ComparisonOperatorIdentifier.None;

            switch (comparisonOperator)
            {
                case TemplateTree.ComparisonOperator.Equal:
                    aimOperator = aim_dotnet.ComparisonOperatorIdentifier.Equal;
                    break;
                case TemplateTree.ComparisonOperator.GreaterThan:
                    aimOperator = aim_dotnet.ComparisonOperatorIdentifier.GreaterThan;
                    break;
                case TemplateTree.ComparisonOperator.GreaterThanEqual:
                    aimOperator = aim_dotnet.ComparisonOperatorIdentifier.GreaterThanEqual;
                    break;
                case TemplateTree.ComparisonOperator.LessThan:
                    aimOperator = aim_dotnet.ComparisonOperatorIdentifier.LessThan;
                    break;
                case TemplateTree.ComparisonOperator.LessThanEqual:
                    aimOperator = aim_dotnet.ComparisonOperatorIdentifier.LessThanEqual;
                    break;
                case TemplateTree.ComparisonOperator.NotEqual:
                    aimOperator = aim_dotnet.ComparisonOperatorIdentifier.NotEqual;
                    break;
            }

            return aimOperator;
        }

        public static Dictionary<int, List<aim_dotnet.AnatomicEntityCharacteristic>> SelectedAnatomicEntityCharacteristicsDictionary(TemplateTree.AimTemplateTreeAnatomicEntityNode anatomicEntity)
        {
            return anatomicEntity.SelectedAnatomicEntityCharacteristicTreeNodes.ToDictionary(aec => aec.ItemNumber,
                aec => new List<aim_dotnet.AnatomicEntityCharacteristic>(SelectedAnatomicEntityCharacteristics(aec)));
        }

        public static Dictionary<int, List<aim_dotnet.ImagingObservationCharacteristic>> SelectedImagingObservationCharacteristicsDictionary(TemplateTree.AimTemplateTreeImagingObservationNode imagingObservation)
        {
            return imagingObservation.SelectedImagingObservationCharacteristicTreeNodes.ToDictionary(ioc => ioc.ItemNumber,
                ioc => new List<aim_dotnet.ImagingObservationCharacteristic>(SelectedImagingObservationCharacteristics(ioc)));
        }

        public static List<aim_dotnet.AnatomicEntityCharacteristic> SelectedAnatomicEntityCharacteristics(TemplateTree.AimTemplateTreeAnatomicEntityCharacteristicNode node)
        {
            var anatomicEntityCharacteristics = new List<aim_dotnet.AnatomicEntityCharacteristic>();

            var selectedCharacteristicQuantifications = new Dictionary<TemplateTree.StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>>();
            foreach (TemplateTree.CharacteristicQuantificationAllowedTerm term in node.SelectedCharacteristicQuantificationAllowedTerms)
            {
                bool valid = true;
                foreach (var quantification in term.CharacteristicQuantifications)
                    if (!quantification.Valid)
                        valid = false;
                if (valid)
                    selectedCharacteristicQuantifications.Add(term, ToCharacteristicQuantifications(term));
            }

            if (selectedCharacteristicQuantifications.Count > 0)
            {
                foreach (var selectedCharacteristicQuantification in selectedCharacteristicQuantifications)
                {
                    double? confidence = null;
                    if (node.HasConfidence)
                        confidence = node.ConfidenceValue;

                    var characteristicCode = ToStandardCodeSequence(selectedCharacteristicQuantification.Key);
                    anatomicEntityCharacteristics.Add(
                        new aim_dotnet.AnatomicEntityCharacteristic
                        {
                            CodeValue = characteristicCode.CodeValue,
                            CodeMeaning = characteristicCode.CodeMeaning,
                            CodingSchemeDesignator = characteristicCode.CodingSchemeDesignator,
                            CodingSchemeVersion = characteristicCode.CodingSchemeVersion,
                            Label = node.Label,
                            AnnotatorConfidence = confidence,
                            CharacteristicQuantificationCollection = selectedCharacteristicQuantification.Value
                        });
                }
            }
            else
            {
                if (node.SelectedCharacteristicQuantificationAllowedTerms == null ||
                    node.SelectedCharacteristicQuantificationAllowedTerms.Count == 0)
                {
                    // Provide default NULL answer when answers are optional
                    if (node.MinCardinality == 0)
                    {
                        anatomicEntityCharacteristics.Add(
                            new aim_dotnet.AnatomicEntityCharacteristic
                            {
                                CodeValue = AimAnnotationComponent.NullCodeValue.CodeValue,
                                CodeMeaning = AimAnnotationComponent.NullCodeValue.CodeMeaning,
                                CodingSchemeDesignator = AimAnnotationComponent.NullCodeValue.CodingSchemeDesignator,
                                CodingSchemeVersion = AimAnnotationComponent.NullCodeValue.CodingSchemeVersion,
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
                        var codeSequence = ToStandardCodeSequence(validTerm);
                        anatomicEntityCharacteristics.Add(
                            new aim_dotnet.AnatomicEntityCharacteristic
                            {
                                CodeValue = codeSequence.CodeValue,
                                CodeMeaning = codeSequence.CodeMeaning,
                                CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
                                CodingSchemeVersion = codeSequence.CodingSchemeVersion,
                                Label = node.Label,
                                AnnotatorConfidence = confidence
                            });
                    }
                }
            }

            return anatomicEntityCharacteristics;
        }

        public static List<aim_dotnet.ImagingObservationCharacteristic> SelectedImagingObservationCharacteristics(TemplateTree.AimTemplateTreeImagingObservationCharacteristicNode node)
        {
            var imagingObservationCharacteristics = new List<aim_dotnet.ImagingObservationCharacteristic>();

            var selectedCharacteristicQuantifications = new Dictionary<TemplateTree.StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>>();
            foreach (TemplateTree.CharacteristicQuantificationAllowedTerm term in node.SelectedCharacteristicQuantificationAllowedTerms)
            {
                bool valid = true;
                foreach (var quantification in term.CharacteristicQuantifications)
                    if (!quantification.Valid)
                        valid = false;
                if (valid)
                    selectedCharacteristicQuantifications.Add(term, ToCharacteristicQuantifications(term));
            }

            if (selectedCharacteristicQuantifications.Count > 0)
            {
                foreach (var selectedCharacteristicQuantification in selectedCharacteristicQuantifications)
                {
                    double? confidence = null;
                    if (node.HasConfidence)
                        confidence = node.ConfidenceValue;

                    var characteristicCode = ToStandardCodeSequence(selectedCharacteristicQuantification.Key);
                    imagingObservationCharacteristics.Add(
                        new aim_dotnet.ImagingObservationCharacteristic
                        {
                            CodeValue = characteristicCode.CodeValue,
                            CodeMeaning = characteristicCode.CodeMeaning,
                            CodingSchemeDesignator = characteristicCode.CodingSchemeDesignator,
                            CodingSchemeVersion = characteristicCode.CodingSchemeVersion,
                            Label = node.Label,
                            AnnotatorConfidence = confidence,
                            CharacteristicQuantificationCollection = selectedCharacteristicQuantification.Value
                        });
                }
            }
            else
            {
                if (node.SelectedCharacteristicQuantificationAllowedTerms == null ||
                    node.SelectedCharacteristicQuantificationAllowedTerms.Count == 0)
                {
                    // Provide default NULL answer when answers are optional
                    if (node.MinCardinality == 0)
                    {
                        imagingObservationCharacteristics.Add(
                            new aim_dotnet.ImagingObservationCharacteristic
                            {
                                CodeValue = AimAnnotationComponent.NullCodeValue.CodeValue,
                                CodeMeaning = AimAnnotationComponent.NullCodeValue.CodeMeaning,
                                CodingSchemeDesignator = AimAnnotationComponent.NullCodeValue.CodingSchemeDesignator,
                                CodingSchemeVersion = AimAnnotationComponent.NullCodeValue.CodingSchemeVersion,
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
                        var codeSequence = ToStandardCodeSequence(validTerm);
                        imagingObservationCharacteristics.Add(
                            new aim_dotnet.ImagingObservationCharacteristic
                            {
                                CodeValue = codeSequence.CodeValue,
                                CodeMeaning = codeSequence.CodeMeaning,
                                CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
                                CodingSchemeVersion = codeSequence.CodingSchemeVersion,
                                Label = node.Label,
                                AnnotatorConfidence = confidence
                            });
                    }
                }
            }

            return imagingObservationCharacteristics;
        }

        public static aim_dotnet.AnatomicEntity ToAnatomicEntity(TemplateTree.StandardCodeSequence codeSequence, string label)
        {
            return codeSequence == null
                    ? null
                    : new aim_dotnet.AnatomicEntity
                        {
                            CodeValue = codeSequence.CodeValue,
                            CodeMeaning = codeSequence.CodeMeaning,
                            CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
                            CodingSchemeVersion = codeSequence.CodingSchemeVersion,
                            Label = label
                        };
        }

        public static aim_dotnet.ImagingObservation ToImagingObservation(TemplateTree.StandardCodeSequence codeSequence, string label)
        {
            return codeSequence == null
                    ? null
                    : new aim_dotnet.ImagingObservation
                        {
                            CodeValue = codeSequence.CodeValue,
                            CodeMeaning = codeSequence.CodeMeaning,
                            CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
                            CodingSchemeVersion = codeSequence.CodingSchemeVersion,
                            Label = label
                        };
        }

        public static aim_dotnet.Inference ToInference(TemplateTree.StandardCodeSequence codeSequence)
        {
            return codeSequence == null
                    ? null
                    : new aim_dotnet.Inference
                        {
                            CodeValue = codeSequence.CodeValue,
                            CodeMeaning = codeSequence.CodeMeaning,
                            CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
                            CodingSchemeVersion = codeSequence.CodingSchemeVersion
                        };
        }

        public static aim_dotnet.Calculation ToCalculation(TemplateTree.StandardCodeSequence codeSequence)
        {
            return codeSequence == null
                    ? null
                    : new aim_dotnet.Calculation
                        {
                            CodeValue = codeSequence.CodeValue,
                            CodeMeaning = codeSequence.CodeMeaning,
                            CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
                            CodingSchemeVersion = codeSequence.CodingSchemeVersion
                        };
        }

        public static TemplateTree.StandardCodeSequence ToStandardCodeSequence(aim_dotnet.AnatomicEntity anatomicEntity)
        {
            return anatomicEntity == null
                    ? null
                    :
                        new TemplateTree.StandardCodeSequence(anatomicEntity.CodeValue, anatomicEntity.CodeMeaning, anatomicEntity.CodingSchemeDesignator,
                                                 anatomicEntity.CodingSchemeVersion);
        }

        public static TemplateTree.StandardCodeSequence ToStandardCodeSequence(aim_dotnet.AnatomicEntityCharacteristic anatomicEntityCharacteristic)
        {
            return anatomicEntityCharacteristic == null
                    ? null
                    :
                        new TemplateTree.StandardCodeSequence(anatomicEntityCharacteristic.CodeValue, anatomicEntityCharacteristic.CodeMeaning,
                                                 anatomicEntityCharacteristic.CodingSchemeDesignator,
                                                 anatomicEntityCharacteristic.CodingSchemeVersion);
        }

        public static TemplateTree.StandardCodeSequence ToStandardCodeSequence(aim_dotnet.ImagingObservation imagingObservation)
        {
            return imagingObservation == null
                    ? null
                    :
                        new TemplateTree.StandardCodeSequence(imagingObservation.CodeValue, imagingObservation.CodeMeaning, imagingObservation.CodingSchemeDesignator,
                                                 imagingObservation.CodingSchemeVersion);
        }

        public static TemplateTree.StandardCodeSequence ToStandardCodeSequence(aim_dotnet.ImagingObservationCharacteristic imagingObservationCharacteristic)
        {
            return imagingObservationCharacteristic == null
                    ? null
                    :
                        new TemplateTree.StandardCodeSequence(imagingObservationCharacteristic.CodeValue, imagingObservationCharacteristic.CodeMeaning, imagingObservationCharacteristic.CodingSchemeDesignator,
                                                 imagingObservationCharacteristic.CodingSchemeVersion);
        }

        public static TemplateTree.StandardCodeSequence ToStandardCodeSequence(aim_dotnet.Inference inference)
        {
            return inference == null
                    ? null
                    :
                        new TemplateTree.StandardCodeSequence(inference.CodeValue, inference.CodeMeaning, inference.CodingSchemeDesignator,
                                                 inference.CodingSchemeVersion);
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

        public static bool IsNullCodeSequence(TemplateTree.StandardCodeSequence codeSequence)
        {
            if (codeSequence == null)
                return true;
            if (codeSequence.CodeMeaning == AimAnnotationComponent.NullCodeValue.CodeMeaning &&
                codeSequence.CodeValue == AimAnnotationComponent.NullCodeValue.CodeValue)
                return true;

            return false;
        }

        /// <summary>
        /// Recursevely traverses given <paramref name="validTerm"/> and appends Code Meanings to the given <paramref name="sb"/>.
        /// This effectively flattens <paramref name="validTerm"/> to a string.
        /// </summary>
        /// <param name="validTerm">Standard Valid Term to traverse</param>
        /// <param name="sb">String Builder taht receives the values</param>
        public static StringBuilder ToStringBuilder(TemplateTree.StandardValidTerm validTerm, StringBuilder sb)
        {
            if (validTerm == null || sb == null)
                return sb;

            if (sb.Length > 0)
                sb.Append(" ");
            sb.Append(validTerm.StandardCodeSequence.CodeMeaning);
            // Traverse the tree in-order
            foreach (TemplateTree.StandardValidTerm standardValidTerm in validTerm.StandardValidTerms)
                ToStringBuilder(standardValidTerm, sb);

            return sb;
        }
    }
}
