#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Generic;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer.Services.LocalDataStore;

namespace SearchComponent
{
	[MenuAction("apply", AIMExplorer.ToolbarSite + "/MenuRetrieveAnnotationAndStudy", "Apply")]
	[ButtonAction("apply", AIMExplorer.MenuSite + "/ToolRetrieveAnnotationAndStudy", "Apply")]
	[Tooltip("apply", "Retrieve Selected Annotation and Study")]
	[IconSet("apply", IconScheme.Colour, "Icons.AIMRetrieveToolSmall.png", "Icons.AIMRetrieveToolMedium.png", "Icons.AIMRetrieveToolLarge.png")]
	[GroupHint("apply", "Tool.SearchComponent.AimRetrieve.RetrieveWithStudy")]

	[EnabledStateObserver("apply", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(AIMSearchResultsToolExtensionPoint))]
	public class AIMRetrieveAnnotationsAndStudiesTool : AIMSearchToolBase
	{
		public AIMRetrieveAnnotationsAndStudiesTool()
		{
		}

		public void Apply()
		{
			ISelection selection = base.Context.Selection;
			if (selection == null || selection.Item == null)
				return;

			if (!LocalDataStoreActivityMonitor.IsConnected)
			{
				this.Context.DesktopWindow.ShowMessageBox(
					"Not connected to the local data store. Is workstation service running?", MessageBoxActions.Ok);
				return;
			}

			this.RetrieveAnnotationsFromAimService(selection.Items);

			List<RetrieveQueryItem> queryItems = new List<RetrieveQueryItem>();
			foreach (AIMSearchResult result in selection.Items)
			{
				if (!string.IsNullOrEmpty(result.Study.StudyInstanceUid))
				{
					RetrieveQueryItem queryItem = new RetrieveQueryItem();
					queryItem.Study.StudyInstanceUid = result.Study.StudyInstanceUid;
					queryItem.Patient.PatientBirthDate = result.Patient.PatientBirthDate;
					queryItem.Patient.PatientId = result.Patient.PatientId;
					queryItem.Patient.PatientsName = result.Patient.PatientsName;
					queryItem.Patient.PatientsSex = result.Patient.PatientsSex;
					Series series = new Series();
					series.Modality = result.Series.Modality;
					series.SeriesInstanceUid = result.Series.SeriesInstanceUid;
					queryItem.Series.Add(series);

					queryItems.Add(queryItem);
				}
			}

			RetrieveCoordinator.Coordinator.RetrieveStudies(queryItems);
		}
	}
}
