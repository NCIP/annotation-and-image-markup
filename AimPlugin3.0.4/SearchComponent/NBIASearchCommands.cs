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

using System;
using System.Collections.Generic;
using System.Data;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using DataServiceUtil;
using NBIAService;

namespace SearchComponent
{
	internal partial class NBIASearchCoordinator
	{
		private class QueryForStudiesCommand : SearchCommand
		{
		    private readonly NBIAQueryParameters _queryParameters;

			public QueryForStudiesCommand(NBIAQueryParameters queryParameters)
			{
			    _queryParameters = queryParameters;
			}

			public override void Execute()
			{
				List<NBIASearchResult> results = new List<NBIASearchResult>();

				NBIAStudy studyService = new NBIAStudy();

				try
				{
					DataTable dtStudies = studyService.getStudyInfo(_queryParameters, SearchSettings.Default.NBIADataServiceUrl);
					if (dtStudies != null)
					{
						foreach (DataRow studyUid in dtStudies.Rows)
						{
							if (base.CancelRequested)
								break;

							NBIASearchResult result = new NBIASearchResult();
							result.Study.StudyInstanceUid = studyUid["studyInstanceUID"].ToString();
							results.Add(result);
						}
					}
				}
				catch (GridServicerException ex)
				{
					base.SetError(ex.Message);
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to query grid for Study data");
				}

				base.AddResultsToTable(results);

				foreach (NBIASearchResult result in base.SearchResults)
				{
					if (base.CancelRequested)
						break;

					NBIAQueryParameters nbiaQueryParameters = _queryParameters.Clone();
					nbiaQueryParameters.StudyInstanceUID = new QueryData(result.Study.StudyInstanceUid, QueryPredicate.EQUAL_TO);

					base.EnqueueNextCommand(new QueryForPatientInfoCommand(nbiaQueryParameters, result));
					base.EnqueueNextCommand(new QueryForClinicalTrialProtocolDataCommand(nbiaQueryParameters, result));
					base.EnqueueNextCommand(new QueryForTrialDataProvenanceCommand(nbiaQueryParameters, result));
					base.EnqueueNextCommand(new QueryForClinicalTrialSiteDataCommand(nbiaQueryParameters, result));
					base.EnqueueNextCommand(new QueryForSeriesDataCommand(nbiaQueryParameters, result));
				}

				base.OnCommandExecuted();
			}
		}

        private class QueryForPatientInfoCommand : SearchCommand
        {
            private readonly NBIAQueryParameters _queryParameters;
            private readonly NBIASearchResult _result;

            public QueryForPatientInfoCommand(NBIAQueryParameters queryParameters, NBIASearchResult result)
            {
                _queryParameters = queryParameters;
                _result = result;
            }

            public override void Execute()
            {
                if (!base.CancelRequested)
                {
                    NBIAPatient patientService = new NBIAPatient();

                    try
                    {
                        DataTable dtStudies = patientService.getPatientInfo(_queryParameters, SearchSettings.Default.NBIADataServiceUrl);
						if (dtStudies != null && dtStudies.Rows.Count > 0)
                        {
                            _result.Patient.PatientId = dtStudies.Rows[0]["patientId"].ToString();
                            _result.Patient.PatientsName = dtStudies.Rows[0]["patientName"].ToString();
                            _result.Patient.PatientsSex = dtStudies.Rows[0]["patientSex"].ToString();
                            if (!string.IsNullOrEmpty(dtStudies.Rows[0]["patientBirthDate"].ToString()))
                            {
                                try
                                {
                                    _result.Patient.PatientBirthDate = DateTime.Parse(dtStudies.Rows[0]["patientBirthDate"].ToString());
                                }
                                catch (Exception)
                                {
                                }
                            }
                            base.OnResultUpdated(_result);
                        }
                    }
                    catch (Exception ex)
                    {
                        Platform.Log(LogLevel.Error, ex, "Failed to query grid for Patient data");
                    }
                }
                base.OnCommandExecuted();
            }
        }

		private class QueryForClinicalTrialProtocolDataCommand : SearchCommand
		{
            private readonly NBIAQueryParameters _queryParameters;
            private readonly NBIASearchResult _result;

            public QueryForClinicalTrialProtocolDataCommand(NBIAQueryParameters queryParameters, NBIASearchResult result)
            {
                _queryParameters = queryParameters;
                _result = result;
            }

