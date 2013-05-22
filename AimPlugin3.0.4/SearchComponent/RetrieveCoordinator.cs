//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
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
