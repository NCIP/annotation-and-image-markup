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
using System.Linq;
using System.Security;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Explorer;
using ClearCanvas.Desktop.Tables;
using ClearCanvas.Desktop.Tools;
using AimDataService.Configuration;

namespace AimDataService
{
    public class AimSearchResultsToolExtensionPoint : ExtensionPoint<ITool>
    {
    }

    [ExtensionOf(typeof(HealthcareArtifactExplorerExtensionPoint))]
    public class AimDataServiceExplorer : IHealthcareArtifactExplorer
    {
        private IApplicationComponent _component;
        public const string MenuSite = "aim-contextmenu";
        public const string ToolbarSite = "aim-toolbar";
        internal static readonly string ToolNamespace = typeof(AimDataServiceExplorer).FullName;

        #region IHealthcareArtifactExplorer Members
        public string Name
        {
            get { return "AIM Data Service 2.0"; }
        }

        public bool IsAvailable
        {
            get { return true; }
        }

        public IApplicationComponent Component
        {
            get
            {
                if (_component == null)
                    _component = CreateComponent();
                return _component;
            }
        }
        #endregion

        public IApplicationComponent CreateComponent()
        {
            var table = new Table<AimeAnnotationContainer>();
            InitializeResultsTable(table);

            var coordinator = new AimDataServiceSearchCoordinator();
            var criteriaComponent = new AimDataServiceSearchCriteriaComponent(coordinator);
            coordinator.CriteriaComponent = criteriaComponent;
            var topPane = new SplitPane("Search", criteriaComponent, true);

            var searchResultsComponent = new AimDataServiceSearchResultsComponent(
                ToolbarSite,
                MenuSite,
                ToolNamespace,
                new AimSearchResultsToolExtensionPoint(),
                table);

            coordinator.SearchResultsComponent = searchResultsComponent;

            var bottomPane = new SplitPane("Results", searchResultsComponent, false);

            return new SplitComponentContainer(topPane, bottomPane, SplitOrientation.Horizontal);
        }

        private static void InitializeResultsTable(Table<AimeAnnotationContainer> table)
        {
            var column = new TableColumn<AimeAnnotationContainer, string>("Patient's Name", delegate(AimeAnnotationContainer result) { return result.PatientName ?? ""; },
                                                              0.15F);
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);
            column = new TableColumn<AimeAnnotationContainer, string>("Sex", delegate(AimeAnnotationContainer result) { return result.PatientSex ?? ""; }, 0.05F);
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);

            // TODO
            //column = new TableColumn<AimSearchResult, string>("DOB",
            //                                                  delegate(AimSearchResult result)
            //                                                      {
            //                                                          return (result.Patient.PatientBirthDate.HasValue
            //                                                                      ? result.Patient.PatientBirthDate.Value.ToString(Format.DateFormat)
            //                                                                      : "");
            //                                                      }
            //                                                  , 0.1F);
            //column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            //table.Columns.Add(column);

