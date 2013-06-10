#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Generic;
using System.Security;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Explorer;
using ClearCanvas.Desktop.Tables;
using ClearCanvas.Desktop.Tools;

namespace SearchComponent
{
	public class AIMSearchResultsToolExtensionPoint : ExtensionPoint<ITool>
	{
	}

	[ExtensionOf(typeof(HealthcareArtifactExplorerExtensionPoint))]
	public class AIMExplorer : GridExplorerBase
	{
		public const string MenuSite = "aim-contextmenu";
		public const string ToolbarSite = "aim-toolbar";
		internal static readonly string ToolNamespace = typeof(AIMExplorer).FullName;

		#region IHealthcareArtifactExplorer Members

		public override string Name
		{
			get { return "AIM Data Service"; }
		}

		#endregion

		protected override IApplicationComponent CreateComponent()
		{
			AIMSearchCoordinator coordinator = new AIMSearchCoordinator();
			AIMSearchCriteriaComponent AIMSearchCriteriaComponent = new AIMSearchCriteriaComponent(coordinator);

			Table<AIMSearchResult> table = new Table<AIMSearchResult>();
			InitializeResultsTable(table);
			SearchResultsComponent resultsComponent = new SearchResultsComponent(ToolbarSite, MenuSite, ToolNamespace, new AIMSearchResultsToolExtensionPoint(), table);

			coordinator.SetSearchResultsComponent(resultsComponent);

			SplitPane topPane = new SplitPane("Search", AIMSearchCriteriaComponent, true);
			SplitPane bottomTopPane = new SplitPane("Results", resultsComponent, 2.0f);
			SplitPane bottopBottomPane = new SplitPane("Retrieve Progress", CreateRetrieveProgressComponent(), 1.0f);
			SplitPane bottomPane = new SplitPane("All Results", new SplitComponentContainer(bottomTopPane, bottopBottomPane, SplitOrientation.Horizontal), false);

			return new SplitComponentContainer(topPane, bottomPane, SplitOrientation.Horizontal);
		}

        private void InitializeResultsTable(Table<AIMSearchResult> table)
        {
            TableColumn<AIMSearchResult, string> column;

            column = new TableColumn<AIMSearchResult, string>("Patient Id", delegate(AIMSearchResult result) { return result.Patient.PatientId ?? ""; }, 0.1F);
        	column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);
            column = new TableColumn<AIMSearchResult, string>("Patient's Name", delegate(AIMSearchResult result) { return result.Patient.PatientsName ?? ""; },
                                                              0.15F);
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
            column = new TableColumn<AIMSearchResult, string>("Sex", delegate(AIMSearchResult result) { return result.Patient.PatientsSex ?? ""; }, 0.05F);
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
            column = new TableColumn<AIMSearchResult, string>("DOB",
                                                              delegate(AIMSearchResult result)
                                                                  {
                                                                      return (result.Patient.PatientBirthDate.HasValue
                                                                                  ? result.Patient.PatientBirthDate.Value.ToString(Format.DateFormat)
                                                                                  : "");
                                                                  }
                                                              , 0.1F);
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);

