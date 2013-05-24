#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