            // Imaging Annotation/Annotation of Annotation Column
            column = new TableColumn<AimeAnnotationContainer, string>(
                "IA/AA",
                delegate(AimeAnnotationContainer result)
                {
                    if (result.AnnotationType == "ImageAnnotation")
                        return "IA";
                    if (result.AnnotationType == "AnnnotationOfAnnotation")
                        return "AA";

                    return "Unknown";
                },
                .07f);
            column.TooltipTextProvider = AETooltipConverter;
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);

            // Imaging Physical Entities Column
            column = new TableColumn<AimeAnnotationContainer, string>(
                "Imaging Physical Entities",
                delegate(AimeAnnotationContainer result)
                {
                    string text = (from annotation in result.Annotations
                                   where annotation.ImagingPhysicalEntities != null
                                   from observation in annotation.ImagingPhysicalEntities
                                   select observation).Aggregate(string.Empty, (current, observation) => current + (observation.TypeCodes[0].DisplayName.Value + ", "));
                    if (!string.IsNullOrEmpty(text))
                        text = text.Substring(0, text.Length - 2);
                    return text;
                },
                .25f);
            column.TooltipTextProvider = AETooltipConverter;
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);

            // Imaging Physical Entity Characteristics Column
            column = new TableColumn<AimeAnnotationContainer, string>(
                "Imaging Physical Entity Characteristics",
                delegate(AimeAnnotationContainer result)
                {
                    string text = (from annotation in result.Annotations where annotation.ImagingPhysicalEntities != null
                                   from observation in annotation.ImagingPhysicalEntities
                                   where observation.ImagingPhysicalEntityCharacteristicCollection != null &&
                                   observation.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics != null 
                                   from characteristic in observation.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics
                                   select characteristic).Aggregate(string.Empty, (current, characteristic) => current + (characteristic.TypeCodes[0].DisplayName.Value + ", "));
                    if (!string.IsNullOrEmpty(text))
                        text = text.Substring(0, text.Length - 2);
                    return text;
                },
                .30f);
            column.TooltipTextProvider = AECTooltipConverter;
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);

            // Imaging Observations Column
            column = new TableColumn<AimeAnnotationContainer, string>(
                "Imaging Observations",
                delegate(AimeAnnotationContainer result)
                {
                    string text = (from annotation in result.Annotations
                                   where annotation.ImagingObservations != null
                                   from observation in annotation.ImagingObservations
                                   select observation).Aggregate(string.Empty, (current, observation) => current + (observation.TypeCodes[0].DisplayName.Value + ", "));

                    if (!string.IsNullOrEmpty(text))
                        text = text.Substring(0, text.Length - 2);
                    return text;
                },
                .25f);
            column.TooltipTextProvider = IOTooltipConverter;
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);

            // Imaging Observation Characteristics Column
            column = new TableColumn<AimeAnnotationContainer, string>(
                "Imaging Observation Characteristics",
                delegate(AimeAnnotationContainer result)
                {
                    string text = (from annotation in result.Annotations where annotation.ImagingObservations != null 
                                   from observation in annotation.ImagingObservations 
                                   where observation.ImagingPhysicalEntityCharacteristicCollection != null && 
                                   observation.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics != null 
                                   from characteristic in observation.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics 
                                   select characteristic).Aggregate(string.Empty, (current, characteristic) => current + (characteristic.TypeCodes[0].DisplayName.Value + ", "));
                    if (!string.IsNullOrEmpty(text))
                        text = text.Substring(0, text.Length - 2);
                    return text;
                },
                .3f);
            column.TooltipTextProvider = IOCTooltipConverter;
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);

            // User Column
            column = new TableColumn<AimeAnnotationContainer, string>(
                "User",
                delegate(AimeAnnotationContainer result)
                {
                    return result.User ?? "";
                },
                .1f);
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);

            // Study UID Column
            column = new TableColumn<AimeAnnotationContainer, string>("Study Instance UID",
                                                              delegate(AimeAnnotationContainer result) { return result.Annotations[0].StudyInstanceUid ?? ""; }, 0.25F);
            column.Visible = !SearchSettings.Default.AimSearchHiddenColumns.Contains(SecurityElement.Escape(column.Name));
            table.Columns.Add(column);
        }

        private static string AETooltipConverter(AimeAnnotationContainer result)
        {
            List<string> tooltipList = (from annotation in result.Annotations
                                        where annotation.ImagingPhysicalEntities != null
                                        from entity in annotation.ImagingPhysicalEntities
                                        select string.Format("[{1}], [{0}], [{2}]", entity.TypeCodes[0].Code ?? "", entity.TypeCodes[0].DisplayName.Value ?? "", entity.TypeCodes[0].CodeSystemName ?? "")).ToList();
            

            return StringUtilities.Combine(tooltipList, "\n");
        }

        private static string AECTooltipConverter(AimeAnnotationContainer result)
        {
            List<string> tooltipList = (from annotation in result.Annotations
                                        where annotation.ImagingPhysicalEntities != null
                                        from entity in annotation.ImagingPhysicalEntities
                                        where entity.ImagingPhysicalEntityCharacteristicCollection != null &&
                                        entity.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics != null
                                        from imagingObservationCharacteristic in entity.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics
                                        select string.Format("[{1}], [{0}], [{2}]", imagingObservationCharacteristic.TypeCodes[0].Code ?? "", imagingObservationCharacteristic.TypeCodes[0].DisplayName.Value ?? "", imagingObservationCharacteristic.TypeCodes[0].CodeSystemName ?? "")).ToList();

            return StringUtilities.Combine(tooltipList, "\n");
        }

        private static string IOTooltipConverter(AimeAnnotationContainer result)
        {
            List<string> tooltipList = (from annotation in result.Annotations
                                        where annotation.ImagingObservations != null
                                        from imagingObservation in annotation.ImagingObservations
                                        select string.Format("[{1}], [{0}], [{2}]", imagingObservation.TypeCodes[0].Code ?? "", imagingObservation.TypeCodes[0].DisplayName.Value ?? "", imagingObservation.TypeCodes[0].CodeSystemName ?? "")).ToList();

            return StringUtilities.Combine(tooltipList, "\n");
        }

        private static string IOCTooltipConverter(AimeAnnotationContainer result)
        {
            List<string> tooltipList = (from annotation in result.Annotations
                                        where annotation.ImagingObservations != null
                                        from observation in annotation.ImagingObservations
                                        where observation.ImagingPhysicalEntityCharacteristicCollection != null && 
                                        observation.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics != null
                                        from imagingObservationCharacteristic in observation.ImagingPhysicalEntityCharacteristicCollection.ImagingPhysicalEntityCharacteristics
                                        select string.Format("[{1}], [{0}], [{2}]", imagingObservationCharacteristic.TypeCodes[0].Code ?? "", imagingObservationCharacteristic.TypeCodes[0].DisplayName.Value ?? "", imagingObservationCharacteristic.TypeCodes[0].CodeSystemName ?? "")).ToList();

            return StringUtilities.Combine(tooltipList, "\n");
        }
    }
}