            column = new TableColumn<AIMSearchResult, string>(
				"Anatomic Entities",
				delegate(AIMSearchResult result)
				{
					string text = string.Empty;
					foreach (AnatomicEntity entity in result.AnatomicEntities)
						text += entity.CodeMeaning + ", ";
					if (!string.IsNullOrEmpty(text))
						text = text.Substring(0, text.Length - 2);
					return text;
				},
				.25f);
            column.TooltipTextProvider = AETooltipConverter;
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);

			column = new TableColumn<AIMSearchResult, string>(
				"Anatomic Entity Characteristics",
				delegate(AIMSearchResult result)
				{
					string text = string.Empty;
					foreach (AnatomicEntityCharacteristic characteristic in result.AnatomicEntityCharacteristics)
						text += characteristic.CodeMeaning + ", ";
					if (!string.IsNullOrEmpty(text))
						text = text.Substring(0, text.Length - 2);
					return text;
				},
				.30f);
			column.TooltipTextProvider = AECTooltipConverter;
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);

            column = new TableColumn<AIMSearchResult, string>(
				"Imaging Observations",
                delegate(AIMSearchResult result)
				{
					string text = string.Empty;
					foreach (ImagingObservation observation in result.ImagingObservations)
						text += observation.CodeMeaning + ", ";
					if (!string.IsNullOrEmpty(text))
						text = text.Substring(0, text.Length - 2);
					return text;
				},
				.25f);
            column.TooltipTextProvider = IOTooltipConverter;
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);

			column = new TableColumn<AIMSearchResult, string>(
				"Imaging Observation Characteristics",
				delegate(AIMSearchResult result)
				{
					string text = string.Empty;
					foreach (ImagingObservationCharacteristic characteristic in result.ImagingObservationCharacteristics)
						text += characteristic.CodeMeaning + ", ";
					if (!string.IsNullOrEmpty(text))
						text = text.Substring(0, text.Length - 2);
					return text;
				},
				.3f);
			column.TooltipTextProvider = IOCTooltipConverter;
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);

			column = new TableColumn<AIMSearchResult, string>(
				"User",
				delegate(AIMSearchResult result)
				{
					return result.User.LoginName ?? "";
				},
				.1f);
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);

            column = new TableColumn<AIMSearchResult, string>("Study Instance UID",
                                                              delegate(AIMSearchResult result) { return result.Study.StudyInstanceUid ?? ""; }, 0.25F);
			column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
			table.Columns.Add(column);
        }

        private static string AETooltipConverter(AIMSearchResult result)
        {
            List<string> tooltipList = new List<string>();
            foreach (AnatomicEntity anatomicEntity in result.AnatomicEntities)
            {
                tooltipList.Add(string.Format("[{1}], [{0}], [{2}]", anatomicEntity.CodeValue ?? "", anatomicEntity.CodeMeaning ?? "",
                                anatomicEntity.CodingSchemeDesignator ?? ""));
            }

            return StringUtilities.Combine(tooltipList, "\n");
        }

		private static string AECTooltipConverter(AIMSearchResult result)
		{
			List<string> tooltipList = new List<string>();
			foreach (AnatomicEntityCharacteristic anatomicEntityCharacteristic in result.AnatomicEntityCharacteristics)
			{
				tooltipList.Add(string.Format("[{1}], [{0}], [{2}]", anatomicEntityCharacteristic.CodeValue ?? "", anatomicEntityCharacteristic.CodeMeaning ?? "",
								anatomicEntityCharacteristic.CodingSchemeDesignator ?? ""));
			}

			return StringUtilities.Combine(tooltipList, "\n");
		}

        private static string IOTooltipConverter(AIMSearchResult result)
        {
            List<string> tooltipList = new List<string>();
            foreach (ImagingObservation imagingObservation in result.ImagingObservations)
            {
                tooltipList.Add(string.Format("[{1}], [{0}], [{2}]", imagingObservation.CodeValue ?? "", imagingObservation.CodeMeaning ?? "",
                                imagingObservation.CodingSchemeDesignator ?? ""));
            }

            return StringUtilities.Combine(tooltipList, "\n");
        }

		private static string IOCTooltipConverter(AIMSearchResult result)
		{
			List<string> tooltipList = new List<string>();
			foreach (ImagingObservationCharacteristic imagingObservationCharacteristic in result.ImagingObservationCharacteristics)
			{
				tooltipList.Add(string.Format("[{1}], [{0}], [{2}]", imagingObservationCharacteristic.CodeValue ?? "", imagingObservationCharacteristic.CodeMeaning ?? "",
								imagingObservationCharacteristic.CodingSchemeDesignator ?? ""));
			}

			return StringUtilities.Combine(tooltipList, "\n");
		}
	}
}
