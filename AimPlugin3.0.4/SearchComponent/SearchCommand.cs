#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Generic;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	internal partial class SearchCoordinator<T> where T : class 
	{
		protected abstract class SearchCommand
		{
			internal SearchCoordinator<T> _coordinator;

			protected int _currentCommandIndex = -1;

			protected SearchCommand()
			{ }

			protected SearchCommand(SearchCoordinator<T> coordinator)
			{
				_coordinator = coordinator;
			}

			private SearchResultsComponent ResultsComponent
			{
				get { return _coordinator._resultsComponent; }
			}

			private Table<T> ResultsTable
			{
				get { return (Table<T>)ResultsComponent.Table; }
			}

			protected IList<T> SearchResults
			{
				get { return ResultsTable.Items; }
			}

			protected void SetError(string errorMessage)
			{
				_coordinator.SetError(errorMessage);
			}

			protected bool CancelRequested
			{
				get { return _coordinator._cancel; }
			}

			public abstract void Execute();

			protected void AddResultsToTable(IEnumerable<T> results)
			{
				_coordinator.AddResultsToTable(results);
			}

			protected void OnResultUpdated(T result)
			{
				_coordinator.OnResultUpdated(result);
			}

			protected void OnCommandExecuted()
			{
				_coordinator.OnCommandExecuted();
			}

			protected void EnqueueNextCommand(SearchCommand nextCommand)
			{
				nextCommand._coordinator = _coordinator;
			    _coordinator._totalCommandsToExecute++;
				_currentCommandIndex = _coordinator._totalCommandsToExecute;
				_coordinator._threadPool.Enqueue(nextCommand.Execute);
			}
		}
	}
}
