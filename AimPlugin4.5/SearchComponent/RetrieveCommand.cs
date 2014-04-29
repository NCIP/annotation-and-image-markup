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
using ClearCanvas.Common;
using ClearCanvas.Dicom;

namespace SearchComponent
{
	internal partial class RetrieveCoordinator
	{
		// Command to retrieve a single study
		protected abstract class RetrieveCommand
		{
			private readonly RetrieveProgressResult _result;

			protected RetrieveCommand()
			{
				_result = new RetrieveProgressResult();
				_result.Status = RetrieveStatus.Queued;
			}

			public abstract void Execute();

			protected void OnCommandExecuted()
			{
				Coordinator.OnCommandExecuted();
			}

			//protected void OnProgressChanged()
			//{
			//    OnResultUpdated(_result);
			//}

			protected void OnCommandCompleted()
			{
				Coordinator.OnStatusChanged(RetrieveStatus.Completed, _result);
				//_result.Status = RetrieveStatus.Completed;
				//OnResultUpdated(_result);
			}

			protected void OnCommandCompleted(string message)
			{
				Coordinator.OnStatusChanged(RetrieveStatus.Completed, message, _result);
				//_result.Status = RetrieveStatus.Completed;
				//OnResultUpdated(_result);
			}

			private void OnResultUpdated(RetrieveProgressResult result)
			{
				Coordinator.OnResultUpdated(result);
			}

			protected void OnCancelRequested()
			{
				Coordinator.OnStatusChanged(RetrieveStatus.Canceled, _result);
				//_result.Status = RetrieveStatus.Canceled;
				//_result.ProgressMessage = null;
				Coordinator.OnCommandExecuted();

				OnResultUpdated(_result);
			}

			protected bool IsCancelRequested()
			{
				return _result.Status == RetrieveStatus.CancelRequested;
			}

			protected void OnProgressUpdated(string message)
			{
				Coordinator.OnStatusChanged(_result.Status, message, _result);
			}

			protected void OnStatusChanged(RetrieveStatus status)
			{
				Coordinator.SetStatus(status, _result);
			}

			protected void OnStatusChanged(RetrieveStatus status, string message)
			{
				Coordinator.SetStatus(status, message, _result);
			}

			protected void OnError(string errorMessage)
			{
				Coordinator.OnStatusChanged(RetrieveStatus.Error, errorMessage, _result);
				//_result.Status = RetrieveStatus.Error;
				//if (!string.IsNullOrEmpty(errorMessage))
				//    _result.ProgressMessage = errorMessage;
				//OnResultUpdated(_result);
			}

			public RetrieveProgressResult Result
			{
				get { return _result; }
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
		}
	}
}
