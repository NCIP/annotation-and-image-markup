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
using System.Drawing;
using System.IO;
using System.Linq;
using ClearCanvas.Common;
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Iod;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.Imaging;
using ClearCanvas.ImageViewer.Mathematics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.StudyManagement;
using Segmentation.Tree;

namespace Segmentation.Graphics
{
    /// <summary>
    /// A series of helper methods for converting to and from ClearCanvas
    /// ROI graphics, segmentation pixel data, and segmentation tree graphics
    /// </summary>
    internal static class SegmentationGraphicsHelpers
    {
        internal static bool GraphicIsUsable(IGraphic graphic)
        {
            if (graphic.ParentPresentationImage != null &&
                graphic is RoiGraphic &&
                !string.IsNullOrWhiteSpace(graphic.Name) &&
                graphic.Visible)
            {
                var roiGraphic = graphic as RoiGraphic;
                if (roiGraphic.Roi is PolygonalRoi)
                    return true;
            }
            return false;
        }

        internal static bool RoiGraphicAndSegGraphicsMatch(IGraphic roiGraphic, ISegGraphic segGraphic)
        {
            return roiGraphic.GetHashCode().Equals(segGraphic.GraphicHashCode) &&
                   roiGraphic.Name == segGraphic.Label;
        }

        internal static PolygonalRoiSegGraphic GraphicToISegGraphic(IGraphic graphic)
        {
            if (!GraphicIsUsable(graphic))
                return null;

            PolygonalRoiSegGraphic segGraphic = null;
            var roiGraphic = graphic as RoiGraphic;
            if (roiGraphic != null)
            {
                if (roiGraphic.Roi is PolygonalRoi)
                {
                    segGraphic = new PolygonalRoiSegGraphic
                                     {
                                         PolygonalRoiGraphic = roiGraphic,
                                         Label = roiGraphic.Name
                                     };
                }
            }

            if (segGraphic != null)
            {
                string sopInstanceUid = String.Empty;
                int frameNumber = 1;
                int imageNumber = 1;

                try
                {
                    if (graphic.ParentPresentationImage is IImageSopProvider)
                    {
                        var imageSopProvider = graphic.ParentPresentationImage as IImageSopProvider;
                        imageNumber = imageSopProvider.ImageSop.InstanceNumber;
                        sopInstanceUid = imageSopProvider.Sop.SopInstanceUid;
                        frameNumber = imageSopProvider.Frame.FrameNumber;
                    }
                    else if (!string.IsNullOrEmpty(graphic.ParentPresentationImage.Uid))
                        sopInstanceUid = graphic.ParentPresentationImage.Uid;
                }
                catch (Exception)
                {
                }
                segGraphic.ImageSopInstanceUid = sopInstanceUid;
                segGraphic.ImageFrameNumber = frameNumber;
                segGraphic.ImageNumber = imageNumber;
            }

            return segGraphic;
        }

        public static SegFrameImageGraphic AddSegFrameImageGraphicToPresentationImage(
            IPresentationImage presentationImage,
            Color color,
            IEnumerable<PointF> vertices)
        {
            var image = presentationImage as IImageGraphicProvider;

            if (image == null)
                return null;

            // Get the base image
            ImageGraphic baseImage = image.ImageGraphic;

            var segFrameImageGraphic = new SegFrameImageGraphic(baseImage.Rows, baseImage.Columns, color);
            segFrameImageGraphic.Alpha = Seg.DefaultOpacity;
            RectangleF boundingBox = RectangleUtilities.ComputeBoundingRectangle(vertices.ToArray());

            // Convert vector polygon to raster on a per pixel basis
            baseImage.PixelData.ForEachPixel(
                delegate(int i, int x, int y, int pixelIndex)
                    {
                        var point = new PointF(x, y);
                        if (boundingBox.Contains(point))
                            if (IsInPolygon(vertices.ToArray(), point))
                            {
                                segFrameImageGraphic[x, y] = true;
                            }
                    }
                );

            var overlayGraphicsProvider = presentationImage as IOverlayGraphicsProvider;
            if (overlayGraphicsProvider != null)
            {
                overlayGraphicsProvider.OverlayGraphics.Add(segFrameImageGraphic);
            }

            return segFrameImageGraphic;
        }

