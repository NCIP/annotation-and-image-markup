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
