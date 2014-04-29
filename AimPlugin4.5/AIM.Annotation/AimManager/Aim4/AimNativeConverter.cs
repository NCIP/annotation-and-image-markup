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
using System.Globalization;
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
using Segmentation.Graphics;

namespace AIM.Annotation.AimManager.Aim4
{
	internal class AimNativeConverter
	{
		public static aim4_dotnet.AnnotationCollection CreateAimAnnotations(IList<IPresentationImage> presentationImages, AimAnnotationCreationContext creationContext, IList<IGraphic> selectedMarkup, out List<IGraphic> annotationsGraphic)
		{
			annotationsGraphic = new List<IGraphic>(); // list that includes all IGraphic objects used to create new annotations

			if (creationContext.SelectedAnnotationKind == AimAnnotationCreationContext.AnnotationKind.ImageAnnotation)
			{
				var annotationCollection = new aim4_dotnet.ImageAnnotationCollection();
				annotationCollection.UniqueIdentifier = NewUid;
				annotationCollection.DateTime = DateTime.Now;
				annotationCollection.SeriesNumber = creationContext.SeriesNumber;
				// list of UIDs to include in the annotation. If empty, include all images from the same set which have markup.
				Dictionary<string, HashSet<int>> annotationSOPsAndFrames = creationContext.SopInstanceUidAndFrameNumbers;
				IImageSopProvider firstUsedImageSop = null; // the first image for which annotation is created

				foreach (IPresentationImage currentImage in presentationImages)
				{
					var currentImageSop = currentImage as IImageSopProvider;
					if (currentImageSop == null) // not an image?
						continue;

					// Skip the image if it's not included in our image annotation set
					if (annotationSOPsAndFrames.Values.Count > 0 &&
						!annotationSOPsAndFrames.ContainsKey(currentImageSop.ImageSop.SopInstanceUid) ||
						(annotationSOPsAndFrames[currentImageSop.ImageSop.SopInstanceUid] != null &&
						!annotationSOPsAndFrames[currentImageSop.ImageSop.SopInstanceUid].Contains(currentImageSop.Frame.FrameNumber)))
						continue;

					var imgAnnotation = CreateImageAnnotation(currentImageSop, creationContext, selectedMarkup, annotationsGraphic,
															  annotationSOPsAndFrames.Count > 0);

					if (imgAnnotation != null)
					{
						if (firstUsedImageSop == null)
							firstUsedImageSop = currentImageSop;

						if (annotationCollection.ImageAnnotations == null)
							annotationCollection.ImageAnnotations = new List<aim4_dotnet.ImageAnnotation>();
						annotationCollection.ImageAnnotations.Add(imgAnnotation);
					}
				}

				// There is no annotation without finding an image to base the annotation on.
				if (firstUsedImageSop == null)
					return null;

				annotationCollection.Person = CreatePatient(firstUsedImageSop);
				annotationCollection.Equipment = CreateEquipment();
				if (creationContext.AnnotationUser != null)
					annotationCollection.User = new aim4_dotnet.User
						{
							Name = creationContext.AnnotationUser.Name,
							LoginName = creationContext.AnnotationUser.LoginName,
							RoleInTrial = creationContext.AnnotationUser.RoleInTrial,
							NumberWithinRoleOfClinicalTrial = creationContext.AnnotationUser.NumberWithinRoleOfClinicalTrial
						};

				return annotationCollection;
			}
			else
			{
				throw new NotImplementedException("Creation of AnnotationOfAnnotation objects is not yet supported ");
			}
		}

