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
using ClearCanvas.Desktop.Tables;

namespace AimDataService
{
    internal partial class AimDataServiceSearchCoordinator
    {
        #region Nested type: AimDataServiceSearchCommand

        internal class AimDataServiceSearchCommand
        {
            internal AimDataServiceSearchCoordinator Coordinator { get; set; }

            private AimDataServiceSearchResultsComponent ResultsComponent
            {
                get { return Coordinator.SearchResultsComponent; }
            }

            private Table<AimeAnnotationContainer> ResultsTable
            {
                get { return (Table<AimeAnnotationContainer>) ResultsComponent.Table; }
            }

            protected IList<AimeAnnotationContainer> SearchResults
            {
                get { return ResultsTable.Items; }
            }

            protected bool CancelRequested
            {
                get { return Coordinator._cancel; }
            }

            protected void SetError(string errorMessage)
            {
                Coordinator.SetError(errorMessage);
            }

            protected void AddResultsToTable(IEnumerable<AimeAnnotationContainer> results)
            {
                Coordinator.AddResultsToTable(results);
            }

            protected void OnResultUpdated(AimeAnnotationContainer result)
            {
                Coordinator.OnResultUpdated(result);
            }

            protected void OnCommandExecuted()
            {
                Coordinator.OnCommandExecuted();
            }

            protected void EnqueueNextCommand(AimDataServiceSearchCommand nextCommand)
            {
                nextCommand.Coordinator = Coordinator;
                Coordinator._totalCommandsToExecute++;
                Coordinator._threadPool.Enqueue(nextCommand.Execute);
            }

            private List<AimeAnnotationContainer> Find()
            {
                var results = new List<AimeAnnotationContainer>();
                AimeSearchCriteria searchCriteria = Coordinator.CriteriaComponent.SearchCriteria;
                ApiKeyCredentials credentials = AimDataServiceLoginTool.Credentials;

                if (!String.IsNullOrEmpty(credentials.ApiKey))
                    results = AimeWebService.Find(credentials.ApiKey, searchCriteria);
                return results;
            }

            public void Execute()
            {
                List<AimeAnnotationContainer> results = null;

                try
                {
                    results = Find();
                }
                catch (Exception ex)
                {
                    // TODO: Smarter handling of invalid credentials/expiring credentials
                    if (ex.Message.Contains("401"))
                        AimDataServiceLoginTool.Credentials = null;
                }

                AddResultsToTable(results);

                OnCommandExecuted();
            }
        }

        #endregion
    }
}
