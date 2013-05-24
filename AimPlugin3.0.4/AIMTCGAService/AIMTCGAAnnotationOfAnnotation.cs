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
using System.Collections;
using System.Collections.Generic;
using System.Data;

using DataServiceUtil;

namespace AIMTCGAService
{
    public class AIMTCGAAnnotationOfAnnotation : AIMTCGAQueryBase
    {
        public string[] getAnnotationOfAnnotationInfo(AIMQueryParameters queryParameters)
        {
            _queryParameters = queryParameters;
            string[] results = null;           
            var result = getAnnotationOfAnnotationCQLInfo();
            if (result != null && result.Items != null && result.Items.Length > 0)
                results = processCQLObjectResult(result);
            return results;
        }

        public List<aim_dotnet.Annotation> getAnnotationOfAnnotationInfoList(AIMQueryParameters queryParameters)
        {
            var annoStr = getAnnotationOfAnnotationInfo(queryParameters);
            if (annoStr == null)
                return null;
            var annotations = new List<aim_dotnet.Annotation>();
            var xmlModel = new aim_dotnet.XmlModel();
        	foreach (var str in annoStr)
            {
            	var annoAnnotation = xmlModel.ReadAnnotationFromXmlString(str) as aim_dotnet.AnnotationOfAnnotation;
            	if (annoAnnotation != null)
                    annotations.Add(annoAnnotation);
            }
        	return annotations;
        }

        public DataTable codeTable(List<aim_dotnet.Annotation> annotations, string aimObjectType)
        {
            var table = new DataTable();
            table.Columns.Add("codeValue");
            table.Columns.Add("codeMeaning");
            table.Columns.Add("codingSchemeDesignator");
            foreach (aim_dotnet.AnnotationOfAnnotation annoAnnotation in annotations)
            {
                switch (aimObjectType)
                {
                    case "AnatomicEntity":
                        foreach (var ae in annoAnnotation.AnatomyEntityCollection)
                        {
                            DataRow dr = table.NewRow();
                            dr["codeValue"] = ae.CodeValue;
                            dr["codeMeaning"] = ae.CodeMeaning;
                            dr["codingSchemeDesignator"] = ae.CodingSchemeDesignator;
                            table.Rows.Add(dr);
                        }
                        break;
                    case "ImagingObservation":
                        foreach (var ae in annoAnnotation.ImagingObservationCollection)
                        {
                            var dr = table.NewRow();
                            dr["codeValue"] = ae.CodeValue;
                            dr["codeMeaning"] = ae.CodeMeaning;
                            dr["codingSchemeDesignator"] = ae.CodingSchemeDesignator;
                            table.Rows.Add(dr);
                        }
                        break;
                    default:
                        table = null;
                        break;
                }
            }
            return table;
        }

