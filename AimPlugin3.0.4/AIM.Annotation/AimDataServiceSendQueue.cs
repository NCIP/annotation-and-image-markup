//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

using AIM.Annotation.Configuration;

namespace AIM.Annotation
{
	internal class AimDataServiceSendQueue
	{
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
			lock(_operationLock)
			{
				if (_isActive)
					return;

				AimSettings.Default.PropertyChanged += OnAimSettingsChanged;

				_isActive = true;
				_stopThread = false;

				_sendThread = new Thread(RunThread);
				_sendThread.IsBackground = true;
				_sendThread.Priority = ThreadPriority.Lowest;
				_sendThread.Start();
				Monitor.Wait(_operationLock);
			}
		}

		internal void Stop()
		{
			lock(_operationLock)
			{
				if (!_isActive)
					return;

				_stopThread = true;
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
				Monitor.Pulse(_operationLock);

				while (true)
				{
					Monitor.Wait(_operationLock, 300000);
					if (_stopThread)
						break;

					if (_sourceFolders == null)
						_sourceFolders = AimSettings.Default.SendQueuesNames;

					if (_sourceFolders != null && _sourceFolders.Count > 0)
					{
						foreach (var sourceFolder in _sourceFolders)
						{
							SendAnnotationsInFolderToDataService(sourceFolder.Value, sourceFolder.Key);
							Monitor.Pulse(_operationLock);
							if (_stopThread || _sourceFolders == null)
								break;
						}

					}

					Monitor.Pulse(_operationLock);
				}
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

			var folderPath = System.IO.Path.Combine(AimSettings.Default.AnnotationQueuesFolder, folderName);
			if (!System.IO.Directory.Exists(folderPath))
				return 0;

			var sentCounter = 0;
			try
			{
				var annotationFiles = System.IO.Directory.GetFiles(folderPath, "*.xml", System.IO.SearchOption.TopDirectoryOnly);

				const int fileCountToSendAtOnce = 10;
				for (var i = 0; i < (annotationFiles.Length + fileCountToSendAtOnce) / fileCountToSendAtOnce; i++)
				{
					var xmlAnnotations = new Dictionary<string, string>();
					var readAnnotationFiles = new List<string>();
					using (var xmlModel = new aim_dotnet.XmlModel())
					{
						var nextBatchMax = Math.Min((i + 1)*fileCountToSendAtOnce, annotationFiles.Length);
						for (var j = i*fileCountToSendAtOnce; j < nextBatchMax; j++)
						{
							var annotationPathName = System.IO.Path.Combine(folderPath, annotationFiles[j]);
							try
							{
								var annotations = xmlModel.ReadAnnotationsFromFile(annotationPathName);
								try
								{
									foreach (var annotation in annotations)
									{
										xmlAnnotations.Add(annotation.UniqueIdentifier, xmlModel.WriteAnnotationToXmlString(annotation));
									}
									readAnnotationFiles.Add(annotationPathName);
								}
								catch (Exception ex)
								{
									Platform.Log(LogLevel.Error, ex, "Failed to convert annotation to XML string. File: {0}", annotationPathName);
									xmlAnnotations.Clear();
								}
								finally
								{
									annotations.Clear();
								}
							}
							catch (Exception ex)
							{
								Platform.Log(LogLevel.Error, ex, "Failed to read annotation file from queue: {0}", annotationPathName);
							}
						}
					}

					if (xmlAnnotations.Count > 0)
					{
						try
						{
							AIMTCGAService.AIMTCGASubmit.sendAIMTCGAAnnotation(new List<string>(xmlAnnotations.Values).ToArray());
							sentCounter += xmlAnnotations.Count;
							Debug.Assert(readAnnotationFiles.Count <= xmlAnnotations.Count, "There are more files to delete than read annoations");
							xmlAnnotations.Clear();
							foreach (var readAnnotationFile in readAnnotationFiles)
							{
								try
								{
									System.IO.File.Delete(readAnnotationFile);
								}
								catch (Exception ex)
								{
									Platform.Log(LogLevel.Error, ex, "Failed to delete sent annoation file ({0}). The file will be send again.", readAnnotationFile);
								}
							}
							readAnnotationFiles.Clear();
						}
						catch (Exception ex)
						{
							Platform.Log(LogLevel.Debug, ex, "Failed to send annotations to the AIM Data Serice ({0}).", dataServiceUrl);
							break;
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