		private static aim4_dotnet.ImageAnnotation CreateImageAnnotation(IImageSopProvider imageSop, AimAnnotationCreationContext creationContext, IList<IGraphic> selectedMarkup, IList<IGraphic> annotationsGraphic, bool createWithNoContent)
		{
			Platform.CheckForNullReference(annotationsGraphic, "annotationGrphic");

			// Find all markups on the image
			var currentOverlayGraphics = imageSop as IOverlayGraphicsProvider;
			if (currentOverlayGraphics != null) // all images should implement IOverlayGraphicsProvider
			{
				// Create one annotation per calculation/geo shape
				int shapeIdentifier = 0;
				var markups = new List<aim4_dotnet.MarkupEntity>();
				List<aim4_dotnet.CalculationEntity> calculations = creationContext.IncludeCalculations ? new List<aim4_dotnet.CalculationEntity>() : null;
				var segmentations = new List<aim4_dotnet.SegmentationEntity>();

				foreach (IGraphic graphic in currentOverlayGraphics.OverlayGraphics)
				{
					// Geometric Shape
					if (selectedMarkup.Contains(graphic))
					{
						RoiGraphic currentRoiGraphic = graphic as RoiGraphic;
						if (currentRoiGraphic != null && currentRoiGraphic.Roi != null)
						{
							// Create Geo Shape for this ROI
							aim4_dotnet.GeometricShapeEntity geoShape =
								Create2DGeoShape(currentRoiGraphic, imageSop.ImageSop.SopInstanceUid, imageSop.Frame.FrameNumber);

							if (geoShape != null)
							{
								// Shape Identifier is just a count
								geoShape.ShapeIdentifier = shapeIdentifier++;

								// Get calculations for this ROI, if required
								if (calculations != null)
									calculations.AddRange(CreateCalculations(currentRoiGraphic, geoShape.ShapeIdentifier));

								markups.Add(geoShape);
								annotationsGraphic.Add(graphic);
							}
						}
						// Text Annotation
						else if (graphic is ContextMenuControlGraphic)
						{
							ContextMenuControlGraphic contextMenuControlGraphic = (ContextMenuControlGraphic)graphic;
							if (contextMenuControlGraphic.Subject != null)
							{
								aim4_dotnet.TextAnnotationEntity textAnnotation =
									CreateTextAnnotation(contextMenuControlGraphic.Subject,
														 imageSop.ImageSop.SopInstanceUid,
														 imageSop.Frame.FrameNumber);

								if (textAnnotation != null)
								{
									if (textAnnotation.GeometricShapeEntity != null)
										textAnnotation.GeometricShapeEntity.ShapeIdentifier = shapeIdentifier++;

									markups.Add(textAnnotation);
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
								aim4_dotnet.GeometricShapeEntity geoShape = Create2DGeoShape(aimRoiGraphic,
																					   imageSop.ImageSop.SopInstanceUid,
																					   imageSop.Frame.FrameNumber);
								if (geoShape != null)
								{
									// Shape Identifier is just a count
									geoShape.ShapeIdentifier = shapeIdentifier++;

									// Get calculations for this ROI, if required
									if (calculations != null)
										calculations.AddRange(CreateCalculations(aimRoiGraphic, geoShape.ShapeIdentifier));

									markups.Add(geoShape);
									annotationsGraphic.Add(graphic);
								}
							}
							else if (aimTextAnnotationGraphic != null)
							{
								aim4_dotnet.TextAnnotationEntity textAnnotation =
									CreateTextAnnotation(aimTextAnnotationGraphic,
														 imageSop.ImageSop.SopInstanceUid,
														 imageSop.Frame.FrameNumber);

								if (textAnnotation != null)
								{
									if (textAnnotation.GeometricShapeEntity != null)
										textAnnotation.GeometricShapeEntity.ShapeIdentifier = shapeIdentifier++;

									markups.Add(textAnnotation);
									annotationsGraphic.Add(graphic);
								}
							}
							else
								Debug.Assert(false, "Failed to convert AimGraphic to an annotation type");
						}
						else if (graphic is SegFrameImageGraphic)
						{
							var segGraphic = (SegFrameImageGraphic) graphic;

							// TODO (future): implement IMarkup for segmentation graphic (if inclusion/exclusion from the annotation is required)??

							var segmentationEntity = new aim4_dotnet.DicomSegmentationEntity
								{
									UniqueIdentifier = NewUid,
									SopInstanceUid = new aim4_dotnet.iso_21090.II(segGraphic.SegmentationDocumentReference.SegmentationDocument.SopInstanceUid),
									SopClassUid = new aim4_dotnet.iso_21090.II(SopClass.SegmentationStorageUid),
									ReferencedSopInstanceUid = new aim4_dotnet.iso_21090.II(imageSop.ImageSop.SopInstanceUid),
									SegmentNumber = segGraphic.SegmentationDocumentReference.SegmentNumber
								};
							segmentations.Add(segmentationEntity);
						}
					}
				}

				// Create annotation if:
				// 1. we are explicitly asked to create an annotation for this SOP, or
				// 2. image has geometric or text markup(s), or
				// 3. image has calculation(s)
				// 4. NOTE: we always include image's segmentations but we do so only when markups, calculation or other conditions are present!
				if (createWithNoContent || markups.Count > 0 || (calculations != null && calculations.Count > 0))
				{
					aim4_dotnet.ImageAnnotation imgAnnotation = new aim4_dotnet.ImageAnnotation();
					PopulateAnnotationEntity(imgAnnotation, creationContext);

					if (markups.Count > 0)
						imgAnnotation.MarkupEntityCollection = markups;

					if (calculations != null && calculations.Count > 0)
						imgAnnotation.CalculationEntityCollection = calculations;

					if (segmentations.Count > 0)
						imgAnnotation.SegmentationEntityCollection = segmentations;

					// Add current image reference to the annotation
					AddDicomImageReference(imgAnnotation, imageSop);

					return imgAnnotation;
				}
			}

			return null;
		}

		// Populate Annotation Entity with its values
		private static void PopulateAnnotationEntity(aim4_dotnet.AnnotationEntity annotationEntity, AimAnnotationCreationContext creationContext)
		{
			Platform.CheckForEmptyString(creationContext.AnnotationName, "AnnotationName");

			//aim4_dotnet.ImageAnnotation imgAnnotation = new aim4_dotnet.ImageAnnotation();
			annotationEntity.UniqueIdentifier = NewUid;
			annotationEntity.TypeCode = new List<aim4_dotnet.iso_21090.CD>
				{
					new aim4_dotnet.iso_21090.CD(
						creationContext.AnnotationTypeCode.CodeValue,
						creationContext.AnnotationTypeCode.CodeMeaning,
						creationContext.AnnotationTypeCode.CodingSchemeDesignator,
						creationContext.AnnotationTypeCode.CodingSchemeVersion)
				};
			annotationEntity.Name = creationContext.AnnotationName;
			annotationEntity.DateTime = DateTime.Now;
			if (!string.IsNullOrEmpty(creationContext.AnnotationComment))
				annotationEntity.Comment = creationContext.AnnotationComment;
			if (!string.IsNullOrEmpty(creationContext.TemplateTree.SelectedTemplateUid))
				annotationEntity.TemplateUid = new aim4_dotnet.iso_21090.II(creationContext.TemplateTree.SelectedTemplateUid);
			if (!string.IsNullOrEmpty(creationContext.TemplateTree.PrecedentReferencedAnnotationUid))
				annotationEntity.PrecedentReferencedAnnotationUid = new aim4_dotnet.iso_21090.II(creationContext.TemplateTree.PrecedentReferencedAnnotationUid);


			var selectedAnatomicEntities = new List<aim4_dotnet.ImagingPhysicalEntity>();
			var selectedImagingObservations = new List<aim4_dotnet.ImagingObservationEntity>();
			var selectedInferences = new List<aim4_dotnet.InferenceEntity>();

			foreach (var node in creationContext.TemplateTree.TemplateNodes)
			{
				if (node is TemplateTree.AimTemplateTreeAnatomicEntityNode)
					selectedAnatomicEntities.AddRange(AimTemplateConverter.ToSelectedAnatomicEntitiesList((TemplateTree.AimTemplateTreeAnatomicEntityNode)node));
				else if (node is TemplateTree.AimTemplateTreeImagingObservationNode)
					selectedImagingObservations.AddRange(AimTemplateConverter.ToSelectedImagingObservationList((TemplateTree.AimTemplateTreeImagingObservationNode)node));
				else if (node is TemplateTree.AimTemplateTreeInferenceNode)
					selectedInferences.AddRange(AimTemplateConverter.ToSelectedInferencesList((TemplateTree.AimTemplateTreeInferenceNode)node));
			}

			// add ImagingPhysicalEntity values
			if (!selectedAnatomicEntities.IsNullOrEmpty())
				annotationEntity.ImagingPhysicalEntityCollection = selectedAnatomicEntities;

			// add ImagingObservation and ImagingObservationCharacteristic values
			if (!selectedImagingObservations.IsNullOrEmpty())
				annotationEntity.ImagingObservationEntityCollection = selectedImagingObservations;

			// add Inferences
			if (!selectedInferences.IsNullOrEmpty())
				annotationEntity.InferenceEntityCollection = selectedInferences;

			//return imgAnnotation;
		}

		private static aim4_dotnet.Person CreatePatient(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");

			aim4_dotnet.Person patient = new aim4_dotnet.Person();
			patient.Id = image.Frame.ParentImageSop.PatientId;
			DateTime birthDate;
			DateParser.Parse(image.Frame.ParentImageSop.PatientsBirthDate, out birthDate);
			patient.BirthDate = birthDate;
			patient.Name = image.Frame.ParentImageSop.PatientsName;
			patient.Sex = image.Frame.ParentImageSop.PatientsSex;
			patient.EthnicGroup = image.ImageSop[DicomTags.EthnicGroup].ToString();

			return patient;
		}

		private static aim4_dotnet.Equipment CreateEquipment()
		{
			aim4_dotnet.Equipment equipment = new aim4_dotnet.Equipment();
			equipment.ManufacturerName = SR.EquipmentManufacturer;
			equipment.ManufacturerModelName = SR.EquipmentManufacturerModelName;
			equipment.SoftwareVersion = string.Format("{0}.{1}.{2}.{3}", Application.Version.Major, Application.Version.Minor, Application.Version.Build,
													  Application.Version.Revision);

			return equipment;
		}

		private static aim4_dotnet.TwoDimensionGeometricShapeEntity Create2DGeoShape(RoiGraphic roiGraphic, string imageUid, int frameNumber)
		{
			Platform.CheckForEmptyString(imageUid, "imageUid");

			aim4_dotnet.TwoDimensionGeometricShapeEntity geoShape = null;
			Roi roi = roiGraphic.Roi;

			//Platform.CheckTrue(graphics.CoordinateSystem == CoordinateSystem.Source, "Source Coordinate System");

			if (roi is EllipticalRoi)
			{
				EllipticalRoi ellipticalRoi = roi as EllipticalRoi;
				Platform.CheckForNullReference(ellipticalRoi, "ellipticalRoi");

				aim4_dotnet.TwoDimensionEllipse ellipseShape = Create2DGeoShape<aim4_dotnet.TwoDimensionEllipse>(imageUid, frameNumber);

				// Bounding box coordinates to DICOM ellipse conversion.
				// Since ellipse's bounding box is not rotated, we just need to find major axis
				// and store the center points of bounding box' side as ellipse vertices.

				//    if (ellipseGraphics.Width >= ellipseGraphics.Height)
				{
					// Horizontal major axis points
					ellipseShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left, ellipticalRoi.BoundingBox.Top + ellipticalRoi.BoundingBox.Height / 2, 0));

					ellipseShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Right, ellipticalRoi.BoundingBox.Top + ellipticalRoi.BoundingBox.Height / 2, 1));

