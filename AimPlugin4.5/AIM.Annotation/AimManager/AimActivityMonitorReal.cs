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
using System.Linq;
using System.Threading;

using ClearCanvas.Common;
using ClearCanvas.ImageViewer.Common.WorkItem;
using GeneralUtilities.Collections;

namespace AIM.Annotation.AimManager
{
	internal class AimActivityMonitorReal : AimActivityMonitor
	{
		internal static TimeSpan UpdateInterval = TimeSpan.FromSeconds(3);

		private readonly object _syncLock = new object();

		private Thread _connectionThread;
		private bool _disposed;

		private event EventHandler _isConnectedChanged;
		private event EventHandler<StudyAimAnnotationsChangedEventArgs> _studyAnnotationChanged;
		private event EventHandler<StudyAimAnnotationClearedEventArgs> _studiesCleared;

		private volatile IWorkItemActivityMonitor _workItemActivityMonitor;

		// Hack: fight 40 sec delay between study being Idle and Complete
		private volatile HashSet<long> _updatedIdleStudies; // Contains a hash of studies that were reported as Idle by the last ProcessStudy WorkItem

		internal AimActivityMonitorReal()
		{
			_connectionThread = new Thread(MonitorConnection) {IsBackground = true};
			lock (_syncLock)
			{
				_connectionThread.Start();
				Monitor.Wait(_syncLock); //Wait for the thread to start up.
			}
		}

		public override bool IsConnected
		{
			get { return _workItemActivityMonitor != null && _workItemActivityMonitor.IsConnected; }
		}

		public override event EventHandler IsConnectedChanged
		{
			add
			{
				lock (_syncLock)
				{
					_isConnectedChanged += value;
					Monitor.Pulse(_syncLock);
				}
			}
			remove
			{
				lock (_syncLock)
				{
					_isConnectedChanged -= value;
					Monitor.Pulse(_syncLock);
				}
			}
		}

		public override event EventHandler<StudyAimAnnotationsChangedEventArgs> StudyAnnotationsChanged
		{
			add
			{
				lock (_syncLock)
				{
					_studyAnnotationChanged += value;
					Monitor.Pulse(_syncLock);
				}
			}
			remove
			{
				lock (_syncLock)
				{
					_studyAnnotationChanged -= value;
					Monitor.Pulse(_syncLock);
				}
			}
		}

		public override event EventHandler<StudyAimAnnotationClearedEventArgs> StudiesCleared
		{
			add
			{
				lock (_syncLock)
				{
					_studiesCleared += value;
					Monitor.Pulse(_syncLock);
				}
			}
			remove
			{
				lock (_syncLock)
				{
					_studiesCleared -= value;
					Monitor.Pulse(_syncLock);
				}
			}
		}

		private void MonitorConnection(object ignore)
		{
			lock (_syncLock)
			{
				//Try to connect first.
				Connect();

				//startup pulse.
				Monitor.Pulse(_syncLock);
			}

			while (true)
			{
				lock (_syncLock)
				{
					//Check disposed before and after the wait because it could have changed.
					if (_disposed) break;

					Monitor.Wait(_syncLock, UpdateInterval);
					if (_disposed) break;
				}

				Connect();
			}

			DropConnection();
		}

		private void Connect()
		{
			if (_workItemActivityMonitor != null)
				return;

			Platform.Log(LogLevel.Debug, "Attempting to connect to ActivityMonitorService.");

			_workItemActivityMonitor = WorkItemActivityMonitor.Create(false);
			_workItemActivityMonitor.WorkItemsChanged += OnWorkItemsChanged;
			_workItemActivityMonitor.StudiesCleared += OnStudiesCleared;
			_workItemActivityMonitor.IsConnectedChanged += OnIsConnectedChanged;

			_updatedIdleStudies = new HashSet<long>();

			FireIsConnectedChanged();

		}

		private void DropConnection()
		{
			if (_workItemActivityMonitor == null)
				return;

			Platform.Log(LogLevel.Debug, "Attempting to disconnect from ActivityMonitorService.");

			_workItemActivityMonitor.WorkItemsChanged -= OnWorkItemsChanged;
			_workItemActivityMonitor.StudiesCleared -= OnStudiesCleared;
			_workItemActivityMonitor.IsConnectedChanged -= OnIsConnectedChanged;
			_workItemActivityMonitor.Dispose();
			_workItemActivityMonitor = null;

			_updatedIdleStudies.Clear();
			_updatedIdleStudies = null;

			AimCache.Instance.ClearCache();

			FireIsConnectedChanged();
		}

