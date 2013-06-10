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
using System.Drawing;

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

namespace AIM.Annotation
{
	internal class AimHelpers
	{
		public static List<aim_dotnet.Annotation> CreateAimAnnotations(IEnumerable<IPresentationImage> presentationImages, AimAnnotationCreationContext creationContext, out List<IGraphic> annotationsGraphic)
		{
			var annotations = new List<aim_dotnet.Annotation>();
			annotationsGraphic = new List<IGraphic>();
			if (creationContext.SelectedAnnotationKind == aim_dotnet.AnnotationKind.AK_ImageAnnotation)
			{
				var annotationSOPs = creationContext.SOPImageUIDs;
				foreach (var currentImage in presentationImages)
				{
					var currentImageSOP = currentImage as IImageSopProvider;
					if (currentImageSOP == null)
						continue;
					if (annotationSOPs.Count > 0 && !annotationSOPs.Contains(currentImageSOP.ImageSop.SopInstanceUid))
						continue;

					var currentOverlayGraphics = currentImage as IOverlayGraphicsProvider;
					if (currentOverlayGraphics != null)
					{
						// Create one annotation per calculation/geo shape
						var shapeIdentifier = 0;
						var geoShapes = new List<aim_dotnet.IGeometricShape>();
						var calculations = creationContext.includeCalculations ? new List<aim_dotnet.Calculation>() : null;
						var textAnnotations = new List<aim_dotnet.TextAnnotation>();
						foreach (var graphic in currentOverlayGraphics.OverlayGraphics)
						{
							var currentRoiGraphic = graphic as RoiGraphic;
							if (currentRoiGraphic != null && currentRoiGraphic.Roi != null)
							{
								// Create Geo Shape for this ROI
								var geoShape = Create2DGeoShape(currentRoiGraphic, currentImageSOP.ImageSop.SopInstanceUid, currentImageSOP.Frame.FrameNumber);
								if (geoShape != null)
								{
									geoShape.ShapeIdetifier = shapeIdentifier++;
									if (calculations != null)
										calculations.AddRange(CreateCalculations(currentRoiGraphic, geoShape.ShapeIdetifier));
									geoShapes.Add(geoShape);
									annotationsGraphic.Add(graphic);
								}
							}
							else if (graphic is ContextMenuControlGraphic)
							{
								var contextMenuControlGraphic = (ContextMenuControlGraphic) graphic;
								if (contextMenuControlGraphic.Subject != null)
								{
									var textAnnotation = 
										CreateTextAnnotation(contextMenuControlGraphic.Subject, currentImageSOP.ImageSop.SopInstanceUid, currentImageSOP.Frame.FrameNumber);
									if (textAnnotation != null)
									{
										if (textAnnotation.ConnectorPoints != null)
											textAnnotation.ConnectorPoints.ShapeIdetifier = shapeIdentifier++;
										textAnnotations.Add(textAnnotation);
										annotationsGraphic.Add(graphic);
									}
								}
							}
						}

						if (annotationSOPs.Count > 0 || geoShapes.Count > 0 || (calculations != null && calculations.Count > 0) || textAnnotations.Count > 0)
						{
							var imgAnn = CreateImageAnnotation(currentImageSOP, creationContext);
							if (geoShapes.Count > 0)
								imgAnn.GeometricShapeCollection = geoShapes;
							if (calculations != null && calculations.Count > 0)
								imgAnn.CalculationCollection = calculations;
							if (textAnnotations.Count > 0)
								imgAnn.TextAnnotationCollection = textAnnotations;
							AddDicomImageReference(imgAnn, currentImageSOP);
							annotations.Add(imgAnn);
						}
					}
				}

				return annotations;
			}

			throw new NotImplementedException("Creation of AnnotationOfAnnotation objects is not yet supported ");
		}

