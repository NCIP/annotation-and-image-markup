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
using ClearCanvas.Desktop;
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Utilities;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.Imaging;
using ClearCanvas.ImageViewer.InteractiveGraphics;
using ClearCanvas.ImageViewer.Mathematics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.RoiGraphics.Analyzers;
using ClearCanvas.ImageViewer.StudyManagement;
using ClearCanvas.ImageViewer.Tools.Measurement;

using AIM.Annotation.Graphics;
using AIM.Annotation.Configuration;
using GeneralUtilities;
using GeneralUtilities.Collections;

namespace AIM.Annotation.AimManager.Aim3
{
    internal class AimNativeConverter
    {
        public static List<aim_dotnet.Annotation> CreateAimAnnotations(IEnumerable<IPresentationImage> presentationImages, AimAnnotationCreationContext creationContext, IEnumerable<IGraphic> selectedMarkup, out List<IGraphic> annotationsGraphic)
        {
            List<aim_dotnet.Annotation> annotations = new List<aim_dotnet.Annotation>();
            annotationsGraphic = new List<IGraphic>(); // list that includes all IGraphic objects used to create new annotations

            if (creationContext.SelectedAnnotationKind == AimAnnotationCreationContext.AnnotationKind.ImageAnnotation)
            {
                Dictionary<string, HashSet<int>> annotationSOPsAndFrames = creationContext.SopInstanceUidAndFrameNumbers;
                // list of UIDs to include in the annotation. If empty, include all images from the same set which have markup.

                foreach (IPresentationImage currentImage in presentationImages)
                {
                    IImageSopProvider currentImageSOP = currentImage as IImageSopProvider;
                    if (currentImageSOP == null) // not an image?
                        continue;

                    // Skip the image if it's not included in our image annotation set
                    if (annotationSOPsAndFrames.Values.Count > 0 &&
                        !annotationSOPsAndFrames.ContainsKey(currentImageSOP.ImageSop.SopInstanceUid) ||
                        (annotationSOPsAndFrames[currentImageSOP.ImageSop.SopInstanceUid] != null &&
                        !annotationSOPsAndFrames[currentImageSOP.ImageSop.SopInstanceUid].Contains(currentImageSOP.Frame.FrameNumber)))
                        continue;

                    // Find all markups on the image
                    IOverlayGraphicsProvider currentOverlayGraphics = currentImage as IOverlayGraphicsProvider;
                    if (currentOverlayGraphics != null) // all images should implement IOverlayGraphicsProvider
                    {
                        // Create one annotation per calculation/geo shape
                        int shapeIdentifier = 0;
                        List<aim_dotnet.IGeometricShape> geoShapes = new List<aim_dotnet.IGeometricShape>();
                        List<aim_dotnet.Calculation> calculations = creationContext.IncludeCalculations ? new List<aim_dotnet.Calculation>() : null;
                        List<aim_dotnet.TextAnnotation> textAnnotations = new List<aim_dotnet.TextAnnotation>();

                        var selectedMarkupList = new List<IGraphic>(selectedMarkup);

                        foreach (IGraphic graphic in currentOverlayGraphics.OverlayGraphics)
                        {
                            // Geometric Shape
                            if (selectedMarkupList.Contains(graphic))
                            {
                                RoiGraphic currentRoiGraphic = graphic as RoiGraphic;
                                if (currentRoiGraphic != null && currentRoiGraphic.Roi != null)
                                {
                                    // Create Geo Shape for this ROI
                                    aim_dotnet.IGeometricShape geoShape = Create2DGeoShape(currentRoiGraphic,
                                                                                           currentImageSOP.ImageSop.
                                                                                               SopInstanceUid,
                                                                                           currentImageSOP.Frame.
                                                                                               FrameNumber);
                                    if (geoShape != null)
                                    {
                                        // Shape Identifier is just a count
                                        geoShape.ShapeIdetifier = shapeIdentifier++;

                                        // Get calculations for this ROI, if required
                                        if (calculations != null)
                                            calculations.AddRange(CreateCalculations(currentRoiGraphic,
                                                                                     geoShape.ShapeIdetifier));

                                        geoShapes.Add(geoShape);
                                        annotationsGraphic.Add(graphic);
                                    }
                                }
                                // Text Annotation
                                else if (graphic is ContextMenuControlGraphic)
                                {
                                    ContextMenuControlGraphic contextMenuControlGraphic = (ContextMenuControlGraphic) graphic;
                                    if (contextMenuControlGraphic.Subject != null)
                                    {
                                        aim_dotnet.TextAnnotation textAnnotation =
                                            CreateTextAnnotation(contextMenuControlGraphic.Subject,
                                                                 currentImageSOP.ImageSop.SopInstanceUid,
                                                                 currentImageSOP.Frame.FrameNumber);

                                        if (textAnnotation != null)
                                        {
                                            if (textAnnotation.ConnectorPoints != null)
                                                textAnnotation.ConnectorPoints.ShapeIdetifier = shapeIdentifier++;

                                            textAnnotations.Add(textAnnotation);
                                            annotationsGraphic.Add(graphic);
                                        }
                                    }
                                }
                                // Aim Graphic can be a source of both Geo Shape or Text Annotation
                                else if (graphic is AimGraphic)
                                {
                                    var aimGraphic = graphic as AimGraphic;
                                    RoiGraphic aimRoiGraphic = null;
                                    IGraphic aimTextAnnotationGraphic = null;
                                    if (aimGraphic.Graphic is RoiGraphic)
                                        aimRoiGraphic = (RoiGraphic)aimGraphic.Graphic;
                                    else if (aimGraphic.Graphic is StandardStatefulGraphic)
                                    {
                                        var aimStdStatefulGraphic = (StandardStatefulGraphic)aimGraphic.Graphic;
                                        if (aimStdStatefulGraphic.Subject is RoiGraphic)
                                            aimRoiGraphic = (RoiGraphic)aimStdStatefulGraphic.Subject;
                                        else if (aimStdStatefulGraphic.Subject is InvariantTextPrimitive)
                                            aimTextAnnotationGraphic = aimStdStatefulGraphic.Subject;
                                        else if (aimStdStatefulGraphic.Subject is CrosshairCalloutGraphic)
                                            aimTextAnnotationGraphic = aimStdStatefulGraphic.Subject;
                                        else if (aimStdStatefulGraphic.Subject is ContextMenuControlGraphic)
                                            aimTextAnnotationGraphic = ((ContextMenuControlGraphic)aimStdStatefulGraphic.Subject).Subject;
                                        else
                                            Debug.Assert(false, "Unexpected graphics type");
                                    }

                                    if (aimRoiGraphic != null)
                                    {
                                        // Create Geo Shape for this ROI
                                        aim_dotnet.IGeometricShape geoShape = Create2DGeoShape(aimRoiGraphic,
                                                                                               currentImageSOP.ImageSop.SopInstanceUid,
                                                                                               currentImageSOP.Frame.FrameNumber);
                                        if (geoShape != null)
                                        {
                                            // Shape Identifier is just a count
                                            geoShape.ShapeIdetifier = shapeIdentifier++;

                                            // Get calculations for this ROI, if required
                                            if (calculations != null)
                                                calculations.AddRange(CreateCalculations(aimRoiGraphic,
                                                                                         geoShape.ShapeIdetifier));

                                            geoShapes.Add(geoShape);
                                            annotationsGraphic.Add(graphic);
                                        }
                                    }
                                    else if (aimTextAnnotationGraphic != null)
                                    {
                                        aim_dotnet.TextAnnotation textAnnotation =
                                            CreateTextAnnotation(aimTextAnnotationGraphic,
                                                                 currentImageSOP.ImageSop.SopInstanceUid,
                                                                 currentImageSOP.Frame.FrameNumber);

                                        if (textAnnotation != null)
                                        {
                                            if (textAnnotation.ConnectorPoints != null)
                                                textAnnotation.ConnectorPoints.ShapeIdetifier = shapeIdentifier++;

                                            textAnnotations.Add(textAnnotation);
                                            annotationsGraphic.Add(graphic);
                                        }
                                    }
                                    else
                                        Debug.Assert(false, "Failed to convert AimGraphic to an annotation type");
                                }
                            }
                        }

                        // Create annotation if:
                        // 1. we are explicitly asked to create an annotation for this SOP, or
                        // 2. image has markup(s), or
                        // 3. image has calculation(s), or
                        // 4. image has text markup
                        if (annotationSOPsAndFrames.Count > 0 || geoShapes.Count > 0 || (calculations != null && calculations.Count > 0) || textAnnotations.Count > 0)
                        {
                            aim_dotnet.ImageAnnotation imgAnn = CreateImageAnnotation(currentImageSOP, creationContext);

                            if (geoShapes.Count > 0)
                                imgAnn.GeometricShapeCollection = geoShapes;

                            if (calculations != null && calculations.Count > 0)
                                imgAnn.CalculationCollection = calculations;

                            if (textAnnotations.Count > 0)
                                imgAnn.TextAnnotationCollection = textAnnotations;

                            // Add current image reference to the annotation
                            AddDicomImageReference(imgAnn, currentImageSOP);

                            annotations.Add(imgAnn);
                        }
                    }
                }

                return annotations;
            }
            else
            {
                throw new NotImplementedException("Creation of AnnotationOfAnnotation objects is not yet supported ");
            }
        }

