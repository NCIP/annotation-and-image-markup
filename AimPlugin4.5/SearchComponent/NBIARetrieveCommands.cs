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

using ClearCanvas.Common;
using NBIAService;

namespace SearchComponent
{
	internal partial class RetrieveCoordinator
	{
		protected class NBIARetrieveCommand : RetrieveCommand
		{
			public NBIARetrieveCommand(List<RetrieveQueryItem> queryItems) : base()
			{
				Result.QueryItems.AddRange(queryItems);
			}

			public override void Execute()
			{
				List<string> studyUids = new List<string>();

				if (Result.QueryItems != null && Result.QueryItems.Count > 0)
				{
					foreach (RetrieveQueryItem queryItem in Result.QueryItems)
					{
						if (queryItem.Study != null && !string.IsNullOrEmpty(queryItem.Study.StudyInstanceUid))
							studyUids.Add(queryItem.Study.StudyInstanceUid);
					}
				}

				if (studyUids.Count == 0)
				{
					OnError("No Study Instance UID is specified");
					OnCommandExecuted();
					return;
				}

				if (this.IsCancelRequested())
				{
					OnCancelRequested();
					OnCommandExecuted();
					return;
				}

				OnStatusChanged(RetrieveStatus.InProgress, "Querying for studies...");

				string url = null;
				try
				{
					NBIARetrieveByStudyUIDs nbiaRetrieveByStudyUIDs = new NBIARetrieveByStudyUIDs();
					url = nbiaRetrieveByStudyUIDs.retrieveStudyURL(studyUids.ToArray(), SearchSettings.Default.NBIADataServiceUrl);
				}
				catch (DataServiceUtil.GridServicerException ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to retrieve images from NBIA");
				}

				if (this.IsCancelRequested())
				{
					OnCancelRequested();
					OnCommandExecuted();
					return;
				}

				if (string.IsNullOrEmpty(url))
				{
					//Result.ProgressMessage = "No studies returned by NBIA.";
					OnCommandCompleted("No studies returned by NBIA.");
					OnCommandExecuted();
					return;
				}

				string downloadedFilesFolder = this.DownloadQueryResults(url);

				if (this.IsCancelRequested())
				{

					// TODO - delete downloaded files

					OnCancelRequested();
					OnCommandExecuted();
					return;
				}

				if (string.IsNullOrEmpty(downloadedFilesFolder))
				{
					// Status/Error should be reported by now

					OnCommandExecuted();
					return;
				}

				OnProgressUpdated("Importing images");

				try
				{
					string[] files = Directory.GetFiles(downloadedFilesFolder, "*.dcm", SearchOption.AllDirectories);
					if (files.Length > 0)
						this.ImportDicomFiles(files);
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Error importing NBIA images");
					OnError("Error importing NBIA images");
					OnCommandExecuted();
					return;
				}

				OnCommandCompleted("Done");
				OnCommandExecuted();
			}

			private string DownloadQueryResults(string sourceUrl)
			{
				if (!string.IsNullOrEmpty(sourceUrl))
				{
					string tempZipDir = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));
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
									string msg;
									if (IsCancelRequested())
									{
										OnCancelRequested();
										if (!canceled)
										{
											webClient.CancelAsync();
										}
										canceled = true;
										return;
									}

									if (e.BytesReceived < 1000*1024)
										msg = string.Format("Retrieving images ({0:0.00}KB)", ((float) e.BytesReceived)/1024);
									else
										msg = string.Format("Retrieving images ({0:0.00}MB)", ((float) e.BytesReceived)/1000/1024);

									OnProgressUpdated(msg);
									//OnResultUpdated(Result);
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

						if (IsCancelRequested())
						{
							OnCancelRequested();
							canceled = true;
						}

						if (!canceled)
						{
							OnProgressUpdated("Processing received images");
							//Result.ProgressMessage = "Processing received images";
							//OnResultUpdated(Result);

							try
							{
								ZipUtil.UnZipFiles(tempZipFile, tempZipDir, "", false, true);
								File.Delete(tempZipFile);
							}
							catch (Exception ex)
							{
								Platform.Log(LogLevel.Error, "Error processing received images", ex);
								OnError("Error processing received images");
								return null;
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
}
