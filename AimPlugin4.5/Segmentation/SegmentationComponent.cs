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
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Threading;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Dicom;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Common.ServerDirectory;
using ClearCanvas.ImageViewer.Common.WorkItem;
using ClearCanvas.ImageViewer.Configuration;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InputManagement;
using ClearCanvas.ImageViewer.Mathematics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.StudyManagement;
using Segmentation.Configuration;
using Segmentation.Graphics;
using Segmentation.Tree;
using Segmentation.Tree.Utilities;
using Path = System.IO.Path;

namespace Segmentation
{
    /// <summary>
    /// Extension point for views onto <see cref="SegmentationComponent"/>.
    /// </summary>
    [ExtensionPoint]
    public sealed class SegmentationComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
    {
    }

    /// <summary>
    /// SegmentationComponent class.
    /// </summary>
    [AssociateView(typeof (SegmentationComponentViewExtensionPoint))]
    public partial class SegmentationComponent : ImageViewerToolComponent
    {
        internal const double PixelSpacingAccuracy = 0.1;
        private readonly Dictionary<IPresentationImage, Dictionary<int, PolygonalRoiSegGraphic>> _existingSegGraphics;
        private IPresentationImage _lastSelectedPresentationImage;
        private SegmentationTree _lastSelectedSegmentationTree;

        /// <summary>
        /// Constructor.
        /// </summary>
        public SegmentationComponent(IDesktopWindow desktopWindow)
            : base(desktopWindow)
        {
            SegmentationTrees = new ObservableDictionary<IImageViewer, SegmentationTree>();
            _existingSegGraphics = new Dictionary<IPresentationImage, Dictionary<int, PolygonalRoiSegGraphic>>();

            PropertyChanged += OnPropertyChanged;
        }


        public ObservableDictionary<IImageViewer, SegmentationTree> SegmentationTrees { get; private set; }

        /// <summary>
        /// Gets the hierarchical collection of segmentation objects
        /// </summary>
        public SegmentationTree SegmentationTree
        {
            get
            {
                if (ImageViewer != null)
                    if (SegmentationTrees.ContainsKey(ImageViewer))
                        return SegmentationTrees[ImageViewer];
                return null;
            }
        }

        /// <summary>
        /// Gets whether the Create Segmentation button should be enabled
        /// </summary>
        public bool CreateSegmentationEnabled
        {
            get
            {
                return IsStarted &&
                       SegmentationTree != null &&
                       SegmentationTree.SelectedSeg != null &&
                       SegmentationTree.SelectedSeg.Editable &&
                       WorkItemActivityMonitor.IsRunning;
            }
        }

        public Seg SelectedSeg
        {
            get { return SegmentationTree == null ? null : SegmentationTree.SelectedSeg; }
        }

        internal List<Category> AvailableCategories { get; set; }

        #region Create New Segmentation

        private void DoCreateSegmentation()
        {
            try
            {
                var task = new BackgroundTask(context =>
                                                  {
                                                      try
                                                      {
                                                          var synchContext = context.UserState as SynchronizationContext;
                                                          string error;
                                                          IImageSopProvider imageSopProvider; // source image
                                                          SegmentationDocument segmentationDocument;
                                                          // the actual document that we serialized. It's a container for the current Seg selection.

                                                          // 1. Create DICOM Segmentation
                                                          context.ReportProgress(new BackgroundTaskProgress(0, 4,
                                                                                                            "Creating Segmentation instance. Please wait."));
                                                          DicomFile dicomFile =
                                                              DoCreateDicomSegmentationDocument(
                                                                  out segmentationDocument, out imageSopProvider,
                                                                  out error);
                                                          if (dicomFile == null || segmentationDocument == null ||
                                                              imageSopProvider == null)
                                                              throw new Exception(error);

                                                          // 2. Save created Segmentation instance
                                                          context.ReportProgress(new BackgroundTaskProgress(1, 4,
                                                                                                            "Publishing created segmentation object. Please wait."));
                                                          if (
                                                              !DoSendSegmentationDicomDocumentToStorage(dicomFile,
                                                                                                        imageSopProvider
                                                                                                            .ImageSop,
                                                                                                        out error))
                                                              throw new Exception(error);

                                                          // 3. Upon successful save, remove ROI graphics and read saved Segmentation instance in (will create graphics and add new SegmentationDocument to the SegmentationTree)
                                                          context.ReportProgress(new BackgroundTaskProgress(2, 4,
                                                                                                            "Removing ROIs. Please wait."));
                                                          if (
                                                              !DoRemoveRoiGraphicFromImages(
                                                                  segmentationDocument.Segs.ToList(), synchContext))
                                                              throw new Exception(
                                                                  "Display cannot be updated. Close and re-open study to see new segmentations");

                                                          context.Complete();
                                                      }
                                                      catch (Exception ex)
                                                      {
                                                          context.Error(ex);
                                                      }
                                                  }, false, SynchronizationContext.Current);

                ProgressDialog.Show(task, DesktopWindow, true, ProgressBarStyle.Continuous);
            }
            catch (Exception ex)
            {
                Platform.Log(LogLevel.Error, ex, "Failed to create Segmentation");
                DesktopWindow.ShowMessageBox(string.Format("Error creating segmentation instance. {0}", ex.Message),
                                             "Segmentation Serialization Error",
                                             MessageBoxActions.Ok);
            }
        }

