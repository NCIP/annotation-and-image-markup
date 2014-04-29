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
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;

namespace SearchComponent
{
	[MenuAction("apply", NBIAExplorer.ToolbarSite + "/MenuRetrieveStudy", "Apply")]
	[ButtonAction("apply", NBIAExplorer.MenuSite + "/ToolRetrieveStudy", "Apply")]
	[Tooltip("apply", "Retrieve Selected Studies")]
	[IconSet("apply", "Icons.NBIARetrieveToolSmall.png", "Icons.NBIARetrieveToolMedium.png", "Icons.NBIARetrieveToolLarge.png")]

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
