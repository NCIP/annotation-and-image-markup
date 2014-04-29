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
using System.Linq;
using System.Text;
using System.Threading;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Dicom.ServiceModel.Query;
using ClearCanvas.Dicom.Utilities;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;
using ClearCanvas.ImageViewer.Common;
using ClearCanvas.ImageViewer.Common.StudyManagement;
using ClearCanvas.ImageViewer.Common.WorkItem;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.StudyManagement;
using Segmentation.Graphics;
using Segmentation.Tree;

namespace Segmentation
{
    [MenuAction("show", "global-menus/MenuSegmentation/SegmentationMenu", "Show")]
    [ButtonAction("show", BUTTON_ACTION_PATH, "Show")]
    [Tooltip("show", "SegmentationTooltip")]
    [IconSet("show", "Icons.SegmentationToolSmall.png", "Icons.SegmentationToolMedium.png",
        "Icons.SegmentationToolLarge.png")]
    [EnabledStateObserver("show", "Enabled", "EnabledChanged")]
    [ExtensionOf(typeof (ImageViewerToolExtensionPoint))]
    public class SegmentationTool : ImageViewerTool
    {
        private const string BUTTON_ACTION_PATH = "global-toolbars/ToolbarStandard/SegmentationButton";

        // List of created shelves
        private static readonly Dictionary<IDesktopWindow, IShelf> _shelves = new Dictionary<IDesktopWindow, IShelf>();
        private readonly ActionResourceResolver _resolver;

        private readonly Dictionary<string, SegmentationMenuInfo> _segmentationMenuInfos =
            new Dictionary<string, SegmentationMenuInfo>();

        private IDesktopWindow _desktopWindow;

        private IWorkItemActivityMonitor _workItemActivityMonitor;

        /// <summary>
        /// Default constructor.
        /// </summary>
        /// <remarks>
        /// A no-args constructor is required by the framework.  Do not remove.
        /// </remarks>
        public SegmentationTool()
        {
            _desktopWindow = null;
            _resolver = new ActionResourceResolver(this);
        }

        public override IActionSet Actions
        {
            get
            {
                int i = 0;
                var actions = new List<IAction>();
                foreach (SegmentationMenuInfo info in _segmentationMenuInfos.Values)
                {
                    var segmentationActionContainer = new SegmentationActionContainer(this, info, i);
                    actions.Add(segmentationActionContainer.Action);
                    i++;
                }
                return new ActionSet(actions).Union(base.Actions);
            }
            protected set { base.Actions = value; }
        }

        /// <summary>
        /// Called by the framework to initialize this tool.
        /// </summary>
        public override void Initialize()
        {
            base.Initialize();

            ImageViewer.EventBroker.DisplaySetChanged += OnDisplaySetChanged;
            ImageViewer.EventBroker.LayoutCompleted += OnLayoutComplete;

            if (WorkItemActivityMonitor.IsSupported)
            {
                _workItemActivityMonitor = WorkItemActivityMonitor.Create();
                _workItemActivityMonitor.WorkItemsChanged += OnWorkItemsChanged;
            }
        }

        /// <summary>
        /// Called when the tool is disposed.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                // TODO - Auto-save new annotations here?

                ImageViewer.EventBroker.DisplaySetChanged -= OnDisplaySetChanged;
                ImageViewer.EventBroker.LayoutCompleted -= OnLayoutComplete;

                if (_workItemActivityMonitor != null)
                {
                    _workItemActivityMonitor.WorkItemsChanged -= OnWorkItemsChanged;
                    _workItemActivityMonitor.Dispose();
                    _workItemActivityMonitor = null;
                }
            }