		private static aim_dotnet.ImageAnnotation CreateImageAnnotation(IImageSopProvider imageSop, AimAnnotationCreationContext creationContext)
		{
			// Create Basic Image Annotation
			Platform.CheckTrue(creationContext.SelectedAnnotationKind == aim_dotnet.AnnotationKind.AK_ImageAnnotation, "ImageAnnotationKind");
			Platform.CheckForEmptyString(creationContext.AnnotationName, "AnnotationName");
			var imgAnnotation = new aim_dotnet.ImageAnnotation();
			imgAnnotation.CodeValue = creationContext.AnnotationTypeCode.CodeValue;
			imgAnnotation.CodeMeaning = creationContext.AnnotationTypeCode.CodeMeaning;
			imgAnnotation.CodingSchemeDesignator = creationContext.AnnotationTypeCode.CodingSchemeDesignator;
			imgAnnotation.CodingSchemeVersion = creationContext.AnnotationTypeCode.CodingSchemeVersion;
			imgAnnotation.UniqueIdentifier = DicomUid.GenerateUid().UID;
			imgAnnotation.Name = creationContext.AnnotationName;
			imgAnnotation.DateTime = DateTime.Now;
			imgAnnotation.Patient = CreatePatient(imageSop);
			imgAnnotation.Equipment = CreateEquipment();
			if (creationContext.AnnotationUser != null)
				imgAnnotation.User = new aim_dotnet.User(creationContext.AnnotationUser);
			if (!string.IsNullOrEmpty(creationContext.AnnotationComment))
				imgAnnotation.Comment = creationContext.AnnotationComment;
			if (creationContext.SelectedAnatomicEntities != null)
				imgAnnotation.AnatomyEntityCollection = new List<aim_dotnet.AnatomicEntity>(creationContext.SelectedAnatomicEntities);
			if (creationContext.SelectedImagingObservations != null)
				imgAnnotation.ImagingObservationCollection = new List<aim_dotnet.ImagingObservation>(creationContext.SelectedImagingObservations);
			if (creationContext.SelectedInferences != null)
				imgAnnotation.InferenceCollection = new List<aim_dotnet.Inference>(creationContext.SelectedInferences);

			return imgAnnotation;
		}

		private static aim_dotnet.Person CreatePatient(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");
			var patient = new aim_dotnet.Person();
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
			var equipment = new aim_dotnet.Equipment();
			equipment.ManufacturerName = SR.EquipmentManufacturer;
			equipment.ManufacturerModelName = SR.EquipmentManufacturerModelName;
			equipment.SoftwareVersion = string.Format("{0}.{1}.{2}.{3}", Application.Version.Major, Application.Version.Minor, Application.Version.Revision,
			                                          Application.Version.Build);

			return equipment;
		}