        /// <summary>
        /// Creates a <see cref="SegFrameImageGraphic"/> and adds the graphic to the given <see cref="IPresentationImage"/>
        /// </summary>
        /// <param name="presentationImage">The image to add the graphic to</param>
        /// <param name="rows">Number of rows in the new graphic</param>
        /// <param name="columns">Number of columns in the new graphic</param>
        /// <param name="xLocation">X coordinate of the graphic's origin</param>
        /// <param name="yLocation">Y coordinate of the graphic's origin</param>
        /// <param name="color">Color of the new graphic</param>
        /// <param name="frameIndex">Image frame index</param>
        /// <param name="label">Graphic's label</param>
        /// <param name="description">Graphic's description</param>
        /// <param name="segPixelData">8-bit pixel data of the segmentation overlay</param>
        /// <param name="segmentationDocumentReference">Reference to the Segmentation document this graphic is created for</param>
        /// <returns></returns>
        public static SegFrameImageGraphic AddSegFrameImageGraphicToPresentationImage(
            IPresentationImage presentationImage, int rows, int columns, float xLocation, float yLocation,
            Color color, int frameIndex, string label,
            string description, byte[] segPixelData,
            SegmentationDocumentReference segmentationDocumentReference)
        {
            // TODO VK: use IApplicationGraphicsProvider here!!!
            var overlayGraphicsProvider = presentationImage as IOverlayGraphicsProvider;
            if (overlayGraphicsProvider == null)
                return null;

            var segFrameImageGraphic = new SegFrameImageGraphic(rows, columns, xLocation, yLocation, color,
                                                                frameIndex, -1, label,
                                                                description, segPixelData, segmentationDocumentReference);

            segFrameImageGraphic.Alpha = Seg.DefaultOpacity;

            var sopProvider = presentationImage as IImageSopProvider;

            if (sopProvider != null)
            {
                segFrameImageGraphic.ImageSopInstanceUid = sopProvider.Sop.SopInstanceUid;
                segFrameImageGraphic.ImageFrameNumber = sopProvider.Frame.FrameNumber;
                segFrameImageGraphic.ImageNumber = sopProvider.ImageSop.InstanceNumber;
            }

            overlayGraphicsProvider.OverlayGraphics.Add(segFrameImageGraphic);

            return segFrameImageGraphic;
        }