			public override void Execute()
			{
                if (!base.CancelRequested)
                {
                    NBIAClinicalTrialProtocol clinicalTrailProtocolService = new NBIAClinicalTrialProtocol();

                    try
                    {
                        DataTable dtStudies = clinicalTrailProtocolService.getClinicalTrialProtocolInfo(_queryParameters, SearchSettings.Default.NBIADataServiceUrl);
                        if (dtStudies != null && dtStudies.Rows.Count > 0)
                        {
                            _result.ClinicalTrialProtocol.ProtocolId = dtStudies.Rows[0]["protocolId"].ToString();
                            _result.ClinicalTrialProtocol.ProtocolName = dtStudies.Rows[0]["protocolName"].ToString();

                            base.OnResultUpdated(_result);
                        }
                    }
                    catch (Exception ex)
                    {
                        Platform.Log(LogLevel.Error, ex, "Failed to query grid for ClinicalTrialProtocol data");
                    }
                }
			    base.OnCommandExecuted();
			}
		}

		private class QueryForTrialDataProvenanceCommand : SearchCommand
		{
            private readonly NBIAQueryParameters _queryParameters;
            private readonly NBIASearchResult _result;

            public QueryForTrialDataProvenanceCommand(NBIAQueryParameters queryParameters, NBIASearchResult result)
            {
                _queryParameters = queryParameters;
                _result = result;
            }

			public override void Execute()
			{
                if (!base.CancelRequested)
                {
                    NBIATrialDataProvenance trailDataProvenanceService = new NBIATrialDataProvenance();

                    try
                    {
						DataTable dtStudies = trailDataProvenanceService.getTrialDataProvenanceInfo(_queryParameters, SearchSettings.Default.NBIADataServiceUrl);
                        if (dtStudies != null && dtStudies.Rows.Count > 0)
                        {
							_result.TrialDataProvenance.Project = _queryParameters.ProjectName.SelectedValue;

                            base.OnResultUpdated(_result);
                        }
                    }
                    catch (Exception ex)
                    {
                        Platform.Log(LogLevel.Error, ex, "Failed to query grid for TrialDataProvenance data");
                    }
                }
			    base.OnCommandExecuted();
			}
		}

        private class QueryForClinicalTrialSiteDataCommand : SearchCommand
        {
            private readonly NBIAQueryParameters _queryParameters;
            private readonly NBIASearchResult _result;

            public QueryForClinicalTrialSiteDataCommand(NBIAQueryParameters queryParameters, NBIASearchResult result)
            {
                _queryParameters = queryParameters;
                _result = result;
            }

            public override void Execute()
            {
                if (!base.CancelRequested)
                {
                    NBIAClinicalTrialSite clinicalTrialSiteService  = new NBIAClinicalTrialSite();

                    try
                    {
						DataTable dtStudies = clinicalTrialSiteService.getClinicalTrialSiteInfo(_queryParameters, SearchSettings.Default.NBIADataServiceUrl);
                        if (dtStudies != null && dtStudies.Rows.Count > 0)
                        {
                            _result.ClinicalTrialSite.SiteId = dtStudies.Rows[0]["siteId"].ToString();
                            _result.ClinicalTrialSite.SiteName = dtStudies.Rows[0]["siteName"].ToString();

                            base.OnResultUpdated(_result);
                        }
                    }
                    catch (Exception ex)
                    {
                        Platform.Log(LogLevel.Error, ex, "Failed to query grid for ClinicalTrialSiteData data");
                    }
                }
                base.OnCommandExecuted();
            }
        }

		private class QueryForSeriesDataCommand : SearchCommand
		{
            private readonly NBIAQueryParameters _queryParameters;
            private readonly NBIASearchResult _result;

            public QueryForSeriesDataCommand(NBIAQueryParameters queryParameters, NBIASearchResult result)
            {
                _queryParameters = queryParameters;
                _result = result;
            }

            public override void Execute()
            {
                if (!base.CancelRequested)
                {
                    NBIASeries seriesService = new NBIASeries();

                    try
                    {
						DataTable dtStudies = seriesService.getSeriesInfo(_queryParameters, SearchSettings.Default.NBIADataServiceUrl);
                        if (dtStudies != null)
                        {
							Console.WriteLine("Project: " + dtStudies.Rows[0].ToString());
                            Dictionary<string, string> modalities = new Dictionary<string, string>();
                            foreach (DataRow row in dtStudies.Rows)
                            {
                                if (!string.IsNullOrEmpty(row["modality"].ToString().Trim()))
                                    modalities[row["modality"].ToString().Trim()] = string.Empty;
                            }
                            if (modalities.Count > 0)
                            {
                                _result.Series.Modality = StringUtilities.Combine(modalities.Keys, ",");

                                base.OnResultUpdated(_result);
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        Platform.Log(LogLevel.Error, ex, "Failed to query grid for Series data");
                    }
                }
                base.OnCommandExecuted();
            }
		}
	}
}
