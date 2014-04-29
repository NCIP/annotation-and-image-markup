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
using System.IO;
using System.Linq;
using System.Threading;
using AIM.Annotation;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.Dicom;
using ClearCanvas.ImageViewer.Common.WorkItem;
using ICSharpCode.SharpZipLib.Zip;
using XnatWebBrowser.Configuration;
using Path = System.IO.Path;

namespace XnatWebBrowser
{
    public enum ImportStatus
    {
        Standby = 0,
        Searching,
        Importing,
        Imported
    }

    [ButtonAction("apply", "global-toolbars/ToolbarStandard/ToolbarWebBrowser", "Apply")]
    [Tooltip("apply", "Checking for XNAT downloads")]
    [IconSet("apply", "blank.gif")]
    [IconSetObserver("apply", "IconSet", "ImportingChanged")]
    [EnabledStateObserver("apply", "Enabled", "EnabledChanged")]
    [ExtensionOf(typeof(DesktopToolExtensionPoint))]
    public class XnatImportTool : Tool<IDesktopToolContext>
    {
        private readonly IconSet _importedIcons;
        private readonly IconSet _importingIcons;
        private readonly IconSet _searchingIcons;
        private readonly IconSet _standbyIcons;
        private AsyncOperation _asyncOperation;
        private volatile bool _checkingForDownloads = true;
        private Thread _downloadCheckingThread;
        private bool _enabled;
        private volatile ImportStatus _importStatus;
        private volatile bool _active;
        private volatile IWorkItemActivityMonitor _workItemActivityMonitor;
        private readonly object _lock;
        private volatile Dictionary<String, String> _studyUidsTempFolders;

        /// <summary>
        /// Default constructor.  A no-args constructor is required by the
        /// framework.  Do not remove.
        /// </summary>
        public XnatImportTool()
        {
            _enabled = false;
            _standbyIcons = new IconSet("blank.gif");
            _searchingIcons = new IconSet("XnatSearchingSmall.gif", "XnatSearchingMedium.gif",
                                          "XnatSearchingLarge.gif");
            _importingIcons = new IconSet("XnatImportingSmall.gif", "XnatImportingMedium.gif",
                                          "XnatImportingLarge.gif");
            _importedIcons = new IconSet("XnatImportedSmall.gif", "XnatImportedMedium.gif",
                                         "XnatImportedLarge.gif");

            _lock = new object();
            _studyUidsTempFolders = new Dictionary<string, string>();
        }

        private String DownloadFolder { get; set; }

        public ImportStatus ImportStatus
        {
            get { return _importStatus; }
            private set
            {
                if (_importStatus != value)
                {
                    _importStatus = value;
                    EventsHelper.Fire(ImportingChanged, this, EventArgs.Empty);
                }
            }
        }