					// Vertical minor axis points
					ellipseShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left + ellipticalRoi.BoundingBox.Width / 2, ellipticalRoi.BoundingBox.Top, 2));

					ellipseShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(ellipticalRoi.BoundingBox.Left + ellipticalRoi.BoundingBox.Width / 2, ellipticalRoi.BoundingBox.Bottom, 3));
				}
				geoShape = ellipseShape;
			}
			else if (roi is PolygonalRoi)
			{
				PolygonalRoi polygonalRoi = roi as PolygonalRoi;
				Platform.CheckForNullReference(polygonalRoi, "polygonalRoi");
				//if (!polygonalRoi.IsClosed)
				//{
				//    Platform.Log(LogLevel.Error, "Object state error: Given polygon is not closed");
				//    return null;
				//}

				aim4_dotnet.TwoDimensionPolyline polylineShape = Create2DGeoShape<aim4_dotnet.TwoDimensionPolyline>(imageUid, frameNumber);
				for (int i = 0; i < polygonalRoi.Polygon.Vertices.Count; i++)
				{
					polylineShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(polygonalRoi.Polygon.Vertices[i].X, polygonalRoi.Polygon.Vertices[i].Y, i));
				}
				if (polygonalRoi.Polygon.Vertices.Count > 0 && polygonalRoi.Polygon.Vertices[polygonalRoi.Polygon.Vertices.Count - 1] != polygonalRoi.Polygon.Vertices[0])
				{
					// Add first point to end of collection to close the shape. - SJT
					polylineShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(polygonalRoi.Polygon.Vertices[0].X, polygonalRoi.Polygon.Vertices[0].Y, polylineShape.TwoDimensionSpatialCoordinateCollection.Count));
				}
				geoShape = polylineShape;
			}
			else if (roi is ProtractorRoi)
			{
				ProtractorRoi protractorRoi = roi as ProtractorRoi;
				Platform.CheckForNullReference(protractorRoi, "protractorRoi");

				aim4_dotnet.TwoDimensionMultiPoint multipointShape = Create2DGeoShape<aim4_dotnet.TwoDimensionMultiPoint>(imageUid, frameNumber);
				for (int i = 0; i < protractorRoi.Points.Count; i++)
				{
					multipointShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(protractorRoi.Points[i].X, protractorRoi.Points[i].Y, i));
				}
				geoShape = multipointShape;
			}
			else if (roi is LinearRoi)
			{
				LinearRoi linearRoi = roi as LinearRoi;
				Platform.CheckForNullReference(linearRoi, "linearRoi");

				aim4_dotnet.TwoDimensionMultiPoint multipointShape = Create2DGeoShape<aim4_dotnet.TwoDimensionMultiPoint>(imageUid, frameNumber);
				for (int i = 0; i < linearRoi.Points.Count; i++)
				{
					multipointShape.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(linearRoi.Points[i].X, linearRoi.Points[i].Y, i));
				}
				geoShape = multipointShape;
			}
			else if (roi is RectangularRoi)
			{
				RectangularRoi rectangularRoi = roi as RectangularRoi;
				Platform.CheckForNullReference(rectangularRoi, "rectangularRoi");

				aim4_dotnet.TwoDimensionPolyline polylineShape = Create2DGeoShape<aim4_dotnet.TwoDimensionPolyline>(imageUid, frameNumber);

				// Top Left
				polylineShape.TwoDimensionSpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Left, rectangularRoi.BoundingBox.Top, 0));

				// Top Right
				polylineShape.TwoDimensionSpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Right, rectangularRoi.BoundingBox.Top, 1));

				// Bottom Right
				polylineShape.TwoDimensionSpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Right, rectangularRoi.BoundingBox.Bottom, 2));

				// Bottom Left
				polylineShape.TwoDimensionSpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(rectangularRoi.BoundingBox.Left, rectangularRoi.BoundingBox.Bottom, 3));

				geoShape = polylineShape;
			}
			else
				Console.WriteLine("AimNativeHelper.Create2DGeoShape. Unhandled ROI type: " + roi.GetType().FullName);

			return geoShape;
		}

		private static T Create2DGeoShape<T>(string imageUid, int frameNumber) where T : aim4_dotnet.TwoDimensionGeometricShapeEntity, new()
		{
			Platform.CheckForEmptyString(imageUid, "Image UID");
			Platform.CheckNonNegative(frameNumber, "frameNumber");

			return new T
				{
					UniqueIdentifier = NewUid,
					TwoDimensionSpatialCoordinateCollection = new List<aim4_dotnet.TwoDimensionSpatialCoordinate>(),
					IncludeFlag = true,
					ImageReferenceUid = new aim4_dotnet.iso_21090.II(imageUid),
					ReferencedFrameNumber = frameNumber
				};
		}

		private static aim4_dotnet.TwoDimensionSpatialCoordinate Create2DSpatialCoordinate(float x, float y, int coordinateIndex)
		{
			aim4_dotnet.TwoDimensionSpatialCoordinate spatialCoord = new aim4_dotnet.TwoDimensionSpatialCoordinate();
			spatialCoord.X = x;
			spatialCoord.Y = y;
			spatialCoord.CoordinateIndex = coordinateIndex;

			return spatialCoord;
		}

		// Returns 'false' if the image already exists in the Image collection or 'true' when a new Image is added.
		private static bool AddDicomImageReference(aim4_dotnet.ImageAnnotation imageAnnotation, IImageSopProvider image)
		{
			Platform.CheckForNullReference(imageAnnotation, "ImageAnnotation");

			if (imageAnnotation.ImageReferenceEntityCollection == null)
				imageAnnotation.ImageReferenceEntityCollection = new List<aim4_dotnet.ImageReferenceEntity>();
			List<aim4_dotnet.ImageReferenceEntity> imageReferences = imageAnnotation.ImageReferenceEntityCollection;

			aim4_dotnet.ImageStudy aimImageStudy = null;
			foreach (aim4_dotnet.ImageReferenceEntity imgRef in imageReferences)
			{
				aim4_dotnet.DicomImageReferenceEntity dicomImgRef = imgRef as aim4_dotnet.DicomImageReferenceEntity;
				if (dicomImgRef != null)
				{
					if (dicomImgRef.ImageStudy.InstanceUid.Uid == image.ImageSop.StudyInstanceUid &&
						dicomImgRef.ImageStudy.ImageSeries.InstanceUid.Uid == image.ImageSop.SeriesInstanceUid)
						aimImageStudy = dicomImgRef.ImageStudy;
				}
			}

			// Create new Study/Series
			if (aimImageStudy == null)
			{
				aimImageStudy = CreateStudy(image);
				aimImageStudy.ImageSeries = CreateSeries(image);
				aimImageStudy.ImageSeries.ImageCollection = new List<aim4_dotnet.Image>();
				aim4_dotnet.DicomImageReferenceEntity dicomImgRef = new aim4_dotnet.DicomImageReferenceEntity();
				dicomImgRef.UniqueIdentifier = NewUid;
				dicomImgRef.ImageStudy = aimImageStudy;
				imageReferences.Add(dicomImgRef);
			}

			foreach (aim4_dotnet.Image existingImage in aimImageStudy.ImageSeries.ImageCollection)
			{
				if (existingImage.SopInstanceUid.Uid == image.ImageSop.SopInstanceUid)
					return false; // already have this image
			}

			aim4_dotnet.Image aimImage = CreateImage(image);
			aimImageStudy.ImageSeries.ImageCollection.Add(aimImage);

			return true;
		}

		private static aim4_dotnet.ImageStudy CreateStudy(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");

			aim4_dotnet.ImageStudy aimStudy = new aim4_dotnet.ImageStudy();
			aimStudy.InstanceUid = new aim4_dotnet.iso_21090.II(image.ImageSop.StudyInstanceUid);
			aimStudy.AccessionNumber = image.ImageSop.AccessionNumber;
			aimStudy.StudyDescription = image.ImageSop.StudyDescription;
			aimStudy.ReferringPhysicianName = image.ImageSop.ReferringPhysiciansName;

			DateTime current = DateTime.Now;
			DateTime studyDateTime;
			var dateTimeValid = DateTimeParser.ParseDateAndTime(null, image.ImageSop.StudyDate, image.ImageSop.StudyTime, out studyDateTime);

			DateTime studyDate;
			if (DateParser.Parse(image.ImageSop.StudyDate, out studyDate) && studyDate != DateTime.MinValue)
				aimStudy.StartDate = studyDate;
			else
			{
				if (dateTimeValid)
					aimStudy.StartDate = studyDateTime;
				else
				{
					Platform.Log(LogLevel.Info, "AIM Converter 4.0: Failed to parse image Study Date [{0}]. Will use current date", image.ImageSop.StudyDate);
					aimStudy.StartDate = current.Subtract(current.TimeOfDay);
				}
			}

			if (dateTimeValid)
				aimStudy.StartTime = studyDateTime;
			else
			{
				Platform.Log(LogLevel.Info, "AIM Converter 4.0: Failed to parse Study Time [{0}]. Will use current date & time", image.ImageSop.StudyTime);
				aimStudy.StartTime = current;
			}

			return aimStudy;
		}

		private static aim4_dotnet.ImageSeries CreateSeries(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");

			aim4_dotnet.ImageSeries aimSeries = new aim4_dotnet.ImageSeries();
			aimSeries.InstanceUid = new aim4_dotnet.iso_21090.II(image.ImageSop.SeriesInstanceUid);
			// NOTE: we don't provide real acquisition modality Code Meaning per DICOM PS 3.16
			aimSeries.Modality = new aim4_dotnet.iso_21090.CD(image.ImageSop.Modality, image.ImageSop.Modality, "DCM");

			return aimSeries;
		}

		private static aim4_dotnet.Image CreateImage(IImageSopProvider image)
		{
			Platform.CheckForNullReference(image, "Image");

			aim4_dotnet.Image aimImage = new aim4_dotnet.Image();

			aimImage.SopClassUid = new aim4_dotnet.iso_21090.II(image.ImageSop.SopClassUid);
			aimImage.SopInstanceUid = new aim4_dotnet.iso_21090.II(image.ImageSop.SopInstanceUid);

			// TODO - get Image View and Image View Modifiers

			return aimImage;
		}

		private static List<aim4_dotnet.CalculationEntity> CreateCalculations(RoiGraphic roiGraphic, int referencedGeoShapeId)
		{
			List<aim4_dotnet.CalculationEntity> calculations = new List<aim4_dotnet.CalculationEntity>();

			Roi roi = roiGraphic.Roi;
			foreach (IRoiAnalyzer analyzer in roiGraphic.Callout.RoiAnalyzers)
			{
				if (analyzer.SupportsRoi(roi))
				{
					// TODO - check all values and nested classes for existence and their values
					aim4_dotnet.CalculationEntity calculation = new aim4_dotnet.CalculationEntity();
					calculation.UniqueIdentifier = NewUid;
					calculation.CalculationResultCollection = new List<aim4_dotnet.CalculationResult>();
					if (analyzer is RoiLengthAnalyzer)
					{
						calculation.TypeCode = new List<aim4_dotnet.iso_21090.CD>
							{
								new aim4_dotnet.iso_21090.CD
									{
										CodeValue = CodeList.CalculationCodeForLength.CodeValue,
										CodeMeaning = CodeList.CalculationCodeForLength.CodeMeaning,
										CodingSchemeDesignator = CodeList.CalculationCodeForLength.CodingSchemeDesignator,
										CodingSchemeVersion = CodeList.CalculationCodeForLength.CodingSchemeVersion
									}
							};
						// TODO - calculation's questionTypeCode?
						calculation.Description = "Length";
						IRoiLengthProvider roiLengthProvider = (IRoiLengthProvider)roi;

						Units oldUnits = roiLengthProvider.Units;
						roiLengthProvider.Units = roiLengthProvider.IsCalibrated ? Units.Millimeters : Units.Pixels;
						calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(roiLengthProvider.Length, UnitsToName(roiLengthProvider.Units), "Value"));
						roiLengthProvider.Units = oldUnits;

						calculations.Add(calculation);
					}
					else if (analyzer is RoiAreaAnalyzer)
					{
						calculation.TypeCode = new List<aim4_dotnet.iso_21090.CD>
							{
								new aim4_dotnet.iso_21090.CD
									{
										CodeValue = CodeList.CalculationCodeForArea.CodeValue,
										CodeMeaning = CodeList.CalculationCodeForArea.CodeMeaning,
										CodingSchemeDesignator = CodeList.CalculationCodeForArea.CodingSchemeDesignator,
										CodingSchemeVersion = CodeList.CalculationCodeForArea.CodingSchemeVersion
									}
							};
						// TODO - calculation's questionTypeCode?
						calculation.Description = "Area";
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

							aim4_dotnet.CalculationEntity calcStdDev = new aim4_dotnet.CalculationEntity(calculation);

							calculation.TypeCode = new List<aim4_dotnet.iso_21090.CD>
								{
									new aim4_dotnet.iso_21090.CD
										{
											CodeValue = CodeList.CalculationCodeForMean.CodeValue,
											CodeMeaning = CodeList.CalculationCodeForMean.CodeMeaning,
											CodingSchemeDesignator = CodeList.CalculationCodeForMean.CodingSchemeDesignator,
											CodingSchemeVersion = CodeList.CalculationCodeForMean.CodingSchemeVersion
										}
								};
							// TODO - calculation's questionTypeCode?
							calculation.Description = "Mean";
							calculation.CalculationResultCollection.Add(CreateScalarCalculationResult(mean, roi.Modality == "CT" ? "HU" : "1", "Value"));

							calcStdDev.TypeCode = new List<aim4_dotnet.iso_21090.CD>
								{
									new aim4_dotnet.iso_21090.CD
										{
											CodeValue = CodeList.CalculationCodeForStandardDeviation.CodeValue,
											CodeMeaning = CodeList.CalculationCodeForStandardDeviation.CodeMeaning,
											CodingSchemeDesignator = CodeList.CalculationCodeForStandardDeviation.CodingSchemeDesignator,
											CodingSchemeVersion = CodeList.CalculationCodeForStandardDeviation.CodingSchemeVersion
										}
								};
							// TODO - calculation's questionTypeCode?
							calcStdDev.Description = "Standard Deviation";
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

							calculation.TypeCode = new List<aim4_dotnet.iso_21090.CD>
								{
									new aim4_dotnet.iso_21090.CD
										{
											CodeValue = CodeList.CalculationCodeForAngle.CodeValue,
											CodeMeaning = CodeList.CalculationCodeForAngle.CodeMeaning,
											CodingSchemeDesignator = CodeList.CalculationCodeForAngle.CodingSchemeDesignator,
											CodingSchemeVersion = CodeList.CalculationCodeForAngle.CodingSchemeVersion
										}
								};
							// TODO - calculation's questionTypeCode?
							calculation.Description = "Angle";
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

		private static aim4_dotnet.CalculationResult CreateScalarCalculationResult(double value, string unit, string label)
		{
			aim4_dotnet.Dimension dimension = new aim4_dotnet.Dimension();
			dimension.Index = 0;
			dimension.Size = 1;
			dimension.Label = label;

			aim4_dotnet.Coordinate coordinate = new aim4_dotnet.Coordinate();
			coordinate.DimensionIndex = 0;
			coordinate.Position = 0;

			aim4_dotnet.CalculationData calculationData = new aim4_dotnet.CalculationData();
			calculationData.Value = value.ToString(CultureInfo.InvariantCulture);
			calculationData.CoordinateCollection = new List<aim4_dotnet.Coordinate>();
			calculationData.CoordinateCollection.Add(coordinate);

			aim4_dotnet.ExtendedCalculationResult result = new aim4_dotnet.ExtendedCalculationResult();
			result.Type = aim4_dotnet.CalculationResultIdentifier.Scalar;
			result.DataType = new aim4_dotnet.iso_21090.CD("C48870", "Double", "NCI");
			result.UnitOfMeasure = unit;
			result.DimensionCollection = new List<aim4_dotnet.Dimension>();
			result.DimensionCollection.Add(dimension);
			result.CalculationDataCollection = new List<aim4_dotnet.CalculationData>();
			result.CalculationDataCollection.Add(calculationData);

			return result;
		}

		private static aim4_dotnet.TextAnnotationEntity CreateTextAnnotation(IGraphic graphic, string imageUid, int frameNumber)
		{
			// TODO - record color, font name, font size, etc.

			if (graphic is UserCalloutGraphic)
			{
				UserCalloutGraphic userCalloutGraphic = (UserCalloutGraphic)graphic;
				aim4_dotnet.TwoDimensionMultiPoint multiPoint = Create2DGeoShape<aim4_dotnet.TwoDimensionMultiPoint>(imageUid, frameNumber);
				foreach (PointF pointF in new[] { userCalloutGraphic.AnchorPoint, userCalloutGraphic.AttachmentPoint })
				{
					multiPoint.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(pointF.X, pointF.Y, multiPoint.TwoDimensionSpatialCoordinateCollection.Count));
				}

				return new aim4_dotnet.TextAnnotationEntity { UniqueIdentifier = NewUid, Text = StringUtils.TrimStringStartOrSelf(userCalloutGraphic.Text, userCalloutGraphic.ParentGraphic.Name).TrimStart(), GeometricShapeEntity = multiPoint };
			}

			if (graphic is InvariantTextPrimitive)
			{
				InvariantTextPrimitive invariantTextPrimitive = (InvariantTextPrimitive)graphic;
				aim4_dotnet.TwoDimensionMultiPoint multiPoint = Create2DGeoShape<aim4_dotnet.TwoDimensionMultiPoint>(imageUid, frameNumber);
				multiPoint.TwoDimensionSpatialCoordinateCollection.Add(
					Create2DSpatialCoordinate(invariantTextPrimitive.Location.X, invariantTextPrimitive.Location.Y, multiPoint.TwoDimensionSpatialCoordinateCollection.Count));

				return new aim4_dotnet.TextAnnotationEntity { UniqueIdentifier = NewUid, Text = StringUtils.TrimStringStartOrSelf(invariantTextPrimitive.Text, graphic.ParentGraphic.Name).TrimStart(), GeometricShapeEntity = multiPoint };
			}

			if (graphic is CrosshairCalloutGraphic)
			{
				var crosshairGraphic = (CrosshairCalloutGraphic)graphic;
				var multiPoint = Create2DGeoShape<aim4_dotnet.TwoDimensionMultiPoint>(imageUid, frameNumber);
				foreach (PointF pointF in new[] { crosshairGraphic.AnchorPoint, crosshairGraphic.AttachmentPoint })
				{
					multiPoint.TwoDimensionSpatialCoordinateCollection.Add(
						Create2DSpatialCoordinate(pointF.X, pointF.Y, multiPoint.TwoDimensionSpatialCoordinateCollection.Count));
				}

				return new aim4_dotnet.TextAnnotationEntity { UniqueIdentifier = NewUid, Text = StringUtils.TrimStringStartOrSelf(crosshairGraphic.Text, graphic.ParentGraphic.Name).TrimStart(), GeometricShapeEntity = multiPoint };
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

		public static bool ReadGraphicsFromAnnotation(Aim4AnnotationInstance aim4AnnotationInstance, IPresentationImage presentationImage)
		{
			Platform.CheckForNullReference(aim4AnnotationInstance, "aimAnnotationInstance");

			bool hasNewRoiGraphic = false;

			IOverlayGraphicsProvider graphicsProvider = presentationImage as IOverlayGraphicsProvider;
			IImageSopProvider currentImageSOP = presentationImage as IImageSopProvider;
			if (graphicsProvider == null || currentImageSOP == null)
				return false;

			if (aim4AnnotationInstance.AimAnnotationEntity is aim4_dotnet.ImageAnnotation)
			{
				var imgAnnotation = (aim4_dotnet.ImageAnnotation) aim4AnnotationInstance.AimAnnotationEntity;
				if (imgAnnotation.MarkupEntityCollection != null)
				{
					foreach (aim4_dotnet.MarkupEntity markupEntity in imgAnnotation.MarkupEntityCollection)
					{
						if (markupEntity is aim4_dotnet.GeometricShapeEntity)
						{
							var geoShape = (aim4_dotnet.GeometricShapeEntity) markupEntity;
							// Check if the image is the one on which the annotation was originally drawn
							if (GetImageSopInstanceUid(geoShape) != currentImageSOP.ImageSop.SopInstanceUid ||
								GetReferencedFrameNumber(geoShape) != currentImageSOP.Frame.FrameNumber)
								continue;

							// Prevent from adding the same annotation again
							bool isAlreadyDisplayed = false;
							foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
							{
								AimGraphic aimGraphic = graphic as AimGraphic;
								isAlreadyDisplayed = aimGraphic != null && aimGraphic.AnnotationUid == imgAnnotation.UniqueIdentifier.Uid &&
													 aimGraphic.ShapeIdentifier == geoShape.ShapeIdentifier;
								if (isAlreadyDisplayed)
									break;
							}
							if (isAlreadyDisplayed)
								continue;

							IGraphic geoGraphic = GeoShapeToGraphic(geoShape, (imgAnnotation.Name ?? string.Empty).Trim());
							if (geoGraphic != null)
							{
								AimGraphic aimGraphic = new AimGraphic(geoGraphic, aim4AnnotationInstance, geoShape.ShapeIdentifier);
								// Choose color for aimGraphic based on the login name of the annotation's creator
								aimGraphic.Color = AimSettings.Default.GetAimGraphicColorForUser(aimGraphic.UserLoginName);
								graphicsProvider.OverlayGraphics.Add(aimGraphic);
							}

							hasNewRoiGraphic |= geoGraphic != null;
						}
						else if (markupEntity is aim4_dotnet.TextAnnotationEntity)
						{
							var textAnnotation = (aim4_dotnet.TextAnnotationEntity) markupEntity;
							if (textAnnotation.GeometricShapeEntity == null)
								continue; // ignore. not image-specific

							// TODO - refactor some of the code below and similar code above into the AIM Mgr when Mgr is implemented

							// Check if the image is the one on which the annotation was originally drawn
							if (GetImageSopInstanceUid(textAnnotation.GeometricShapeEntity) != currentImageSOP.ImageSop.SopInstanceUid ||
								GetReferencedFrameNumber(textAnnotation.GeometricShapeEntity) != currentImageSOP.Frame.FrameNumber)
								continue;

							// Prevent from adding the same annotation again
							bool isAlreadyDisplayed = false;
							foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
							{
								AimGraphic aimGraphic = graphic as AimGraphic;
								isAlreadyDisplayed = aimGraphic != null && aimGraphic.AnnotationUid == imgAnnotation.UniqueIdentifier.Uid &&
													 aimGraphic.ShapeIdentifier == textAnnotation.GeometricShapeEntity.ShapeIdentifier;
								if (isAlreadyDisplayed)
									break;
							}
							if (isAlreadyDisplayed)
								continue;

							IGraphic textGraphic = TextAnnotationToGraphic(textAnnotation, (imgAnnotation.Name ?? string.Empty).Trim());
							if (textGraphic != null)
							{
								AimGraphic aimGraphic = new AimGraphic(textGraphic, aim4AnnotationInstance, textAnnotation.GeometricShapeEntity.ShapeIdentifier);
								aimGraphic.Color = Color.SlateBlue;
								graphicsProvider.OverlayGraphics.Add(aimGraphic);
							}

							hasNewRoiGraphic |= textGraphic != null;
						}
						else
						{
							Debug.Assert(false, "Unexpected MarkupEntity type: " + markupEntity.GetType().Name);
						}
					}
				}
			}
			else
			{
				throw new NotImplementedException("AIM4: Reading non-image annotation is not implemented");
			}

			return hasNewRoiGraphic;
		}

		// Returns SOP Instance UID of the image the given shape belongs to
		// 2D images are supported only
		private static string GetImageSopInstanceUid(aim4_dotnet.GeometricShapeEntity geoShape)
		{
			if (geoShape is aim4_dotnet.TwoDimensionGeometricShapeEntity)
			{
				var geoShape2D = (aim4_dotnet.TwoDimensionGeometricShapeEntity)geoShape;
				if (geoShape2D.ImageReferenceUid != null)
					return geoShape2D.ImageReferenceUid.Uid;
			}
			else if (geoShape is aim4_dotnet.ThreeDimensionGeometricShapeEntity)
			{
				var geoShape3D = (aim4_dotnet.ThreeDimensionGeometricShapeEntity)geoShape;
				if (geoShape3D.FrameOfReferenceUid != null)
					return geoShape3D.FrameOfReferenceUid.Uid;
			}

			return string.Empty;
		}

		private static int GetReferencedFrameNumber(aim4_dotnet.GeometricShapeEntity geoShape)
		{
			if (geoShape is aim4_dotnet.TwoDimensionGeometricShapeEntity)
			{
				var geoShape2D = (aim4_dotnet.TwoDimensionGeometricShapeEntity)geoShape;
				if (geoShape2D.ReferencedFrameNumber.HasValue)
				{
					Debug.Assert(geoShape2D.ReferencedFrameNumber.Value > 0, "Referenced Frame Number must be positive");
					return geoShape2D.ReferencedFrameNumber.Value;
				}
			}
			else
			{
				Debug.Assert(false, "Only 2D SOP Instances have Referenced Frame Number");
			}

			return 1; // 1 - default 1st frame in the image in the CC's implementation
		}

		private static IGraphic GeoShapeToGraphic(aim4_dotnet.GeometricShapeEntity geoShape, string shapeLabel)
		{
			var shape = geoShape as aim4_dotnet.TwoDimensionGeometricShapeEntity;
			if (shape != null)
				return GeoShapeToGraphic(shape, shapeLabel);

			var entity = geoShape as aim4_dotnet.ThreeDimensionGeometricShapeEntity;
			if (entity != null)
				return GeoShapeToGraphic(entity, shapeLabel);

			return null;
		}

		private static IGraphic GeoShapeToGraphic(aim4_dotnet.TwoDimensionGeometricShapeEntity geoShape, string shapeLabel)
		{
			IGraphic graphic = null;

			if (GeneralCollectionUtils.IsNullOrEmpty(geoShape.TwoDimensionSpatialCoordinateCollection))
				return null;

			if (geoShape is aim4_dotnet.TwoDimensionCircle)
			{
				// Ellipse
				aim4_dotnet.TwoDimensionCircle shapeCircle = geoShape as aim4_dotnet.TwoDimensionCircle;
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
			else if (geoShape is aim4_dotnet.TwoDimensionEllipse)
			{
				// Ellipse
				aim4_dotnet.TwoDimensionEllipse shapeEllipse = geoShape as aim4_dotnet.TwoDimensionEllipse;
				PointF firstMajorAxisPt = AsPointF(shapeEllipse.TwoDimensionSpatialCoordinateCollection[0]);
				PointF secondMajorAxisPt = AsPointF(shapeEllipse.TwoDimensionSpatialCoordinateCollection[1]);
				PointF firstMinorAxisPt = AsPointF(shapeEllipse.TwoDimensionSpatialCoordinateCollection[2]);
				PointF secondMinorAxisPt = AsPointF(shapeEllipse.TwoDimensionSpatialCoordinateCollection[3]);

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
			else if (geoShape is aim4_dotnet.TwoDimensionPoint)
			{
				aim4_dotnet.TwoDimensionPoint shapePoint = geoShape as aim4_dotnet.TwoDimensionPoint;

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
					callout.TextLocation = callout.AnchorPoint - new SizeF(30, 30);

					StandardStatefulGraphic statefulGraphic = new StandardStatefulGraphic(callout);
					statefulGraphic.State = statefulGraphic.CreateInactiveState();

					graphic = statefulGraphic;
				}
			}
			else if (geoShape is aim4_dotnet.TwoDimensionMultiPoint)
			{
				// How this case works:
				// If we have 2 points, it's a line
				// If we have 3 points, it's a protractor
				// All others - unknown unclosed object (not supported)

				aim4_dotnet.TwoDimensionMultiPoint shapeMultiPoint = geoShape as aim4_dotnet.TwoDimensionMultiPoint;
				switch (shapeMultiPoint.TwoDimensionSpatialCoordinateCollection.Count)
				{
					case 2:
						{
							// Line
							VerticesControlGraphic interactiveGraphic = new VerticesControlGraphic(new MoveControlGraphic(new PolylineGraphic()));
							PointF firstPt = AsPointF(shapeMultiPoint.TwoDimensionSpatialCoordinateCollection[0]);
							PointF secondPt = AsPointF(shapeMultiPoint.TwoDimensionSpatialCoordinateCollection[1]);
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
							PointF firstPt = AsPointF(shapeMultiPoint.TwoDimensionSpatialCoordinateCollection[0]);
							PointF secondPt = AsPointF(shapeMultiPoint.TwoDimensionSpatialCoordinateCollection[1]);
							PointF thirdPt = AsPointF(shapeMultiPoint.TwoDimensionSpatialCoordinateCollection[2]);
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
			else if (geoShape is aim4_dotnet.TwoDimensionPolyline)
			{
				aim4_dotnet.TwoDimensionPolyline shapePolyline = geoShape as aim4_dotnet.TwoDimensionPolyline;

				bool isRectangle = false; // true - if we have CC's rectangle coordinates
				// Check if this is a non-rotated rectangle
				if (shapePolyline.TwoDimensionSpatialCoordinateCollection.Count == 4)
				{
					PointF twoDPoint1 = AsPointF(shapePolyline.TwoDimensionSpatialCoordinateCollection[0]);
					PointF twoDPoint2 = AsPointF(shapePolyline.TwoDimensionSpatialCoordinateCollection[1]);
					PointF twoDPoint3 = AsPointF(shapePolyline.TwoDimensionSpatialCoordinateCollection[2]);
					PointF twoDPoint4 = AsPointF(shapePolyline.TwoDimensionSpatialCoordinateCollection[3]);
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
						for (int i = 0; i < shapePolyline.TwoDimensionSpatialCoordinateCollection.Count; i++)
						{
							PointF twoDPoint = AsPointF(shapePolyline.TwoDimensionSpatialCoordinateCollection[i]);
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

		private static IGraphic GeoShapeToGraphic(aim4_dotnet.ThreeDimensionGeometricShapeEntity geoShape, string shapeLabel)
		{
			Debug.Assert(false, "Converting ThreeDimensionalGeometricShapeEntity to IGraphic is not implemented");
			return null;
		}

		private static IGraphic TextAnnotationToGraphic(aim4_dotnet.TextAnnotationEntity textAnnotation, string shapeLabel)
		{
			Platform.CheckForNullReference(textAnnotation, "textAnnotation");
			Platform.CheckForNullReference(textAnnotation.GeometricShapeEntity, "textAnnotation.GeometricShapeEntity");

			if (textAnnotation.GeometricShapeEntity == null)
				return null;

			var geoShape2D = textAnnotation.GeometricShapeEntity as aim4_dotnet.TwoDimensionGeometricShapeEntity;
			if (geoShape2D == null || geoShape2D.TwoDimensionSpatialCoordinateCollection == null)
			{
				Debug.Assert(false, "Text Annotation's Geometric Shape is not 2D or its coordinates are missing");
				return null;
			}
			var graphicText = AimHelpers.FormatPointCalloutText(shapeLabel, textAnnotation.Text.Trim());
			switch (geoShape2D.TwoDimensionSpatialCoordinateCollection.Count)
			{
				case 1:
					{
						InvariantTextPrimitive textPrimitive = new InvariantTextPrimitive(graphicText);
						textPrimitive.Location = AsPointF(geoShape2D.TwoDimensionSpatialCoordinateCollection[0]);

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
							crosshair.AnchorPoint = AsPointF(geoShape2D.TwoDimensionSpatialCoordinateCollection[0]);
							crosshair.TextLocation = AsPointF(geoShape2D.TwoDimensionSpatialCoordinateCollection[1]);
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
							callout.AnchorPoint = AsPointF(geoShape2D.TwoDimensionSpatialCoordinateCollection[0]);
							callout.TextLocation = AsPointF(geoShape2D.TwoDimensionSpatialCoordinateCollection[1]);

							StandardStatefulGraphic statefulGraphic = new StandardStatefulGraphic(callout);
							statefulGraphic.State = statefulGraphic.CreateInactiveState();
							statefulGraphic.Name = shapeLabel;

							return statefulGraphic;
						}
					}
					break;
				default:
					Debug.Assert(false, "Unexpected number of points is read from Text Annotation graphics");
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

		internal static PointF AsPointF(aim4_dotnet.TwoDimensionSpatialCoordinate spatialCoord)
		{
			Platform.CheckForNullReference(spatialCoord, "spatialCoord");

			return new PointF((float)spatialCoord.X, (float)spatialCoord.Y);
		}

		internal static aim4_dotnet.iso_21090.II NewUid
		{
			get { return new aim4_dotnet.iso_21090.II(DicomUid.GenerateUid().UID); }
		}
	}
}
