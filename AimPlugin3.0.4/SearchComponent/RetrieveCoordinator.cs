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