		private void FireIsConnectedChanged()
		{
			Delegate[] delegates;
			lock (_syncLock)
			{
				if (_disposed)
					return;

				delegates = _isConnectedChanged != null ? _isConnectedChanged.GetInvocationList() : new Delegate[0];
			}

			if (delegates.Length > 0)
			{
				//ThreadPool.QueueUserWorkItem(ignore => CallDelegates(delegates, EventArgs.Empty));
				CallDelegates(delegates, EventArgs.Empty);
			}
		}

		private void OnWorkItemsChanged(object sender, WorkItemsChangedEventArgs eventArgs)
		{
			if (eventArgs.EventType != WorkItemsChangedEventType.Update || eventArgs.ChangedItems.IsNullOrEmpty())
				return; // We are only interested in Update events

			foreach (var workItemData in eventArgs.ChangedItems)
			{
				// Fire event when import ends or an item is removed
				if (workItemData.Type == "ProcessStudy")
				{
					if (workItemData.Status == WorkItemStatusEnum.Idle || workItemData.Status == WorkItemStatusEnum.Complete || workItemData.Status == WorkItemStatusEnum.Deleted)
					{
						// HACK: To minimize number of readings of annotation documents, we remember studies that were already updated when their Status == Idle
						long idleKey = 0x3B3402E0 ^ workItemData.Identifier ^ workItemData.StudyInstanceUid.GetHashCode();
						if (workItemData.Status == WorkItemStatusEnum.Idle)
						{
							// NOTE: we cannot skip updating on any Idle status because there could be new SOPs processed just before the Idle status kicked in

							if (!_updatedIdleStudies.Contains(idleKey))
								_updatedIdleStudies.Add(idleKey);
						}
						else
						{
							if (_updatedIdleStudies.Contains(idleKey))
							{
								_updatedIdleStudies.Remove(idleKey);
								continue; // update event was sent already
							}
						}

						DoStudyUpdate(workItemData.StudyInstanceUid);
					}
				}
				else if (workItemData.Type == "DeleteSeries")
				{
					if (workItemData.Status == WorkItemStatusEnum.Complete)
					{
						DoStudyUpdate(workItemData.StudyInstanceUid);
					}
				}
				else if (workItemData.Type == "DeleteStudy")
				{
					if (workItemData.Status == WorkItemStatusEnum.Complete)
					{
						DoStudyUpdate(workItemData.StudyInstanceUid);
					}
				}
			}
		}

		private void DoStudyUpdate(string studyInstanceUid)
		{
			var studyUpdateArgs = AimCache.Instance.UpdateCache(studyInstanceUid);
			if (studyUpdateArgs == null)
				return; // Cache knows of no open study to update

			IList<Delegate> delegates;
			lock (_syncLock)
			{
				if (_disposed)
					return;
				delegates = _studyAnnotationChanged != null ? _studyAnnotationChanged.GetInvocationList() : new Delegate[0];
			}

			if (delegates.Count > 0)
				CallDelegates(delegates, studyUpdateArgs);
		}

		private void OnStudiesCleared(object sender, EventArgs args)
		{
			var studyList = AimCache.Instance.ClearCache();

			if (!studyList.Any())
				return;

			IList<Delegate> delegates;
			lock (_syncLock)
			{
				delegates = _studiesCleared != null ? _studiesCleared.GetInvocationList() : new Delegate[0];
			}

			if (delegates.Count > 0)
			{
				var clearedEvent = new StudyAimAnnotationClearedEventArgs(studyList);
				CallDelegates(delegates, clearedEvent);
			}
		}

		private void OnIsConnectedChanged(object sender, EventArgs eventArgs)
		{
			FireIsConnectedChanged();
		}

		private void CallDelegates(IEnumerable<Delegate> delegates, EventArgs e)
		{
			foreach (var @delegate in delegates)
			{
				try
				{
					@delegate.DynamicInvoke(this, e);
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Error encountered while firing event.");
				}
			}
		}

		protected override void Dispose(bool disposing)
		{
			if (!disposing)
				return;

			lock (_syncLock)
			{
				if (_disposed)
					return;

				_disposed = true; //Setting disposed causes the thread to stop.
				Monitor.Pulse(_syncLock);

				//Don't bother joining - no point.
				_connectionThread = null;
			}
		}
	}
}