        private DicomFile DoCreateDicomSegmentationDocument(out SegmentationDocument segmentationDocument,
                                                            out IImageSopProvider sourceImageSopProvider,
                                                            out string error)
        {
            sourceImageSopProvider = null;
            segmentationDocument = null;

            Seg selectedSeg = SelectedSeg;
            if (selectedSeg == null)
            {
                error = "No segmentation is selected";
                return null;
            }

            SegmentationDocument selectedSegmentationDocument =
                SegmentationTree.SegmentationDocuments.FirstOrDefault(item => item.Segs.Contains(selectedSeg));
            if (selectedSegmentationDocument == null)
            {
                error = "Filed to locate Segmentation Document object for the current segmentation";
                Platform.Log(LogLevel.Error,
                             "Failed to find Segmentation Document object for the current Seg. No DICOM Segmentation is created");
                return null;
            }

            // Set user-specific color
            foreach (var seg in selectedSegmentationDocument.Segs)
                seg.Color = UserInfo.GetGraphicColorForUser();

            PolygonalRoiSegGraphic polygonalGraphic =
                selectedSeg.SegGraphics.OfType<PolygonalRoiSegGraphic>().FirstOrDefault();
            if (polygonalGraphic == null)
            {
                error = "No supported ROI is found";
                return null;
            }
            sourceImageSopProvider = polygonalGraphic.PolygonalRoiGraphic.ParentPresentationImage as IImageSopProvider;
            if (sourceImageSopProvider == null)
            {
                error = "Graphic's parent image is of incorrect type.";
                return null;
            }

            segmentationDocument = new SegmentationDocument();
            segmentationDocument.ContentLabel = string.IsNullOrEmpty(selectedSegmentationDocument.ContentLabel)
                                                    ? selectedSeg.Label
                                                    : selectedSegmentationDocument.ContentLabel;
            segmentationDocument.CreationDateTime = selectedSegmentationDocument.CreationDateTime;
            segmentationDocument.PreviousSegmentationUid = selectedSegmentationDocument.PreviousSegmentationUid;
            segmentationDocument.UserInfo = selectedSegmentationDocument.UserInfo == null ||
                                            string.IsNullOrEmpty(selectedSegmentationDocument.UserInfo.Name)
                                                ? UserInfo.GetCurrentUserInfo()
                                                : new UserInfo
                                                      {
                                                          LoginName = selectedSegmentationDocument.UserInfo.LoginName,
                                                          Name = selectedSegmentationDocument.UserInfo.Name
                                                      };
            string defaultSeriesDescription = string.Format("Segmentation{0}",
                                                            segmentationDocument.UserInfo == null ||
                                                            string.IsNullOrEmpty(segmentationDocument.UserInfo.Name)
                                                                ? ""
                                                                : " " + segmentationDocument.UserInfo.Name);
            segmentationDocument.SeriesDescription = string.IsNullOrEmpty(selectedSegmentationDocument.SeriesDescription)
                                                         ? defaultSeriesDescription
                                                         : selectedSegmentationDocument.SeriesDescription;
            segmentationDocument.SeriesInstanceUid = selectedSegmentationDocument.SeriesInstanceUid;
            // NOTE: This only considers loaded series. Any series added after the current study was open are not looked at.
            segmentationDocument.SeriesNumber = sourceImageSopProvider.ImageSop.ParentSeries.ParentStudy.Series.Max(
                series => series.SeriesNumber) + 1;
            segmentationDocument.Segs.Add(selectedSeg);

            DicomFile dicomSegmentation =
                new SegmentationSerializer(segmentationDocument).Serialize(OnSegmentationSerializerCallback);

            if (dicomSegmentation == null)
            {
                segmentationDocument = null;
                sourceImageSopProvider = null;
                error = "Segmentation serializer produced no document. Contact system administrator.";
                Platform.Log(LogLevel.Error, "Serialization failed: failed to create new DICOM Segmentation instance");
            }
            else
            {
                error = null;
                // Test code. Save new segmentation object in a Windows Desktop folder
                if (SegmentationSettings.Default.SaveCopyOfNewSegmentationDocumentToDesktop)
                {
                    try
                    {
                        string tempSegFolder = Path.Combine(
                            Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "temp_segmentation");
                        string tempSegFile = dicomSegmentation.DataSet[DicomTags.SopInstanceUid].GetString(0, null);
                        if (tempSegFile == null)
                        {
                            tempSegFile = Path.GetRandomFileName();
                            tempSegFile = Path.ChangeExtension(tempSegFile, ".dcm");
                        }
                        else
                        {
                            tempSegFile += ".dcm";
                        }
                        tempSegFile = Path.Combine(tempSegFolder, tempSegFile);
                        if (!Directory.Exists(tempSegFolder))
                            Directory.CreateDirectory(tempSegFolder);
                        dicomSegmentation.Save(tempSegFile);
                    }
                    catch (Exception e)
                    {
                        Platform.Log(LogLevel.Error, e, "Failed to save test Segmentation instance");
                    }
                }
            }
            return dicomSegmentation;
        }

        private IPresentationImage OnSegmentationSerializerCallback(string sopInstanceUid, int frameNumber)
        {
            return ImageViewer.PhysicalWorkspace.ImageBoxes.Where(
                imageBox => imageBox.DisplaySet != null && imageBox.DisplaySet.PresentationImages != null)
                .Select(imageBox => imageBox.DisplaySet.PresentationImages.FirstOrDefault(presentationImage =>
                                                                                              {
                                                                                                  var imageSopProvider =
                                                                                                      presentationImage
                                                                                                      as
                                                                                                      IImageSopProvider;
                                                                                                  return
                                                                                                      imageSopProvider !=
                                                                                                      null &&
                                                                                                      imageSopProvider.
                                                                                                          ImageSop.
                                                                                                          SopInstanceUid ==
                                                                                                      sopInstanceUid &&
                                                                                                      imageSopProvider.
                                                                                                          Frame.
                                                                                                          FrameNumber ==
                                                                                                      frameNumber;
                                                                                              })).FirstOrDefault(
                                                                                                  presImgs =>
                                                                                                  presImgs != null);
        }