        private CQLQueryResults getAnnotationOfAnnotationCQLInfo()
        {
            object[] obj = null;
            Attribute attrTemp = null;
            Association assoTemp = null;
            var proxy = new AIM3DataServicePortTypeClient();

            proxy.Endpoint.Address = new System.ServiceModel.EndpointAddress(AIMDataServiceSettings.Default.AIMDataServiceUrl);
            var associationList = new ArrayList();
			obj = null;
			Association aecAssociation = null;
			foreach (var queryData in _queryParameters.AecQueryParameters)
			{
				var results = new ArrayList();
				if (!queryData.CodeValue.IsEmpty)
					results.Add(CreateAttribute("codeValue", queryData.CodeValue));
				if (!queryData.CodeMeaning.IsEmpty)
					results.Add(CreateAttribute("codeMeaning", queryData.CodeMeaning));
				if (!queryData.CodingSchemeDesignator.IsEmpty)
					results.Add(CreateAttribute("codingSchemeDesignator", queryData.CodingSchemeDesignator));
				if (!queryData.CodingSchemeVersion.IsEmpty)
					results.Add(CreateAttribute("codingSchemeVersion", queryData.CodingSchemeVersion));
				if (!queryData.Confidence.IsEmpty)
					results.Add(CreateAttribute("annotatorConfidence", queryData.Confidence));
				if (results.Count > 0)
					obj = (object[])results.ToArray(typeof(object));
				if (obj != null && obj.Length > 0)
				{
					Group grpAnnatomicEntityCharacteristic = null;
					if (obj.Length > 1)
					{
						grpAnnatomicEntityCharacteristic = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
						obj = null;
					}
					else
						attrTemp = obj[0] as Attribute;

					aecAssociation = CreateQRAttrAssoGroup.createAssociation("edu.northwestern.radiology.aim.AnatomicEntityCharacteristic", "anatomicEntityCharacteristicCollection", grpAnnatomicEntityCharacteristic, attrTemp, null);
				}
			}

			obj = null;
			if (aecAssociation != null && _queryParameters.AeQueryParameters.Count == 0)
			{
				var queryData = new AimAnatomicEntityQueryData();
				queryData.CodeMeaning = new QueryData(String.Empty, QueryPredicate.LIKE);
				_queryParameters.AeQueryParameters.Add(queryData);
			}
			foreach (var queryData in _queryParameters.AeQueryParameters)
			{
				var results = new ArrayList();
				if (!queryData.CodeValue.IsEmpty)
					results.Add(CreateAttribute("codeValue", queryData.CodeValue));
				//if (!queryData.CodeMeaning.IsEmpty)
					results.Add(CreateAttribute("codeMeaning", queryData.CodeMeaning));
				if (!queryData.CodingSchemeDesignator.IsEmpty)
					results.Add(CreateAttribute("codingSchemeDesignator", queryData.CodingSchemeDesignator));
				if (!queryData.CodingSchemeVersion.IsEmpty)
					results.Add(CreateAttribute("codingSchemeVersion", queryData.CodingSchemeVersion));
				if (!queryData.Confidence.IsEmpty)
					results.Add(CreateAttribute("annotatorConfidence", queryData.Confidence));
				if (aecAssociation != null)
					results.Add(aecAssociation);
				if (results.Count > 0)
					obj = (object[])results.ToArray(typeof(object));
				if (obj != null && obj.Length > 0)
				{
					Group grpAnnatomicEntity = null;
					if (obj.Length > 1)
					{
						grpAnnatomicEntity = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
						obj = null;
					}
					else
						attrTemp = obj[0] as Attribute;
					associationList.Add(CreateQRAttrAssoGroup.createAssociation("edu.northwestern.radiology.aim.AnatomicEntity", "anatomicEntityCollection", grpAnnatomicEntity, attrTemp, null));
				}
			}

			obj = null;
			Association iocAssociation = null;
			foreach (var queryData in _queryParameters.ImcQueryParameters)
			{
				var results = new ArrayList();
				if (!queryData.CodeValue.IsEmpty)
					results.Add(CreateAttribute("codeValue", queryData.CodeValue));
				if (!queryData.CodeMeaning.IsEmpty)
					results.Add(CreateAttribute("codeMeaning", queryData.CodeMeaning));
				if (!queryData.CodingSchemeDesignator.IsEmpty)
					results.Add(CreateAttribute("codingSchemeDesignator", queryData.CodingSchemeDesignator));
				if (!queryData.CodingSchemeVersion.IsEmpty)
					results.Add(CreateAttribute("codingSchemeVersion", queryData.CodingSchemeVersion));
				if (!queryData.Confidence.IsEmpty)
					results.Add(CreateAttribute("annotatorConfidence", queryData.Confidence));
				if (!queryData.Comment.IsEmpty)
					results.Add(CreateAttribute("comment", queryData.Comment));
				if (results.Count > 0)
					obj = (object[])results.ToArray(typeof(object));
				if (obj != null && obj.Length > 0)
				{
					Group grpImagingObservationCharacteristic = null;
					if (obj.Length > 1)
					{
						grpImagingObservationCharacteristic = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
						obj = null;
					}
					else
						attrTemp = obj[0] as Attribute;

					iocAssociation = CreateQRAttrAssoGroup.createAssociation("edu.northwestern.radiology.aim.ImagingObservationCharacteristic", "imagingObservationCharacteristicCollection", grpImagingObservationCharacteristic, attrTemp, null);
				}
			}

			obj = null;
			if (iocAssociation != null && _queryParameters.ImQueryParameters.Count == 0)
			{
				var queryData = new AimImagingObservationQueryData();
				queryData.CodeMeaning = new QueryData(String.Empty, QueryPredicate.LIKE);
				_queryParameters.ImQueryParameters.Add(queryData);
			}
			foreach (var queryData in _queryParameters.ImQueryParameters)
			{
				var results = new ArrayList();
				if (!queryData.CodeValue.IsEmpty)
					results.Add(CreateAttribute("codeValue", queryData.CodeValue));
				//if (!queryData.CodeMeaning.IsEmpty)
					results.Add(CreateAttribute("codeMeaning", queryData.CodeMeaning));
				if (!queryData.CodingSchemeDesignator.IsEmpty)
					results.Add(CreateAttribute("codingSchemeDesignator", queryData.CodingSchemeDesignator));
				if (!queryData.CodingSchemeVersion.IsEmpty)
					results.Add(CreateAttribute("codingSchemeVersion", queryData.CodingSchemeVersion));
				if (!queryData.Comment.IsEmpty)
					results.Add(CreateAttribute("comment", queryData.Comment));
				if (!queryData.Confidence.IsEmpty)
					results.Add(CreateAttribute("annotatorConfidence", queryData.Confidence));
				if (iocAssociation != null)
					results.Add(iocAssociation);
				if (results.Count > 0)
					obj = (object[])results.ToArray(typeof(object));
				if (obj != null && obj.Length > 0)
				{
					attrTemp = null;
					Group grpImagingObservation = null;
					if (obj.Length > 1)
					{
						grpImagingObservation = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);
						obj = null;
					}
					else
						attrTemp = obj[0] as Attribute;
					associationList.Add(CreateQRAttrAssoGroup.createAssociation("edu.northwestern.radiology.aim.ImagingObservation", "imagingObservationCollection", grpImagingObservation, attrTemp, null));
				}
			}
			obj = null;
			foreach (var queryData in _queryParameters.UserParameters)
			{
				var results = new ArrayList();
				if (!queryData.IsEmpty)
				{
					results.Add(CreateAttribute("loginName", queryData));
					results.Add(CreateAttribute("name", queryData));
				}
				if (results.Count > 0)
					obj = (object[])results.ToArray(typeof(Attribute));
				if (obj != null && obj.Length > 0)
				{
					Group grpAnnatomicEntityCharacteristic = null;
					if (obj.Length > 1)
					{
						grpAnnatomicEntityCharacteristic = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.OR);
						obj = null;
					}
					else
						attrTemp = obj[0] as Attribute;
					associationList.Add(CreateQRAttrAssoGroup.createAssociation("edu.northwestern.radiology.aim.User", "user", grpAnnatomicEntityCharacteristic, attrTemp, null));
				}
			}
            obj = null;
            Group grpAnnotationOfAnnotation = null;
            if (associationList.Count > 0)
                obj = (object[])associationList.ToArray(typeof(Association)); 
            if (obj != null && obj.Length > 0)
            { 
                assoTemp = null;
                if (obj.Length > 1)
                    grpAnnotationOfAnnotation = CreateQRAttrAssoGroup.createGroup(obj, LogicalOperator.AND);                  
                else
                    assoTemp = obj[0] as Association;
            }
            var arg = CreateQRAttrAssoGroup.createQueryRequestCqlQuery("edu.northwestern.radiology.aim.AnnotationOfAnnotation", null, null, assoTemp, grpAnnotationOfAnnotation);
            var doc = XMLSerializingDeserializing.Serialize(arg);
            Console.WriteLine(doc.InnerXml);
            CQLQueryResults result; 
            try
            {
                result = proxy.query(arg);
            }
            catch (System.Net.WebException ex)
            {
                Console.WriteLine(ex.Message);
                result = null;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                result = null;
                throw new GridServicerException("Error querying AIM data service", e);
            }
            return result;
        }
    }
}
