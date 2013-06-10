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
using System.Threading;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	internal partial class SearchCoordinator<T> where T : class 
	{
		private const int CONCURRENCY = 5;

		private SearchResultsComponent _resultsComponent;
		private readonly SimpleBlockingThreadPool _threadPool = new SimpleBlockingThreadPool(CONCURRENCY);

		private SynchronizationContext _uiThreadSynchronizationContext;
		private readonly object _syncLock = new object();

		private int _totalCommandsToExecute;
		private int _commandsExecuted = 0;

		private volatile bool _cancel = false;
		private volatile bool _resultsAdded = false;

		private Table<T> ResultsTable
		{
			get { return (Table<T>)_resultsComponent.Table; }
		}

		public void SetSearchResultsComponent(SearchResultsComponent resultsComponent)
		{
			_resultsComponent = resultsComponent;
		}

		public void CancelSearch()
		{
			_cancel = true;
		}

		public void Reset()
		{
			_resultsComponent.Table.Items.Clear();

			_cancel = false;
			_resultsAdded = false;

			_resultsComponent.Title = "Search Results";
		}

		protected void PerformSearch(SearchCommand initialSearchCommand)
		{
			initialSearchCommand._coordinator = this;
			_resultsComponent.Table.Items.Clear();

			_uiThreadSynchronizationContext = SynchronizationContext.Current;

			_totalCommandsToExecute = 1;
			_commandsExecuted = 0;

			_cancel = false;
			_resultsAdded = false;

		    _resultsComponent.Title = "Searching...";

			_threadPool.Start();
			_threadPool.Enqueue(initialSearchCommand.Execute);

		}

		private void SetError(string errorMessage)
		{
			_resultsComponent.ErrorMessage = errorMessage;
		}

		protected virtual void OnQueryComplete()
		{
			_threadPool.Stop(true);
			_resultsComponent.Title = String.Format("{0} results found", _resultsComponent.Table.Items.Count);
		}

		private void AddResultsToTable(IEnumerable<T> results)
		{
			if (_resultsAdded)
				throw new InvalidOperationException("Results must all be added at once, then only updated.");

			if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
			{
				lock (_syncLock)
				{
					_uiThreadSynchronizationContext.Post(delegate { AddResultsToTable(results); }, null);
					Monitor.Wait(_syncLock);
				}
			}
			else
			{
				lock (_syncLock)
				{
					if (_resultsComponent.IsStarted)
					{
						foreach (T result in results)
							ResultsTable.Items.Add(result);
					}

					_resultsAdded = true;
					Monitor.Pulse(_syncLock);
				}

		        _resultsComponent.Title = String.Format("{0} results found. Searching for study details...", ResultsTable.Items.Count);
			}
		}

		private void OnResultUpdated(T result)
		{
			if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
			{
				_uiThreadSynchronizationContext.Post(delegate { OnResultUpdated(result); }, null);
			}
			else
			{
				if (_resultsComponent.IsStarted)
					ResultsTable.Items.NotifyItemUpdated(result);
			}
		}

		private void OnCommandExecuted()
		{
			if (Interlocked.Increment(ref _commandsExecuted) == _totalCommandsToExecute)
				_uiThreadSynchronizationContext.Post(delegate { OnQueryComplete(); }, null);
		}
	}
}