        private static aim_dotnet.ImageAnnotation CreateImageAnnotation(IImageSopProvider imageSop, AimAnnotationCreationContext creationContext)
        {
            // Create Basic Image Annotation
            Platform.CheckTrue(creationContext.SelectedAnnotationKind == AimAnnotationCreationContext.AnnotationKind.ImageAnnotation, "ImageAnnotationKind");
            Platform.CheckForEmptyString(creationContext.AnnotationName, "AnnotationName");

            aim_dotnet.ImageAnnotation imgAnnotation = new aim_dotnet.ImageAnnotation();
            imgAnnotation.CodeValue = creationContext.AnnotationTypeCode.CodeValue;
            imgAnnotation.CodeMeaning = creationContext.AnnotationTypeCode.CodeMeaning;
            imgAnnotation.CodingSchemeDesignator = creationContext.AnnotationTypeCode.CodingSchemeDesignator;
            imgAnnotation.CodingSchemeVersion = creationContext.AnnotationTypeCode.CodingSchemeVersion;
            imgAnnotation.UniqueIdentifier = DicomUid.GenerateUid().UID; // TODO - replace ClearCanvas root UID with an appropriate value
            imgAnnotation.Name = creationContext.AnnotationName;
            imgAnnotation.DateTime = DateTime.Now;
            imgAnnotation.Patient = CreatePatient(imageSop);
            imgAnnotation.Equipment = CreateEquipment();
            if (creationContext.AnnotationUser != null)
                imgAnnotation.User = new aim_dotnet.User
                    {
                        Name = creationContext.AnnotationUser.Name,
                        LoginName = creationContext.AnnotationUser.LoginName,
                        RoleInTrial = creationContext.AnnotationUser.RoleInTrial,
                        NumberWithinRoleOfClinicalTrial = creationContext.AnnotationUser.NumberWithinRoleOfClinicalTrial
                    };
            if (!string.IsNullOrEmpty(creationContext.AnnotationComment))
                imgAnnotation.Comment = creationContext.AnnotationComment;


            var selectedAnatomicEntities = new List<aim_dotnet.AnatomicEntity>();
            var selectedImagingObservations = new List<aim_dotnet.ImagingObservation>();
            var selectedInferences = new List<aim_dotnet.Inference>();

            foreach (var node in creationContext.TemplateTree.TemplateNodes)
            {
                if (node is TemplateTree.AimTemplateTreeAnatomicEntityNode)
                    selectedAnatomicEntities.AddRange(AimTemplateConverter.ToSelectedAnatomicEntitiesList((TemplateTree.AimTemplateTreeAnatomicEntityNode)node));
                if (node is TemplateTree.AimTemplateTreeImagingObservationNode)
                    selectedImagingObservations.AddRange(AimTemplateConverter.ToSelectedImagingObservationList((TemplateTree.AimTemplateTreeImagingObservationNode)node));
                if (node is TemplateTree.AimTemplateTreeInferenceNode)
                    selectedInferences.AddRange(AimTemplateConverter.ToSelectedInferencesList((TemplateTree.AimTemplateTreeInferenceNode)node));
            }

            // add AnatomicEntity
            if (!selectedAnatomicEntities.IsNullOrEmpty())
                imgAnnotation.AnatomyEntityCollection = selectedAnatomicEntities;

            // add ImagingObservation and ImagingObservationCharacteristic values
            if (!selectedImagingObservations.IsNullOrEmpty())
                imgAnnotation.ImagingObservationCollection = selectedImagingObservations;

            // add Inferences
            if (!selectedInferences.IsNullOrEmpty())
                imgAnnotation.InferenceCollection = selectedInferences;

            return imgAnnotation;
        }

        private static aim_dotnet.Person CreatePatient(IImageSopProvider image)
        {
            Platform.CheckForNullReference(image, "Image");

            aim_dotnet.Person patient = new aim_dotnet.Person();
            patient.Id = image.Frame.ParentImageSop.PatientId;
            DateTime birthDate;
            DateParser.Parse(image.Frame.ParentImageSop.PatientsBirthDate, out birthDate);
            patient.BirthDate = birthDate;
            patient.Name = image.Frame.ParentImageSop.PatientsName;
            patient.Sex = image.Frame.ParentImageSop.PatientsSex;
            patient.EthnicGroup = image.ImageSop[DicomTags.EthnicGroup].ToString();

            return patient;
        }

        private static aim_dotnet.Equipment CreateEquipment()
        {
            aim_dotnet.Equipment equipment = new aim_dotnet.Equipment();
            equipment.ManufacturerName = SR.EquipmentManufacturer;
            equipment.ManufacturerModelName = SR.EquipmentManufacturerModelName;
            equipment.SoftwareVersion = string.Format("{0}.{1}.{2}.{3}", Application.Version.Major, Application.Version.Minor, Application.Version.Build,
                                                      Application.Version.Revision);

            return equipment;
        }

