#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using System.IO;
using ClearCanvas.Common;
using ClearCanvas.ImageViewer.Services.LocalDataStore;

namespace SearchComponent
{
	internal partial class RetrieveCoordinator
	{
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

			protected void OnCommandCompleted()
			{
				Coordinator.OnStatusChanged(RetrieveStatus.Completed, _result);
			}

			protected void OnCommandCompleted(string message)
			{
				Coordinator.OnStatusChanged(RetrieveStatus.Completed, message, _result);
			}

			private void OnResultUpdated(RetrieveProgressResult result)
			{
				Coordinator.OnResultUpdated(result);
			}

			protected void OnCancelRequested()
			{
				Coordinator.OnStatusChanged(RetrieveStatus.Canceled, _result);
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
			}

			public RetrieveProgressResult Result
			{
				get { return _result; }
			}

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
					catch (Exception)
					{
						client.Abort();
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
		}
	}
}
