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
using System.Linq;
using System.Text;

namespace DataServiceUtil
{
    public enum QueryPredicate
    {
        EQUAL_TO,
        NOT_EQUAL_TO,
        LIKE,
        IS_NULL,
        IS_NOT_NULL,
        LESS_THAN,
        LESS_THAN_EQUAL_TO,
        GREATER_THAN,
        GREATER_THAN_EQUAL_TO,
    }

    public class QueryData
    {
        private string _selectedValue;
        private QueryPredicate _predicate;

        public QueryData(string selectedValue, QueryPredicate predicate)
        {
            _selectedValue = selectedValue;
            _predicate = predicate;
        }

        public string SelectedValue
        {
            get { return _selectedValue; }
        }

        public QueryPredicate Predicate
        {
            get { return _predicate; }
        }

        public bool IsEmpty
        {
            get { return string.IsNullOrEmpty(_selectedValue); }
        }

        internal static QueryData DefaultQueryData
        {
            get { return new QueryData("", QueryPredicate.EQUAL_TO); }
        }
    }

    public class AIMQueryParameters
    {
        private QueryData _aeCodeValue;
        private QueryData _aeCodeMeaning;
        private QueryData _aeCodingSchemeDesignator;
        private QueryData _aeCodingSchemeVersion;
        private QueryData _aeConfidence;
        private QueryData _imCodeValue;
        private QueryData _imCodeMeaning;
        private QueryData _imCodingSchemeDesignator;
        private QueryData _imCodingSchemeVersion;
        private QueryData _imConfidence;
        private QueryData _imComment;
        private QueryData _studyInstanceUID;

        public QueryData AECodeValue
        {
            get { return _aeCodeValue == null ? QueryData.DefaultQueryData : _aeCodeValue; }
            set { _aeCodeValue = value; }
        }

        public QueryData AECodeMeaning
        {
            get { return _aeCodeMeaning == null ? QueryData.DefaultQueryData : _aeCodeMeaning; }
            set { _aeCodeMeaning = value; }
        }

        public QueryData AECodingSchemeDesignator
        {
            get { return _aeCodingSchemeDesignator == null ? QueryData.DefaultQueryData : _aeCodingSchemeDesignator; }
            set { _aeCodingSchemeDesignator = value; }
        }

        public QueryData AECodingSchemeVersion
        {
            get { return _aeCodingSchemeVersion == null ? QueryData.DefaultQueryData : _aeCodingSchemeVersion; }
            set { _aeCodingSchemeVersion = value; }
        }

        public QueryData AEConfidence
        {
            get { return _aeConfidence == null ? QueryData.DefaultQueryData : _aeConfidence; }
            set { _aeConfidence = value; }
        }

        public QueryData IMCodeValue
        {
            get { return _imCodeValue == null ? QueryData.DefaultQueryData : _imCodeValue; }
            set { _imCodeValue = value; }
        }

        public QueryData IMCodeMeaning
        {
            get { return _imCodeMeaning == null ? QueryData.DefaultQueryData : _imCodeMeaning; }
            set { _imCodeMeaning = value; }
        }

        public QueryData IMCodingSchemeDesignator
        {
            get { return _imCodingSchemeDesignator == null ? QueryData.DefaultQueryData : _imCodingSchemeDesignator; }
            set { _imCodingSchemeDesignator = value; }
        }

        public QueryData IMCodingSchemeVersion
        {
            get { return _imCodingSchemeVersion == null ? QueryData.DefaultQueryData : _imCodingSchemeVersion; }
            set { _imCodingSchemeVersion = value; }
        }

        public QueryData IMConfidence
        {
            get { return _imConfidence == null ? QueryData.DefaultQueryData : _imConfidence; }
            set { _imConfidence = value; }
        }

        public QueryData IMComment
        {
            get { return _imComment == null ? QueryData.DefaultQueryData : _imComment; }
            set { _imComment = value; }
        }

        public QueryData StudyInstanceUID
        {
            get { return _studyInstanceUID == null ? QueryData.DefaultQueryData : _studyInstanceUID; }
            set { _studyInstanceUID = value; }
        }

