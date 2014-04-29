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

using System.Security;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Explorer;
using ClearCanvas.Desktop.Tables;
using ClearCanvas.Desktop.Tools;

namespace SearchComponent
{
	public class NBIASearchResultsToolExtensionPoint : ExtensionPoint<ITool>
	{
	}

	[ExtensionOf(typeof(HealthcareArtifactExplorerExtensionPoint))]
	public class NBIAExplorer : GridExplorerBase // IHealthcareArtifactExplorer
	{
		public const string MenuSite = "nbia-contextmenu";
		public const string ToolbarSite = "nbia-toolbar";
		internal static readonly string ToolNamespace = typeof(NBIAExplorer).FullName;

		#region IHealthcareArtifactExplorer Members

		public override string Name
		{
			get { return "NBIA Data Service"; }
		}

		#endregion

		protected override IApplicationComponent CreateComponent()
		{
			NBIASearchCoordinator coordinator = new NBIASearchCoordinator();
			NBIASearchCriteriaComponent nbiaSearchCriteriaComponent = new NBIASearchCriteriaComponent(coordinator);

			Table<NBIASearchResult> table = new Table<NBIASearchResult>();
			InitializeResultsTable(table);
			SearchResultsComponent resultsComponent = new SearchResultsComponent(ToolbarSite, MenuSite, ToolNamespace, new NBIASearchResultsToolExtensionPoint(), table);

			coordinator.SetSearchResultsComponent(resultsComponent);

			SplitPane topPane = new SplitPane("Search", nbiaSearchCriteriaComponent, true);
			//SplitPane bottomPane = new SplitPane("Results", resultsComponent, false);

			SplitPane bottomTopPane = new SplitPane("Results", resultsComponent, 2.0f);
			SplitPane bottopBottomPane = new SplitPane("Retrieve Progress", base.CreateRetrieveProgressComponent(), 1.0f);

			SplitPane bottomPane = new SplitPane("All Results", new SplitComponentContainer(bottomTopPane, bottopBottomPane, SplitOrientation.Horizontal), false);

			return new SplitComponentContainer(topPane, bottomPane, SplitOrientation.Horizontal);
		}

		private void InitializeResultsTable(Table<NBIASearchResult> table)
		{
			TableColumn<NBIASearchResult, string> column;

			column = new TableColumn<NBIASearchResult, string>("Patient Id", delegate(NBIASearchResult result) { return result.Patient.PatientId ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
			column = new TableColumn<NBIASearchResult, string>("Patient's Name", delegate(NBIASearchResult result) { return result.Patient.PatientsName ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
			column = new TableColumn<NBIASearchResult, string>("Sex", delegate(NBIASearchResult result) { return result.Patient.PatientsSex ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
			column = new TableColumn<NBIASearchResult, string>("DOB",
				delegate(NBIASearchResult result)
				{ return result.Patient.PatientBirthDate.HasValue ? result.Patient.PatientBirthDate.Value.ToString(Format.DateFormat) : ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);

			column = new TableColumn<NBIASearchResult, string>("Project", delegate(NBIASearchResult result) { return result.TrialDataProvenance.Project ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
			// Unused columns
			//column = new TableColumn<NBIASearchResult, string>("Protocol Id", delegate(NBIASearchResult result) { return result.ClinicalTrialProtocol.ProtocolId ?? ""; }, 0.25F);
			//column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			//table.Columns.Add(column);
			//column = new TableColumn<NBIASearchResult, string>("Protocol Name", delegate(NBIASearchResult result)
			//	{ return result.ClinicalTrialProtocol.ProtocolName ?? ""; }, 0.25F);
			//column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			//table.Columns.Add(column);
			column = new TableColumn<NBIASearchResult, string>("Study Instance UID", delegate(NBIASearchResult result) { return result.Study.StudyInstanceUid ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
			column = new TableColumn<NBIASearchResult, string>("Modality", delegate(NBIASearchResult result) { return result.Series.Modality ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
			// Unused columns
			//column = new TableColumn<NBIASearchResult, string>("Site Id", delegate(NBIASearchResult result) { return result.ClinicalTrialSite.SiteId ?? ""; }, 0.25F);
			//column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			//table.Columns.Add(column);
			//column = new TableColumn<NBIASearchResult, string>("Site Name", delegate(NBIASearchResult result) { return result.ClinicalTrialSite.SiteName ?? ""; }, 0.25F);
			//column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			//table.Columns.Add(column);
		}
	}
}
