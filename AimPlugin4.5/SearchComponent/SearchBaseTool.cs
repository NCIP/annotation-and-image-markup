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
using System.Net;
using AIM.Annotation;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.Dicom;
using ClearCanvas.ImageViewer.Common.WorkItem;
using NBIAService;

namespace SearchComponent
{
	public abstract class SearchBaseTool : Tool<ISearchResultsToolContext>
	{
		private bool _enabled;
		private event EventHandler _enabledChanged;
		private bool _localDataStoreConnected;

		private IWorkItemActivityMonitor _workItemActivityMonitor;


		protected SearchBaseTool()
		{
			_localDataStoreConnected = WorkItemActivityMonitor.IsRunning;
		}

		public override void Initialize()
		{
			base.Initialize();

			this.Context.SelectionChanged += OnSelectedStudyChanged;

			_workItemActivityMonitor = WorkItemActivityMonitor.Create();
			_workItemActivityMonitor.IsConnectedChanged += OnIsConnectedChanged;
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				this.Context.SelectionChanged -= OnSelectedStudyChanged;

				_workItemActivityMonitor.IsConnectedChanged -= OnIsConnectedChanged;
				_workItemActivityMonitor.Dispose();
				_workItemActivityMonitor = null;
			}
			base.Dispose(disposing);
		}

		private void OnIsConnectedChanged(object sender, EventArgs e)
		{
			_localDataStoreConnected = _workItemActivityMonitor.IsConnected;
			this.UpdateEnabled();
		}

		private void UpdateEnabled()
		{
			this.Enabled = _localDataStoreConnected && this.Context.Selection != null && this.Context.Selection.Item != null;
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
		/// <param name="filePathNames">Complete paths of the files to load</param>
		protected void ImportDicomFiles(ICollection<string> filePathNames)
		{
			try
			{
				var dicomFiles = new List<DicomFile>();
				foreach (var filePathName in filePathNames)
				{
					var dicomFile = new DicomFile(filePathName);
					dicomFile.Load();
					dicomFiles.Add(dicomFile);
				}

				AimDicomFilePublisher.PublishLocal(dicomFiles);
				//Platform.GetService((IPublishFiles w) => w.PublishLocal(dicomFiles));
			}
			catch (Exception e)
			{
				Platform.Log(LogLevel.Error, e, "Failed to import Grid files into the local storage");
				try
				{
					foreach (string file in filePathNames)
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
						BackgroundTaskProgress progress = new BackgroundTaskProgress(0, 3, "Querying for available images");
						context.ReportProgress(progress);
						if (context.CancelRequested)
						{
							context.Cancel();
							return;
						}

						NBIARetrieveByStudyUIDs nbiaRetrieveByStudyUIDs = new NBIARetrieveByStudyUIDs();
						string url = nbiaRetrieveByStudyUIDs.retrieveStudyURL(studyUids.ToArray(), SearchSettings.Default.NBIADataServiceUrl);

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

								if (e.BytesReceived < 1000 * 1024)
									progressMsg = string.Format("Retrieving images ({0:0.00}KB)", ((float)e.BytesReceived) / 1024);
								else
									progressMsg = string.Format("Retrieving images ({0:0.00}MB)", ((float)e.BytesReceived) / 1000 / 1024);
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
					//webClient.DownloadFile(sourceUrl, tempZipFile);

					while (!downloadCompleted)
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
