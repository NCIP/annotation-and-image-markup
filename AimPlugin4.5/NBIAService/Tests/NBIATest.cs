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

#if	UNIT_TESTS

#pragma warning disable 1591,0419,1574,1587

using System;
using System.Data;
using System.Diagnostics;
using DataServiceUtil;
using NUnit.Framework;

namespace NBIAService.Tests
{
    [TestFixture]
    public class NBIATest
    {
        public NBIATest() { }

        [Test]
        public void TestNBIASearchQueries(string endPointUrl)
        {
            NBIATestParameters testParameters = new NBIATestParameters();
            testParameters.Project = "TCGA";
			TestNBIAStudy(testParameters, endPointUrl);

            testParameters.StudyInstanceUid = "1.3.6.1.4.1.9328.50.45.278844795194298910084884570122397123437";
			TestNBIAPatient(testParameters, endPointUrl);

            testParameters.StudyInstanceUid = "1.3.6.1.4.1.9328.50.4.677842";
			TestNBIATialDataProvenance(testParameters, endPointUrl);
        }

        private void TestNBIAStudy(NBIATestParameters testParameters, string endPointUrl)
        {
			NBIAStudy study = new NBIAStudy();
			DataTable dataTable = study.getStudyInfo(testParameters.NBIAQueryParameters, endPointUrl);
			Assert.IsNotNull(dataTable.Rows, "Rows null");
			Assert.IsTrue(dataTable.Rows.Count > 0, "Rows empty");
        }

		private void TestNBIAPatient(NBIATestParameters testParameters, string endPointUrl)
        {
            NBIAPatient patient = new NBIAPatient();
            DataTable dataTable = patient.getPatientInfo(testParameters.NBIAQueryParameters, endPointUrl);
            Assert.IsNotNull(dataTable.Rows, "Rows null");
            Assert.IsTrue(dataTable.Rows.Count > 0, "Rows empty");
        }

		private void TestNBIASeries(NBIATestParameters testParameters, string endPointUrl)
        {
            NBIASeries series = new NBIASeries();
			DataTable dataTable = series.getSeriesInfo(testParameters.NBIAQueryParameters, endPointUrl);
            Assert.IsNotNull(dataTable.Rows, "Rows null");
            Assert.IsTrue(dataTable.Rows.Count > 0, "Rows empty");
        }

		private void TestNBIATialDataProvenance(NBIATestParameters testParameters, string endPointUrl)
        {
            NBIATrialDataProvenance trialDataProvenance = new NBIATrialDataProvenance();
			DataTable dataTable = trialDataProvenance.getTrialDataProvenanceInfo(testParameters.NBIAQueryParameters, endPointUrl);
            Assert.IsNotNull(dataTable.Rows, "Rows null");
            Assert.IsTrue(dataTable.Rows.Count > 0, "Rows empty");
        }

		private void TestNBIAImage(NBIATestParameters testParameters, string endPointUrl)
        {
            NBIAImage image = new NBIAImage();
			DataTable dataTable = image.getImageInfo(testParameters.NBIAQueryParameters, endPointUrl);
            Assert.IsNotNull(dataTable.Rows, "Rows null");
            Assert.IsTrue(dataTable.Rows.Count > 0, "Rows empty");
        }

        private void TestNBIAClinicalTrialSite(NBIATestParameters testParameters)
        {
        }

        private class NBIATestParameters
        {
            public String StudyInstanceUid { get; set; }
            public String PatientId { get; set; }
            public String PatientsName { get; set; }
            public String PatientsSex { get; set; }
            public DateTime? PatientsBirthDate { get; set; }
            public String Project { get; set; }
            public String Modality { get; set; }
            public String SliceThickness { get; set; }


            public NBIAQueryParameters NBIAQueryParameters
            {
                get
                {
                    NBIAQueryParameters queryParamters = new NBIAQueryParameters();

                    // Get user parameters
                    NBIAQueryParameters queryParameters = new NBIAQueryParameters();
                    // Study
                    queryParameters.StudyInstanceUID = this.CreateQueryDataForLikePredicate(StudyInstanceUid);
                    // Patient
                    queryParameters.PatientId = this.CreateQueryDataForLikePredicate(PatientId);
                    queryParameters.PatientName = this.CreateQueryDataForLikePredicate(PatientsName);
                    queryParameters.PatientSex = this.CreateQueryDataForLikePredicate(PatientsSex);
                    if (PatientsBirthDate.HasValue)
                    {
                        string bdValue = PatientsBirthDate.Value.ToString("yyyy-MM-dd hh:mm:ss.f");
                        queryParameters.PatientBirthDate = new QueryData(bdValue, QueryPredicate.LIKE);
                    }
                    // Trial Data Provenace
                    queryParameters.ProjectName = this.CreateQueryDataForLikePredicate(Project);

                    // Series
                    queryParameters.Modality = new QueryData(Modality, QueryPredicate.EQUAL_TO);
                    // Image
                    if (!string.IsNullOrEmpty(SliceThickness))
                        queryParameters.SliceThickness = new QueryData(SliceThickness, QueryPredicate.GREATER_THAN_EQUAL_TO);


                    return queryParamters;
                }
            }

            private QueryData CreateQueryDataForLikePredicate(string input)
            {
                if (string.IsNullOrEmpty((input ?? "").Trim()))
                    return null;

                return new QueryData(input.Trim(), QueryPredicate.LIKE);
                //			return new QueryData(string.Format("{0}%", input.Trim().TrimEnd('%')), QueryPredicate.LIKE);
            }
        }
    }
}

#endif