        public static void CreateSeriesGraphicsForSeg(IPresentationImage presentationImage, Seg seg,
                                                      SegmentationDocument segmentationDocument,
                                                      IDicomMessageSopDataSource dicomMessageSopDataSourceSop)
        {
            Platform.CheckForNullReference(presentationImage, "presentationImage");
            Platform.CheckForNullReference(seg, "seg");
            Platform.CheckForNullReference(segmentationDocument, "segmentationDocument");

            SegmentImageData segImageData = seg.SegmentImageData;
            if (segImageData == null)
            {
                Platform.Log(LogLevel.Error,
                             "Cannot create segmentation graphics when no segmentation imaging data is provided");
                return;
            }

            var imageSopProvider = presentationImage as IImageSopProvider;
            if (imageSopProvider == null)
            {
                Platform.Log(LogLevel.Error,
                             "Failed to populate SegFrameGraphics collection. Image is not an ImageSopProvider");
                return;
            }

            DicomPixelData segmentationPixelData = DicomPixelData.CreateFrom(dicomMessageSopDataSourceSop.SourceMessage);
            var rawPixelData =
                (byte[]) dicomMessageSopDataSourceSop.SourceMessage.DataSet.GetAttribute(DicomTags.PixelData).Values;
            var pixelDataGetter = new Func<int, byte[]>(frameIndex =>
                                                            {
                                                                if (segImageData.BitsStored == 1)
                                                                {
                                                                    // Do unpacking
                                                                    int frameLength = segImageData.Rows*
                                                                                      segImageData.Columns;
                                                                    var overlayData =
                                                                        new OverlayData(frameIndex*frameLength,
                                                                                        segImageData.Rows,
                                                                                        segImageData.Columns, false,
                                                                                        rawPixelData);
                                                                    return overlayData.Unpack();
                                                                }
                                                                if (segImageData.BitsStored == 8)
                                                                {
                                                                    return segmentationPixelData.GetFrame(frameIndex);
                                                                }
                                                                throw new InvalidDataException(
                                                                    "Segmentation objects need to have BitsStored as either 1 or 8");
                                                            });

            // NOTE: SegmentFrameData was already sorted
            foreach (SegmentFrameData segmentFrameData in segImageData.SegmentFrameData)
            {
                IPresentationImage segPresentationImage = null;

                // Get the presentation image if we have an image reference
                string referencedSopInstanceUid = segmentFrameData.ReferencedSopInstanceUid;
                int referencedImageFrameNumber = segmentFrameData.ReferencedFrameNumber ?? 1;
                if (!string.IsNullOrEmpty(referencedSopInstanceUid))
                {
                    segPresentationImage =
                        presentationImage.ParentDisplaySet.PresentationImages.OfType<IImageSopProvider>()
                            .FirstOrDefault(curImageSopProvider => curImageSopProvider != null &&
                                                                   curImageSopProvider.ImageSop.SopInstanceUid ==
                                                                   referencedSopInstanceUid &&
                                                                   curImageSopProvider.Frame.FrameNumber ==
                                                                   referencedImageFrameNumber) as IPresentationImage;
                }

                // Location defaults to 0, 0 unless determined otherwise from image position and image orientation
                var segLocation = new PointF();

                // Get the presentation image from the image position and orientation
                if (segmentFrameData.ImagePositionPatient != null &&
                    segmentFrameData.ImagePositionPatient.Count() > 2 &&
                    segmentFrameData.ImageOrientationPatient != null &&
                    segmentFrameData.ImageOrientationPatient.Count() > 5)
                {
                    var imagePositionPatient = new ImagePositionPatient(
                        segmentFrameData.ImagePositionPatient[0],
                        segmentFrameData.ImagePositionPatient[1],
                        segmentFrameData.ImagePositionPatient[2]);
                    var imageOrientationPatient = new ImageOrientationPatient(
                        segmentFrameData.ImageOrientationPatient[0],
                        segmentFrameData.ImageOrientationPatient[1],
                        segmentFrameData.ImageOrientationPatient[2],
                        segmentFrameData.ImageOrientationPatient[3],
                        segmentFrameData.ImageOrientationPatient[4],
                        segmentFrameData.ImageOrientationPatient[5]);
                    IDisplaySet displaySet = presentationImage.ParentDisplaySet;

                    if (segPresentationImage == null)
                    {
                        segPresentationImage = PresentationImageFromPositionOrientation(
                            imagePositionPatient,
                            imageOrientationPatient,
                            displaySet,
                            segImageData.FrameOfReferenceUid);
                    }

                    var imageSop = segPresentationImage as IImageSopProvider;
                    if (imageSop != null)
                    {
                        Vector3D segImageLocation =
                            imageSop.Frame.ImagePlaneHelper.ConvertToImagePlane(new Vector3D(
                                                                                    (float) imagePositionPatient.X,
                                                                                    (float) imagePositionPatient.Y,
                                                                                    (float) imagePositionPatient.Z));
                        PointF? segPixelLocation =
                            imageSop.Frame.ImagePlaneHelper.ConvertToImage(
                                new PointF(segImageLocation.X, segImageLocation.Y));
                        if (segPixelLocation.HasValue)
                            segLocation = segPixelLocation.Value;
                    }
                }

                if (segPresentationImage != null)
                {
                    SegFrameImageGraphic newGraphic = AddSegFrameImageGraphicToPresentationImage(
                        segPresentationImage,
                        segImageData.Rows,
                        segImageData.Columns,
                        segLocation.X,
                        segLocation.Y,
                        seg.Color,
                        referencedImageFrameNumber,
                        seg.Label,
                        seg.Description,
                        pixelDataGetter.Invoke(segmentFrameData.FrameNumber - 1),
                        new SegmentationDocumentReference(segmentationDocument, seg.SegmentationNumber));
                    if (newGraphic != null &&
                        segPresentationImage == segPresentationImage.ParentDisplaySet.ImageBox.TopLeftPresentationImage)
                    {
                        newGraphic.Draw();
                    }
                }
                else
                {
                    Platform.Log(LogLevel.Error, "Failed to find Presentation Image to display a segment on");
                }
            }
        }