		private static aim_dotnet.IGeometricShape Create2DGeoShape(RoiGraphic roiGraphic, string imageUID, int frameNumber)
		{
			Platform.CheckForEmptyString(imageUID, "imageUID");

			aim_dotnet.IGeometricShape geoShape = null;
			var roi = roiGraphic.Roi;
			if (roi is EllipticalRoi)
			{
				var ellipticalRoi = roi as EllipticalRoi;
				Platform.CheckForNullReference(ellipticalRoi, "ellipticalRoi");
				var ellipseShape = new aim_dotnet.Ellipse();
				ellipseShape.EllipseCollection = new List<aim_dotnet.ISpatialCoordinate>();
				ellipseShape.EllipseCollection.Add(
					Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left, ellipticalRoi.BoundingBox.Top + ellipticalRoi.BoundingBox.Height/2, imageUID, frameNumber, 0));
				ellipseShape.EllipseCollection.Add(
					Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Right, ellipticalRoi.BoundingBox.Top + ellipticalRoi.BoundingBox.Height/2, imageUID, frameNumber, 1));
				ellipseShape.EllipseCollection.Add(
					Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left + ellipticalRoi.BoundingBox.Width/2, ellipticalRoi.BoundingBox.Top, imageUID, frameNumber, 2));
				ellipseShape.EllipseCollection.Add(
					Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left + ellipticalRoi.BoundingBox.Width/2, ellipticalRoi.BoundingBox.Bottom, imageUID, frameNumber, 3));

				geoShape = ellipseShape;
			}
			else if (roi is PolygonalRoi)
			{
				var polygonalRoi = roi as PolygonalRoi;
				Platform.CheckForNullReference(polygonalRoi, "polygonalRoi");
				var polylineShape = new aim_dotnet.Polyline();
				polylineShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
				polylineShape.IsIncludeFlag = true;
				for (var i = 0; i < polygonalRoi.Polygon.Vertices.Count; i++)
				{
					polylineShape.SpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(polygonalRoi.Polygon.Vertices[i].X, polygonalRoi.Polygon.Vertices[i].Y, imageUID, frameNumber, i));
				}
				if (polygonalRoi.Polygon.Vertices.Count > 0 && polygonalRoi.Polygon.Vertices[polygonalRoi.Polygon.Vertices.Count - 1] != polygonalRoi.Polygon.Vertices[0])
				{
					polylineShape.SpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(polygonalRoi.Polygon.Vertices[0].X, polygonalRoi.Polygon.Vertices[0].Y, imageUID,
						                          frameNumber, 0));
				}
				geoShape = polylineShape;
			}
			else if (roi is ProtractorRoiInfo)
			{
				var protractorRoi = roi as ProtractorRoiInfo;
				Platform.CheckForNullReference(protractorRoi, "protractorRoi");
				var multipointShape = new aim_dotnet.MultiPoint();
				multipointShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
				multipointShape.IsIncludeFlag = true;
				for (var i = 0; i < protractorRoi.Points.Count; i++)
				{
					multipointShape.SpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(protractorRoi.Points[i].X, protractorRoi.Points[i].Y, imageUID, frameNumber, i));
				}
				geoShape = multipointShape;
			}
			else if (roi is LinearRoi)
			{
				var linearRoi = roi as LinearRoi;
				Platform.CheckForNullReference(linearRoi, "linearRoi");
				var multipointShape = new aim_dotnet.MultiPoint();
				multipointShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
				multipointShape.IsIncludeFlag = true;
				for (var i = 0; i < linearRoi.Points.Count; i++)
				{
					multipointShape.SpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(linearRoi.Points[i].X, linearRoi.Points[i].Y, imageUID, frameNumber, i));
				}
				geoShape = multipointShape;
			}
			else if (roi is RectangularRoi)
			{
				var rectangularRoi = roi as RectangularRoi;
				Platform.CheckForNullReference(rectangularRoi, "rectangularRoi");
				var polylineShape = new aim_dotnet.Polyline();
				polylineShape.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
				// Top Left
				polylineShape.SpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Left, rectangularRoi.BoundingBox.Top, imageUID, frameNumber, 0));
				// Top Right
				polylineShape.SpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Right, rectangularRoi.BoundingBox.Top, imageUID, frameNumber, 1));
				// Buttom Right
				polylineShape.SpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Right, rectangularRoi.BoundingBox.Bottom, imageUID, frameNumber, 2));
				// Buttom Left
				polylineShape.SpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Left, rectangularRoi.BoundingBox.Bottom, imageUID, frameNumber, 3));

				geoShape = polylineShape;
			}
			else
				Platform.Log(LogLevel.Error, "AIMHelper.CreateGeoShape. Unhandled ROI type: " + roi.GetType().FullName);

			return geoShape;
		}

		private static aim_dotnet.TwoDimensionSpatialCoordinate Create2DSpatialCoordinate(float x, float y, string imageUID, int frameNumber, int coordinateIndex)
		{
			var spatialCoord = new aim_dotnet.TwoDimensionSpatialCoordinate();
			spatialCoord.X = x;
			spatialCoord.Y = y;
			spatialCoord.ImageReferenceUID = imageUID;
			spatialCoord.ReferencedFrameNumber = frameNumber;
			spatialCoord.CoordinateIndex = coordinateIndex;

			return spatialCoord;
		}

		private static bool AddDicomImageReference(aim_dotnet.ImageAnnotation imageAnnotation, IImageSopProvider image)
		{
			Platform.CheckForNullReference(imageAnnotation, "ImageAnnotation");
			if (imageAnnotation.ImageReferenceCollection == null)
				imageAnnotation.ImageReferenceCollection = new List<aim_dotnet.ImageReference>();
			var imageReferences = imageAnnotation.ImageReferenceCollection;
			aim_dotnet.ImageStudy aimImageStudy = null;
			foreach (var imgRef in imageReferences)
			{
				var dicomImgRef = imgRef as aim_dotnet.DICOMImageReference;
				if (dicomImgRef != null)
				{
					if (dicomImgRef.Study.InstanceUID == image.ImageSop.StudyInstanceUid &&
					    dicomImgRef.Study.Series.InstanceUID == image.ImageSop.SeriesInstanceUid)
						aimImageStudy = dicomImgRef.Study;
				}
			}
			if (aimImageStudy == null)
			{
				aimImageStudy = CreateStudy(image);
				aimImageStudy.Series = CreateSeries(image);
				aimImageStudy.Series.ImageCollection = new List<aim_dotnet.Image>();
				var dicomImgRef = new aim_dotnet.DICOMImageReference();
				dicomImgRef.Study = aimImageStudy;
				imageReferences.Add(dicomImgRef);
			}
			foreach (var existingImage in aimImageStudy.Series.ImageCollection)
			{
				if (existingImage.SopInstanceUID == image.ImageSop.SopInstanceUid)
					return false;
			}
			var aimImage = CreateImage(image);
			aimImageStudy.Series.ImageCollection.Add(aimImage);

			return true;
		}

		private static aim_dotnet.ImageStudy CreateStudy(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");
			var aimStudy = new aim_dotnet.ImageStudy();
			aimStudy.InstanceUID = image.ImageSop.StudyInstanceUid;
			DateTime studyDate;
			if (DateTimeParser.ParseDateAndTime(null, image.ImageSop.StudyDate, image.ImageSop.StudyTime, out studyDate))
				aimStudy.StartDate = studyDate;

			return aimStudy;
		}

		private static aim_dotnet.ImageSeries CreateSeries(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");
			var aimSeries = new aim_dotnet.ImageSeries();
			aimSeries.InstanceUID = image.ImageSop.SeriesInstanceUid;

			return aimSeries;
		}

		private static aim_dotnet.Image CreateImage(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");
			var aimImage = new aim_dotnet.Image();
			aimImage.SopClassUID = image.ImageSop.SopClassUid;
			aimImage.SopInstanceUID = image.ImageSop.SopInstanceUid;

			return aimImage;
		}

		private static List<aim_dotnet.Calculation> CreateCalculations(RoiGraphic roiGraphic, int referencedGeoShapeId)
		{
			var calculations = new List<aim_dotnet.Calculation>();
			List<aim_dotnet.ReferencedGeometricShape> referencedGeometricShapes = null;
			if (referencedGeoShapeId >= 0)
			{
				referencedGeometricShapes = new List<aim_dotnet.ReferencedGeometricShape>();
				referencedGeometricShapes.Add(new aim_dotnet.ReferencedGeometricShape {ReferencedShapeIdentifier = referencedGeoShapeId});
			}

			var roi = roiGraphic.Roi;
			foreach (var analyzer in roiGraphic.Callout.RoiAnalyzers)
			{
				if (analyzer.SupportsRoi(roi))
				{
					var calculation = new aim_dotnet.Calculation();
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
						var roiLengthProvider = (IRoiLengthProvider) roi;

						var oldUnits = roiLengthProvider.Units;
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
						var roiAreaProvider = (IRoiAreaProvider) roi;

						var oldUnits = roiAreaProvider.Units;
						roiAreaProvider.Units = roiAreaProvider.IsCalibrated ? Units.Millimeters : Units.Pixels;
						calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(roiAreaProvider.Area, UnitsToName(roiAreaProvider.Units), "Value"));
						roiAreaProvider.Units = oldUnits;

						calculations.Add(calculation);
					}
					else if (analyzer is RoiStatisticsAnalyzer)
					{
						if (roi.PixelData is GrayscalePixelData && IsBoundingBoxInImage(roi.BoundingBox, roi.ImageColumns, roi.ImageRows))
						{
							var statisticsProvider = (IRoiStatisticsProvider) roi;
							var mean = statisticsProvider.Mean;
							var stdDev = statisticsProvider.StandardDeviation;
							var calcStdDev = new aim_dotnet.Calculation(calculation);

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
					else if (analyzer is ProtractorAngleCalculator)
					{
						var protractorRoiInfo = roi as ProtractorRoiInfo;
						if (protractorRoiInfo != null && protractorRoiInfo.Points.Count >= 3)
						{
							var normalizedPoints = NormalizePoints(protractorRoiInfo);
							var angle = Math.Abs(Vector.SubtendedAngle(normalizedPoints[0], normalizedPoints[1], normalizedPoints[2]));

							calculation.CodeValue = CodeList.CalculationCodeForAngle.CodeValue;
							calculation.CodeMeaning = CodeList.CalculationCodeForAngle.CodeMeaning;
							calculation.CodingSchemeDesignator = CodeList.CalculationCodeForAngle.CodingSchemeDesignator;
							calculation.CodingSchemeVersion = CodeList.CalculationCodeForAngle.CodingSchemeVersion;
							calculation.Description = "Angle";
							calculation.ReferencedGeometricShapeCollection = referencedGeometricShapes;
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
					System.Diagnostics.Debug.Assert(false, "Unexpected calculation units");
					break;
			}
			return string.Empty;
		}

		private static aim_dotnet.CalculationResult CreateScalarCalculationResult(double value, string unit, string label)
		{
			var dimension = new aim_dotnet.Dimension();
			dimension.Index = 0;
			dimension.Size = 1;
			dimension.Label = label;

			var coordinate = new aim_dotnet.Coordinate();
			coordinate.DimensionIndex = 0;
			coordinate.Position = 0;

			var calculationData = new aim_dotnet.CalculationData();
			calculationData.Value = value;
			calculationData.CoordinateCollection = new List<aim_dotnet.Coordinate>();
			calculationData.CoordinateCollection.Add(coordinate);

			var result = new aim_dotnet.CalculationResult();
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
			if (graphic is UserCalloutGraphic)
			{
				var userCalloutGraphic = (UserCalloutGraphic) graphic;
				var multiPoint = new aim_dotnet.MultiPoint();
				multiPoint.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
				foreach (var pointF in new[] {userCalloutGraphic.AnchorPoint, userCalloutGraphic.AttachmentPoint})
				{
					multiPoint.SpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(pointF.X, pointF.Y, imageUid, frameNumber, multiPoint.SpatialCoordinateCollection.Count));
				}

				return new aim_dotnet.TextAnnotation {Text = userCalloutGraphic.Text, ConnectorPoints = multiPoint};
			}

			if (graphic is InvariantTextPrimitive)
			{
				var invariantTextPrimitive = (InvariantTextPrimitive) graphic;
				var multiPoint = new aim_dotnet.MultiPoint();
				multiPoint.SpatialCoordinateCollection = new List<aim_dotnet.ISpatialCoordinate>();
				multiPoint.SpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(invariantTextPrimitive.Location.X, invariantTextPrimitive.Location.Y, imageUid, frameNumber,
					                          multiPoint.SpatialCoordinateCollection.Count));

				return new aim_dotnet.TextAnnotation {Text = invariantTextPrimitive.Text, ConnectorPoints = multiPoint};
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

		private static List<PointF> NormalizePoints(ProtractorRoiInfo roiInfo)
		{
			var aspectRatio = 1F;
			if (roiInfo.PixelAspectRatio.IsNull)
			{
				if (!roiInfo.NormalizedPixelSpacing.IsNull)
					aspectRatio = (float)roiInfo.NormalizedPixelSpacing.AspectRatio;
			}
			else
			{
				aspectRatio = roiInfo.PixelAspectRatio.Value;
			}

			var normalized = new List<PointF>();
			foreach (var point in roiInfo.Points)
				normalized.Add(new PointF(point.X, point.Y * aspectRatio));

			return normalized;
		}

		// ====================================================================
		//
		//  Read and display annotation back
		//
		// ====================================================================

		public static bool ReadGraphicsFromAnnotation(aim_dotnet.Annotation annotation, IPresentationImage presentationImage)
		{
			var hasNewRoiGraphic = false;

			var graphicsProvider = presentationImage as IOverlayGraphicsProvider;
			var currentImageSOP = presentationImage as IImageSopProvider;
			if (graphicsProvider == null || currentImageSOP == null)
				return false;

			if (annotation is aim_dotnet.ImageAnnotation)
			{
				var imgAnnotation = annotation as aim_dotnet.ImageAnnotation;
				if (imgAnnotation.GeometricShapeCollection != null)
				{
					foreach (var geoShape in imgAnnotation.GeometricShapeCollection)
					{
						if (GetImageSOPInstanceUID(geoShape) != currentImageSOP.ImageSop.SopInstanceUid)
							continue;

						var isAlreadyDisplayed = false;
						foreach (var graphic in graphicsProvider.OverlayGraphics)
						{
							var aimGraphic = graphic as AimGraphic;
							isAlreadyDisplayed = aimGraphic != null && aimGraphic.AimAnnotation.UniqueIdentifier == imgAnnotation.UniqueIdentifier &&
							                     aimGraphic.ShapeIdentifier == geoShape.ShapeIdetifier;
							if (isAlreadyDisplayed)
								break;
						}
						if (isAlreadyDisplayed)
							continue;

						var geoGraphic = GeoShapeToGraphic(geoShape, string.IsNullOrEmpty(imgAnnotation.Name) ? string.Empty : imgAnnotation.Name);
						if (geoGraphic != null)
						{
							var aimGraphic = new AimGraphic(geoGraphic, imgAnnotation, geoShape.ShapeIdetifier);
                            aimGraphic.Color = AimSettings.Default.GetAimGraphicColorForUser(aimGraphic.UserLoginName);
							graphicsProvider.OverlayGraphics.Add(aimGraphic);
						}

						hasNewRoiGraphic |= geoGraphic != null;
					}
				}
				if (imgAnnotation.TextAnnotationCollection != null)
				{
					foreach (var textAnnotation in imgAnnotation.TextAnnotationCollection)
					{
						if (textAnnotation.ConnectorPoints == null)
							continue;
						if (GetImageSOPInstanceUID(textAnnotation.ConnectorPoints) != currentImageSOP.ImageSop.SopInstanceUid)
							continue;

						var isAlreadyDisplayed = false;
						foreach (var graphic in graphicsProvider.OverlayGraphics)
						{
							var aimGraphic = graphic as AimGraphic;
							isAlreadyDisplayed = aimGraphic != null && aimGraphic.AimAnnotation.UniqueIdentifier == imgAnnotation.UniqueIdentifier &&
							                     aimGraphic.ShapeIdentifier == textAnnotation.ConnectorPoints.ShapeIdetifier;
							if (isAlreadyDisplayed)
								break;
						}
						if (isAlreadyDisplayed)
							continue;

						var textGraphic = TextAnnotationToGraphic(textAnnotation, string.IsNullOrEmpty(imgAnnotation.Name) ? string.Empty : imgAnnotation.Name);
						if (textGraphic != null)
						{
							var aimGraphic = new AimGraphic(textGraphic, imgAnnotation, textAnnotation.ConnectorPoints.ShapeIdetifier);
							aimGraphic.Color = Color.SlateBlue;
							graphicsProvider.OverlayGraphics.Add(aimGraphic);
						}
						hasNewRoiGraphic |= textGraphic != null;
					}
				}
			}

			return hasNewRoiGraphic;
		}

		private static string GetImageSOPInstanceUID(aim_dotnet.IGeometricShape geoShape)
		{
			if (geoShape.SpatialCoordinateCollection != null && geoShape.SpatialCoordinateCollection.Count > 0 &&
			    geoShape.SpatialCoordinateCollection[0].CoordinateType == aim_dotnet.SpatialCoordinateType.SPATIAL_COORD_2D)
			{
				var twoDSpatialCoord = geoShape.SpatialCoordinateCollection[0] as aim_dotnet.TwoDimensionSpatialCoordinate;
				if (twoDSpatialCoord != null)
					return twoDSpatialCoord.ImageReferenceUID;
			}

			return string.Empty;
		}

		private static IGraphic GeoShapeToGraphic(aim_dotnet.IGeometricShape geoShape, string shapeLabel)
		{
			if (geoShape.SpatialCoordinateCollection == null || geoShape.SpatialCoordinateCollection.Count == 0)
				return null;

			IGraphic graphic = null;
			if (geoShape is aim_dotnet.Circle)
			{
				// Ellipse
				var shapeCircle = geoShape as aim_dotnet.Circle;
				var centerPt = AsPointF(shapeCircle.Center);
				var radiusPt = AsPointF(shapeCircle.RadiusPoint);
				var radiusLength = Vector.Distance(centerPt, radiusPt);
				RoiGraphic roiGraphic = AimRoiGraphic.CreateEllipse();
				var boundableGraphic = roiGraphic.Subject as BoundableGraphic;
				if (boundableGraphic != null)
				{
					roiGraphic.Suspend();
					roiGraphic.Name = shapeLabel;
					boundableGraphic.TopLeft = new PointF((float) (centerPt.X - radiusLength), (float) (centerPt.Y - radiusLength));
					boundableGraphic.BottomRight = new PointF((float) (centerPt.X + radiusLength), (float) (centerPt.Y + radiusLength));
					roiGraphic.Resume(true);
				}
				graphic = roiGraphic;
			}
			else if (geoShape is aim_dotnet.Ellipse)
			{
				// Ellipse
				var shapeEllipse = geoShape as aim_dotnet.Ellipse;
				var firstMajorAxisPt = AsPointF(shapeEllipse.EllipseCollection[0]);
				var secondMajorAxisPt = AsPointF(shapeEllipse.EllipseCollection[1]);
				var firstMinorAxisPt = AsPointF(shapeEllipse.EllipseCollection[2]);
				var secondMinorAxisPt = AsPointF(shapeEllipse.EllipseCollection[3]);
				RoiGraphic roiGraphic = AimRoiGraphic.CreateEllipse();
				var boundableGraphic = roiGraphic.Subject as BoundableGraphic;
				if (boundableGraphic != null)
				{
					roiGraphic.Suspend();
					roiGraphic.Name = shapeLabel;
					boundableGraphic.TopLeft = new PointF(firstMajorAxisPt.X, firstMinorAxisPt.Y);
					boundableGraphic.BottomRight = new PointF(secondMajorAxisPt.X, secondMinorAxisPt.Y);
					roiGraphic.Resume(true);
				}
				graphic = roiGraphic;
			}
			else if (geoShape is aim_dotnet.Point)
			{
				var shapePoint = geoShape as aim_dotnet.Point;
				var callout = new CalloutGraphic(shapeLabel);
				callout.LineStyle = LineStyle.Solid;
				callout.ShowArrowhead = true;
				callout.AnchorPoint = AsPointF(shapePoint.Center);
				callout.TextLocation = callout.AnchorPoint - new SizeF(30, 30);
				var statefulGraphic = new StandardStatefulGraphic(callout);
				statefulGraphic.State = statefulGraphic.CreateInactiveState();
				graphic = statefulGraphic;
			}
			else if (geoShape is aim_dotnet.MultiPoint)
			{
				// How this case works:
				// If we have 2 points, it's a line
				// If we have 3 points, it's a protractor
				// All others - unknown unclosed object (not supported)
				var shapeMultiPoint = geoShape as aim_dotnet.MultiPoint;
				switch (shapeMultiPoint.SpatialCoordinateCollection.Count)
				{
					case 2:
						{
							// Line
							var interactiveGraphic = new VerticesControlGraphic(new MoveControlGraphic(new PolylineGraphic()));
							var firstPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[0]);
							var secondPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[1]);
							interactiveGraphic.Subject.Points.Add(firstPt);
							interactiveGraphic.Subject.Points.Add(secondPt);
							var roiGraphic = CreateRoiGraphic(interactiveGraphic, null);
							roiGraphic.Name = shapeLabel;
							roiGraphic.Resume(true);
							graphic = roiGraphic;
						}
						break;
					case 3:
						{
							// Protractor
							var interactiveGraphic = new VerticesControlGraphic(new MoveControlGraphic(new ProtractorGraphic()));
							var firstPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[0]);
							var secondPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[1]);
							var thirdPt = AsPointF(shapeMultiPoint.SpatialCoordinateCollection[2]);
							interactiveGraphic.Subject.Points.Add(firstPt);
							interactiveGraphic.Subject.Points.Add(secondPt);
							interactiveGraphic.Subject.Points.Add(thirdPt);
							var roiGraphic = CreateRoiGraphic(interactiveGraphic,  new ProtractorRoiCalloutLocationStrategy());
							roiGraphic.Name = shapeLabel;
							roiGraphic.Resume(true);
							graphic = roiGraphic;
						}
						break;
					default:
						throw new NotImplementedException("Reading non-linear or non-triangular MultiPoint shape is not implemented");
				}
			}
			else if (geoShape is aim_dotnet.Polyline)
			{
				var shapePolyline = geoShape as aim_dotnet.Polyline;
				var isRectangle = false;
				if (shapePolyline.SpatialCoordinateCollection.Count == 4)
				{
					var twoDPoint1 = AsPointF(shapePolyline.SpatialCoordinateCollection[0]);
					var twoDPoint2 = AsPointF(shapePolyline.SpatialCoordinateCollection[1]);
					var twoDPoint3 = AsPointF(shapePolyline.SpatialCoordinateCollection[2]);
					var twoDPoint4 = AsPointF(shapePolyline.SpatialCoordinateCollection[3]);
					if ((twoDPoint1.X == twoDPoint2.X && twoDPoint2.Y == twoDPoint3.Y && twoDPoint3.X == twoDPoint4.X && twoDPoint4.Y == twoDPoint1.Y) ||
					    (twoDPoint1.Y == twoDPoint2.Y && twoDPoint2.X == twoDPoint3.X && twoDPoint3.Y == twoDPoint4.Y && twoDPoint4.X == twoDPoint1.X))
					{
						isRectangle = true;

						RoiGraphic roiGraphic = AimRoiGraphic.CreateRectangle();
						var boundableGraphic = roiGraphic.Subject as BoundableGraphic;
						if (boundableGraphic != null)
						{
							roiGraphic.Suspend();
							roiGraphic.Name = shapeLabel;
							boundableGraphic.TopLeft = twoDPoint1;
							boundableGraphic.BottomRight = twoDPoint3;
							roiGraphic.Resume(true);
						}

						graphic = roiGraphic;
					}
				}
				if (!isRectangle)
				{
					RoiGraphic roiGraphic = AimRoiGraphic.CreatePolygon();
					var polylineGraphic = roiGraphic.Subject as PolylineGraphic;
					if (polylineGraphic != null)
					{
						roiGraphic.Suspend();
						for (var i = 0; i < shapePolyline.SpatialCoordinateCollection.Count; i++)
						{
							var twoDPoint = AsPointF(shapePolyline.SpatialCoordinateCollection[i]);
							polylineGraphic.Points.Add(twoDPoint);
						}
						// We deal with closed polygons only
						if (polylineGraphic.Points.Count > 0)
							polylineGraphic.Points.Add(polylineGraphic.Points[0]);
						roiGraphic.Name = shapeLabel;
						roiGraphic.Resume(true);
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

			var graphicText = shapeLabel.Trim();
			graphicText = string.IsNullOrEmpty(graphicText)
			              	? textAnnotation.Text.Trim()
			              	: string.Format("{0}:\r\n{1}", graphicText, textAnnotation.Text.Trim());
			switch (textAnnotation.ConnectorPoints.SpatialCoordinateCollection.Count)
			{
				case 1:
					{
						var textPrimitive = new InvariantTextPrimitive(graphicText);
						textPrimitive.Location = AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
						var statefulGraphic = new StandardStatefulGraphic(textPrimitive);
						statefulGraphic.State = statefulGraphic.CreateInactiveState();
						return statefulGraphic;
					}
					break;
				case 2:
					{
						var callout = new CalloutGraphic(graphicText);
						callout.LineStyle = LineStyle.Solid;
						callout.ShowArrowhead = true;
						callout.AnchorPoint = AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[0]);
						callout.TextLocation = AsPointF(textAnnotation.ConnectorPoints.SpatialCoordinateCollection[1]);
						var statefulGraphic = new StandardStatefulGraphic(callout);
						statefulGraphic.State = statefulGraphic.CreateInactiveState();
						return statefulGraphic;
					}
					break;
				default:
					break;
			}
			return null;
		}

		private static RoiGraphic CreateRoiGraphic(IGraphic interactiveGraphic, IAnnotationCalloutLocationStrategy strategy)
		{
			RoiGraphic roiGraphic = strategy == null ? new AimRoiGraphic(interactiveGraphic) : new AimRoiGraphic(interactiveGraphic, strategy);

			roiGraphic.Name = "ROI";
			roiGraphic.State = roiGraphic.CreateInactiveState();

			return roiGraphic;
		}

		private static PointF AsPointF(aim_dotnet.ISpatialCoordinate spatialCoord)
		{
			Platform.CheckTrue(spatialCoord != null, "Spatial Coordinate Exists");
			Platform.CheckTrue(spatialCoord.CoordinateType == aim_dotnet.SpatialCoordinateType.SPATIAL_COORD_2D, "SpatialCoordinate is 2D");
			var twoDCoord = spatialCoord as aim_dotnet.TwoDimensionSpatialCoordinate;
			if (twoDCoord == null)
				throw new ArgumentException("Spatial coordinate is not 2D");

			return new PointF((float)twoDCoord.X, (float)twoDCoord.Y);
		}

		// ====================================================================
		//
		//  Annotation creation and manipulation helpers
		//
		// ====================================================================

		public static bool IsImageMarkupPresent(IPresentationImage image)
		{
			var currentOverlayGraphics = image as IOverlayGraphicsProvider;
			if (currentOverlayGraphics != null)
			{
				foreach (var graphic in currentOverlayGraphics.OverlayGraphics)
				{
					if (graphic is RoiGraphic)
						return true;

					var contextMenuControlGraphic = graphic as ContextMenuControlGraphic;
					if (contextMenuControlGraphic != null && contextMenuControlGraphic.Subject != null)
					{
						var userCalloutGraphic = contextMenuControlGraphic.Subject as UserCalloutGraphic;
						if (userCalloutGraphic != null)
							return true;

						var invariantTextPrimitive = contextMenuControlGraphic.Subject as InvariantTextPrimitive;
						if (invariantTextPrimitive != null)
							return true;
					}
				}
			}
			return false;
		}

		public static bool WriteXmlAnnotationToFile(aim_dotnet.Annotation annotation, string filePathName)
		{
			var xmlModel = new aim_dotnet.XmlModel();
			try
			{
				xmlModel.WriteAnnotationToFile(annotation, filePathName);
				return true;
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to save annotation to file \"{0}\"", filePathName);
			}
			finally
			{
				xmlModel = null;
			}

			return false;
		}

		public static string[] WriteXmlAnnotationsToFolder(List<aim_dotnet.Annotation> annotations, string folderPath)
		{
			var savedFileNames = new List<string>();
			var xmlModel = new aim_dotnet.XmlModel();
			foreach (var annotation in annotations)
			{
				string xmlFileName = null;
				var fileName = string.IsNullOrEmpty(annotation.UniqueIdentifier) ? System.IO.Path.GetRandomFileName() : annotation.UniqueIdentifier;
				try
				{
					xmlFileName = System.IO.Path.ChangeExtension(System.IO.Path.Combine(folderPath, fileName), "xml");
					xmlModel.WriteAnnotationToFile(annotation, xmlFileName);
					savedFileNames.Add(xmlFileName);
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to save annotation to file \"{0}\"", xmlFileName);
					try
					{
						if (!string.IsNullOrEmpty(xmlFileName))
							System.IO.File.Delete(xmlFileName);
					}
					catch (Exception)
					{
					}
				}
			}
			xmlModel = null;

			return savedFileNames.ToArray();
		}
	}
}