        private static aim_dotnet.IGeometricShape Create2DGeoShape(RoiGraphic roiGraphic, string imageUID, int frameNumber)
        {
            Platform.CheckForEmptyString(imageUID, "imageUID");

            aim_dotnet.IGeometricShape geoShape = null;
            Roi roi = roiGraphic.Roi;

            //Platform.CheckTrue(graphics.CoordinateSystem == CoordinateSystem.Source, "Source Coordinate System");

            if (roi is EllipticalRoi)
            {
                EllipticalRoi ellipticalRoi = roi as EllipticalRoi;
                Platform.CheckForNullReference(ellipticalRoi, "ellipticalRoi");

                aim_dotnet.Ellipse ellipseShape = new aim_dotnet.Ellipse();
                ellipseShape.EllipseCollection = new List<aim_dotnet.ISpatialCoordinate>();
                ellipseShape.IsIncludeFlag = true;

                // Bounding box coordinates to DICOM ellipse conversion.
                // Since ellipse's bounding box is not rotated, we just need to find major axis
                // and store the center points of bounding box' side as ellipse vertices.

                ellipseShape.EllipseCollection.Add(
                    Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left, ellipticalRoi.BoundingBox.Top + ellipticalRoi.BoundingBox.Height / 2, imageUID, frameNumber, 0));

                ellipseShape.EllipseCollection.Add(
                    Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Right, ellipticalRoi.BoundingBox.Top + ellipticalRoi.BoundingBox.Height / 2, imageUID, frameNumber, 1));

                // Vertical minor axis points
                ellipseShape.EllipseCollection.Add(
                    Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left + ellipticalRoi.BoundingBox.Width / 2, ellipticalRoi.BoundingBox.Top, imageUID, frameNumber, 2));