        public static bool IsSegmentationDocumentGraphicLoaded(SegmentationDocument segmentationDocument, IDisplaySet displaySet)
        {
            Platform.CheckForNullReference(segmentationDocument, "segmentationDocument");
            Platform.CheckForNullReference(displaySet, "displaySet");

            return
                displaySet.PresentationImages.OfType<IOverlayGraphicsProvider>()
                          .SelectMany(overlayGraphicProvider => overlayGraphicProvider.OverlayGraphics.OfType<SegFrameImageGraphic>())
                          .Any(
                              segFrameImageGraphic =>
                              segFrameImageGraphic.SegmentationDocumentReference.SegmentationDocument.SopInstanceUid == segmentationDocument.SopInstanceUid);
        }

        internal static IEnumerable<ImageCalculationInfo> ImageCalculationInfoStackFromImageStack(
            IEnumerable<SegFrameImageGraphic> images)
        {
            return from image in images
                   let pixelData = image.ParentPresentationImage as IImageGraphicProvider
                   let modalityLut = image.ParentPresentationImage as IModalityLutProvider
                   where pixelData != null && modalityLut != null
                   select new ImageCalculationInfo
                              {
                                  ModalityLut = modalityLut.ModalityLut,
                                  PixelData = pixelData.ImageGraphic.PixelData, 
                                  // We can't use bounding boxes to optimize calculations for segmentations
                                  // read from file since they're not 
                                  RoiBoundingBox = new RectangleF(0, 0, image.Columns, image.Rows),
                                  SegFrameImageGraphic = image
                              };
        }

        internal static double CalculateMeanForStack(List<ImageCalculationInfo> imageCalculationInfoStack)
        {
            double sum = 0;
            int pixelCount = 0;

            for (int imageCount = 0; imageCount < imageCalculationInfoStack.Count; imageCount++)
            {
                PixelData pixelData = imageCalculationInfoStack[imageCount].PixelData;
                SegFrameImageGraphic segFrameImageGraphic = imageCalculationInfoStack[imageCount].SegFrameImageGraphic;
                RectangleF roiBoundingBox = imageCalculationInfoStack[imageCount].RoiBoundingBox;
                IModalityLut modalityLut = imageCalculationInfoStack[imageCount].ModalityLut;

                Rectangle boundingBox =
                    RectangleUtilities.RoundInflate(RectangleUtilities.ConvertToPositiveRectangle(roiBoundingBox));

                int left = boundingBox.Left;
                if (left < 0)
                    left = 0;
                if (left >= segFrameImageGraphic.Columns)
                    left = segFrameImageGraphic.Columns - 1;
                int right = boundingBox.Right;
                if (right < 0)
                    right = 0;
                if (right >= segFrameImageGraphic.Columns)
                    right = segFrameImageGraphic.Columns - 1;
                int top = boundingBox.Top;
                if (top < 0)
                    top = 0;
                if (top >= segFrameImageGraphic.Rows)
                    top = segFrameImageGraphic.Rows - 1;
                int bottom = boundingBox.Bottom;
                if (bottom < 0)
                    bottom = 0;
                if (bottom >= segFrameImageGraphic.Rows)
                    bottom = segFrameImageGraphic.Rows - 1;

                pixelData.ForEachPixel(
                    left,
                    top,
                    right,
                    bottom,
                    delegate(int i, int x, int y, int pixelIndex)
                        {
                            //if (x >= 0 && x < segFrameImageGraphic.Columns && y >= 0 && y < segFrameImageGraphic.Rows)
                            if (segFrameImageGraphic[x, y])
                            {
                                ++pixelCount;
                                // Make sure we run the raw pixel through the modality LUT
                                // when doing the calculation. Note that the modality LUT
                                // can be something other than a rescale intercept, so we can't
                                // just run the mean through the LUT.
                                int storedValue = pixelData.GetPixel(pixelIndex);
                                double realValue = modalityLut != null ? modalityLut[storedValue] : storedValue;
                                sum += realValue;
                            }
                        });
            }

            if (pixelCount == 0)
                return 0;

            return sum/pixelCount;
        }

