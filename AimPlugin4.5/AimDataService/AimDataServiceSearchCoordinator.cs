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
using System.Threading;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Tables;

namespace AimDataService
{
    internal partial class AimDataServiceSearchCoordinator
    {
        private const int Concurrency = 5;

        private readonly object _syncLock = new object();
        private readonly SimpleBlockingThreadPool _threadPool = new SimpleBlockingThreadPool(Concurrency);

        private volatile bool _cancel;
        private int _commandsExecuted;
        private volatile bool _resultsAdded;
        private int _totalCommandsToExecute;
        private SynchronizationContext _uiThreadSynchronizationContext;

        private Table<AimeAnnotationContainer> ResultsTable
        {
            get { return (Table<AimeAnnotationContainer>) SearchResultsComponent.Table; }
        }

        public AimDataServiceSearchResultsComponent SearchResultsComponent { get; set; }

        internal AimDataServiceSearchCriteriaComponent CriteriaComponent { get; set; }

        public void CancelSearch()
        {
            _cancel = true;
        }

        public void Reset()
        {
            SearchResultsComponent.Table.Items.Clear();

            _cancel = false;
            _resultsAdded = false;

            SearchResultsComponent.Title = "Search Results";
        }

        private void SetError(string errorMessage)
        {
            SearchResultsComponent.ErrorMessage = errorMessage;
        }

        protected virtual void OnQueryComplete()
        {
            _threadPool.Stop(true);
            SearchResultsComponent.Title = String.Format("{0} results found", SearchResultsComponent.Table.Items.Count);
        }

        private void AddResultsToTable(IEnumerable<AimeAnnotationContainer> results)
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
                    if (SearchResultsComponent.IsStarted)
                    {
                        if (results != null)
                            foreach (AimeAnnotationContainer result in results)
                                ResultsTable.Items.Add(result);
                    }

                    _resultsAdded = true;
                    Monitor.Pulse(_syncLock);
                }

                SearchResultsComponent.Title = String.Format("{0} results found. Searching for study details...",
                                                             ResultsTable.Items.Count);
            }
        }

        private void OnResultUpdated(AimeAnnotationContainer result)
        {
            if (SynchronizationContext.Current != _uiThreadSynchronizationContext)
            {
                _uiThreadSynchronizationContext.Post(delegate { OnResultUpdated(result); }, null);
            }
            else
            {
                if (SearchResultsComponent.IsStarted)
                    ResultsTable.Items.NotifyItemUpdated(result);
            }
        }

        private void OnCommandExecuted()
        {
            if (Interlocked.Increment(ref _commandsExecuted) == _totalCommandsToExecute)
                _uiThreadSynchronizationContext.Post(delegate { OnQueryComplete(); }, null);
        }

        public void PerformSearch()
        {
            var initialSearchCommand = new AimDataServiceSearchCommand();

            initialSearchCommand.Coordinator = this;
            SearchResultsComponent.Table.Items.Clear();

            _uiThreadSynchronizationContext = SynchronizationContext.Current;

            _totalCommandsToExecute = 1;
            _commandsExecuted = 0;

            _cancel = false;
            _resultsAdded = false;

            SearchResultsComponent.Title = "Searching...";

            ApiKeyCredentials credentials = AimDataServiceLoginTool.Credentials;

            if (credentials == null)
            {
                AimDataServiceLoginTool.RequestLogin();
                credentials = AimDataServiceLoginTool.Credentials;
            }

            if (credentials != null)
            {
                _threadPool.Start();
                _threadPool.Enqueue(initialSearchCommand.Execute);
            }
        }
    }
}