        public IconSet IconSet
        {
            get
            {
                IconSet iconSet = _standbyIcons;
                switch (ImportStatus)
                {
                    case ImportStatus.Searching:
                        iconSet = _searchingIcons;
                        break;
                    case ImportStatus.Imported:
                        iconSet = _importedIcons;
                        break;
                    case ImportStatus.Importing:
                        iconSet = _importingIcons;
                        break;
                }
                return iconSet;
            }
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
                    EventsHelper.Fire(EnabledChanged, this, EventArgs.Empty);
                }
            }
        }

        public override void Initialize()
        {
            base.Initialize();

            _workItemActivityMonitor = WorkItemActivityMonitor.Create();
            _workItemActivityMonitor.IsConnectedChanged += IsConnectedChanged;
            _workItemActivityMonitor.WorkItemsChanged += WorkItemsChanged;
            Enabled = _workItemActivityMonitor.IsConnected;

            _asyncOperation = AsyncOperationManager.CreateOperation(null);

            if (XnatSettings.Default.DownloadCheckInterval > 0)
                StartDownloadCheckingThread();
        }

        void WorkItemsChanged(object sender, WorkItemsChangedEventArgs e)
        {
            if (e.EventType == WorkItemsChangedEventType.Update)
            {
                foreach (var workItem in e.ChangedItems)
                {
                    if (!String.IsNullOrEmpty(workItem.StudyInstanceUid) && workItem.Type == "ProcessStudy")
                    {
                        if (workItem.Status == WorkItemStatusEnum.Idle)
                        {
                            // Assume studies are all imported when an idle has been received for each import
                            lock (_lock)
                            {
                                foreach (var item in e.ChangedItems)
                                {
                                    if (_studyUidsTempFolders.ContainsKey(item.StudyInstanceUid))
                                    {
                                        _asyncOperation.Post(delegate { ImportStatus = ImportStatus.Imported; }, this);
                                    }
                                }
                            }
                        }

                        if (workItem.Status == WorkItemStatusEnum.Complete)
                        {
                            // Actually delete the unzipped files from the XNAT download folder when a complete is received from the workitemactivitymonitor
                            lock (_lock)
                            {
                                foreach (var item in e.ChangedItems)
                                {
                                    if (_studyUidsTempFolders.ContainsKey(item.StudyInstanceUid))
                                    {
                                        Directory.Delete(_studyUidsTempFolders[item.StudyInstanceUid], true);
                                        OnImportCompleted(this);
                                        _asyncOperation.Post(delegate { ImportStatus = ImportStatus.Searching; }, this);
                                        _studyUidsTempFolders.Remove(item.StudyInstanceUid);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


        void IsConnectedChanged(object sender, EventArgs e)
        {
            Enabled = _workItemActivityMonitor.IsConnected;
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                _workItemActivityMonitor.IsConnectedChanged -= IsConnectedChanged;
                _workItemActivityMonitor.WorkItemsChanged -= WorkItemsChanged;
                _workItemActivityMonitor.Dispose();
                _workItemActivityMonitor = null;

                ImportStatus = ImportStatus.Standby;
                _checkingForDownloads = false;

                // Attempt to clean up temp files
                foreach (var studyUidFolder in _studyUidsTempFolders)
                {
                    Directory.Delete(_studyUidsTempFolders[studyUidFolder.Key], true);
                }
            }

            base.Dispose(disposing);
        }

        public void Apply()
        {
        }

        public event EventHandler EnabledChanged;
        public event EventHandler ImportingChanged;
        public event EventHandler FileSearch;
        public event EventHandler ImportStarted;
        public event EventHandler ImportCompleted;

        private void StartDownloadCheckingThread()
        {
            DownloadFolder = GetDownloadFolder();

            _downloadCheckingThread = new Thread(CheckForDownloadedZip);
            _downloadCheckingThread.Start();
        }

        private string GetDownloadFolder()
        {
            string downloadFolder = XnatSettings.Default.DownloadFolder;
            if (String.IsNullOrEmpty(downloadFolder))
            {
                downloadFolder = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "AIM XNAT Downloads");

                XnatSettings.Default.DownloadFolder = downloadFolder;
                XnatSettings.Default.Save();
            }
            if (!Directory.Exists(downloadFolder))
            {
                try
                {
                    Directory.CreateDirectory(downloadFolder);
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Error, ex, "Unable to create download folder");
                }
            }
            return downloadFolder;
        }


        private void CheckForDownloadedZip()
        {
            while (_checkingForDownloads)
            {
                Thread.Sleep(XnatSettings.Default.DownloadCheckInterval * 1000);

                if (XnatWebBrowserTool.Active)
                {
                    if (!_active)
                    {
                        _asyncOperation.Post(delegate { ImportStatus = ImportStatus.Searching; }, this);
                        _active = true;
                    }

                    _asyncOperation.Post(OnFileSearch, this);

                    try
                    {
                        Platform.Log(LogLevel.Debug, "XNAT: checking for zip files in {0}", DownloadFolder);
                        string[] files = Directory.GetFiles(DownloadFolder, "*.zip");
                        // We need to double check that it's a zip file because GetFiles filter would pick files like "test.zip123" as well.
                        List<string> zipFiles = files.Where(file => string.Compare(Path.GetExtension(file), ".zip", StringComparison.InvariantCultureIgnoreCase) == 0).ToList();
                        Platform.Log(LogLevel.Debug, "XNAT: found {0} zip file(s) in {1}", zipFiles.Count, DownloadFolder);

                        foreach (string zipFile in zipFiles)
                            if (!ProcessZipFile(zipFile))
                                MoveToBadFilesDir(zipFile);
                    }
                    catch (Exception ex)
                    {
                        Platform.Log(LogLevel.Error, ex, "Failed to process XNAT's zip file(s)");
                    }
                }
                else
                {
                    if (_active)
                    {
                        _asyncOperation.Post(delegate { ImportStatus = ImportStatus.Standby; }, this);
                        _active = false;
                    }
                }
            }
        }

        private bool ProcessZipFile(string filename)
        {
            try
            {
                Platform.Log(LogLevel.Debug, "XNAT: Beginning to process zip file {0}", filename);
                _asyncOperation.Post(delegate { ImportStatus = ImportStatus.Importing; }, this);
                string subfolder = Path.GetFileNameWithoutExtension(filename);
                string path = Path.Combine(DownloadFolder, subfolder);
                UnZipFiles(filename, path, null, true, false);

                _asyncOperation.Post(OnImportStarted, this);

                ImportImages(path);

                return true;
            }
            catch (Exception ex)
            {
                Platform.Log(LogLevel.Error, ex, "Error handling ZIP file ({0}) or importing images into workstation.", filename);
                return false;
            }
        }

        private void MoveToBadFilesDir(string filePathName)
        {
            var badFileDir = Path.Combine(DownloadFolder, "bad_files");
            try
            {
                if (!Directory.Exists(badFileDir)) Directory.CreateDirectory(badFileDir);
                var newFilePathName = Path.Combine(badFileDir, Path.GetFileName(filePathName));
                var cnt = 0;
                // Make sure that the file name is unique like this: file(1).ext
                while (File.Exists(newFilePathName))
                    newFilePathName = Path.Combine(badFileDir, string.Format("{0} ({1}){2}", Path.GetFileNameWithoutExtension(filePathName), ++cnt, Path.GetExtension(filePathName)));
                File.Move(filePathName, newFilePathName);
            }
            catch (Exception ex)
            {
                Platform.Log(LogLevel.Error, ex, "Failed to move file ({0}) to bad_files dir ({1})", filePathName, badFileDir);
            }
        }

        private void OnFileSearch(object state)
        {
            EventsHelper.Fire(FileSearch, this, EventArgs.Empty);
        }

        private void OnImportStarted(object state)
        {
            EventsHelper.Fire(ImportStarted, this, EventArgs.Empty);
        }

        private void OnImportCompleted(object state)
        {
            EventsHelper.Fire(ImportCompleted, this, EventArgs.Empty);
        }

        public static void UnZipFiles(string zipPathAndFile, string outputFolder, string password, bool deleteZipFile,
                                      bool ignoreFolderNames)
        {
            Platform.Log(LogLevel.Debug, "XNAT: Unzipping file {0} into folder {1}", zipPathAndFile, outputFolder);
            using (var s = new ZipInputStream(File.OpenRead(zipPathAndFile)))
            {
                if (!string.IsNullOrEmpty(password))
                    s.Password = password;
                ZipEntry theEntry;
                while ((theEntry = s.GetNextEntry()) != null)
                {
                    string directoryName = outputFolder;
                    string fileName = Path.GetFileName(theEntry.Name);
                    // create directory 
                    if (directoryName != "")
                    {
                        Directory.CreateDirectory(directoryName);
                    }
                    if (!String.IsNullOrEmpty(fileName))
                    {
                        if (theEntry.Name.IndexOf(".ini") < 0)
                        {
                            string fullPath;
                            if (ignoreFolderNames)
                                fullPath = Path.Combine(directoryName, fileName);
                            else
                                fullPath = Path.Combine(directoryName, theEntry.Name);
                            fullPath = fullPath.Replace("\\ ", "\\");
                            string fullDirPath = Path.GetDirectoryName(fullPath);
                            Platform.Log(LogLevel.Debug, "XNAT: Need to write to folder {0}", fullDirPath);
                            if (!Directory.Exists(fullDirPath)) Directory.CreateDirectory(fullDirPath);
                            Platform.Log(LogLevel.Debug, "XNAT: Ready to write to folder {0}", fullDirPath);
                            FileStream streamWriter = File.Create(fullPath);
                            int size = 2048;
                            var data = new byte[size];
                            while (true)
                            {
                                size = s.Read(data, 0, data.Length);
                                if (size > 0)
                                {
                                    streamWriter.Write(data, 0, size);
                                }
                                else
                                {
                                    break;
                                }
                            }
                            streamWriter.Close();
                            Platform.Log(LogLevel.Debug, "XNAT: Done writing to folder {0}", fullDirPath);
                        }
                    }
                }
                s.Close();
            }
            if (deleteZipFile)
            {
                Platform.Log(LogLevel.Debug, "XNAT: Deleting file {0}", zipPathAndFile);
                File.Delete(zipPathAndFile);
            }
        }

        private void ImportImages(string path)
        {
            // Import into the local storage
            var filePaths = GetFiles(path).ToList();
            var dicomFiles = new List<DicomFile>();
            foreach (var tempAnnFileName in filePaths)
            {
                try
                {
                    var annFile = new DicomFile(tempAnnFileName);
                    annFile.Load(DicomReadOptions.Default | DicomReadOptions.DoNotStorePixelDataInDataSet);
                    dicomFiles.Add(annFile);
                    string studyInstanceUid = annFile.DataSet[DicomTags.StudyInstanceUid];
                    lock (_lock)
                    {
                        _studyUidsTempFolders.Add(studyInstanceUid, path);
                    }
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Warn, ex, "Ignoring file for XNAT import: " + tempAnnFileName, tempAnnFileName);
                }
            }

            try
            {
                AimDicomFilePublisher.PublishLocal(dicomFiles);
            }
            catch (Exception ex)
            {
                Platform.Log(LogLevel.Error, ex, "Failed to store annotations");
            }
        }

        private static IEnumerable<string> GetFiles(string path)
        {
            var queue = new Queue<string>();
            queue.Enqueue(path);
            while (queue.Count > 0)
            {
                path = queue.Dequeue();
                try
                {
                    foreach (string subDir in Directory.GetDirectories(path))
                    {
                        queue.Enqueue(subDir);
                    }
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Error, ex, "XNAT: Failed to enumerate all directories in the path: {0}", path);
                }
                string[] files = null;
                try
                {
                    files = Directory.GetFiles(path);
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Error, ex, "XNAT: Failed to get all files from path: {0}", path);
                }
                if (files != null)
                {
                    foreach (string t in files)
                    {
                        yield return t;
                    }
                }
            }
        }
    }
}
