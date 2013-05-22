//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Collections.Generic;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;

namespace SearchComponent
{
	[MenuAction("apply", NBIAExplorer.ToolbarSite + "/MenuRetrieveStudy", "Apply")]
    [ButtonAction("apply", NBIAExplorer.MenuSite + "/ToolRetrieveStudy", "Apply")]
	[Tooltip("apply", "Retrieve Selected Studies")]
    [IconSet("apply", IconScheme.Colour, "Icons.NBIARetrieveToolSmall.png", "Icons.NBIARetrieveToolMedium.png", "Icons.NBIARetrieveToolLarge.png")]

    [EnabledStateObserver("apply", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(NBIASearchResultsToolExtensionPoint))]
	public class NBIARetrieveTool : SearchBaseTool
	{
		public NBIARetrieveTool()
		{
		}

        public void Apply()
        {
            ISelection selection = base.Context.Selection;
            if (selection == null || selection.Items == null)
                return;

            List<RetrieveQueryItem> queryItems = new List<RetrieveQueryItem>();
            foreach (NBIASearchResult result in selection.Items)
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
