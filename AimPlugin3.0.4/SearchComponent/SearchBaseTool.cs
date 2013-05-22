//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.ImageViewer.Services.LocalDataStore;
using NBIAService;

namespace SearchComponent
{
    public abstract class SearchBaseTool : Tool<ISearchResultsToolContext>
    {
        private bool _enabled;
        private event EventHandler _enabledChanged;
    	private bool _localDataStoreConnected;

		private ILocalDataStoreEventBroker _localDataStoreEventBroker;


        protected SearchBaseTool()
        {
        	_localDataStoreConnected = LocalDataStoreActivityMonitor.IsConnected;
        }

        public override void Initialize()
        {
            base.Initialize();
            
			this.Context.SelectionChanged += OnSelectedStudyChanged;

			_localDataStoreEventBroker = LocalDataStoreActivityMonitor.CreatEventBroker();
			_localDataStoreEventBroker.Connected += OnLocalDataStoreConnected;
			_localDataStoreEventBroker.LostConnection += OnLocalDataStoreLostConnection;
        }
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				this.Context.SelectionChanged -= OnSelectedStudyChanged;

				_localDataStoreEventBroker.Connected -= OnLocalDataStoreConnected;
				_localDataStoreEventBroker.LostConnection -= OnLocalDataStoreLostConnection;
				_localDataStoreEventBroker.Dispose();
				_localDataStoreEventBroker = null;
			}
			base.Dispose(disposing);
		}

		private void OnLocalDataStoreLostConnection(object sender, EventArgs e)
		{
			_localDataStoreConnected = false;
			this.UpdateEnabled();
		}

		private void OnLocalDataStoreConnected(object sender, EventArgs e)
		{
			_localDataStoreConnected = true;
			this.UpdateEnabled();
		}

		private void UpdateEnabled()
		{
			this.Enabled = _localDataStoreConnected && this.Context.Selection.Item != null;
		}

        protected virtual void OnSelectedStudyChanged(object sender, EventArgs e)
        {
        	this.UpdateEnabled();
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
        protected void ImportDicomFiles(IEnumerable<string> dicomFiles)
        {
            try
            {
                LocalDataStoreServiceClient client = new LocalDataStoreServiceClient();
                client.Open();
                try
                {
                    FileImportRequest request = new FileImportRequest();
                    request.BadFileBehaviour = BadFileBehaviour.Move;
                    request.FileImportBehaviour = FileImportBehaviour.Move;
                    request.FilePaths = dicomFiles;
                    request.Recursive = false;
                    request.IsBackground = true;
                    client.Import(request);
                    client.Close();
                }
                catch (Exception ex)
                {
                    client.Abort();
                    Platform.Log(LogLevel.Error, ex, "Failed to import Grid files into the local storage");
                    throw;
                }
            }
            catch (Exception e)
            {
                Platform.Log(LogLevel.Error, e, "Failed to import Grid files into the local storage");
                try
                {
                    foreach (string file in dicomFiles)
                    {
                        File.Delete(file);
                    }
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Error, ex, "Failed to remove temp Grid files");
                }
                throw;
            }
        }

        protected void RetrieveStudiesFromNBIA(List<string> studyUids)
        {
            string errorMsg = null;
            BackgroundTask task = new BackgroundTask(
                delegate(IBackgroundTaskContext context)
                {
                    if (studyUids.Count == 0)
                    {
                        context.Complete(null);
                        return;
                    }

                    try
                    {
                        BackgroundTaskProgress progress = new BackgroundTaskProgress(0, 3, "Quering for available images");
                        context.ReportProgress(progress);
						if (context.CancelRequested)
						{
							context.Cancel();
							return;
						}

                    	NBIARetrieveByStudyUIDs nbiaRetrieveByStudyUIDs = new NBIARetrieveByStudyUIDs();
                        string url = nbiaRetrieveByStudyUIDs.retrieveStudyURL(studyUids.ToArray(), SearchSettings.Default.NBIADataServiceTransferUrl);

                        if (!string.IsNullOrEmpty(url))
                        {
                            progress = new BackgroundTaskProgress(1, 3, "Retrieving images");
                            context.ReportProgress(progress);
							if (context.CancelRequested)
							{
								context.Cancel();
								return;
							}

                            string downloadedFilesFolder = this.DownloadQueryResults(url, context);

                            if (!string.IsNullOrEmpty(downloadedFilesFolder))
                            {
                                progress = new BackgroundTaskProgress(2, 3, "Importing images");
                                context.ReportProgress(progress);
								if (context.CancelRequested)
								{
									context.Cancel();
									return;
								}

                            	string[] files = Directory.GetFiles(downloadedFilesFolder, "*.dcm", SearchOption.AllDirectories);
                                if (files.Length > 0)
                                    this.ImportDicomFiles(files);
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        errorMsg = ex.Message;
                        Platform.Log(LogLevel.Error, ex, "Failed to retrieve requested study(ies)");
                    }

                    context.Complete(null);

                }, true);

            ProgressDialog.Show(task, this.Context.DesktopWindow, true, ProgressBarStyle.Blocks);

            if (!string.IsNullOrEmpty(errorMsg))
                this.Context.DesktopWindow.ShowMessageBox(errorMsg, MessageBoxActions.Ok);
        }

        private string DownloadQueryResults(string sourceUrl, IBackgroundTaskContext context)
        {
			if (!string.IsNullOrEmpty(sourceUrl))
			{
				string tempZipDir = System.IO.Path.Combine(System.IO.Path.GetTempPath(),
				                                           System.IO.Path.GetFileNameWithoutExtension(System.IO.Path.GetRandomFileName()));
				string tempZipFile = tempZipDir + ".zip";
				WebClient webClient = null;
				bool canceled = false;
				try
				{
					webClient = new WebClient();
					bool downloadCompleted = false;
					webClient.DownloadProgressChanged +=
						delegate(object sender, DownloadProgressChangedEventArgs e)
							{
								if (context != null)
								{
									string progressMsg;

									if (e.BytesReceived < 1000*1024)
										progressMsg = string.Format("Retrieving images ({0:0.00}KB)", ((float)e.BytesReceived)/1024);
									else
										progressMsg = string.Format("Retrieving images ({0:0.00}MB)", ((float)e.BytesReceived)/1000/1024);
									BackgroundTaskProgress progress = new BackgroundTaskProgress(1, 3, progressMsg);
									context.ReportProgress(progress);
									if (context.CancelRequested)
									{
										if (!canceled)
										{
											webClient.CancelAsync();
										}
										context.Cancel();
										canceled = true;
									}
								}
							};
					webClient.DownloadFileCompleted +=
						delegate(object sender, System.ComponentModel.AsyncCompletedEventArgs e)
							{
								downloadCompleted = true;
							};
					webClient.DownloadFileAsync(new Uri(sourceUrl), tempZipFile);

					while(!downloadCompleted)
						System.Threading.Thread.Sleep(500);

					if (!canceled)
					{
						if (context != null)
						{
							BackgroundTaskProgress progress = new BackgroundTaskProgress(1, 3, "Processing received images");
							context.ReportProgress(progress);
							if (context.CancelRequested)
							{
								context.Cancel();
								canceled = true;
							}
						}
						ZipUtil.UnZipFiles(tempZipFile, tempZipDir, "", false, true);

						try
						{
							File.Delete(tempZipFile);
						}
						catch (Exception)
						{
						}

						return tempZipDir;
					}
				}
				finally
				{
					if (webClient != null)
					{
						webClient.Dispose();
					}
				}
			}
        	return null;
        }
    }
}