            base.Dispose(disposing);
        }

        private SegmentationComponent GetActiveComponent()
        {
            if (_shelves.ContainsKey(Context.DesktopWindow))
                return _shelves[Context.DesktopWindow].Component as SegmentationComponent;
            return null;
        }

        public void Show()
        {
            // check if a layout component is already displayed
            if (_shelves.ContainsKey(Context.DesktopWindow))
            {
                _shelves[Context.DesktopWindow].Activate();
            }
            else
            {
                BlockingOperation.Run(delegate
                                          {
                                              _desktopWindow = Context.DesktopWindow;

                                              var component =
                                                  new SegmentationComponent(Context.DesktopWindow);

                                              IShelf shelf = ApplicationComponent.LaunchAsShelf(
                                                  _desktopWindow,
                                                  component,
                                                  SR.SegmentationTitle,
                                                  "DICOM Segmentation",
                                                  ShelfDisplayHint.DockRight | ShelfDisplayHint.DockAutoHide);

                                              shelf.Closed += OnShelfClosed;
                                              _shelves[_desktopWindow] = shelf;
                                          });
            }
        }

        private void OnShelfClosed(object sender, ClosedEventArgs e)
        {
            // We need to cache the owner DesktopWindow (_desktopWindow) because this tool is an 
            // ImageViewer tool, disposed when the viewer component is disposed.  Shelves, however,
            // exist at the DesktopWindow level and there can only be one of each type of shelf
            // open at the same time per DesktopWindow (otherwise things look funny).  Because of 
            // this, we need to allow this event handling method to be called after this tool has
            // already been disposed (e.g. viewer workspace closed), which is why we store the 
            // _desktopWindow variable.

            _shelves[_desktopWindow].Closed -= OnShelfClosed;
            _shelves.Remove(_desktopWindow);
            _desktopWindow = null;
        }

        private void OnDisplaySetChanged(object sender, DisplaySetChangedEventArgs e)
        {
            if (e.NewDisplaySet != null && e.NewDisplaySet.Visible)
            {
                var studyToSeriesAndInstanceDictionary = new Dictionary<string, Dictionary<string, IImageSopProvider>>();
                foreach (
                    IImageSopProvider imageSopPrivider in
                        e.NewDisplaySet.PresentationImages.OfType<IImageSopProvider>().Where(
                            imageSopPrivider => imageSopPrivider != null))
                {
                    if (imageSopPrivider != null)
                    {
                        string studyInstanceUid = imageSopPrivider.ImageSop.StudyInstanceUid;
                        string seriesInstanceUid = imageSopPrivider.ImageSop.SeriesInstanceUid;

                        Dictionary<string, IImageSopProvider> seriesToSopInstanceDict;
                        if (studyToSeriesAndInstanceDictionary.ContainsKey(studyInstanceUid))
                        {
                            seriesToSopInstanceDict = studyToSeriesAndInstanceDictionary[studyInstanceUid];
                        }
                        else
                        {
                            seriesToSopInstanceDict = new Dictionary<string, IImageSopProvider>();
                            studyToSeriesAndInstanceDictionary[studyInstanceUid] = seriesToSopInstanceDict;
                        }

                        // Store one SOP Instance for each series
                        if (!seriesToSopInstanceDict.ContainsKey(seriesInstanceUid))
                            seriesToSopInstanceDict[seriesInstanceUid] = imageSopPrivider;
                    }
                }

                bool updateComponent = false;
                foreach (string studyInstanceUid in studyToSeriesAndInstanceDictionary.Keys)
                {
                    List<Sop> segmentationSopInstances = LoadSegmentationSopsForStudy(studyInstanceUid);
                    if (segmentationSopInstances != null)
                    {
                        foreach (Sop segSop in segmentationSopInstances)
                        {
                            SegmentationDocument segmentationDocument =
                                new SegmentationDeserializer(segSop).DeserializeSegmenationDocument();
                            if (segmentationDocument != null &&
                                !SegmentationGraphicsHelpers.IsSegmentationDocumentGraphicLoaded(segmentationDocument,
                                                                                                 e.NewDisplaySet))
                            {
                                foreach (Seg seg in segmentationDocument.Segs)
                                {
                                    IPresentationImage segPresentationImage = null;
                                    if (seg.ImageSeriesUid == null)
                                    {
                                        if (seg.SegmentImageData != null &&
                                            seg.SegmentImageData.SegmentFrameData != null &&
                                            seg.SegmentImageData.SegmentFrameData.Count > 0)
                                        {
                                            segPresentationImage = SegmentationGraphicsHelpers.
                                                PresentationImageFromPositionOrientation(
                                                    seg.SegmentImageData.SegmentFrameData[0].ImagePositionPatient,
                                                    seg.SegmentImageData.SegmentFrameData[0].ImageOrientationPatient,
                                                    e.NewDisplaySet,
                                                    seg.SegmentImageData.FrameOfReferenceUid);

                                            //var sop = segPresentationImage as IImageSopProvider;
                                            //if (sop != null)
                                            //{
                                            //    seg.ImageSeriesUid = sop.Frame.SeriesInstanceUid;
                                            //}
                                        }
                                    }
                                    else if (
                                        studyToSeriesAndInstanceDictionary[studyInstanceUid].ContainsKey(
                                            seg.ImageSeriesUid))
                                    {
                                        segPresentationImage =
                                            studyToSeriesAndInstanceDictionary[studyInstanceUid][seg.ImageSeriesUid] as
                                            IPresentationImage;
                                    }
                                    if (segPresentationImage == null)
                                    {
                                        Platform.Log(LogLevel.Info,
                                                     "Failed to find a series and image to display a segmentation frame on (SOP Instance UID={0}, Label = {1})",
                                                     segmentationDocument.SopInstanceUid, seg.Label);
                                    }
                                    else
                                    {
                                        SegmentationGraphicsHelpers.CreateSeriesGraphicsForSeg(
                                            segPresentationImage, seg, segmentationDocument,
                                            segSop.DataSource as IDicomMessageSopDataSource);
                                        updateComponent = true;
                                    }

                                    var sopProvider = segPresentationImage as ISopProvider;
                                    if (sopProvider != null)
                                        AddSegmentationMenuInfo(segmentationDocument, seg, sopProvider.Sop);
                                }
                            }
                        }
                    }
                }

                // Update component if new graphics is loaded
                if (updateComponent)
                    UpdateSegmentationTreeInComponent();
            }
        }

        private List<Sop> LoadSegmentationSopsForStudy(string studyInstanceUid)
        {
            const string segmentationModality = "SEG";

            Study study = ImageViewer.StudyTree.GetStudy(studyInstanceUid);
            if (study != null && study.ModalitiesInStudy.Any(modality => modality == segmentationModality))
            {
                IEnumerable<Series> segSeries = study.Series.Where(series => series.Modality == segmentationModality);
                var sops = new List<Sop>();
                foreach (Series series in segSeries)
                    sops.AddRange(series.Sops);

                return sops;
            }

            return null;
        }

        private void OnLayoutComplete(object sender, EventArgs e)
        {
            // There may be studies with no series displayed. We need to load segmentation data
            // for those studies in order to have a complete SEG list in the right-click menu.
            foreach (var currentStudy in ImageViewer.StudyTree.Studies.Select(study => study.StudyInstanceUid))
            {
                if (_segmentationMenuInfos.Values.All(menuInfo => menuInfo.StudyInstanceUid != currentStudy))
                {
                    List<Sop> studySegSops = LoadSegmentationSopsForStudy(currentStudy);
                    if (studySegSops != null)
                    {
                        foreach (Sop segSop in studySegSops)
                        {
                            SegmentationDocument segmentationDocument =
                                new SegmentationDeserializer(segSop).DeserializeSegmenationDocument();
                            if (segmentationDocument != null)
                            {
                                foreach (Seg seg in segmentationDocument.Segs)
                                    AddSegmentationMenuInfo(segmentationDocument, seg, segSop);
                            }
                        }
                    }
                }
            }
        }

        private void OnWorkItemsChanged(object sender, WorkItemsChangedEventArgs e)
        {
            if (e.EventType != WorkItemsChangedEventType.Update || e.ChangedItems == null || !e.ChangedItems.Any())
                return; // We are only interested in Update events

            var studiesWithAddedInstances = new HashSet<string>();
            foreach (WorkItemData workItemData in e.ChangedItems)
            {
                if (workItemData.Type == "ProcessStudy")
                {
                    if (workItemData.Status == WorkItemStatusEnum.Idle ||
                        workItemData.Status == WorkItemStatusEnum.Complete ||
                        workItemData.Status == WorkItemStatusEnum.Deleted)
                    {
                        if (workItemData.Status == WorkItemStatusEnum.Idle)
                        {
                            // NOTE: new SOPs are already available when Idle status kicked in

                            if (!string.IsNullOrEmpty(workItemData.StudyInstanceUid))
                                studiesWithAddedInstances.Add(workItemData.StudyInstanceUid);
                        }
                    }
                }
                else if (workItemData.Type == "DeleteSeries")
                {
                    // TODO: remove graphics if the Segmentation instance is deleted?
                    //if (workItemData.Status == WorkItemStatusEnum.Complete)
                    //{
                    //}
                }
            }

            if (studiesWithAddedInstances.Any())
            {
                // Load new segmentations asynchronously
                SynchronizationContext.Current.Post((state => LoadNewSeries(studiesWithAddedInstances.ToList())), null);
            }
        }

        private void LoadNewSeries(List<string> changedStudyInstanceUids)
        {
            const string segmentationModality = "SEG";

            foreach (string studyInstanceUid in changedStudyInstanceUids)
            {
                Study loadedStudy = ImageViewer.StudyTree.GetStudy(studyInstanceUid);
                if (loadedStudy == null)
                    continue; // the given study is not loaded in this ImageViewer

                // Query for new segmentation SOP Instances for the given study
                var seriesIdentifier = new SeriesIdentifier
                                           {
                                               StudyInstanceUid = studyInstanceUid,
                                               Modality = segmentationModality
                                           };
                var seriesEntryRequest = new GetSeriesEntriesRequest
                                             {Criteria = new SeriesEntry {Series = seriesIdentifier}};

                List<SeriesEntry> entries = null;
                Platform.GetService<IStudyStoreQuery>(
                    s =>
                    entries =
                    s.GetSeriesEntries(seriesEntryRequest)
                        .SeriesEntries.Where(
                            entry =>
                            loadedStudy.Series.All(series => series.SeriesInstanceUid != entry.Series.SeriesInstanceUid))
                        .ToList());

                // Get all unique AE Titles for the study. Can study have more than one?
                // We only need to query each AETitle once, or there will be duplicates/errors.
                List<IDicomServiceNode> studyAes =
                    (from seriesEntry in entries where seriesEntry != null select seriesEntry.Series.RetrieveAE).GroupBy
                        (
                            ae => ae.AETitle).Select(ae1 => ae1.First()).OfType<IDicomServiceNode>().ToList();

                if (!studyAes.Any())
                    continue;

                var reallyUpdatedStudies = new HashSet<string>();
                foreach (IDicomServiceNode studyAe in studyAes)
                {
                    IStudyLoader studyLoader;
                    try
                    {
                        studyLoader = studyAe.GetService<IStudyLoader>();
                    }
                    catch (Exception ex)
                    {
                        //Platform.Log(LogLevel.Error, ex, "Cannot get study loader", studyAe);
                        throw new Exception("Cannot get study loader", ex);
                    }

                    int numberOfSops =
                        studyLoader.Start(new StudyLoaderArgs(studyInstanceUid, null, new StudyLoaderOptions(true)));

                    // Load new segmentation SOP Instances
                    if (numberOfSops > 0)
                    {
                        for (int i = 0; i < numberOfSops; i++)
                        {
                            Sop sop = studyLoader.LoadNextSop();
                            if (sop != null && sop.Modality == segmentationModality)
                            {
                                try
                                {
                                    if (ImageViewer.StudyTree.AddSop(sop))
                                    {
                                        SegmentationDocument segmentationDocument =
                                            new SegmentationDeserializer(sop).DeserializeSegmenationDocument();
                                        if (segmentationDocument != null)
                                        {
                                            foreach (Seg seg in segmentationDocument.Segs)
                                            {
                                                IPresentationImage segPresentationImage = null;
                                                if (seg.ImageSeriesUid == null)
                                                {
                                                    if (seg.SegmentImageData != null &&
                                                        seg.SegmentImageData.SegmentFrameData != null &&
                                                        seg.SegmentImageData.SegmentFrameData.Count > 0)
                                                    {
                                                        foreach (
                                                            IImageBox imageBox in
                                                                ImageViewer.PhysicalWorkspace.ImageBoxes.Where(
                                                                    imageBox => imageBox != null))
                                                        {
                                                            if (imageBox.DisplaySet != null)
                                                            {
                                                                segPresentationImage = SegmentationGraphicsHelpers.
                                                                    PresentationImageFromPositionOrientation(
                                                                        seg.SegmentImageData.SegmentFrameData[0].
                                                                            ImagePositionPatient,
                                                                        seg.SegmentImageData.SegmentFrameData[0].
                                                                            ImageOrientationPatient,
                                                                        imageBox.DisplaySet,
                                                                        seg.SegmentImageData.FrameOfReferenceUid);
                                                            }
                                                            if (segPresentationImage != null)
                                                                break;
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    segPresentationImage =
                                                        GetFirstPresentationImageForSeries(sop.StudyInstanceUid,
                                                                                           seg.ImageSeriesUid);
                                                }
                                                if (segPresentationImage == null)
                                                {
                                                    Platform.Log(LogLevel.Info,
                                                                 "Failed to find a series and image to display a segmentation frame on (SOP Instance UID={0}, Label = {1}) (New)",
                                                                 segmentationDocument.SopInstanceUid, seg.Label);
                                                }
                                                else
                                                {
                                                    SegmentationGraphicsHelpers.CreateSeriesGraphicsForSeg(
                                                        segPresentationImage, seg, segmentationDocument,
                                                        sop.DataSource as IDicomMessageSopDataSource);
                                                    reallyUpdatedStudies.Add(studyInstanceUid);
                                                }

                                                var sopProvider = segPresentationImage as ISopProvider;
                                                if (sopProvider != null)
                                                    AddSegmentationMenuInfo(segmentationDocument, seg, sopProvider.Sop);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        sop.Dispose();
                                    }
                                }
                                catch (SopValidationException ex)
                                {
                                    Platform.Log(LogLevel.Error, ex,
                                                 "Failed to add newly loaded Segmentation SOP  to the StudyTree (studyInstanceUid={0}; SOPInstaceUID={1})",
                                                 sop.StudyInstanceUid, sop.SopInstanceUid);
                                    sop.Dispose();
                                }
                            }
                            else
                            {
                                sop.Dispose();
                            }
                        }
                    }
                }

                // Update component, if present
                if (reallyUpdatedStudies.Count > 0)
                    UpdateSegmentationTreeInComponent();
            }
        }

        private void AddSegmentationMenuInfo(SegmentationDocument segmentationDocument, Seg seg, Sop sop)
        {
            if (
                !_segmentationMenuInfos.ContainsKey(
                    segmentationDocument.SopInstanceUid + seg.SegmentationNumber))
            {
                SegmentationMenuInfo info =
                    MenuInfoFromDocumentAndSeg(segmentationDocument, seg, sop);
                if (info != null)
                    _segmentationMenuInfos.Add(
                        segmentationDocument.SopInstanceUid + seg.SegmentationNumber,
                        info);
            }
        }

        private SegmentationMenuInfo MenuInfoFromDocumentAndSeg(SegmentationDocument segmentationDocument, Seg seg, Sop sop)
        {
            if (seg.SegmentImageData != null &&
                seg.SegmentImageData.SegmentFrameData != null &&
                seg.SegmentImageData.SegmentFrameData.Count > 0)
            {
                return new SegmentationMenuInfo
                           {
                               DisplayLabel = seg.DisplayLabel,
                               DisplayImageSeriesUid = seg.ImageSeriesUid,
                               SegmentationNumber = seg.SegmentationNumber,
                               SegmentationDocumentUid = segmentationDocument.SopInstanceUid,
                               SeriesNumber = segmentationDocument.SeriesNumber,
                               ImagePositionPatient = seg.SegmentImageData.SegmentFrameData[0].ImagePositionPatient,
                               ImageOrientationPatient =
                                   seg.SegmentImageData.SegmentFrameData[0].ImageOrientationPatient,
                               FrameOfReferenceUid = seg.SegmentImageData.FrameOfReferenceUid,
                               PatientId = sop.PatientId,
                               PatientsName = sop.PatientsName,
                               StudyAccessionNumber = sop.AccessionNumber,
                               StudyDate = sop.StudyDate,
                               StudyTime = sop.StudyTime,
                               StudyDescription = sop.StudyDescription,
                               StudyInstanceUid = sop.StudyInstanceUid
                           };
            }

            return null;
        }

        private IPresentationImage GetFirstPresentationImageForSeries(string studyInstanceUid, string seriesInstanceUid)
        {
            return (from imageBox in ImageViewer.PhysicalWorkspace.ImageBoxes.Where(imageBox => imageBox!= null)
                    from image in imageBox.DisplaySet.PresentationImages
                    let imageSop = image as IImageSopProvider
                    where
                        imageSop != null && imageSop.Frame.StudyInstanceUid == studyInstanceUid &&
                        imageSop.Frame.SeriesInstanceUid == seriesInstanceUid
                    select image).FirstOrDefault();
        }

        private void UpdateSegmentationTreeInComponent()
        {
            IDesktopWindow desktopWindow = ImageViewer.DesktopWindow;
            if (desktopWindow != null && _shelves.ContainsKey(desktopWindow))
            {
                var component = _shelves[desktopWindow].Component as SegmentationComponent;
                if (component != null)
                    component.UpdateSegmentationTreeWithAllLoadedDocuments(ImageViewer);
            }
        }

        /// <summary>
        /// Checks whether the specified series is loaded into the current ImageViewer.
        /// If not loaded, the method will load the series into the currently selected ImageBox.
        /// </summary>
        /// <param name="seriesInstanceUid">Series Instance UID to validate</param>
        /// <param name="imagePositionPatient">Image Position Patient from an image in the series</param>
        /// <param name="imageOrientationPatient">Image Orientation Patient from an image in the series</param>
        /// <param name="frameOfReferenceUid">Frame of Reference UID of the given series</param>
        /// <returns><value>true</value> is series now loaded, or <value>false</value> if no matching
        /// series could be found or loaded</returns>
        /// <remarks>Either <paramref name="seriesInstanceUid"/> or <paramref name="imagePositionPatient"/> and
        ///  <paramref name="imageOrientationPatient"/> must be not null</remarks>
        private bool EnsureSeriesIsLoaded(string seriesInstanceUid, double[] imagePositionPatient,
                                          double[] imageOrientationPatient, string frameOfReferenceUid)
        {
            if (string.IsNullOrEmpty(seriesInstanceUid) &&
                (imagePositionPatient == null || imageOrientationPatient == null))
                return false;

            bool isLoaded = false;

            foreach (IImageBox imageBox in ImageViewer.PhysicalWorkspace.ImageBoxes.Where(
                imageBox =>
                imageBox != null && imageBox.DisplaySet != null && imageBox.DisplaySet.PresentationImages != null))
            {
                if (string.IsNullOrEmpty(seriesInstanceUid))
                {
                    IPresentationImage segPresentationImage = SegmentationGraphicsHelpers.
                        PresentationImageFromPositionOrientation(
                            imagePositionPatient,
                            imageOrientationPatient,
                            imageBox.DisplaySet,
                            frameOfReferenceUid);
                    if (segPresentationImage != null)
                    {
                        isLoaded = true;
                        break;
                    }
                }
                else
                {
                    IImageSopProvider imageSopProvider =
                        imageBox.DisplaySet.PresentationImages.OfType<IImageSopProvider>().FirstOrDefault();
                    if (imageSopProvider != null && imageSopProvider.Frame.SeriesInstanceUid == seriesInstanceUid)
                    {
                        isLoaded = true;
                        break;
                    }
                }
            }
            if (!isLoaded)
            {
                IImageBox targetImageBox = ImageViewer.PhysicalWorkspace.SelectedImageBox ??
                                           (ImageViewer.PhysicalWorkspace.ImageBoxes.Count > 0
                                                ? ImageViewer.PhysicalWorkspace.ImageBoxes[0]
                                                : null);
                if (targetImageBox == null)
                {
                    Platform.Log(LogLevel.Error, "Failed to find an ImageBox in which to load segmentation's series.");
                }
                else
                {
                    foreach (IImageSet imageSet in ImageViewer.LogicalWorkspace.ImageSets.Where(
                        imageSet => imageSet != null && imageSet.DisplaySets != null))
                    {
                        foreach (IDisplaySet displaySet in imageSet.DisplaySets.Where(
                            displaySet => displaySet != null && displaySet.PresentationImages != null))
                        {
                            if (string.IsNullOrEmpty(seriesInstanceUid))
                            {
                                IPresentationImage segPresentationImage = SegmentationGraphicsHelpers.
                                    PresentationImageFromPositionOrientation(
                                        imagePositionPatient,
                                        imageOrientationPatient,
                                        displaySet,
                                        frameOfReferenceUid);
                                if (segPresentationImage != null)
                                {
                                    IDisplaySet targetDisplaySet = displaySet.CreateFreshCopy();
                                    targetImageBox.DisplaySet = targetDisplaySet;
                                    // TODO - verify whether any of the Selected properties need re-setting
                                    isLoaded = true;
                                    break;
                                }
                            }
                            else
                            {
                                IImageSopProvider imageSopProvider =
                                    displaySet.PresentationImages.OfType<IImageSopProvider>().FirstOrDefault();
                                if (imageSopProvider != null &&
                                    imageSopProvider.Frame.SeriesInstanceUid == seriesInstanceUid)
                                {
                                    IDisplaySet targetDisplaySet = displaySet.CreateFreshCopy();
                                    targetImageBox.DisplaySet = targetDisplaySet;
                                    // TODO - verify whether any of the Selected properties need re-setting
                                    isLoaded = true;
                                    break;
                                }
                            }
                        }
                        if (isLoaded)
                            break;
                    }
                }
            }

            return isLoaded;
        }

        internal static IEnumerable<SegFrameImageGraphic> GetSegmentationImageGraphicsFromSeg(IImageViewer imageViewer,
                                                                                              Seg seg)
        {
            var segGraphics = new List<SegFrameImageGraphic>();
            foreach (IImageBox imageBox in imageViewer.PhysicalWorkspace.ImageBoxes)
            {
                if (imageBox != null && imageBox.DisplaySet != null)
                {
                    foreach (IPresentationImage presentationImage in imageBox.DisplaySet.PresentationImages)
                    {
                        var graphicsProvider = presentationImage as IOverlayGraphicsProvider;

                        if (graphicsProvider != null)
                        {
                            segGraphics.AddRange(graphicsProvider.OverlayGraphics.OfType<SegFrameImageGraphic>().Where(
                                segGraphic =>
                                segGraphic.SegmentationDocumentReference.SegmentationDocument.Segs.Contains(seg)).Where(
                                    segGraphic =>
                                    segGraphic.SegmentationDocumentReference.SegmentNumber == seg.SegmentationNumber));
                        }
                    }
                }
            }
            return segGraphics;
        }

        internal static IEnumerable<ISegGraphic> GetAllSegmentationGraphicsFromSeg(IImageViewer imageViewer, Seg seg)
        {
            var graphics = new List<ISegGraphic>();
            graphics.AddRange(seg.SegGraphics);
            graphics.AddRange(GetSegmentationImageGraphicsFromSeg(imageViewer, seg));
            return graphics;
        }

        #region Nested type: SegmentationActionContainer

        private class SegmentationActionContainer
        {
            private readonly MenuAction _action;
            private readonly SegmentationMenuInfo _info;
            private readonly SegmentationTool _ownerTool;

            public SegmentationActionContainer(SegmentationTool ownerTool, SegmentationMenuInfo info, int index)
            {
                _ownerTool = ownerTool;
                _info = info;

                StringBuilder pathStringBuilder = new StringBuilder();
                pathStringBuilder.AppendFormat("{0}/", ImageViewerComponent.ContextMenuSite);
                // Multiple patients
                if (_ownerTool.Context.Viewer.StudyTree.Studies.Any(study => study.ParentPatient.PatientId != info.PatientId))
                {
                    pathStringBuilder.AppendFormat("{0} · {1}/", info.PatientsName, info.PatientId);
                }
                // Multiple Studies
                if (_ownerTool.Context.Viewer.StudyTree.Studies.Any(study => study.StudyInstanceUid != info.StudyInstanceUid))
                {
                    // We are trying to replicate what ImageSetDescriptior.GetName() does here:
                    string modalitiesInStudy = StringUtilities.Combine(CollectionUtils.Sort(
                        _ownerTool.Context.Viewer.StudyTree.Studies.First(
                        study => study.StudyInstanceUid == info.StudyInstanceUid).ModalitiesInStudy), ", ");

                    DateTime studyDate;
                    DateParser.Parse(info.StudyDate, out studyDate);
                    DateTime studyTime;
                    TimeParser.Parse(info.StudyTime, out studyTime);

                    pathStringBuilder.AppendFormat("{0} {1}", studyDate.ToString(Format.DateFormat), studyTime.ToString(Format.TimeFormat));
                    if (!string.IsNullOrEmpty(info.StudyAccessionNumber))
                        pathStringBuilder.AppendFormat(", A#: {0}", info.StudyAccessionNumber);
                    pathStringBuilder.AppendFormat(", [{0}] {1}/", modalitiesInStudy ?? "", info.StudyDescription);
                }
                pathStringBuilder.AppendFormat("SEG{0}", index);

                string actionId = String.Format("{0}:apply{1}", typeof (SegmentationTool).FullName, index);
                var actionPath = new ActionPath(pathStringBuilder.ToString(), _ownerTool._resolver);
                _action = new MenuAction(actionId, actionPath, ClickActionFlags.None, _ownerTool._resolver);
                _action.GroupHint = new GroupHint("DisplaySets");

                _action.Label = String.Format("{0} SEG: {1}", _info.SeriesNumber, _info.DisplayLabel);
                _action.SetClickHandler(Apply);
            }

            public ClickAction Action
            {
                get { return _action; }
            }

            private void Apply()
            {
                _ownerTool.Show();
                SegmentationComponent component = _ownerTool.GetActiveComponent();
                if (component != null)
                {
                    bool isLoaded = _ownerTool.EnsureSeriesIsLoaded(_info.DisplayImageSeriesUid,
                                                                    _info.ImagePositionPatient,
                                                                    _info.ImageOrientationPatient,
                                                                    _info.FrameOfReferenceUid);
                    if (isLoaded)
                    {
                        Seg seg = component.SegFromDocumentUidAndSegNumber(_info.SegmentationDocumentUid,
                                                                           _info.SegmentationNumber);
                        if (seg != null)
                        {
                            component.SegmentationTree.SelectedSeg = seg;
                            component.ShowImageContainingSeg(seg);
                        }
                    }
                }
            }
        }

        #endregion

        #region Nested type: SegmentationMenuInfo

        private class SegmentationMenuInfo
        {
            public string DisplayLabel { get; set; }
            public string DisplayImageSeriesUid { get; set; }
            public string SegmentationDocumentUid { get; set; }
            public int SegmentationNumber { get; set; }
            public int SeriesNumber { get; set; }
            public double[] ImagePositionPatient { get; set; }
            public double[] ImageOrientationPatient { get; set; }
            public string FrameOfReferenceUid { get; set; }
            public string PatientsName { get; set; }
            public string PatientId { get; set; }
            public string StudyAccessionNumber { get; set; }
            public string StudyDate { get; set; }
            public string StudyTime { get; set; }
            public string StudyDescription { get; set; }
            public string StudyInstanceUid { get; set; }
        }

        #endregion
    }
}