        internal static double CalculateStandardDeviationForStack(double mean,
                                                                  List<ImageCalculationInfo> imageCalculationInfoStack)
        {
            double sum = 0;
            int pixelCount = 0;

            for (int imageCount = 0; imageCount < imageCalculationInfoStack.Count; imageCount++)
            {
                PixelData pixelData = imageCalculationInfoStack[imageCount].PixelData;
                SegFrameImageGraphic segFrameImageGraphic = imageCalculationInfoStack[imageCount].SegFrameImageGraphic;
                RectangleF roiBoundingBox = imageCalculationInfoStack[imageCount].RoiBoundingBox;
                IModalityLut modalityLut = imageCalculationInfoStack[imageCount].ModalityLut;

                Rectangle boundingBox =
                    RectangleUtilities.RoundInflate(RectangleUtilities.ConvertToPositiveRectangle(roiBoundingBox));

                int left = boundingBox.Left;
                if (left < 0)
                    left = 0;
                if (left >= segFrameImageGraphic.Columns)
                    left = segFrameImageGraphic.Columns - 1;
                int right = boundingBox.Right;
                if (right < 0)
                    right = 0;
                if (right >= segFrameImageGraphic.Columns)
                    right = segFrameImageGraphic.Columns - 1;
                int top = boundingBox.Top;
                if (top < 0)
                    top = 0;
                if (top >= segFrameImageGraphic.Rows)
                    top = segFrameImageGraphic.Rows - 1;
                int bottom = boundingBox.Bottom;
                if (bottom < 0)
                    bottom = 0;
                if (bottom >= segFrameImageGraphic.Rows)
                    bottom = segFrameImageGraphic.Rows - 1;

                pixelData.ForEachPixel(
                    left,
                    top,
                    right,
                    bottom,
                    delegate(int i, int x, int y, int pixelIndex)
                        {
                            if (segFrameImageGraphic[x, y])
                            {
                                ++pixelCount;
                                int storedValue = pixelData.GetPixel(pixelIndex);
                                double realValue = modalityLut != null ? modalityLut[storedValue] : storedValue;

                                double deviation = realValue - mean;
                                sum += deviation*deviation;
                            }
                        });
            }

            if (pixelCount == 0)
                return 0;

            return Math.Sqrt(sum/pixelCount);
        }

        public static bool IsInPolygon(PointF[] poly, PointF p)
        {
            bool inside = false;

            if (poly.Length < 3)
                return false;

            var oldPoint = new PointF(
                poly[poly.Length - 1].X, poly[poly.Length - 1].Y);

            for (int i = 0; i < poly.Length; i++)
            {
                var newPoint = new PointF(poly[i].X, poly[i].Y);

                PointF p1, p2;
                if (newPoint.X > oldPoint.X)
                {
                    p1 = oldPoint;
                    p2 = newPoint;
                }

                else
                {
                    p1 = newPoint;
                    p2 = oldPoint;
                }


                if ((newPoint.X < p.X) == (p.X <= oldPoint.X)
                    && (p.Y - (long) p1.Y)*(p2.X - p1.X)
                    < (p2.Y - (long) p1.Y)*(p.X - p1.X))
                {
                    inside = !inside;
                }

                oldPoint = newPoint;
            }
            return inside;
        }

