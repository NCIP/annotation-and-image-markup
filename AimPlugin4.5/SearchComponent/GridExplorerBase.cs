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

using System.Collections.Generic;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Explorer;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	public abstract class GridExplorerBase : IHealthcareArtifactExplorer
	{
		protected IApplicationComponent _component;

		#region IHealthcareArtifactExplorer Members

		public IApplicationComponent Component
		{
			get
			{
				if (_component == null)
					_component = CreateComponent();
				return _component;
			}
		}

		public bool IsAvailable
		{
			get { return true; }
		}

		public virtual string Name
		{
			get { return "caGrid Data Service"; }
		}

		#endregion

		protected abstract IApplicationComponent CreateComponent();

		protected RetrieveProgressComponent CreateRetrieveProgressComponent()
		{
			Table<RetrieveProgressResult> table = new Table<RetrieveProgressResult>();
			InitializeRetrieveProgressTable(table);

			RetrieveProgressComponent retrieveProgressComponent =
				new RetrieveProgressComponent(RetrieveProgressComponent.ToolbarSite, RetrieveProgressComponent.MenuSite,
											  RetrieveProgressComponent.ToolNamespace,
											  new RetrieveProgressToolExtensionPoint(), table);

			return retrieveProgressComponent;
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
