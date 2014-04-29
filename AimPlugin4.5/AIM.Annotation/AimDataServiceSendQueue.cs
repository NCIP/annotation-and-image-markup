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
using System.Diagnostics;
using System.Linq;
using System.Threading;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

using AIM.Annotation.Configuration;

namespace AIM.Annotation
{
	internal class AimDataServiceSendQueue
	{
		// Event parameter data
		public class AimDataServiceSendItem
		{
			private readonly string _fileName;
			private readonly string _destinationServerUrl;

			public AimDataServiceSendItem(string fileName, string destinationServerUrl)
			{
				_fileName = fileName;
				_destinationServerUrl = destinationServerUrl;
			}

			public string DestinationServerUrl
			{
				get { return _destinationServerUrl; }
			}

			public string FileName
			{
				get { return _fileName; }
			}
		}

		private static AimDataServiceSendQueue _instance;
		private readonly object _operationLock = new object();
		private bool _isActive;
		private bool _stopThread;
		private Thread _sendThread;
		private Dictionary<String, String> _sourceFolders;

		private readonly object _subscriptionLock = new object();
		private event EventHandler<ItemEventArgs<AimDataServiceSendItem>> _sendProgressUpdate;

		private AimDataServiceSendQueue()
		{
		}

		internal static AimDataServiceSendQueue Instance
		{
			get
			{
				try
				{
					if (_instance == null)
						_instance = new AimDataServiceSendQueue();
				}
				catch (Exception e)
				{
					Platform.Log(LogLevel.Error, e);
					_instance = null;

				}

				return _instance;
			}
		}

		internal event EventHandler<ItemEventArgs<AimDataServiceSendItem>> SendProgressUpdate
		{
			add
			{
				lock (_subscriptionLock)
				{
					_sendProgressUpdate += value;
				}
			}
			remove
			{
				lock (_subscriptionLock)
				{
					_sendProgressUpdate -= value;
				}
			}
		}

		internal void Start()
		{
			lock (_operationLock)
			{
				if (_isActive)
					return;

				AimSettings.Default.PropertyChanged += OnAimSettingsChanged;

				_isActive = true;
				_stopThread = false;

				_sendThread = new Thread(this.RunThread);
				_sendThread.IsBackground = true;
				_sendThread.Priority = ThreadPriority.Lowest;

				_sendThread.Start();
				Monitor.Wait(_operationLock); //wait for the thread to signal it has started.
			}
		}

		internal void Stop()
		{
			lock (_operationLock)
			{
				if (!_isActive)
					return;

				_stopThread = true;

				//release the thread and wait for it to signal it has stopped running.
				Monitor.Pulse(_operationLock);
				Monitor.Wait(_operationLock);

				AimSettings.Default.PropertyChanged -= OnAimSettingsChanged;

				_sendThread.Join();
				_sendThread = null;

				_isActive = false;
			}
		}

		private void OnAimSettingsChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
		{
			Debug.Assert(AimSettings.Default.SendQueuesNames != new object(), "AIMSettings \"SendQueuesNames\" is missing");
			if (e.PropertyName == "SendQueuesNames")
			{
				lock (_operationLock)
				{
					_sourceFolders = null;
				}
			}
		}

		private void RunThread()
		{
			lock (_operationLock)
			{
				//signal the thread has started up.
				Monitor.Pulse(_operationLock);

				while (true)
				{
					Monitor.Wait(_operationLock, 300000); // 5 min = 1000 * 60 * 5 = 300000

					if (_stopThread)
						break;

					// 1. Get List of folders
					if (_sourceFolders == null)
						_sourceFolders = AimSettings.Default.SendQueuesNames;

					if (_sourceFolders != null && _sourceFolders.Count > 0)
					{
						foreach (KeyValuePair<String, String> sourceFolder in _sourceFolders)
						{
							// Get annotations and send to server
							this.SendAnnotationsInFolderToDataService((string)sourceFolder.Value, (string)sourceFolder.Key);

							Monitor.Pulse(_operationLock);
							// This can be cleared under us when new server added
							if (_stopThread || _sourceFolders == null)
								break;
						}

					}

					Monitor.Pulse(_operationLock);
				}

				// Signal to Stop
				Monitor.Pulse(_operationLock);
			}
		}

		private int SendAnnotationsInFolderToDataService(string folderName, string dataServiceUrl)
		{
			if (string.IsNullOrEmpty(folderName) || string.IsNullOrEmpty(dataServiceUrl))
			{
				Platform.Log(LogLevel.Error, "Trying to send queued annotations from an invalid folder ({0}) or to an invalid data service ({1})", folderName, dataServiceUrl);
				return 0;
			}

			string folderPath = System.IO.Path.Combine(AimSettings.Default.AnnotationQueuesFolder, folderName);

			if (!System.IO.Directory.Exists(folderPath))
				return 0;

			int sentCounter = 0;
			try
			{
				string[] annotationFiles = System.IO.Directory.GetFiles(folderPath, "*.xml", System.IO.SearchOption.TopDirectoryOnly);

				if (annotationFiles.Any())
				{
					IAimDataService aimDataService = new AimDataServiceExtensionPoint().CreateExtensions().OfType<IAimDataService>().FirstOrDefault(dataService => dataService.ServiceUrl == dataServiceUrl);
					if (aimDataService == null)
					{
						Platform.Log(LogLevel.Error, "Trying to send queued annotations to data service at ({0}). There is no data service configured for the URL");
						return 0;
					}

					const int fileCountToSendAtOnce = 10; // # of files to read at one time
					for (int i = 0; i < (annotationFiles.Length + fileCountToSendAtOnce) / fileCountToSendAtOnce; i++)
					{

						// Read next batch
						var annotationPathNames = new List<string>();
						int nextBatchMaxCnt = Math.Min((i + 1) * fileCountToSendAtOnce, annotationFiles.Length);
						for (int j = i * fileCountToSendAtOnce; j < nextBatchMaxCnt; j++)
							annotationPathNames.Add(System.IO.Path.Combine(folderPath, annotationFiles[j]));

						var xmlAnnotations = AimManager.AimManager.Instance.ReadXmlAnnotationsToMemory(aimDataService.AimVersion, annotationPathNames);

						// Send read annotations to the Data Service
						if (xmlAnnotations.Count > 0)
						{
							try
							{
								aimDataService.SendAnnotations(new List<string>(xmlAnnotations.Values));

								sentCounter += xmlAnnotations.Count;

								// Delete sent files
								Debug.Assert(annotationPathNames.Count > xmlAnnotations.Count, "Was not able to read all annotations");
								xmlAnnotations.Clear();
								foreach (var readAnnotationFile in xmlAnnotations.Keys)
								{
									try
									{
										System.IO.File.Delete(readAnnotationFile);
									}
									catch (Exception ex)
									{
										Platform.Log(LogLevel.Error, ex, "Failed to delete sent annotation file ({0}). The file will be send again.", readAnnotationFile);
									}
								}
								xmlAnnotations.Clear();
							}
							catch (Exception ex)
							{
								Platform.Log(LogLevel.Debug, ex, "Failed to send annotations to the AIM Data Service ({0}).", dataServiceUrl);

								break; // assume that data service is unavailable
							}
						}
					}
				}
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to send files from {0} to server {1}", folderPath, dataServiceUrl);
			}

			return sentCounter;
		}
	}
}