        public static IPresentationImage PresentationImageFromPositionOrientation(
            ImagePositionPatient imagePositionPatient,
            ImageOrientationPatient imageOrientationPatient,
            IDisplaySet displaySet,
            string frameOfReferenceUid)
        {
            var point = new Vector3D(
                (float) imagePositionPatient.X,
                (float) imagePositionPatient.Y,
                (float) imagePositionPatient.Z);

            if (displaySet != null)
            {
                var firstSop = displaySet.PresentationImages.OfType<IImageSopProvider>().FirstOrDefault();
                // Match Frame of Reference UID, if present
                if (firstSop == null || string.IsNullOrEmpty(frameOfReferenceUid) ||
                    string.IsNullOrEmpty(firstSop.Frame.FrameOfReferenceUid) || frameOfReferenceUid == firstSop.Frame.FrameOfReferenceUid)
                {
                    foreach (IPresentationImage image in displaySet.PresentationImages)
                    {
                        var sop = image as IImageSopProvider;
                        if (sop != null)
                        {
                            Vector3D planeRow = new Vector3D(
                                (float) sop.Frame.ImageOrientationPatient.RowX,
                                (float) sop.Frame.ImageOrientationPatient.RowY,
                                (float) sop.Frame.ImageOrientationPatient.RowZ).Normalize();
                            Vector3D planeColumn = new Vector3D(
                                (float) sop.Frame.ImageOrientationPatient.ColumnX,
                                (float) sop.Frame.ImageOrientationPatient.ColumnY,
                                (float) sop.Frame.ImageOrientationPatient.ColumnZ).Normalize();
                            Vector3D planeNormal = planeRow.Cross(planeColumn);

                            var planePosition = new Vector3D(
                                (float) sop.Frame.ImagePositionPatient.X,
                                (float) sop.Frame.ImagePositionPatient.Y,
                                (float) sop.Frame.ImagePositionPatient.Z);
                            if (PointIsInPlane(point, planeNormal, planePosition))
                                return image;
                        }
                    }
                }
            }

            return null;
        }

        public static bool PointIsInPlane(Vector3D point, Vector3D planeNormal, Vector3D planePosition)
        {
            const float accuracy = 0.001f;
            if (point.Equals(planePosition))
                return true;
            Vector3D pointDirection = (point - planePosition).Normalize();
            planeNormal = planeNormal.Normalize();
            if (Math.Abs(pointDirection.Dot(planeNormal)) < accuracy)
                return true;
            return false;
        }

        public static IPresentationImage PresentationImageFromPositionOrientation(
            double[] imagePositionPatientValues,
            double[] imageOrientationPatientValues,
            IDisplaySet displaySet,
            string frameOfReferenceUid)
        {
            Platform.CheckForNullReference(displaySet, "displaySet");

            if (imagePositionPatientValues != null && imagePositionPatientValues.Length > 2 &&
                imageOrientationPatientValues != null && imageOrientationPatientValues.Length > 5)
            {
                var imagePositionPatient = new ImagePositionPatient(
                    imagePositionPatientValues[0],
                    imagePositionPatientValues[1],
                    imagePositionPatientValues[2]);
                var imageOrientationPatient = new ImageOrientationPatient(
                    imageOrientationPatientValues[0],
                    imageOrientationPatientValues[1],
                    imageOrientationPatientValues[2],
                    imageOrientationPatientValues[3],
                    imageOrientationPatientValues[4],
                    imageOrientationPatientValues[5]);

                return PresentationImageFromPositionOrientation(
                    imagePositionPatient,
                    imageOrientationPatient,
                    displaySet,
                    frameOfReferenceUid);
            }

            return null;
        }

        #region Nested type: ImageCalculationInfo

        internal class ImageCalculationInfo
        {
            public RectangleF RoiBoundingBox { get; set; }
            public IModalityLut ModalityLut { get; set; }
            public PixelData PixelData { get; set; }
            public SegFrameImageGraphic SegFrameImageGraphic { get; set; }
        }

        #endregion
    }
}