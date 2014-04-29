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
using System.IO;
using AIM.Annotation;
using AIM.Annotation.AimManager;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.Dicom;
using Path = System.IO.Path;

namespace AimDataService
{
    [MenuAction("apply", AimDataServiceExplorer.ToolbarSite + "/MenuRetrieveAnnotation", "Apply")]
    [ButtonAction("apply", AimDataServiceExplorer.MenuSite + "/ToolRetrieveAnnotation", "Apply")]
    [Tooltip("apply", "Retrieve Selected Annotation")]
    [IconSet("apply", IconScheme.Colour, "Icons.AIMRetrieveToolSmall.png", "Icons.AIMRetrieveToolMedium.png",
        "Icons.AIMRetrieveToolLarge.png")]
    [GroupHint("apply", "Tool.SearchComponent.AimRetrieve.Retrieve")]
    [EnabledStateObserver("apply", "Enabled", "EnabledChanged")]
    [ExtensionOf(typeof (AimSearchResultsToolExtensionPoint))]
    public class RetrieveAnnotationsTool : Tool<ISearchResultsToolContext>
    {
        private bool _enabled;
        private bool _localDataStoreConnected;

        private IAimActivityMonitor _aimActivityMonitor;

        void AimActivityMonitorIsConnectedChanged(object sender, EventArgs e)
        {
            _localDataStoreConnected = _aimActivityMonitor.IsConnected;
            UpdateEnabled();
        }

        /// <summary>
        /// Called to determine whether this tool is enabled/disabled in the UI.
        /// </summary>
        public bool Enabled
        {
            get { return _enabled; }
            protected set
            {
                if (_enabled != value)
                {
                    _enabled = value;
                    EventsHelper.Fire(_enabledChanged, this, EventArgs.Empty);
                }
            }
        }

        public void Apply()
        {
            ISelection selection = Context.Selection;
            if (selection == null || selection.Item == null)
                return;

            if (!_aimActivityMonitor.IsConnected)
            {
                Context.DesktopWindow.ShowMessageBox(
                    "Failed to save annotation. Not connected to the local data store. Is workstation service running?",
                    MessageBoxActions.Ok);
                return;
            }

            // Import Annotations
            RetrieveAnnotationsFromAimService(selection.Items);
        }

        protected void RetrieveAnnotationsFromAimService(object[] searchResults)
        {
            string errorMsg = null;
            if (!AimDataServiceLoginTool.CredentialsValid)
                AimDataServiceLoginTool.RequestLogin();
            var task = new BackgroundTask(
                delegate(IBackgroundTaskContext context)
                    {
                        try
                        {
                            int cnt = 0;
                            BackgroundTaskProgress progress;
                            var xmlFiles = new List<string>();

                            foreach (AimeAnnotationContainer result in searchResults)
                            {
                                cnt++;

                                if (result.Annotations == null)
                                    continue;

                                xmlFiles.Add(DownloadAnnotationFromWebService(result.AnnotationContainerUid));

                                progress = new BackgroundTaskProgress(cnt, searchResults.Length + 1,
                                                                      "Discovering Annotation " + cnt);
                                context.ReportProgress(progress);
                            }

                            if (xmlFiles.Count > 0)
                            {
                                List<string> invalidFiles;
                                List<string> tempDcmFiles =
                                    AimManager.ConvertAnnotationsFromXmlToDicomFiles(AimManager.DefaultAimVersion,
                                                                                     xmlFiles, context, out invalidFiles);

                                if (tempDcmFiles.Count > 0)
                                {
                                    progress = new BackgroundTaskProgress(searchResults.Length, searchResults.Length + 1,
                                                                          "Importing Annotations");
                                    context.ReportProgress(progress);

                                    ImportDicomFiles(tempDcmFiles);
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            // TODO: Smarter handling of invalid credentials/expiring credentials
                            if (ex.Message.Contains("401"))
                                AimDataServiceLoginTool.Credentials = null;

                            errorMsg = ex.Message;
                            Platform.Log(LogLevel.Error, ex, "Failed to import annotation(s)");
                        }

                        context.Complete(null);
                    }, true);

            ProgressDialog.Show(task, Context.DesktopWindow, true, ProgressBarStyle.Blocks);

            if (!string.IsNullOrEmpty(errorMsg))
                Context.DesktopWindow.ShowMessageBox(errorMsg, MessageBoxActions.Ok);
        }

        private string DownloadAnnotationFromWebService(string annotationContainerUid)
        {
            string filename = Path.GetTempFileName();

            // Will cause GUI thread exception unless run on the original synchronization context
            // The RetrieveAnnotationsFromAimService should already be checking this, so leaving commented out
            //if (!AimDataServiceLoginTool.CredentialsValid)
            //    AimDataServiceLoginTool.RequestLogin();
            if (AimDataServiceLoginTool.CredentialsValid)
            {
                string xml = AimeWebService.Retrieve(AimDataServiceLoginTool.Credentials.ApiKey,
                                                     new AimeSearchCriteria
                                                         {AnnotationContainreUid = annotationContainerUid});

                using (var streamWriter = new StreamWriter(filename))
                {
                    streamWriter.Write(xml);
                }
            }

            return filename;
        }

        private event EventHandler _enabledChanged;


        public override void Initialize()
        {
            base.Initialize();

            Context.SelectionChanged += OnSelectedStudyChanged;

            _aimActivityMonitor = AimActivityMonitor.Create(false);
            _localDataStoreConnected = _aimActivityMonitor.IsConnected;
            _aimActivityMonitor.IsConnectedChanged += AimActivityMonitorIsConnectedChanged;
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                Context.SelectionChanged -= OnSelectedStudyChanged;

                _aimActivityMonitor.IsConnectedChanged -= AimActivityMonitorIsConnectedChanged;
                _aimActivityMonitor.Dispose();
                _aimActivityMonitor = null;
            }
            base.Dispose(disposing);
        }

        private void UpdateEnabled()
        {
            Enabled = _localDataStoreConnected && Context.Selection.Item != null;
        }

        protected virtual void OnSelectedStudyChanged(object sender, EventArgs e)
        {
            UpdateEnabled();
        }

        /// <summary>
        /// Notifies that the Enabled state of this tool has changed.
        /// </summary>
        public event EventHandler EnabledChanged
        {
            add { _enabledChanged += value; }
            remove { _enabledChanged -= value; }
        }

        /// <summary>
        /// Imports the given dicom files into the local storage
        /// </summary>
        /// <param name="dicomFiles"></param>
        protected void ImportDicomFiles(IEnumerable<string> fileNames)
        {
            var dicomFiles = new List<DicomFile>();
            // Import into the local storage
            foreach (var fileName in fileNames)
            {
                try
                {
                    var annFile = new DicomFile(fileName);
                    annFile.Load(DicomReadOptions.Default | DicomReadOptions.DoNotStorePixelDataInDataSet);
                    dicomFiles.Add(annFile);
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Warn, ex, "Ignoring file for XNAT import: " + fileName, fileName);
                }
            }

            try
            {
                AimDicomFilePublisher.PublishLocal(dicomFiles);
            }
            catch (Exception ex)
            {
                Platform.Log(LogLevel.Error, ex, "Failed to store annotations");
                //this.DesktopWindow.ShowMessageBox("Failed to store your annotation(s).", "Annotation Import Error", MessageBoxActions.Ok);
            }
        }
    }
}
