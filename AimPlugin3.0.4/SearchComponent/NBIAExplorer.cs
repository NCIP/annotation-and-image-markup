#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

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
	public class NBIAExplorer : GridExplorerBase
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
            column = new TableColumn<NBIASearchResult, string>("Study Instance Uid", delegate(NBIASearchResult result) { return result.Study.StudyInstanceUid ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
            column = new TableColumn<NBIASearchResult, string>("Modality", delegate(NBIASearchResult result) { return result.Series.Modality ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
		}
	}
}