        public AIMQueryParameters()
        {

        }

        protected AIMQueryParameters(AIMQueryParameters src)
        {
            _aeCodeValue = src.AECodeValue;
            _aeCodeMeaning = src.AECodeMeaning;
            _aeCodingSchemeDesignator = src.AECodingSchemeDesignator;
            _aeCodingSchemeVersion = src.AECodingSchemeVersion;
            _aeConfidence = src.AEConfidence;
            _imCodeValue = src.IMCodeValue;
            _imCodeMeaning = src.IMCodeMeaning;
            _imCodingSchemeDesignator = src.IMCodingSchemeDesignator;
            _imCodingSchemeVersion = src.IMCodingSchemeVersion;
            _imConfidence = src.IMConfidence;
            _imComment = src.IMComment;
            _studyInstanceUID = src.StudyInstanceUID;
        }

        public AIMQueryParameters Clone()
        {
            return new AIMQueryParameters(this);
        }

    }

    public class NBIAQueryParameters
    {
        private QueryData _projectName;
        private QueryData _protocolId;
        private QueryData _protocolName;
        private QueryData _patientId;
        private QueryData _patientName;
        private QueryData _patientSex;
        private QueryData _patientBirthDate;
        private QueryData _siteName;
        private QueryData _siteId;
        private QueryData _modality;
        private QueryData _sliceThickness;
        private QueryData _studyInstanceUID;

        public NBIAQueryParameters()
        {
        }

        protected NBIAQueryParameters(NBIAQueryParameters src)
        {
            _projectName = src._projectName;
            _protocolId = src._protocolId;
            _protocolName = src._protocolName;
            _patientId = src._patientId;
            _patientName = src._patientName;
            _patientSex = src._patientSex;
            _patientBirthDate = src._patientBirthDate;
            _siteName = src._siteName;
            _siteId = src._siteId;
            _modality = src._modality;
            _sliceThickness = src._sliceThickness;
            _studyInstanceUID = src._studyInstanceUID;
        }

        public NBIAQueryParameters Clone()
        {
            return new NBIAQueryParameters(this);
        }

        public QueryData ProjectName
        {
            get { return _projectName == null ? QueryData.DefaultQueryData : _projectName; }
            set { _projectName = value; }
        }

        public QueryData ProtocolId
        {
            get { return _protocolId == null ? QueryData.DefaultQueryData : _protocolId; }
            set { _protocolId = value; }
        }

        public QueryData ProtocolName
        {
            get { return _protocolName == null ? QueryData.DefaultQueryData : _protocolName; }
            set { _protocolName = value; }
        }

        public QueryData PatientId
        {
            get { return _patientId  == null ? QueryData.DefaultQueryData : _patientId; }
            set { _patientId = value; }
        }

        public QueryData PatientName
        {
            get { return _patientName == null ? QueryData.DefaultQueryData : _patientName; }
            set { _patientName = value; }
        }

        public QueryData PatientSex
        {
            get { return _patientSex == null ? QueryData.DefaultQueryData : _patientSex; }
            set { _patientSex = value; }
        }

        public QueryData PatientBirthDate
        {
            get { return _patientBirthDate == null ? QueryData.DefaultQueryData : _patientBirthDate; }
            set { _patientBirthDate = value; }
        }

        public QueryData SiteName
        {
            get { return _siteName == null ? QueryData.DefaultQueryData : _siteName; }
            set { _siteName = value; }
        }

        public QueryData SiteId
        {
            get { return _siteId == null ? QueryData.DefaultQueryData : _siteId; }
            set { _siteId = value; }
        }

        public QueryData Modality
        {
            get { return _modality == null ? QueryData.DefaultQueryData : _modality; }
            set { _modality = value; }
        }

        public QueryData SliceThickness
        {
            get { return _sliceThickness == null ? QueryData.DefaultQueryData : _sliceThickness; }
            set { _sliceThickness = value; }
        }

        public QueryData StudyInstanceUID
        {
            get { return _studyInstanceUID == null ? QueryData.DefaultQueryData : _studyInstanceUID; }
            set { _studyInstanceUID = value; }
        }
    }
}