                ellipseShape.EllipseCollection.Add(
                    Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left + ellipticalRoi.BoundingBox.Width / 2, ellipticalRoi.BoundingBox.Bottom, imageUID, frameNumber, 3));

                geoShape = ellipseShape;
            }
            else if (roi is PolygonalRoi)
            {
                PolygonalRoi polygonalRoi = roi as PolygonalRoi;
                Platform.CheckForNullReference(polygonalRoi, "polygonalRoi");

                aim_dotnet.Polyline polylineShape = new aim_dotnet.Polyline();
                polylineShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
                polylineShape.IsIncludeFlag = true;
                for (int i = 0; i < polygonalRoi.Polygon.Vertices.Count; i++)
                {
                    polylineShape.SpatialCoordinateCollection.Add(
                        Create2DSpatialCoordinate(polygonalRoi.Polygon.Vertices[i].X, polygonalRoi.Polygon.Vertices[i].Y, imageUID, frameNumber, i));
                }
                if (polygonalRoi.Polygon.Vertices.Count > 0 && polygonalRoi.Polygon.Vertices[polygonalRoi.Polygon.Vertices.Count - 1] != polygonalRoi.Polygon.Vertices[0])
                {
                    // Add first point to end of collection to close the shape. - SJT
                    polylineShape.SpatialCoordinateCollection.Add(
                        Create2DSpatialCoordinate(polygonalRoi.Polygon.Vertices[0].X, polygonalRoi.Polygon.Vertices[0].Y, imageUID,
                                                  frameNumber, 0));
                }
                geoShape = polylineShape;
            }
            else if (roi is ProtractorRoi)
            {
                ProtractorRoi protractorRoi = roi as ProtractorRoi;
                Platform.CheckForNullReference(protractorRoi, "protractorRoi");

                aim_dotnet.MultiPoint multipointShape = new aim_dotnet.MultiPoint();
                multipointShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
                multipointShape.IsIncludeFlag = true;
                for (int i = 0; i < protractorRoi.Points.Count; i++)
                {
                    multipointShape.SpatialCoordinateCollection.Add(
                        Create2DSpatialCoordinate(protractorRoi.Points[i].X, protractorRoi.Points[i].Y, imageUID, frameNumber, i));
                }
                geoShape = multipointShape;
            }
            else if (roi is LinearRoi)
            {
                LinearRoi linearRoi = roi as LinearRoi;
                Platform.CheckForNullReference(linearRoi, "linearRoi");

                aim_dotnet.MultiPoint multipointShape = new aim_dotnet.MultiPoint();
                multipointShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
                multipointShape.IsIncludeFlag = true;
                for (int i = 0; i < linearRoi.Points.Count; i++)
                {
                    multipointShape.SpatialCoordinateCollection.Add(
                        Create2DSpatialCoordinate(linearRoi.Points[i].X, linearRoi.Points[i].Y, imageUID, frameNumber, i));
                }
                geoShape = multipointShape;
            }
            else if (roi is RectangularRoi)
            {
                RectangularRoi rectangularRoi = roi as RectangularRoi;
                Platform.CheckForNullReference(rectangularRoi, "rectangularRoi");

                aim_dotnet.Polyline polylineShape = new aim_dotnet.Polyline();
                polylineShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
                polylineShape.IsIncludeFlag = true;

                // Top Left
                polylineShape.SpatialCoordinateCollection.Add(
                    Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Left, rectangularRoi.BoundingBox.Top, imageUID, frameNumber, 0));

                // Top Right
                polylineShape.SpatialCoordinateCollection.Add(
                    Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Right, rectangularRoi.BoundingBox.Top, imageUID, frameNumber, 1));

                // Bottom Right
                polylineShape.SpatialCoordinateCollection.Add(
                    Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Right, rectangularRoi.BoundingBox.Bottom, imageUID, frameNumber, 2));

                // Bottom Left
                polylineShape.SpatialCoordinateCollection.Add(
                    Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Left, rectangularRoi.BoundingBox.Bottom, imageUID, frameNumber, 3));

                geoShape = polylineShape;
            }
            else
                Console.WriteLine("AIMHelper.CreateGeoShape. Unhandled ROI type: " + roi.GetType().FullName);

            return geoShape;
        }

        private static aim_dotnet.TwoDimensionSpatialCoordinate Create2DSpatialCoordinate(float x, float y, string imageUID, int frameNumber, int coordinateIndex)
        {
            aim_dotnet.TwoDimensionSpatialCoordinate spatialCoord = new aim_dotnet.TwoDimensionSpatialCoordinate();
            spatialCoord.X = x;
            spatialCoord.Y = y;
            spatialCoord.ImageReferenceUID = imageUID;
            spatialCoord.ReferencedFrameNumber = frameNumber;
            spatialCoord.CoordinateIndex = coordinateIndex;

            return spatialCoord;
        }

        // Returns 'false' if the image already exists in the Image collection or 'true' when a new Image is added.
        private static bool AddDicomImageReference(aim_dotnet.ImageAnnotation imageAnnotation, IImageSopProvider image)
        {
            Platform.CheckForNullReference(imageAnnotation, "ImageAnnotation");

            if (imageAnnotation.ImageReferenceCollection == null)
                imageAnnotation.ImageReferenceCollection = new List<aim_dotnet.ImageReference>();
            List<aim_dotnet.ImageReference> imageReferences = imageAnnotation.ImageReferenceCollection;

            aim_dotnet.ImageStudy aimImageStudy = null;
            foreach (aim_dotnet.ImageReference imgRef in imageReferences)
            {
                aim_dotnet.DICOMImageReference dicomImgRef = imgRef as aim_dotnet.DICOMImageReference;
                if (dicomImgRef != null)
                {
                    if (dicomImgRef.Study.InstanceUID == image.ImageSop.StudyInstanceUid &&
                        dicomImgRef.Study.Series.InstanceUID == image.ImageSop.SeriesInstanceUid)
                        aimImageStudy = dicomImgRef.Study;
                }
            }

            // Create new Study/Series
            if (aimImageStudy == null)
            {
                aimImageStudy = CreateStudy(image);
                aimImageStudy.Series = CreateSeries(image);
                aimImageStudy.Series.ImageCollection = new List<aim_dotnet.Image>();
                aim_dotnet.DICOMImageReference dicomImgRef = new aim_dotnet.DICOMImageReference();
                dicomImgRef.Study = aimImageStudy;
                imageReferences.Add(dicomImgRef);
            }

            foreach (aim_dotnet.Image existingImage in aimImageStudy.Series.ImageCollection)
            {
                if (existingImage.SopInstanceUID == image.ImageSop.SopInstanceUid)
                    return false; // already have this image
            }

            aim_dotnet.Image aimImage = CreateImage(image);
            aimImageStudy.Series.ImageCollection.Add(aimImage);

            return true;
        }

        private static aim_dotnet.ImageStudy CreateStudy(IImageSopProvider image)
        {
            Platform.CheckForNullReference(image, "Image");

            aim_dotnet.ImageStudy aimStudy = new aim_dotnet.ImageStudy();
            aimStudy.InstanceUID = image.ImageSop.StudyInstanceUid;
            DateTime studyDate;
            if (DateTimeParser.ParseDateAndTime(null, image.ImageSop.StudyDate, image.ImageSop.StudyTime, out studyDate))
                aimStudy.StartDate = studyDate;

            return aimStudy;
        }

        private static aim_dotnet.ImageSeries CreateSeries(IImageSopProvider image)
        {
            Platform.CheckForNullReference(image, "Image");

            aim_dotnet.ImageSeries aimSeries = new aim_dotnet.ImageSeries();
            aimSeries.InstanceUID = image.ImageSop.SeriesInstanceUid;

            return aimSeries;
        }

        private static aim_dotnet.Image CreateImage(IImageSopProvider image)
        {
            Platform.CheckForNullReference(image, "Image");

            aim_dotnet.Image aimImage = new aim_dotnet.Image();

            aimImage.SopClassUID = image.ImageSop.SopClassUid;
            aimImage.SopInstanceUID = image.ImageSop.SopInstanceUid;

            // TODO - get Image View and Image View Modifiers

            return aimImage;
        }

        private static List<aim_dotnet.Calculation> CreateCalculations(RoiGraphic roiGraphic, int referencedGeoShapeId)
        {
            List<aim_dotnet.Calculation> calculations = new List<aim_dotnet.Calculation>();
            List<aim_dotnet.ReferencedGeometricShape> referencedGeometricShapes = null;
            if (referencedGeoShapeId >= 0)
            {
                referencedGeometricShapes = new List<aim_dotnet.ReferencedGeometricShape>();
                referencedGeometricShapes.Add(new aim_dotnet.ReferencedGeometricShape { ReferencedShapeIdentifier = referencedGeoShapeId });
            }

            Roi roi = roiGraphic.Roi;
            foreach (IRoiAnalyzer analyzer in roiGraphic.Callout.RoiAnalyzers)
            {
                if (analyzer.SupportsRoi(roi))
                {
                    aim_dotnet.Calculation calculation = new aim_dotnet.Calculation();
                    calculation.UID = DicomUid.GenerateUid().UID;
                    calculation.CalculationResultCollection = new List<aim_dotnet.CalculationResult>();
                    if (analyzer is RoiLengthAnalyzer)
                    {
                        calculation.CodeValue = CodeList.CalculationCodeForLength.CodeValue;
                        calculation.CodeMeaning = CodeList.CalculationCodeForLength.CodeMeaning;
                        calculation.CodingSchemeDesignator = CodeList.CalculationCodeForLength.CodingSchemeDesignator;
                        calculation.CodingSchemeVersion = CodeList.CalculationCodeForLength.CodingSchemeVersion;
                        calculation.Description = "Length";
                        calculation.ReferencedGeometricShapeCollection = referencedGeometricShapes;
                        IRoiLengthProvider roiLengthProvider = (IRoiLengthProvider)roi;

                        Units oldUnits = roiLengthProvider.Units;
                        roiLengthProvider.Units = roiLengthProvider.IsCalibrated ? Units.Millimeters : Units.Pixels;
                        calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(roiLengthProvider.Length, UnitsToName(roiLengthProvider.Units), "Value"));
                        roiLengthProvider.Units = oldUnits;

                        calculations.Add(calculation);
                    }
                    else if (analyzer is RoiAreaAnalyzer)
                    {
                        calculation.CodeValue = CodeList.CalculationCodeForArea.CodeValue;
                        calculation.CodeMeaning = CodeList.CalculationCodeForArea.CodeMeaning;
                        calculation.CodingSchemeDesignator = CodeList.CalculationCodeForArea.CodingSchemeDesignator;
                        calculation.CodingSchemeVersion = CodeList.CalculationCodeForArea.CodingSchemeVersion;
                        calculation.Description = "Area";
                        calculation.ReferencedGeometricShapeCollection = referencedGeometricShapes;
                        IRoiAreaProvider roiAreaProvider = (IRoiAreaProvider)roi;

                        Units oldUnits = roiAreaProvider.Units;
                        roiAreaProvider.Units = roiAreaProvider.IsCalibrated ? Units.Millimeters : Units.Pixels;
                        calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(roiAreaProvider.Area, UnitsToName(roiAreaProvider.Units), "Value"));
                        roiAreaProvider.Units = oldUnits;

                        calculations.Add(calculation);
                    }
                    else if (analyzer is RoiStatisticsAnalyzer)
                    {
                        if (roi.PixelData is GrayscalePixelData && IsBoundingBoxInImage(roi.BoundingBox, roi.ImageColumns, roi.ImageRows))
                        {
                            IRoiStatisticsProvider statisticsProvider = (IRoiStatisticsProvider)roi;

                            double mean = statisticsProvider.Mean;
                            double stdDev = statisticsProvider.StandardDeviation;

                            aim_dotnet.Calculation calcStdDev = new aim_dotnet.Calculation(calculation);

                            calculation.CodeValue = CodeList.CalculationCodeForMean.CodeValue;
                            calculation.CodeMeaning = CodeList.CalculationCodeForMean.CodeMeaning;
                            calculation.CodingSchemeDesignator = CodeList.CalculationCodeForMean.CodingSchemeDesignator;
                            calculation.CodingSchemeVersion = CodeList.CalculationCodeForMean.CodingSchemeVersion;
                            calculation.Description = "Mean";
                            calculation.ReferencedGeometricShapeCollection = referencedGeometricShapes;
                            calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(mean, roi.Modality == "CT" ? "HU" : "1", "Value"));

                            calcStdDev.CodeValue = CodeList.CalculationCodeForStandardDeviation.CodeValue;
                            calcStdDev.CodeMeaning = CodeList.CalculationCodeForStandardDeviation.CodeMeaning;
                            calcStdDev.CodingSchemeDesignator = CodeList.CalculationCodeForStandardDeviation.CodingSchemeDesignator;
                            calcStdDev.CodingSchemeVersion = CodeList.CalculationCodeForStandardDeviation.CodingSchemeVersion;
                            calcStdDev.Description = "Standard Deviation";
                            calcStdDev.ReferencedGeometricShapeCollection = referencedGeometricShapes;
                            calcStdDev.CalculationResultCollection.Add(CreateScalarCalculationResult(stdDev, roi.Modality == "CT" ? "HU" : "1", "Value"));

                            calculations.Add(calculation);
                            calculations.Add(calcStdDev);
                        }
                    }
                    else if (analyzer is ProtractorAnalyzer)
                    {
                        ProtractorRoi protractorRoiInfo = roi as ProtractorRoi;
                        if (protractorRoiInfo != null && protractorRoiInfo.Points.Count >= 3)
                        {
                            List<PointF> normalizedPoints = NormalizePoints(protractorRoiInfo);
                            double angle = Math.Abs(Vector.SubtendedAngle(normalizedPoints[0], normalizedPoints[1], normalizedPoints[2]));

                            calculation.CodeValue = CodeList.CalculationCodeForAngle.CodeValue;
                            calculation.CodeMeaning = CodeList.CalculationCodeForAngle.CodeMeaning;
                            calculation.CodingSchemeDesignator = CodeList.CalculationCodeForAngle.CodingSchemeDesignator;
                            calculation.CodingSchemeVersion = CodeList.CalculationCodeForAngle.CodingSchemeVersion;
                            calculation.Description = "Angle";
                            calculation.ReferencedGeometricShapeCollection = referencedGeometricShapes;
                            //       calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(angle, "rad", "Value"));
                            calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(angle, "deg", "Value"));

                            calculations.Add(calculation);
                        }
                    }
                }
            }

            return calculations;
        }

        private static string UnitsToName(Units units)
        {
            switch (units)
            {
                case Units.Pixels:
                    return "pixel";
                case Units.Centimeters:
                    return "cm";
                case Units.Millimeters:
                    return "mm";
                default:
                    Debug.Assert(false, "Unexpected calculation units");
                    break;
            }
            return string.Empty;
        }

        private static aim_dotnet.CalculationResult CreateScalarCalculationResult(double value, string unit, string label)
        {
            aim_dotnet.Dimension dimension = new aim_dotnet.Dimension();
            dimension.Index = 0;
            dimension.Size = 1;
            dimension.Label = label;

            aim_dotnet.Coordinate coordinate = new aim_dotnet.Coordinate();
            coordinate.DimensionIndex = 0;
            coordinate.Position = 0;

            aim_dotnet.CalculationData calculationData = new aim_dotnet.CalculationData();
            calculationData.Value = value;
            calculationData.CoordinateCollection = new List<aim_dotnet.Coordinate>();
            calculationData.CoordinateCollection.Add(coordinate);

            aim_dotnet.CalculationResult result = new aim_dotnet.CalculationResult();
            result.TypeOfCalculationResult = aim_dotnet.CalculationResultIdentifier.Scalar;
            result.UnitOfMeasure = unit;
            result.DimensionCollection = new List<aim_dotnet.Dimension>();
            result.DimensionCollection.Add(dimension);
            result.NumberOfDimensions = result.DimensionCollection.Count;
            result.CalculationDataCollection = new List<aim_dotnet.CalculationData>();
            result.CalculationDataCollection.Add(calculationData);

            return result;
        }

        private static aim_dotnet.TextAnnotation CreateTextAnnotation(IGraphic graphic, string imageUid, int frameNumber)
        {
            // TODO - record color, font name, font size, etc.

            if (graphic is UserCalloutGraphic)
            {
                UserCalloutGraphic userCalloutGraphic = (UserCalloutGraphic)graphic;
                aim_dotnet.MultiPoint multiPoint = new aim_dotnet.MultiPoint();
                multiPoint.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
                multiPoint.IsIncludeFlag = true;
                foreach (PointF pointF in new[] { userCalloutGraphic.AnchorPoint, userCalloutGraphic.AttachmentPoint })
                {
                    multiPoint.SpatialCoordinateCollection.Add(
                        Create2DSpatialCoordinate(pointF.X, pointF.Y, imageUid, frameNumber, multiPoint.SpatialCoordinateCollection.Count));
                }

                return new aim_dotnet.TextAnnotation { Text = StringUtils.TrimStringStartOrSelf(userCalloutGraphic.Text, userCalloutGraphic.ParentGraphic.Name).TrimStart(), ConnectorPoints = multiPoint };
            }

            if (graphic is InvariantTextPrimitive)
            {
                InvariantTextPrimitive invariantTextPrimitive = (InvariantTextPrimitive)graphic;
                aim_dotnet.MultiPoint multiPoint = new aim_dotnet.MultiPoint();
                multiPoint.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
                multiPoint.IsIncludeFlag = true;
                multiPoint.SpatialCoordinateCollection.Add(
                    Create2DSpatialCoordinate(invariantTextPrimitive.Location.X, invariantTextPrimitive.Location.Y, imageUid, frameNumber,
                                              multiPoint.SpatialCoordinateCollection.Count));

                return new aim_dotnet.TextAnnotation { Text = StringUtils.TrimStringStartOrSelf(invariantTextPrimitive.Text, graphic.ParentGraphic.Name).TrimStart(), ConnectorPoints = multiPoint };
            }

            if (graphic is CrosshairCalloutGraphic)
            {
                var crosshairGraphic = (CrosshairCalloutGraphic)graphic;
                var multiPoint = new aim_dotnet.MultiPoint();
                multiPoint.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
                multiPoint.IsIncludeFlag = true;
                foreach (PointF pointF in new[] { crosshairGraphic.AnchorPoint, crosshairGraphic.AttachmentPoint })
                {
                    multiPoint.SpatialCoordinateCollection.Add(
                        Create2DSpatialCoordinate(pointF.X, pointF.Y, imageUid, frameNumber, multiPoint.SpatialCoordinateCollection.Count));
                }

                return new aim_dotnet.TextAnnotation { Text = StringUtils.TrimStringStartOrSelf(crosshairGraphic.Text, graphic.ParentGraphic.Name).TrimStart(), ConnectorPoints = multiPoint };
            }

            return null;
        }

        private static bool IsBoundingBoxInImage(RectangleF boundingBox, float imageColumns, float imageRows)
        {
            boundingBox = RectangleUtilities.ConvertToPositiveRectangle(boundingBox);

            if (boundingBox.Width == 0 || boundingBox.Height == 0)
                return false;

            if (boundingBox.Left < 0 ||
                boundingBox.Top < 0 ||
                boundingBox.Right > (imageColumns - 1) ||
                boundingBox.Bottom > (imageRows - 1))
                return false;

            return true;
        }

        private static List<PointF> NormalizePoints(ProtractorRoi roiInfo)
        {
            float aspectRatio = 1F;

            if (roiInfo.PixelAspectRatio.IsNull)
            {
                if (!roiInfo.NormalizedPixelSpacing.IsNull)
                    aspectRatio = (float)roiInfo.NormalizedPixelSpacing.AspectRatio;
            }
            else
            {
                aspectRatio = roiInfo.PixelAspectRatio.Value;
            }

            List<PointF> normalized = new List<PointF>();
            foreach (PointF point in roiInfo.Points)
                normalized.Add(new PointF(point.X, point.Y * aspectRatio));

            return normalized;
        }

        // ====================================================================
        //
        //  Read and display annotation back
        //
        // ====================================================================

        public static bool ReadGraphicsFromAnnotation(Aim3AnnotationInstance aim3AnnotationInstance, IPresentationImage presentationImage)
        {
            bool hasNewRoiGraphic = false;

            IOverlayGraphicsProvider graphicsProvider = presentationImage as IOverlayGraphicsProvider;
            //IApplicationGraphicsProvider graphicsProvider = presentationImage as IApplicationGraphicsProvider;
            IImageSopProvider currentImageSOP = presentationImage as IImageSopProvider;
            if (graphicsProvider == null || currentImageSOP == null)
                return false;

            if (aim3AnnotationInstance.AimAnnotation is aim_dotnet.ImageAnnotation)
            {
                aim_dotnet.ImageAnnotation imgAnnotation = (aim_dotnet.ImageAnnotation)aim3AnnotationInstance.AimAnnotation;
                if (imgAnnotation.GeometricShapeCollection != null)
                {
                    foreach (aim_dotnet.IGeometricShape geoShape in imgAnnotation.GeometricShapeCollection)
                    {
                        // Check if the image is the one on which the annotation was originally drawn
                        if (GetImageSOPInstanceUID(geoShape) != currentImageSOP.ImageSop.SopInstanceUid ||
                            GetReferencedFrameNumber(geoShape) != currentImageSOP.Frame.FrameNumber)
                            continue;

                        // Prevent from adding the same annotation again
                        bool isAlreadyDisplayed = false;
                        foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
                        {
                            AimGraphic aimGraphic = graphic as AimGraphic;
                            isAlreadyDisplayed = aimGraphic != null && aimGraphic.AnnotationUid == imgAnnotation.UniqueIdentifier &&
                                                 aimGraphic.ShapeIdentifier == geoShape.ShapeIdetifier;
                            if (isAlreadyDisplayed)
                                break;
                        }
                        if (isAlreadyDisplayed)
                            continue;

                        IGraphic geoGraphic = GeoShapeToGraphic(geoShape, (imgAnnotation.Name ?? string.Empty).Trim());
                        if (geoGraphic != null)
                        {
                            AimGraphic aimGraphic = new AimGraphic(geoGraphic, aim3AnnotationInstance, geoShape.ShapeIdetifier);
                            // Choose color for aimGraphic based on the login name of the annotation's creator
                            aimGraphic.Color = AimSettings.Default.GetAimGraphicColorForUser(aimGraphic.UserLoginName);
                            graphicsProvider.OverlayGraphics.Add(aimGraphic);
                        }

                        hasNewRoiGraphic |= geoGraphic != null;
                    }
                }
                if (imgAnnotation.TextAnnotationCollection != null)
                {
                    foreach (aim_dotnet.TextAnnotation textAnnotation in imgAnnotation.TextAnnotationCollection)
                    {
                        if (textAnnotation.ConnectorPoints == null)
                            continue; // ignore. not image-specific

                        // TODO - refactor some of the code below and similar code above into the AIM Mgr when Mgr is implemented

                        // Check if the image is the one on which the annotation was originally drawn
                        if (GetImageSOPInstanceUID(textAnnotation.ConnectorPoints) != currentImageSOP.ImageSop.SopInstanceUid||
                            GetReferencedFrameNumber(textAnnotation.ConnectorPoints) != currentImageSOP.Frame.FrameNumber)
                            continue;

                        // Prevent from adding the same annotation again
                        bool isAlreadyDisplayed = false;
                        foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
                        {
                            AimGraphic aimGraphic = graphic as AimGraphic;
                            isAlreadyDisplayed = aimGraphic != null && aimGraphic.AnnotationUid == imgAnnotation.UniqueIdentifier &&
                                                 aimGraphic.ShapeIdentifier == textAnnotation.ConnectorPoints.ShapeIdetifier;
                            if (isAlreadyDisplayed)
                                break;
                        }
                        if (isAlreadyDisplayed)
                            continue;

                        IGraphic textGraphic = TextAnnotationToGraphic(textAnnotation, (imgAnnotation.Name ?? string.Empty).Trim());
                        if (textGraphic != null)
                        {
                            AimGraphic aimGraphic = new AimGraphic(textGraphic, aim3AnnotationInstance, textAnnotation.ConnectorPoints.ShapeIdetifier);
                            aimGraphic.Color = Color.SlateBlue;
                            graphicsProvider.OverlayGraphics.Add(aimGraphic);
                        }

                        hasNewRoiGraphic |= textGraphic != null;
                    }
                }
            }
            else
            {
                throw new NotImplementedException("AIM3: Reading non-image annotation is not implemented");
            }

            return hasNewRoiGraphic;
        }

        // Returns SOP Instance UID of the image the given shape belongs to
        // 2D images are supported only
        private static string GetImageSOPInstanceUID(aim_dotnet.IGeometricShape geoShape)
        {
            if (geoShape.SpatialCoordinateCollection != null && geoShape.SpatialCoordinateCollection.Count > 0 &&
                geoShape.SpatialCoordinateCollection[0].CoordinateType == aim_dotnet.SpatialCoordinateType.SPATIAL_COORD_2D)
            {
                aim_dotnet.TwoDimensionSpatialCoordinate twoDSpatialCoord = geoShape.SpatialCoordinateCollection[0] as aim_dotnet.TwoDimensionSpatialCoordinate;
                if (twoDSpatialCoord != null)
                    return twoDSpatialCoord.ImageReferenceUID;
            }
            else if (geoShape.SpatialCoordinateCollection != null && geoShape.SpatialCoordinateCollection.Count > 0 &&
                geoShape.SpatialCoordinateCollection[0].CoordinateType == aim_dotnet.SpatialCoordinateType.SPATIAL_COORD_3D)
            {
                Debug.Assert(false, "Reading 3D SOP Instance UID is not implemented");
            }

            return string.Empty;
        }

        private static int GetReferencedFrameNumber(aim_dotnet.IGeometricShape geoShape)
        {
            if (geoShape.SpatialCoordinateCollection != null && geoShape.SpatialCoordinateCollection.Count > 0 &&
                geoShape.SpatialCoordinateCollection[0].CoordinateType == aim_dotnet.SpatialCoordinateType.SPATIAL_COORD_2D)
            {
                aim_dotnet.TwoDimensionSpatialCoordinate twoDSpatialCoord = geoShape.SpatialCoordinateCollection[0] as aim_dotnet.TwoDimensionSpatialCoordinate;
                if (twoDSpatialCoord != null)
                {
                    Debug.Assert(twoDSpatialCoord.ReferencedFrameNumber > 0, "Referenced Frame Number must be positive");
                    return twoDSpatialCoord.ReferencedFrameNumber;
                }
            }
            else
            {
                Debug.Assert(false, "Only 2D SOP Instances have Referenced Frame Number");
            }

            return 1; // 1 - default 1st frame in the image in the CC's implementation
        }

        private static IGraphic GeoShapeToGraphic(aim_dotnet.IGeometricShape geoShape, string shapeLabel)
        {
            IGraphic graphic = null;

            if (geoShape.SpatialCoordinateCollection == null || geoShape.SpatialCoordinateCollection.Count == 0)
                return null;

            if (geoShape is aim_dotnet.Circle)
            {
                // Ellipse
                aim_dotnet.Circle shapeCircle = geoShape as aim_dotnet.Circle;
                PointF centerPt = AsPointF(shapeCircle.Center);
                PointF radiusPt = AsPointF(shapeCircle.RadiusPoint);
                double radiusLength = Vector.Distance(centerPt, radiusPt);
                RoiGraphic roiGraphic = AimRoiGraphic.CreateEllipse();
                BoundableGraphic boundableGraphic = roiGraphic.Subject as BoundableGraphic;
                if (boundableGraphic != null)
                {
                    roiGraphic.Suspend(); // prevent callout location calculation until all points are set
                    roiGraphic.Name = shapeLabel;
                    boundableGraphic.TopLeft = new PointF((float)(centerPt.X - radiusLength), (float)(centerPt.Y - radiusLength));
                    boundableGraphic.BottomRight = new PointF((float)(centerPt.X + radiusLength), (float)(centerPt.Y + radiusLength));
                    roiGraphic.Resume(true); // Force callout location calculation
                }
                graphic = roiGraphic;
            }
            else if (geoShape is aim_dotnet.Ellipse)
            {
                // Ellipse
                aim_dotnet.Ellipse shapeEllipse = geoShape as aim_dotnet.Ellipse;
                PointF firstMajorAxisPt = AsPointF(shapeEllipse.EllipseCollection[0]);
                PointF secondMajorAxisPt = AsPointF(shapeEllipse.EllipseCollection[1]);
                PointF firstMinorAxisPt = AsPointF(shapeEllipse.EllipseCollection[2]);
                PointF secondMinorAxisPt = AsPointF(shapeEllipse.EllipseCollection[3]);

                RoiGraphic roiGraphic = AimRoiGraphic.CreateEllipse();
                BoundableGraphic boundableGraphic = roiGraphic.Subject as BoundableGraphic;
                if (boundableGraphic != null)
                {
                    roiGraphic.Suspend(); // prevent callout location calculation until all points are set
                    roiGraphic.Name = shapeLabel;
                    boundableGraphic.TopLeft = new PointF(firstMajorAxisPt.X, firstMinorAxisPt.Y);
                    boundableGraphic.BottomRight = new PointF(secondMajorAxisPt.X, secondMinorAxisPt.Y);
                    roiGraphic.Resume(true); // Force callout location calculation
                }
                graphic = roiGraphic;
            }
            else if (geoShape is aim_dotnet.Point)
            {
                aim_dotnet.Point shapePoint = geoShape as aim_dotnet.Point;

                // If arrow callouts selected for point objects

                if (AimSettings.Default.UseCrosshairsForTextCallouts)
                {
                    var crosshairGraphic = new CrosshairCalloutGraphic(shapeLabel);
                    crosshairGraphic.LineStyle = LineStyle.Solid;
                    crosshairGraphic.AnchorPoint = AsPointF(shapePoint.Center);
                    crosshairGraphic.TextLocation = crosshairGraphic.AnchorPoint - new SizeF(30, 30);
                    crosshairGraphic.Name = shapeLabel;
                    crosshairGraphic.ShowShaft = !String.IsNullOrEmpty(shapeLabel);
                    // Hard code position of callout text for now.  Future implementation should probably have the graphics builder using a 
                    // callout strategy positioner
                    crosshairGraphic.TextLocation = crosshairGraphic.AnchorPoint - new SizeF(30, -60);
                    StandardStatefulGraphic statefulGraphic = new StandardStatefulGraphic(crosshairGraphic);
                    statefulGraphic.State = statefulGraphic.CreateInactiveState();

                    graphic = statefulGraphic;
                }
                else
                {
                    //UserCalloutGraphic callout = new UserCalloutGraphic();
                    CalloutGraphic callout = new CalloutGraphic(shapeLabel);
                    callout.LineStyle = LineStyle.Solid;
                    callout.ShowArrowhead = true;
                    //    callout.Text = "Point";
                    // If this does not work, do it after ContextMenuControlGraphic initialization: (UserCalloutGraphic)contextGraphic.ParentGraphic
                    //            callout.CoordinateSystem = CoordinateSystem.Destination;
                    callout.AnchorPoint = AsPointF(shapePoint.Center);
                    callout.TextLocation = callout.AnchorPoint - new SizeF(30, 30);
                    //            callout.ResetCoordinateSystem();

                    StandardStatefulGraphic statefulGraphic = new StandardStatefulGraphic(callout);
                    statefulGraphic.State = statefulGraphic.CreateInactiveState();

                    graphic = statefulGraphic;
                }
            }
            else if (geoShape is aim_dotnet.MultiPoint)
            {
                // How this case works:
                // If we have 2 points, it's a line
                // If we have 3 points, it's a protractor
                // All others - unknown unclosed object (not supported)

                aim_dotnet.MultiPoint shapeMultiPoint = geoShape as aim_dotnet.MultiPoint;
                switch (shapeMultiPoint.SpatialCoordinateCollection.Count)
                {
                    case 2:
                        {
                            // Line
                            VerticesControlGraphic interactiveGraphic = new VerticesControlGraphic(new MoveControlGraphic(new PolylineGraphic()));
                            PointF firstPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[0]);
                            PointF secondPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[1]);
                            interactiveGraphic.Subject.Points.Add(firstPt);
                            interactiveGraphic.Subject.Points.Add(secondPt);

                            RoiGraphic roiGraphic = CreateRoiGraphic(interactiveGraphic, null);
                            roiGraphic.Name = shapeLabel;
                            roiGraphic.Resume(true); // Force callout location calculation

                            graphic = roiGraphic;
                        }
                        break;
                    case 3:
                        {
                            // Protractor
                            VerticesControlGraphic interactiveGraphic = new VerticesControlGraphic(new MoveControlGraphic(new ProtractorGraphic()));
                            PointF firstPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[0]);
                            PointF secondPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[1]);
                            PointF thirdPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[2]);
                            interactiveGraphic.Subject.Points.Add(firstPt);
                            interactiveGraphic.Subject.Points.Add(secondPt);
                            interactiveGraphic.Subject.Points.Add(thirdPt);

                            RoiGraphic roiGraphic = CreateRoiGraphic(interactiveGraphic, new ProtractorRoiCalloutLocationStrategy());

                            roiGraphic.Name = shapeLabel;
                            roiGraphic.Resume(true); // Force callout location calculation

                            graphic = roiGraphic;
                        }
                        break;
                    default:
                        throw new NotImplementedException("Reading non-linear or non-triangular MultiPoint shape is not implemented");
                }
            }
            else if (geoShape is aim_dotnet.Polyline)
            {
                aim_dotnet.Polyline shapePolyline = geoShape as aim_dotnet.Polyline;

                bool isRectangle = false; // true - if we have CC's rectangle coordinates
                // Check if this is a non-rotated rectangle
                if (shapePolyline.SpatialCoordinateCollection.Count == 4)
                {
                    PointF twoDPoint1 = AsPointF(shapePolyline.SpatialCoordinateCollection[0]);
                    PointF twoDPoint2 = AsPointF(shapePolyline.SpatialCoordinateCollection[1]);
                    PointF twoDPoint3 = AsPointF(shapePolyline.SpatialCoordinateCollection[2]);
                    PointF twoDPoint4 = AsPointF(shapePolyline.SpatialCoordinateCollection[3]);
                    // If it's a rectangle with sides parallel to the axes
                    if ((twoDPoint1.X == twoDPoint2.X && twoDPoint2.Y == twoDPoint3.Y && twoDPoint3.X == twoDPoint4.X && twoDPoint4.Y == twoDPoint1.Y) ||
                        (twoDPoint1.Y == twoDPoint2.Y && twoDPoint2.X == twoDPoint3.X && twoDPoint3.Y == twoDPoint4.Y && twoDPoint4.X == twoDPoint1.X))
                    {
                        isRectangle = true;

                        RoiGraphic roiGraphic = AimRoiGraphic.CreateRectangle();
                        BoundableGraphic boundableGraphic = roiGraphic.Subject as BoundableGraphic;
                        if (boundableGraphic != null)
                        {
                            roiGraphic.Suspend(); // prevent callout location calculation until all points are set
                            roiGraphic.Name = shapeLabel;
                            // Assume that the points are in order and start at the top left corner.
                            boundableGraphic.TopLeft = twoDPoint1;
                            boundableGraphic.BottomRight = twoDPoint3;

                            roiGraphic.Resume(true); // Force callout location calculation
                        }

                        graphic = roiGraphic;
                    }
                }
                // It's a CC's polygon if it's not a rectangle
                if (!isRectangle)
                {
                    RoiGraphic roiGraphic = AimRoiGraphic.CreatePolygon();
                    PolylineGraphic polylineGraphic = roiGraphic.Subject as PolylineGraphic;
                    if (polylineGraphic != null)
                    {
                        roiGraphic.Suspend();
                        for (int i = 0; i < shapePolyline.SpatialCoordinateCollection.Count; i++)
                        {
                            PointF twoDPoint = AsPointF(shapePolyline.SpatialCoordinateCollection[i]);
                            polylineGraphic.Points.Add(twoDPoint);
                        }
                        // We deal with closed polygons only
                        if (polylineGraphic.Points.Count > 0)
                            polylineGraphic.Points.Add(polylineGraphic.Points[0]);
                        roiGraphic.Name = shapeLabel;
                        roiGraphic.Resume(true); // Force callout location calculation
                    }

                    graphic = roiGraphic;
                }
            }
            else
                throw new Exception("Unknown shape type encountered: " + geoShape.GetType().FullName);

            return graphic;
        }

        private static IGraphic TextAnnotationToGraphic(aim_dotnet.TextAnnotation textAnnotation, string shapeLabel)
        {
            Platform.CheckForNullReference(textAnnotation.ConnectorPoints, "ConnectorPoints");
            Platform.CheckForNullReference(textAnnotation.ConnectorPoints.SpatialCoordinateCollection, "SpatialCoordinateCollection");
            Platform.CheckArgumentRange(textAnnotation.ConnectorPoints.SpatialCoordinateCollection.Count, 1, 2, "SpatialCoordinateCollection");

            if (textAnnotation.ConnectorPoints == null || textAnnotation.ConnectorPoints.SpatialCoordinateCollection == null)
                return null;

            var graphicText = AimHelpers.FormatPointCalloutText(shapeLabel, textAnnotation.Text.Trim());
            switch (textAnnotation.ConnectorPoints.SpatialCoordinateCollection.Count)
            {
                case 1:
                    {
                        InvariantTextPrimitive textPrimitive = new InvariantTextPrimitive(graphicText);
                        textPrimitive.Location = AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);

                        StandardStatefulGraphic statefulGraphic = new StandardStatefulGraphic(textPrimitive);
                        statefulGraphic.State = statefulGraphic.CreateInactiveState();
                        statefulGraphic.Name = shapeLabel;

                        return statefulGraphic;
                    }
                    break;
                case 2:
                    {
                        if (AimSettings.Default.UseCrosshairsForTextCallouts)
                        {
                            var crosshair = new CrosshairCalloutGraphic(graphicText);
                            crosshair.Name = shapeLabel;
                            crosshair.LineStyle = LineStyle.Solid;
                            crosshair.AnchorPoint =
                                AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
                            crosshair.TextLocation =
                                AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[1]);
                            crosshair.ShowShaft = !String.IsNullOrEmpty(graphicText);
                            StandardStatefulGraphic statefulGraphic = new StandardStatefulGraphic(crosshair);
                            statefulGraphic.State = statefulGraphic.CreateInactiveState();
                            statefulGraphic.Name = shapeLabel;

                            return statefulGraphic;
                        }
                        else
                        {
                            CalloutGraphic callout = new CalloutGraphic(graphicText);
                            callout.LineStyle = LineStyle.Solid;
                            callout.ShowArrowhead = true;
                            callout.AnchorPoint = AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
                            callout.TextLocation =
                                AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[1]);

                            StandardStatefulGraphic statefulGraphic = new StandardStatefulGraphic(callout);
                            statefulGraphic.State = statefulGraphic.CreateInactiveState();
                            statefulGraphic.Name = shapeLabel;

                            return statefulGraphic;
                        }
                    }
                    break;
                default:
                    break;
            }

            return null;
        }

        // Helper method
        private static RoiGraphic CreateRoiGraphic(IGraphic interactiveGraphic, IAnnotationCalloutLocationStrategy strategy)
        {
            RoiGraphic roiGraphic;
            if (strategy == null)
                roiGraphic = new AimRoiGraphic(interactiveGraphic);
            else
                roiGraphic = new AimRoiGraphic(interactiveGraphic, strategy);

            roiGraphic.Name = "ROI"; // string.Empty;
            roiGraphic.State = roiGraphic.CreateInactiveState();

            return roiGraphic;
        }

        internal static PointF AsPointF(aim_dotnet.ISpatialCoordinate spatialCoord)
        {
            Platform.CheckTrue(spatialCoord != null, "Spatial Coordinate Exists");
            Platform.CheckTrue(spatialCoord.CoordinateType == aim_dotnet.SpatialCoordinateType.SPATIAL_COORD_2D, "SpatialCoordinate is 2D");

            aim_dotnet.TwoDimensionSpatialCoordinate twoDCoord = spatialCoord as aim_dotnet.TwoDimensionSpatialCoordinate;
            if (twoDCoord == null)
                throw new ArgumentException("Spatial coordinate is not 2D");

            return new PointF((float)twoDCoord.X, (float)twoDCoord.Y);
        }
    }
}
