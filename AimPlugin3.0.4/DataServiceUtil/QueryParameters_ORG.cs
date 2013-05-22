//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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