        private static bool DoSendSegmentationDicomDocumentToStorage(DicomFile segmentationDocument,
                                                                     ImageSop sourceImageSop, out string error)
        {
            ISopDataSource sopDataSource = sourceImageSop == null ? null : sourceImageSop.DataSource;
            if (sopDataSource == null)
            {
                Platform.Log(LogLevel.Error,
                             "Failed to send Segmentation to data store. [Could not find image SOP DataSource]");
                error = "Failed to store segmentation instance. Cannot find Referenced Image SOP DataSource";
                return false;
            }

            // NOTE: This is what KeyImagePublisher does as well
            var dicomPublishingHelper = new DicomPublishingHelper();
            //dicomPublishingHelper.OriginServer = ServerDirectory.GetLocalServer();
            dicomPublishingHelper.OriginServer =
                ServerDirectory.GetRemoteServersByAETitle(
                    sopDataSource[DicomTags.SourceApplicationEntityTitle].ToString()).FirstOrDefault();
            dicomPublishingHelper.SourceServer = sopDataSource.Server ?? ServerDirectory.GetLocalServer();
            // GetLocalServer() allows to import annotations created for locally opened files

            // TODO: make a copy of DicomPublishingHelper() and change the copy to allow for publishing SOPs to local data store even when the parent Study does not exist locally

            dicomPublishingHelper.Files.Add(segmentationDocument);

            try
            {
                error = null;
                return dicomPublishingHelper.Publish();
            }
            catch (Exception ex)
            {
                Platform.Log(LogLevel.Error, ex, "Failed to store annotations");
                error = "Failed to publish segmentation. " + ex.Message;
            }
            return false;
        }

        private bool DoRemoveRoiGraphicFromImages(List<Seg> segs, SynchronizationContext synchContext)
        {
            bool retVal = segs != null && segs.Count > 0;
            while (segs != null && segs.Count > 0)
            {
                Seg seg = segs[0];

                // NOTE: we need to post back to the UI thread since SegmentationTree and SegGraphics collections were created on that thread
                if (synchContext == null)
                    RemoveSegAndSegRoiGraphics(seg);
                else
                    synchContext.Post(state => RemoveSegAndSegRoiGraphics(seg), null);
                segs.Remove(seg);
            }

            return retVal;
        }

        // Removes the Seg and its ROI graphics from the SegmentationTree and images
        private void RemoveSegAndSegRoiGraphics(Seg seg)
        {
            // 1. Remove Seg from the main Tree
            SegmentationDocument formerOwnerSegDoc =
                SegmentationTree.SegmentationDocuments.FirstOrDefault(treeDoc => treeDoc.Segs.Remove(seg));
            Debug.Assert(formerOwnerSegDoc != null, "Failed to remove Seg from its doc?");

            // 2. Remove Seg's graphics from images
            PolygonalRoiSegGraphic polygonalRoiSegGraphic;
            while ((polygonalRoiSegGraphic = seg.SegGraphics.OfType<PolygonalRoiSegGraphic>().FirstOrDefault()) != null)
            {
                var graphicsProvider =
                    polygonalRoiSegGraphic.PolygonalRoiGraphic.ParentPresentationImage as IOverlayGraphicsProvider;
                if (graphicsProvider != null)
                {
                    graphicsProvider.OverlayGraphics.Remove(polygonalRoiSegGraphic.PolygonalRoiGraphic);
                    polygonalRoiSegGraphic.PolygonalRoiGraphic.Dispose();
                }
                seg.SegGraphics.Remove(polygonalRoiSegGraphic);
            }
        }

        #endregion Create New Segmentation

