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

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using DataServiceUtil;
using System.Data;

namespace NBIAService
{
    public class NBIAClinicalTrialSite : NBIAQueryBase
    {
        public DataTable getClinicalTrialSiteInfo(NBIAQueryParameters queryParameters, string endPointUrl)
        {
            _queryParameters = queryParameters;
            DataTable dataTable = null;
            NBIAService.CQLQueryResults result = getClinicalTrialSiteCQLInfo(endPointUrl);
            if (result != null && result.Items != null && result.Items.Length > 0)
                dataTable = this.processCQLObjectResult(result);
            return dataTable;
        }

        private CQLQueryResults getClinicalTrialSiteCQLInfo(string endPointUrl)
        {           
            object[] obj;
            CQLQueryResults result;
            Association assoTrialDataProvenance = null;
            Association assoClinicalTrialProtocol = null;
            Association assoClinicalTrialSubject = null;
            Association assoImage = null;
            Association assoSeries = null;
            Association assoStudy = null;
            Association assoPatient = null;
            ArrayList results = new ArrayList();
            NCIACoreServicePortTypeClient proxy = new NCIACoreServicePortTypeClient();
            proxy.Endpoint.Address = new System.ServiceModel.EndpointAddress(endPointUrl);
            string[] items = new string[] { "siteId", "siteName" };
            ItemsChoiceType[] itemsChoiceType1 = new ItemsChoiceType[] {
                ItemsChoiceType.AttributeNames, ItemsChoiceType.AttributeNames, ItemsChoiceType.AttributeNames};
            // Image
            assoImage = null;
            if (!_queryParameters.SliceThickness.IsEmpty)
            {
                Attribute attrPatient = this.CreateAttribute("sliceThickness", _queryParameters.SliceThickness);
                Group grpPatient = CreateQRAttrAssoGroup.createGroup(attrPatient, LogicalOperator.AND);
                assoImage = CreateQRAttrAssoGroup.createAssociation("gov.nih.nci.ncia.domain.Image", "imageCollection", grpPatient);
            }
            // Series
            results = new ArrayList();
            assoSeries = null;
            obj = null;
            if (assoImage != null)
                results.Add(assoImage);
            if (!_queryParameters.Modality.IsEmpty)
                results.Add(this.CreateAttribute("modality", _queryParameters.Modality));
            if (results.Count > 0)
                obj = (object[])results.ToArray(typeof(object));
            if (obj != null)
            {
                Group grpSeries = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
                assoSeries = CreateQRAttrAssoGroup.createAssociation("gov.nih.nci.ncia.domain.Series", "seriesCollection", grpSeries);
            }
            // Study
            obj = null;
            assoStudy = null;
            results = new ArrayList();
            if (assoSeries != null)
                results.Add(assoSeries);
            if (!_queryParameters.StudyInstanceUID.IsEmpty)
                results.Add(this.CreateAttribute("studyInstanceUID", _queryParameters.StudyInstanceUID));
            assoStudy = null;
            if (results.Count > 0)
                obj = (object[])results.ToArray(typeof(object));
            if (obj != null)
            {
                Group groupStudy = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
                assoStudy = CreateQRAttrAssoGroup.createAssociation("gov.nih.nci.ncia.domain.Study", "studyCollection", groupStudy);
            }

            // TrialDataProvenance
            assoTrialDataProvenance = null;
            if (!_queryParameters.ProjectName.IsEmpty)
            {
                Attribute attrTrialDataProvenance = this.CreateAttribute("project", _queryParameters.ProjectName);
                Group grpTrialDataProvenance = CreateQRAttrAssoGroup.createGroup(attrTrialDataProvenance, LogicalOperator.AND);
                assoTrialDataProvenance = CreateQRAttrAssoGroup.createAssociation("gov.nih.nci.ncia.domain.TrialDataProvenance", "dataProvenance", grpTrialDataProvenance);
            }
            // Patient
            obj = null;
            results = new ArrayList();
           if (assoStudy != null)
                results.Add(assoStudy);
            if (assoTrialDataProvenance != null)
                results.Add(assoTrialDataProvenance);
            if (!_queryParameters.PatientBirthDate.IsEmpty)
                results.Add(this.CreateAttribute("patientBirthDate", _queryParameters.PatientBirthDate));
            if (!_queryParameters.PatientId.IsEmpty)
                results.Add(this.CreateAttribute("patientId", _queryParameters.PatientId));
            if (!_queryParameters.PatientName.IsEmpty)
                results.Add(this.CreateAttribute("patientName", _queryParameters.PatientName));
            if (!_queryParameters.PatientSex.IsEmpty)
                results.Add(this.CreateAttribute("patientSex", _queryParameters.PatientSex));
            if (results.Count > 0)
                obj = (object[])results.ToArray(typeof(object));
            if (obj != null)
            {
                Group patientGroup = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
                assoPatient = CreateQRAttrAssoGroup.createAssociation("gov.nih.nci.ncia.domain.Patient", "patient", patientGroup);
            }

            // Clinical Trial Protocol
            assoClinicalTrialProtocol = null;
            obj = null;
            results = new ArrayList();
            if (!_queryParameters.ProtocolId.IsEmpty)
                results.Add(this.CreateAttribute("protocolId", _queryParameters.ProtocolId));
            if (!_queryParameters.ProtocolName.IsEmpty)
                results.Add(this.CreateAttribute("protocolName", _queryParameters.ProtocolName));
            if (results.Count > 0)
                obj = (object[])results.ToArray(typeof(object));
            if (obj != null)
            {
                Group grpClinicalTrialProtocol = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
                assoClinicalTrialProtocol = CreateQRAttrAssoGroup.createAssociation("gov.nih.nci.ncia.domain.ClinicalTrialProtocol",
                                                                                            "protocol", grpClinicalTrialProtocol);
            }

            // Clinical Trial Subject
            results = new ArrayList();
            if (assoClinicalTrialProtocol != null)
                results.Add(assoClinicalTrialProtocol);
            if (assoPatient != null)
                results.Add(assoPatient);
            if (results.Count > 0)
            {
                obj = (object[])results.ToArray(typeof(object));
                Group grpClinicalTrialSubject = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
                assoClinicalTrialSubject = CreateQRAttrAssoGroup.createAssociation("gov.nih.nci.ncia.domain.ClinicalTrialSubject", "subjectCollection", grpClinicalTrialSubject);
            }

            // Clinical Trial Site (Root)
            obj = null;
            results = new ArrayList();
            if (assoClinicalTrialSubject != null)
                results.Add(assoClinicalTrialSubject);
            if (!_queryParameters.SiteId.IsEmpty)
                results.Add(this.CreateAttribute("siteId", _queryParameters.SiteId));
            if (!_queryParameters.SiteName.IsEmpty)
                results.Add(this.CreateAttribute("siteName", _queryParameters.SiteName));
            if (results.Count > 0)
                obj = (object[])results.ToArray(typeof(object));
            Group groupClinicalTrialSite = null;
            if (obj != null)
                groupClinicalTrialSite = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
            QueryRequestCqlQuery arg = CreateQRAttrAssoGroup.createQueryRequestCqlQuery("gov.nih.nci.ncia.domain.ClinicalTrialSite", items, itemsChoiceType1, null, groupClinicalTrialSite);

            XmlDocument doc = XMLSerializingDeserializing.Serialize(arg);
            Console.WriteLine(((System.Xml.XmlDocument)((System.Xml.XmlNode)(doc))).InnerXml);

            try
            {
                result = proxy.query(arg);
            }
            catch (System.Net.WebException ex)
            {
                System.Console.WriteLine(ex.Message); 
                result = null;
            }
            catch (Exception e)
            {
                System.Console.WriteLine(e.Message); 
                result = null;
                throw new GridServicerException("Error querying NCIA Grid", e);
            }
            return result; 
        }
    }
}
