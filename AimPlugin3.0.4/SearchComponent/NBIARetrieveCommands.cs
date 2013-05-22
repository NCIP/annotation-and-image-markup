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

				OnStatusChanged(RetrieveStatus.InProgress, "Quering for studies...");

				string url = null;
				try
				{
					NBIARetrieveByStudyUIDs nbiaRetrieveByStudyUIDs = new NBIARetrieveByStudyUIDs();
					url = nbiaRetrieveByStudyUIDs.retrieveStudyURL(studyUids.ToArray(), SearchSettings.Default.NBIADataServiceTransferUrl);
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
					OnCommandCompleted("No studies returned by NBIA.");
					OnCommandExecuted();
					return;
				}

				string downloadedFilesFolder = this.DownloadQueryResults(url);

				if (this.IsCancelRequested())
				{
					OnCancelRequested();
					OnCommandExecuted();
					return;
				}

				if (string.IsNullOrEmpty(downloadedFilesFolder))
				{
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
					string tempZipDir = Path.Combine(Path.GetTempPath(),
															   Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));
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
								};
						webClient.DownloadFileCompleted +=
							delegate(object sender, System.ComponentModel.AsyncCompletedEventArgs e)
								{
									downloadCompleted = true;
								};
						webClient.DownloadFileAsync(new Uri(sourceUrl), tempZipFile);

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
