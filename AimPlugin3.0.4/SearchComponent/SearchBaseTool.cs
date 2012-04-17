#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

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