        private void OnPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "SegmentationTree")
            {
                if (_lastSelectedSegmentationTree != null)
                {
                    _lastSelectedSegmentationTree.PropertyChanged -= LastSelectedSegmentationTreeOnPropertyChanged;
                }

                _lastSelectedSegmentationTree = SegmentationTree;

                if (_lastSelectedSegmentationTree != null)
                    _lastSelectedSegmentationTree.PropertyChanged += LastSelectedSegmentationTreeOnPropertyChanged;
            }
        }

        private void LastSelectedSegmentationTreeOnPropertyChanged(object sender,
                                                                   PropertyChangedEventArgs propertyChangedEventArgs)
        {
            if (propertyChangedEventArgs.PropertyName == "SelectedSeg")
            {
                NotifyPropertyChanged("SelectedSegOpacity");
                NotifyPropertyChanged("SelectedSegGraphics");

                // Updated calculations if needed
                if (SelectedSeg != null &&
                    !SelectedSeg.Editable &&
                    !SelectedSeg.Volume.HasValue)
                {
                    List<SegFrameImageGraphic> images =
                        SegmentationTool.GetSegmentationImageGraphicsFromSeg(ImageViewer, SelectedSeg).ToList();
                    List<SegmentationGraphicsHelpers.ImageCalculationInfo> imageCalculationInfoStack =
                        SegmentationGraphicsHelpers.ImageCalculationInfoStackFromImageStack(images).ToList();
                    SelectedSeg.Volume = CalculateSegVolume(SelectedSeg, images);
                    SelectedSeg.PixelIntensityMean =
                        SegmentationGraphicsHelpers.CalculateMeanForStack(imageCalculationInfoStack);
                    SegmentationTree.SelectedSeg.PixelIntensityStandardDeviation =
                        SegmentationGraphicsHelpers.CalculateStandardDeviationForStack(
                            SegmentationTree.SelectedSeg.PixelIntensityMean.Value,
                            imageCalculationInfoStack);
                }
            }
        }

        private void SegmentationTreeOnPropertyChanged(object sender, PropertyChangedEventArgs propertyChangedEventArgs)
        {
            if (propertyChangedEventArgs.PropertyName == "SelectedSeg")
            {
                NotifyPropertyChanged("CreateSegmentationEnabled");
                ShowImageContainingSeg(SegmentationTree.SelectedSeg);
            }
        }

        private bool SegImagesValidForSegmentationCreation(Seg seg, out string errorMessage)
        {
            var images = new List<IPresentationImage>();

            List<PolygonalRoiSegGraphic> graphics = seg.SegGraphics.ToList();
            // Sort by image number if the image numbers aren't all the same
            if (graphics.Select(graphic => graphic.ImageNumber).ToList().Distinct().Count() != 1)
                graphics.Sort((graphic1, graphic2) => graphic1.ImageNumber.CompareTo(graphic2.ImageNumber));
            // Sort by frame number if the frame numbers aren't all the same
            if (graphics.Select(graphic => graphic.ImageFrameNumber).ToList().Distinct().Count() != 1)
                graphics.Sort((graphic1, graphic2) => graphic1.ImageFrameNumber.CompareTo(graphic2.ImageFrameNumber));

            foreach (ISegGraphic segGraphic in graphics)
            {
                IPresentationImage image = GetImageFromSopInstanceUid(
                    segGraphic.ImageSopInstanceUid,
                    segGraphic.ImageFrameNumber);
                if (image != null)
                {
                    if (!images.Contains(image))
                        images.Add(image);
                }
                else
                {
                    errorMessage = "Unable to match segmentation graphic to presentation image.";
                    Platform.Log(LogLevel.Error, errorMessage, segGraphic);
                    return false;
                }
            }

            if (images.Count > 1)
            {
                List<IImageSopProvider> sops = images.OfType<IImageSopProvider>().ToList();
                if (sops.Count > 1)
                {
                    string seriesInstanceUid = sops[0].Sop.SeriesInstanceUid;
                    int rows = sops[0].Frame.Rows;
                    int columns = sops[0].Frame.Columns;
                    double xPixelSpacing = sops[0].Frame.ImagePlaneHelper.PixelSpacing.Column;
                    double yPixelSpacing = sops[0].Frame.ImagePlaneHelper.PixelSpacing.Row;
                    double sliceSpacing = CalculateSpaceBetweenPlanes(sops[0].Frame, sops[1].Frame);
                    // Check for slice thickness of zero
                    if (sliceSpacing < PixelSpacingAccuracy)
                    {
                        errorMessage = "Slice thickness cannot be zero.";
                        Platform.Log(LogLevel.Error, errorMessage, images);
                        return false;
                    }
                    int sliceStart = graphics[0].ImageNumber;
                    int frameStart = graphics[0].ImageFrameNumber;

                    for (int i = 1; i < sops.Count; i++)
                    {
                        IImageSopProvider sop = sops[i];
                        if (sop.Sop.SeriesInstanceUid != seriesInstanceUid)
                        {
                            errorMessage = "Segmentation graphics cannot span multiple series.";
                            Platform.Log(LogLevel.Error, errorMessage, sop);
                            return false;
                        }
                        if (sop.Frame.Rows != rows)
                        {
                            errorMessage = "Images containing segmentations cannot be different sizes.";
                            Platform.Log(LogLevel.Error, errorMessage, sop);
                            return false;
                        }
                        if (sop.Frame.Columns != columns)
                        {
                            errorMessage = "Images containing segmentations cannot be different sizes.";
                            Platform.Log(LogLevel.Error, errorMessage, sop);
                            return false;
                        }
                        if ((Math.Abs(sop.Frame.ImagePlaneHelper.PixelSpacing.Column - xPixelSpacing) >
                             PixelSpacingAccuracy))
                        {
                            errorMessage = "Images containing segmentations cannot have different pixel spacings.";
                            Platform.Log(LogLevel.Error, errorMessage, sop);
                            return false;
                        }
                        if ((Math.Abs(sop.Frame.ImagePlaneHelper.PixelSpacing.Row - yPixelSpacing) >
                             PixelSpacingAccuracy))
                        {
                            errorMessage = "Images containing segmentations cannot have different pixel spacings.";
                            Platform.Log(LogLevel.Error, errorMessage, sop);
                            return false;
                        }
                        if ((sops[i].ImageSop.InstanceNumber != sliceStart + 1 && sops[i].Frame.FrameNumber != frameStart + 1))
                        {
                            errorMessage = "Images containing segmentations must be consecutive without gaps.";
                            Platform.Log(LogLevel.Error, errorMessage, sop);
                            return false;
                        }
                        if ((Math.Abs(CalculateSpaceBetweenPlanes(sop.Frame, sops[i - 1].Frame) - sliceSpacing) >
                             PixelSpacingAccuracy))
                        {
                            errorMessage = "Images containing segmentations cannot have different slice thicknesses.";
                            Platform.Log(LogLevel.Error, errorMessage, sop);
                            return false;
                        }
                        sliceStart++;
                        frameStart++;
                    }
                }
                else
                {
                    errorMessage = "Unable to find images containing segmentations.";
                    Platform.Log(LogLevel.Error, errorMessage, images);
                    return false;
                }
            }
            errorMessage = String.Empty;
            return true;
        }

        private static float CalculateSpaceBetweenPlanes(Frame frame1, Frame frame2)
        {
            Vector3D point1 = frame1.ImagePlaneHelper.ImagePositionPatientVector;
            Vector3D point2 = frame2.ImagePlaneHelper.ImagePositionPatientVector;
            Vector3D delta = point1 - point2;

            // spacing between images should be measured along normal to image plane, regardless of actual orientation of images! (e.g. consider gantry tiled images)
            return delta.IsNull ? 0f : Math.Abs(delta.Dot(frame1.ImagePlaneHelper.GetNormalVector()));
        }

        internal double? CalculateSegVolume(Seg seg, IEnumerable<SegFrameImageGraphic> images)
        {
            if (!seg.Editable && images.Any())
            {
                // Pixel spacing and slice thickness must be the same for all frames

                SegFrameImageGraphic segFrameImageGraphic = images.First();
                SegmentFrameData segFrameData = seg.SegmentImageData.SegmentFrameData.FirstOrDefault();

                if (segFrameImageGraphic != null && segFrameData != null)
                {
                    var sop = segFrameImageGraphic.ParentPresentationImage as IImageSopProvider;
                    double xPixelSpacing = sop.Frame.ImagePlaneHelper.PixelSpacing.Column;
                    double yPixelSpacing = sop.Frame.ImagePlaneHelper.PixelSpacing.Row;
                    IPresentationImage adjImage = GetAdjacentImage(segFrameImageGraphic.ParentPresentationImage);
                    var adjSop = adjImage as IImageSopProvider;
                    double sliceThickness = 1;
                    if (segFrameData.SliceThickness.HasValue)
                        sliceThickness = segFrameData.SliceThickness.Value;
                    double volume = 0;
                    if (adjSop != null)
                    {
                        sliceThickness = CalculateSpaceBetweenPlanes(adjSop.Frame, sop.Frame);
                    }

                    foreach (SegFrameImageGraphic segGraphic in images)
                    {
                        int pixelCount = 0;
                        for (int row = 0; row < segGraphic.Rows; row++)
                        {
                            for (int column = 0; column < segGraphic.Columns; column++)
                            {
                                if (segGraphic[column, row])
                                    pixelCount++;
                            }
                        }
                        volume += sliceThickness*pixelCount*xPixelSpacing*yPixelSpacing;
                    }

                    return volume;
                }
            }

            return null;
        }

        private IPresentationImage GetAdjacentImage(IPresentationImage presentationImage)
        {
            foreach (IImageBox imageBox in ImageViewer.PhysicalWorkspace.ImageBoxes)
            {
                if (imageBox.DisplaySet != null && imageBox.DisplaySet.PresentationImages.Contains(presentationImage))
                {
                    List<IImageSopProvider> sops =
                        imageBox.DisplaySet.PresentationImages.OfType<IImageSopProvider>().ToList();
                    var sop = presentationImage as IImageSopProvider;
                    if (sops.Count > 1)
                    {
                        var image =
                            sops.FirstOrDefault(
                                adjSop =>
                                adjSop.ImageSop.InstanceNumber == sop.ImageSop.InstanceNumber - 1 ||
                                adjSop.ImageSop.InstanceNumber == sop.ImageSop.InstanceNumber + 1) as IPresentationImage;
                        // Multiframe
                        if (image == null)
                        {
                            image =
                            sops.FirstOrDefault(
                                adjSop =>
                                adjSop.Frame.FrameNumber == sop.Frame.FrameNumber - 1 ||
                                adjSop.Frame.FrameNumber == sop.Frame.FrameNumber + 1) as IPresentationImage;
                        }
                        return image;
                    }
                }
            }
            return null;
        }

        private IPresentationImage GetImageFromSopInstanceUid(string sopInstanceUid, int frameNumber)
        {
            foreach (IImageBox imageBox in ImageViewer.PhysicalWorkspace.ImageBoxes)
                if (imageBox.DisplaySet != null)
                {
                    foreach (IPresentationImage presentationImage in imageBox.DisplaySet.PresentationImages)
                    {
                        var sopProvider = presentationImage as IImageSopProvider;
                        if (sopProvider != null)
                        {
                            if (sopProvider.Frame != null)
                            {
                                if (sopProvider.ImageSop.SopInstanceUid == sopInstanceUid &&
                                    sopProvider.Frame.FrameNumber == frameNumber)
                                    return presentationImage;
                            }
                            else if (sopProvider.ImageSop.SopInstanceUid == sopInstanceUid) return presentationImage;
                        }
                    }
                }
            return null;
        }

        public Seg SegFromDocumentUidAndSegNumber(string documentUid, int segNumber)
        {
            if (SegmentationTree != null)
            {
                SegmentationDocument doc =
                    SegmentationTree.SegmentationDocuments.FirstOrDefault(segDoc => segDoc.SopInstanceUid == documentUid);
                if (doc != null)
                    return doc.Segs.FirstOrDefault(seg => seg.SegmentationNumber == segNumber);
            }
            return null;
        }

        public void ShowImageContainingSeg(Seg seg)
        {
            if (seg != null)
            {
                List<ISegGraphic> graphics =
                    SegmentationTool.GetAllSegmentationGraphicsFromSeg(ImageViewer, seg).ToList();
                if (graphics != null && graphics.Count > 0)
                {
                    // Sort by image number if the image numbers aren't all the same
                    if (graphics.Select(graphic => graphic.ImageNumber).ToList().Distinct().Count() != 1)
                        graphics.Sort((graphic1, graphic2) => graphic1.ImageNumber.CompareTo(graphic2.ImageNumber));
                    // Sort by frame number if the frame numbers aren't all the same
                    if (graphics.Select(graphic => graphic.ImageFrameNumber).ToList().Distinct().Count() != 1)
                        graphics.Sort(
                            (graphic1, graphic2) => graphic1.ImageFrameNumber.CompareTo(graphic2.ImageFrameNumber));
                    if (graphics.Count > 0)
                    {
                        // Get the middle graphic object
                        var middleImage = (int) Math.Round(graphics.Count/2f);
                        middleImage--;
                        if (middleImage < 0)
                            middleImage = 0;
                        IPresentationImage image = GetImageFromSopInstanceUid(
                            graphics[middleImage].ImageSopInstanceUid,
                            graphics[middleImage].ImageFrameNumber);
                        if (image != null)
                        {
                            foreach (IImageBox imageBox in ImageViewer.PhysicalWorkspace.ImageBoxes)
                            {
                                if (imageBox.DisplaySet != null &&
                                    imageBox.DisplaySet.PresentationImages.Contains(image))
                                {
                                    imageBox.TopLeftPresentationImage = image;
                                    image.Tile.Select();
                                    image.Draw();
                                }
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Creates a segmentation object from the current segmentation tree
        /// </summary>
        public void CreateSegmentation()
        {
            string errorMessage;
            if (!SegImagesValidForSegmentationCreation(SegmentationTree.SelectedSeg, out errorMessage))
            {
                DesktopWindow.ShowMessageBox(
                    "Images do not match or are incompatible for segmentation creation.  " + errorMessage,
                    "Incompatible Segmentation Images",
                    MessageBoxActions.Ok);
                return;
            }
            if (!SegmentationSettings.Default.ShowSegmentationCreationDialog ||
                DesktopWindow.ShowMessageBox(
                    "Do you wish to convert the selected ROIs to segmentation images?  This action cannot be undone.",
                    "Confirm Segmentation Creation",
                    MessageBoxActions.YesNo) ==
                DialogBoxAction.Yes)
            {
                // Create and save segmentation object for the currently selected Seg in the tree
                DoCreateSegmentation();
            }
        }

        public void UpdateSegmentationTreeWithAllLoadedDocuments(IImageViewer imageViewer)
        {
            if (imageViewer == null)
                return;

            var allLoadedSegDocuments = new HashSet<SegmentationDocument>();
            foreach (
                IImageBox imageBox in
                    imageViewer.PhysicalWorkspace.ImageBoxes.Where(
                        imageBox => imageBox != null && imageBox.DisplaySet != null))
            {
                IDisplaySet displaySet = imageBox.DisplaySet;
                foreach (
                    IOverlayGraphicsProvider graphicProvider in
                        displaySet.PresentationImages.OfType<IOverlayGraphicsProvider>().Where(
                            graphicsProvider => graphicsProvider != null))
                {
                    foreach (
                        SegFrameImageGraphic segFrameGraphic in
                            graphicProvider.OverlayGraphics.OfType<SegFrameImageGraphic>().Where(
                                segFrameGraphic => segFrameGraphic.SegmentationDocumentReference != null))
                    {
                        allLoadedSegDocuments.Add(segFrameGraphic.SegmentationDocumentReference.SegmentationDocument);
                    }
                }
            }
            if (allLoadedSegDocuments.Count > 0)
            {
                SegmentationTree workingTree;
                if (SegmentationTrees.ContainsKey(imageViewer))
                {
                    workingTree = SegmentationTrees[imageViewer];
                }
                else
                {
                    workingTree = new SegmentationTree
                                      {
                                          StudyId =
                                              allLoadedSegDocuments.First().SegmentationDocumentIod.StudyInstanceUid,
                                          StudyDescription =
                                              allLoadedSegDocuments.First().SegmentationDocumentIod.SeriesDescription
                                      };
                    SegmentationTrees.Add(imageViewer, workingTree);
                }
                if (workingTree != null)
                {
                    var documentsToRemoveFromTree = new HashSet<SegmentationDocument>();
                    // Compare new docs with the already stored in the tree
                    foreach (
                        SegmentationDocument segmentationDocument in
                            workingTree.SegmentationDocuments.Where(doc => doc.Saved))
                    {
                        if (allLoadedSegDocuments.Contains(segmentationDocument))
                            allLoadedSegDocuments.Remove(segmentationDocument);
                            // the doc is already loaded into the tree
                        else
                            documentsToRemoveFromTree.Add(segmentationDocument);
                        // loaded doc is no longer in the data storage
                    }

                    // Remove no longer stored documents from the tree
                    foreach (SegmentationDocument removedSegDocument in documentsToRemoveFromTree)
                    {
                        workingTree.SegmentationDocuments.Remove(removedSegDocument);
                    }

                    // Add newly available segmentation documents to the tree
                    foreach (SegmentationDocument loadedSegDocument in allLoadedSegDocuments)
                    {
                        workingTree.SegmentationDocuments.Add(loadedSegDocument);
                    }
                }
            }
        }

        private void FindAllMarkup()
        {
            foreach (IImageBox imageBox in ImageViewer.PhysicalWorkspace.ImageBoxes)
            {
                if (imageBox.DisplaySet != null)
                {
                    foreach (IPresentationImage presentationImage in imageBox.DisplaySet.PresentationImages)
                    {
                        CheckPresentationImageForGraphicsChanges(presentationImage);
                    }
                }
            }
        }

        private void CheckPresentationImageForGraphicsChanges(IPresentationImage presentationImage)
        {
            var graphicsProvider = presentationImage as IOverlayGraphicsProvider;
            if (graphicsProvider != null)
            {
                var sop = presentationImage as ISopProvider;

                if (sop != null)
                {
                    // Check for removed graphics
                    if (_existingSegGraphics.ContainsKey(presentationImage))
                    {
                        foreach (
                            var segGraphicKeyValuePair in _existingSegGraphics[presentationImage].ToList())
                        {
                            IGraphic existingGraphic =
                                graphicsProvider.OverlayGraphics.FirstOrDefault(
                                    graphic =>
                                    SegmentationGraphicsHelpers.RoiGraphicAndSegGraphicsMatch(graphic,
                                                                                              segGraphicKeyValuePair.
                                                                                                  Value));

                            if (existingGraphic == null &&
                                _existingSegGraphics[presentationImage].ContainsKey(segGraphicKeyValuePair.Key))
                            {
                                _existingSegGraphics[presentationImage].Remove(segGraphicKeyValuePair.Key);

                                Seg existingSeg = SegmentationTree.AllNewSegs.FirstOrDefault(
                                    seg =>
                                    seg.Label == segGraphicKeyValuePair.Value.Label &&
                                    seg.ImageSeriesUid == sop.Sop.SeriesInstanceUid);

                                if (existingSeg != null)
                                {
                                    existingSeg.SegGraphics.Remove(segGraphicKeyValuePair.Value);
                                    // Remove the seg if it's empty
                                    if (existingSeg.SegGraphics.Count == 0)
                                    {
                                        SegmentationDocument segDocument =
                                            SegmentationTree.SegmentationDocuments.FirstOrDefault(
                                                doc => doc.Segs.Contains(existingSeg));
                                        if (segDocument != null)
                                        {
                                            segDocument.Segs.Remove(existingSeg);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Check for new graphics
                    foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
                    {
                        AddSegGraphicIfNewRoi(graphic);
                    }
                }
            }
        }

        private void AddSegGraphicIfNewRoi(IGraphic graphic)
        {
            var roiGraphic = graphic as RoiGraphic;

            if (roiGraphic != null && roiGraphic.Roi != null)
            {
                IPresentationImage presentationImage = roiGraphic.ParentPresentationImage;
                var sop = roiGraphic.Roi.PresentationImage as IImageSopProvider;
                if (sop != null && SegmentationGraphicsHelpers.GraphicIsUsable(graphic))
                {
                    PolygonalRoiSegGraphic segGraphic =
                        SegmentationGraphicsHelpers.GraphicToISegGraphic(graphic);

                    if (segGraphic != null)
                    {
                        // Track all graphics by presentation image
                        if (!_existingSegGraphics.ContainsKey(presentationImage))
                            _existingSegGraphics.Add(presentationImage,
                                                     new Dictionary<int, PolygonalRoiSegGraphic>());
                        if (
                            !_existingSegGraphics[presentationImage].ContainsKey(
                                segGraphic.GraphicHashCode))
                        {
                            _existingSegGraphics[presentationImage].Add(segGraphic.GraphicHashCode,
                                                                        segGraphic);

                            Seg existingSeg = SegmentationTree.AllNewSegs.FirstOrDefault(
                                seg =>
                                seg.Label == segGraphic.Label &&
                                seg.ImageSeriesUid == sop.ImageSop.SeriesInstanceUid);

                            // Add the graphic to an existing Seg with that label and series
                            // else create a new a seg if none exists with that label and series
                            if (existingSeg != null)
                            {
                                existingSeg.SegGraphics.Add(segGraphic);
                            }
                            else
                            {
                                Seg newSeg = CreateNewSeg(segGraphic.Label, sop.ImageSop.SeriesInstanceUid);
                                newSeg.SegGraphics.Add(segGraphic);
                            }
                        }
                    }
                }
            }
        }

        private Seg CreateNewSeg(string label, string imageSeriesUid)
        {
            var seg = new Seg
                          {
                              Label = label,
                              ImageSeriesUid = imageSeriesUid,
                              AvailableCategories = DeepCopyAvailableCategories()
                          };

            if (SegmentationTree != null && SegmentationTree.WorkingSegmentationDocument != null)
                SegmentationTree.WorkingSegmentationDocument.Segs.Add(seg);

            return seg;
        }

        protected override void OnActiveImageViewerChanged(ActiveImageViewerChangedEventArgs e)
        {
            // Add update event handlers
            if (e.ActivatedImageViewer != null)
            {
                UpdateImageViewerEventSubscriptions(e.ActivatedImageViewer, true);
                UpdateCurrentSegmentationTree();
            }

            NotifyPropertyChanged("SegmentationTree");
            NotifyPropertyChanged("SegmentationModuleEnabled");
            NotifyPropertyChanged("CreateSegmentationEnabled");
            NotifyPropertyChanged("CalculationInfo");
            NotifyPropertyChanged("SelectedSegOpacity");
            NotifyPropertyChanged("SelectedSegGraphics");
        }

        protected override void OnActiveImageViewerChanging(ActiveImageViewerChangedEventArgs e)
        {
            // Remove update event handlers
            if (e.DeactivatedImageViewer != null)
            {
                UpdateImageViewerEventSubscriptions(e.DeactivatedImageViewer, false);
                if (SegmentationTree != null)
                    SegmentationTree.PropertyChanged -= SegmentationTreeOnPropertyChanged;
            }
        }

        private void UpdateCurrentSegmentationTree()
        {
            if (ImageViewer != null && SegmentationTrees != null)
            {
                string studyInstanceUid = String.Empty;
                string studyDescription = String.Empty;

                var sopProvider = ImageViewer.SelectedPresentationImage as ISopProvider;
                if (sopProvider != null)
                {
                    studyInstanceUid = sopProvider.Sop.StudyInstanceUid;
                    studyDescription = sopProvider.Sop.StudyDescription;
                }
                else if (ImageViewer.StudyTree != null &&
                         ImageViewer.StudyTree.Studies != null &&
                         ImageViewer.StudyTree.Studies.Any())
                {
                    studyInstanceUid = ImageViewer.StudyTree.Studies.First().StudyInstanceUid;
                    studyDescription = ImageViewer.StudyTree.Studies.First().StudyDescription;
                }

                if (!String.IsNullOrEmpty(studyInstanceUid))
                {
                    if (!SegmentationTrees.ContainsKey(ImageViewer))
                    {
                        var segmentationTree = new SegmentationTree
                                                   {
                                                       StudyInstanceUid = studyInstanceUid,
                                                       StudyDescription = studyDescription
                                                   };

                        segmentationTree.PropertyChanged += SegmentationTreeOnPropertyChanged;
                        var segmentationDocument = new SegmentationDocument
                                                       {
                                                           CreationDateTime = DateTime.Now,
                                                       };

                        segmentationTree.SegmentationDocuments.Add(segmentationDocument);
                        segmentationTree.WorkingSegmentationDocument = segmentationDocument;
                        SegmentationTrees.Add(ImageViewer, segmentationTree);

                        UpdateSegmentationTreeWithAllLoadedDocuments(ImageViewer);
                    }
                    else
                    {
                        SegmentationTrees[ImageViewer].PropertyChanged += SegmentationTreeOnPropertyChanged;
                    }
                    NotifyPropertyChanged("SegmentationTree");
                    NotifyPropertyChanged("SegmentationModuleEnabled");
                    NotifyPropertyChanged("CreateSegmentationEnabled");
                    NotifyPropertyChanged("CalculationInfo");
                    NotifyPropertyChanged("SelectedSegOpacity");
                    NotifyPropertyChanged("SelectedSegGraphics");
                }
            }
        }

        /// <summary>
        /// Changes event subscription on the given <see cref="IImageViewer"/>
        /// </summary>
        /// <param name="imageViewer">ImageViewer to add or remove events from</param>
        /// <param name="subscribe"><code>true</code> - add event subscription, <code>false</code> - remove event subscription</param>
        private void UpdateImageViewerEventSubscriptions(IImageViewer imageViewer, bool subscribe)
        {
            if (imageViewer != null)
            {
                if (subscribe)
                {
                    imageViewer.EventBroker.TileSelected += OnTileSelected;
                    imageViewer.EventBroker.MouseCaptureChanged += OnMouseCaptureChanged;
                    imageViewer.EventBroker.GraphicSelectionChanged += OnGraphicSelectionChanged;
                    imageViewer.EventBroker.PresentationImageSelected += OnPresentationImageSelected;
                }
                else
                {
                    imageViewer.EventBroker.TileSelected -= OnTileSelected;
                    imageViewer.EventBroker.MouseCaptureChanged -= OnMouseCaptureChanged;
                    imageViewer.EventBroker.GraphicSelectionChanged -= OnGraphicSelectionChanged;
                    imageViewer.EventBroker.PresentationImageSelected -= OnPresentationImageSelected;
                }
            }
        }

        private void OverlayGraphicsOnItemAdded(object sender, ListEventArgs<IGraphic> listEventArgs)
        {
            var roiGraphic = listEventArgs.Item as RoiGraphic;
            if (roiGraphic != null)
            {
                roiGraphic.NameChanged += RoiGraphicOnNameChanged;
            }
        }

        private void OverlayGraphicsOnItemRemoved(object sender, ListEventArgs<IGraphic> listEventArgs)
        {
            var roiGraphic = listEventArgs.Item as RoiGraphic;
            if (roiGraphic != null)
            {
                roiGraphic.NameChanged -= RoiGraphicOnNameChanged;
            }
        }

        private void RoiGraphicOnNameChanged(object sender, EventArgs eventArgs)
        {
            UpdateSegmentationGraphics();
        }

        private void SubscribeToOverlayGraphics()
        {
            IPresentationImage presentationImage = ImageViewer == null ? null : ImageViewer.SelectedPresentationImage;
            if (_lastSelectedPresentationImage == presentationImage)
                return;

            DoSubscribeToOverlayGraphics(_lastSelectedPresentationImage as IOverlayGraphicsProvider, false);
            DoSubscribeToOverlayGraphics(presentationImage as IOverlayGraphicsProvider, true);
            _lastSelectedPresentationImage = presentationImage;
        }

        private void DoSubscribeToOverlayGraphics(IOverlayGraphicsProvider graphicsProvider, bool subscribe)
        {
            if (graphicsProvider != null)
            {
                if (subscribe)
                {
                    graphicsProvider.OverlayGraphics.ItemAdded += OverlayGraphicsOnItemAdded;
                    graphicsProvider.OverlayGraphics.ItemRemoved += OverlayGraphicsOnItemRemoved;
                }
                else
                {
                    graphicsProvider.OverlayGraphics.ItemAdded -= OverlayGraphicsOnItemAdded;
                    graphicsProvider.OverlayGraphics.ItemRemoved -= OverlayGraphicsOnItemRemoved;
                }
            }
        }

        protected void OnPresentationImageSelected(object sender, PresentationImageSelectedEventArgs e)
        {
            UpdateSegmentationGraphics();

            SubscribeToOverlayGraphics();

            //NotifyPropertyChanged("SegmentationModuleEnabled");
            NotifyPropertyChanged("CreateSegmentationEnabled");
            NotifyPropertyChanged("CalculationInfo");
        }

        private void OnTileSelected(object sender, TileSelectedEventArgs e)
        {
            // NOTE: When PresentationImage is present, markup will be updated in the OnPresentationImageSelected event
            if (e.SelectedTile.PresentationImage == null)
                UpdateSegmentationGraphics();
            NotifyPropertyChanged("SegmentationModuleEnabled");
            NotifyPropertyChanged("CreateSegmentationEnabled");
            NotifyPropertyChanged("CalculationInfo");
        }

        private void OnMouseCaptureChanged(object sender, MouseCaptureChangedEventArgs e)
        {
            UpdateSegmentationGraphics();
            NotifyPropertyChanged("CreateSegmentationEnabled");
            NotifyPropertyChanged("CalculationInfo");
        }

        private void OnGraphicSelectionChanged(object sender, GraphicSelectionChangedEventArgs e)
        {
            UpdateSegmentationGraphics();
            NotifyPropertyChanged("SegmentationModuleEnabled");
            NotifyPropertyChanged("CreateSegmentationEnabled");
            //NotifyPropertyChanged("CalculationInfo");
        }

        /// <summary>
        /// Called by the host to initialize the application component.
        /// </summary>
        public override void Start()
        {
            base.Start();

            // TODO VK: reinitialize when the settings change?
            AvailableCategories = new ConfigurationFileReader().ReadConfigurationFile();

            UpdateCurrentSegmentationTree();

            if (SegmentationTree != null)
            {
                FindAllMarkup();

                if (SegmentationTree.AllNewSegs != null && SegmentationTree.AllNewSegs.Count > 0)
                {
                    Seg lastNewSeg = SegmentationTree.AllNewSegs.Last();
                    if (lastNewSeg != null)
                        SegmentationTree.SelectedSeg = lastNewSeg;
                }
            }

            SubscribeToOverlayGraphics();
        }

        private List<Category> DeepCopyAvailableCategories()
        {
            XmlObjectSerializer serializer = new DataContractSerializer(typeof (List<Category>));
            List<Category> categories = null;
            try
            {
                using (var stream = new MemoryStream())
                {
                    serializer.WriteObject(stream, AvailableCategories);
                    stream.Flush();
                    stream.Position = 0;
                    categories = ((List<Category>) serializer.ReadObject(stream));
                }
            }
            catch (Exception ex)
            {
                Platform.Log(LogLevel.Error, ex, "Failed to copy segmentation categories");
            }


            return categories;
        }

        /// <summary>
        /// Called by the host when the application component is being terminated.
        /// </summary>
        public override void Stop()
        {
            UpdateImageViewerEventSubscriptions(ImageViewer, false);
            if (SegmentationTree != null)
            {
                SegmentationTree.PropertyChanged -= SegmentationTreeOnPropertyChanged;
            }

            if (_lastSelectedSegmentationTree != null)
            {
                _lastSelectedSegmentationTree.PropertyChanged -= LastSelectedSegmentationTreeOnPropertyChanged;
                _lastSelectedSegmentationTree = null;
            }

            // Cancel last overlay graphics event subscription
            DoSubscribeToOverlayGraphics(_lastSelectedPresentationImage as IOverlayGraphicsProvider, false);
            _lastSelectedPresentationImage = null;

            base.Stop();
        }


        private void UpdateSegmentationGraphics()
        {
            if (SegmentationTree != null)
            {
                if (ImageViewer != null)
                {
                    CheckPresentationImageForGraphicsChanges(ImageViewer.SelectedPresentationImage);
                }
            }
        }
    }
}
