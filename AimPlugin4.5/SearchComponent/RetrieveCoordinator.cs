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
using System.Text;
using System.Threading;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	[Flags]
	public enum RetrieveStatus
	{
		Unknown,
		Queued,
		InProgress,
		Completed,
		CancelRequested,
		Canceled,
		Error
	}

	// Singleton class for managing study retrieval & importation
	internal partial class RetrieveCoordinator
	{
		private static readonly RetrieveCoordinator _instance = new RetrieveCoordinator();

		private readonly SimpleBlockingThreadPool _threadPool = new SimpleBlockingThreadPool(2, true);

		private SynchronizationContext _uiThreadSynchronizationContext;
		private readonly object _syncLock = new object();

		private long _totalCommandsToExecute = 0;
		private long _commandsExecuted = 0;

		private bool _startCalled = false;

		private readonly ITable _table;


		protected RetrieveCoordinator()
		{
			Table<RetrieveProgressResult> table = new Table<RetrieveProgressResult>();
			InitializeRetrieveProgressTable(table);
			_table = table;
		}


		// Explicit static constructor to tell C# compiler
		// not to mark type as beforefieldinit
		static RetrieveCoordinator()
		{
		}

		internal static RetrieveCoordinator Coordinator
		{
			get { return _instance; }
		}

		public void RetrieveStudies(List<RetrieveQueryItem> retrieveQueryItems)
		{
			if (retrieveQueryItems == null || retrieveQueryItems.Count == 0)
				return;

			this.EnqueueCommand(new NBIARetrieveCommand(retrieveQueryItems));
		}

		public ITable Table
		{
			get { return _table; }
		}

		private Table<RetrieveProgressResult> ResultsTable
		{
			get { return (Table<RetrieveProgressResult>)_table; }
		}

		protected void EnqueueCommand(RetrieveCommand command)
		{
			if (!_startCalled)
				_uiThreadSynchronizationContext = SynchronizationContext.Current;

			OnResultAdded(command.Result);

			Interlocked.Increment(ref _totalCommandsToExecute);
			_threadPool.Enqueue(command.Execute);

			lock (_syncLock)
			{
				_threadPool.Start();
				_startCalled = true;
			}
		}

		public void CancelAll()
		{
			lock (_syncLock)
			{
				_threadPool.Stop();
				_startCalled = false;
			}
		}

		//public void ClearCompletedResults()
		//{
		//    foreach (RetrieveProgressResult result in ResultsTable.Items)
		//    {
		//        if (result.Status == RetrieveStatus.Completed || result.Status == RetrieveStatus.Canceled)
		//            ResultsTable.Items.Remove(result);
		//    }
		//}

		public void CancelRetrieve(RetrieveProgressResult result)
		{
			this.SetStatus(RetrieveStatus.CancelRequested, result);
		}

		public void RemoveResult(RetrieveProgressResult result)
		{
			OnResultRemoved(result);
		}

		protected void SetStatus(RetrieveStatus status, RetrieveProgressResult result)
		{
			if (result != null && status != result.Status)
			{
				OnStatusChanged(status, result);
			}
		}

		protected void SetStatus(RetrieveStatus status, string message, RetrieveProgressResult result)
		{
			if (result != null && status != result.Status)
			{
				OnStatusChanged(status, message, result);
			}
		}

		protected virtual void OnQueryComplete()
		{
			lock (_syncLock)
			{
				_threadPool.Stop(true);
				//_progressComponent.Title = "Finished retrieving studies";
			}
		}

		protected void OnCommandExecuted()
		{
			if (Interlocked.Increment(ref _commandsExecuted) == _totalCommandsToExecute)
				_uiThreadSynchronizationContext.Post(delegate { OnQueryComplete(); }, null);
		}

		protected void OnResultUpdated(RetrieveProgressResult result)
		{
			if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
			{
				_uiThreadSynchronizationContext.Post(delegate { OnResultUpdated(result); }, null);
			}
			else
			{
				ResultsTable.Items.NotifyItemUpdated(result);
			}
		}

		protected void OnResultAdded(RetrieveProgressResult result)
		{
			if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
			{
				_uiThreadSynchronizationContext.Post(delegate { OnResultAdded(result); }, null);
			}
			else
			{
				ResultsTable.Items.Add(result);
			}
		}

		protected void OnResultRemoved(RetrieveProgressResult result)
		{
			if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
			{
				_uiThreadSynchronizationContext.Post(delegate { OnResultRemoved(result); }, null);
			}
			else
			{
				ResultsTable.Items.Remove(result);
			}
		}

		protected void OnStatusChanged(RetrieveStatus status, RetrieveProgressResult result)
		{
			if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
			{
				_uiThreadSynchronizationContext.Post(delegate { OnStatusChanged(status, result); }, null);
			}
			else
			{
				result.Status = status;
				ResultsTable.Items.NotifyItemUpdated(result);
			}
		}

		protected void OnStatusChanged(RetrieveStatus status, string message, RetrieveProgressResult result)
		{
			if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
			{
				_uiThreadSynchronizationContext.Post(delegate { OnStatusChanged(status, message, result); }, null);
			}
			else
			{
				result.Status = status;
				result.ProgressMessage = string.IsNullOrEmpty(message) ? "" : message;
				ResultsTable.Items.NotifyItemUpdated(result);
			}
		}

		private void InitializeRetrieveProgressTable(Table<RetrieveProgressResult> table)
		{
			TableColumn<RetrieveProgressResult, string> column;

			column = new TableColumn<RetrieveProgressResult, string>("Status", delegate(RetrieveProgressResult result)
			{
				string msg = string.IsNullOrEmpty(result.ProgressMessage)
								? null
								: result.ProgressMessage;

				switch (result.Status)
				{
					case RetrieveStatus.Queued:
						return "Waiting";
					case RetrieveStatus.InProgress:
						return msg ?? "Downloading...";
					case RetrieveStatus.Canceled:
						return "Canceled";
					case RetrieveStatus.Completed:
						return "Done";
					case RetrieveStatus.CancelRequested:
						return string.Format("{0}...Canceling", msg ?? "");
				}
				return msg ?? "";
			}, 0.25F);
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Study Count", delegate(RetrieveProgressResult result)
			{
				return result.QueryItems.Count.ToString();
			}, 0.05F);
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Patient Id", delegate(RetrieveProgressResult result)
			{
				switch (result.QueryItems.Count)
				{
					case 0:
						break;
					case 1:
						return result.QueryItems[0].Patient.PatientId ?? "";
					default:
						return string.Format("1. {0}...", result.QueryItems[0].Patient.PatientId ?? "");
				}
				return "";
			}, 0.25F);
			column.TooltipTextProvider =
				delegate(RetrieveProgressResult result)
				{
					if (result.QueryItems.Count > 1)
					{
						List<string> tooltipList = new List<string>();
						int cnt = 0;
						foreach (RetrieveQueryItem queryItem in result.QueryItems)
						{
							tooltipList.Add(string.Format("{0}. {1}", ++cnt, queryItem.Patient.PatientId ?? ""));
						}

						return StringUtilities.Combine(tooltipList, "\n");
					}

					return result.QueryItems.Count > 0 ? result.QueryItems[0].Patient.PatientId ?? "" : "";
				};
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Patient's Name", delegate(RetrieveProgressResult result)
			{
				switch (result.QueryItems.Count)
				{
					case 0:
						break;
					case 1:
						return result.QueryItems[0].Patient.PatientsName ?? "";
					default:
						return string.Format("1. {0}...", result.QueryItems[0].Patient.PatientsName ?? "");
				}
				return "";
			}, 0.25F);
			column.TooltipTextProvider =
				delegate(RetrieveProgressResult result)
				{
					if (result.QueryItems.Count > 1)
					{
						List<string> tooltipList = new List<string>();
						int cnt = 0;
						foreach (RetrieveQueryItem queryItem in result.QueryItems)
						{
							tooltipList.Add(string.Format("{0}. {1}", ++cnt, queryItem.Patient.PatientsName ?? ""));
						}

						return StringUtilities.Combine(tooltipList, "\n");
					}

					return result.QueryItems.Count > 0 ? result.QueryItems[0].Patient.PatientsName ?? "" : "";
				};
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Study", delegate(RetrieveProgressResult result)
			{
				switch (result.QueryItems.Count)
				{
					case 0:
						break;
					case 1:
						return result.QueryItems[0].Study.StudyInstanceUid ?? "";
					default:
						return string.Format("1. {0}...", result.QueryItems[0].Study.StudyInstanceUid ?? "");
				}
				return "";

			}, 0.25F);
			column.TooltipTextProvider =
				delegate(RetrieveProgressResult result)
				{
					if (result.QueryItems.Count > 1)
					{
						List<string> tooltipList = new List<string>();
						int cnt = 0;
						foreach (RetrieveQueryItem queryItem in result.QueryItems)
						{
							tooltipList.Add(string.Format("{0}. {1}", ++cnt, queryItem.Study.StudyInstanceUid ?? ""));
						}

						return StringUtilities.Combine(tooltipList, "\n");
					}

					return result.QueryItems.Count > 0 ? result.QueryItems[0].Study.StudyInstanceUid ?? "" : "";
				};
			table.Columns.Add(column);
		}

	}
}
