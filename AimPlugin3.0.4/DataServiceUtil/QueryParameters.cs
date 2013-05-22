//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Collections.Generic;

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

		internal QueryData(QueryData queryData)
		{
			_selectedValue = queryData._selectedValue;
			_predicate = queryData._predicate;
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

	public class AimAnatomicEntityQueryData
	{
		private QueryData _codeValue;
		private QueryData _codeMeaning;
		private QueryData _codingSchemeDesignator;
		private QueryData _codingSchemeVersion;
		private QueryData _confidence;

		public AimAnatomicEntityQueryData()
		{
		}

		internal AimAnatomicEntityQueryData(AimAnatomicEntityQueryData queryData)
		{
			_codeValue = queryData._codeValue == null ? null : new QueryData(queryData._codeValue);
			_codeMeaning = queryData._codeMeaning == null ? null : new QueryData(queryData._codeMeaning);
			_codingSchemeDesignator = queryData._codingSchemeDesignator == null ? null : new QueryData(queryData._codingSchemeDesignator);
			_codingSchemeVersion = queryData._codingSchemeVersion == null ? null : new QueryData(queryData._codingSchemeVersion);
			_confidence = queryData._confidence == null ? null : new QueryData(queryData._confidence);
		}

		public AimAnatomicEntityQueryData Clone()
		{
			return new AimAnatomicEntityQueryData(this);
		}

		public QueryData CodeValue
		{
			get { return _codeValue ?? QueryData.DefaultQueryData; }
			set { _codeValue = value; }
		}

		public QueryData CodeMeaning
		{
			get { return _codeMeaning ?? QueryData.DefaultQueryData; }
			set { _codeMeaning = value; }
		}

		public QueryData CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator ?? QueryData.DefaultQueryData; }
			set { _codingSchemeDesignator = value; }
		}

		public QueryData CodingSchemeVersion
		{
			get { return _codingSchemeVersion ?? QueryData.DefaultQueryData; }
			set { _codingSchemeVersion = value; }
		}

		public QueryData Confidence
		{
			get { return _confidence ?? QueryData.DefaultQueryData; }
			set { _confidence = value; }
		}
	}

	public class AimAnatomicEntityCharacteristicQueryData
	{
		private QueryData _codeValue;
		private QueryData _codeMeaning;
		private QueryData _codingSchemeDesignator;
		private QueryData _codingSchemeVersion;
		private QueryData _confidence;

		public AimAnatomicEntityCharacteristicQueryData()
		{
		}

		internal AimAnatomicEntityCharacteristicQueryData(AimAnatomicEntityCharacteristicQueryData queryData)
		{
			_codeValue = queryData._codeValue == null ? null : new QueryData(queryData._codeValue);
			_codeMeaning = queryData._codeMeaning == null ? null : new QueryData(queryData._codeMeaning);
			_codingSchemeDesignator = queryData._codingSchemeDesignator == null ? null : new QueryData(queryData._codingSchemeDesignator);
			_codingSchemeVersion = queryData._codingSchemeVersion == null ? null : new QueryData(queryData._codingSchemeVersion);
			_confidence = queryData._confidence == null ? null : new QueryData(queryData._confidence);
		}

		public AimAnatomicEntityCharacteristicQueryData Clone()
		{
			return new AimAnatomicEntityCharacteristicQueryData(this);
		}

		public QueryData CodeValue
		{
			get { return _codeValue ?? QueryData.DefaultQueryData; }
			set { _codeValue = value; }
		}

		public QueryData CodeMeaning
		{
			get { return _codeMeaning ?? QueryData.DefaultQueryData; }
			set { _codeMeaning = value; }
		}

		public QueryData CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator ?? QueryData.DefaultQueryData; }
			set { _codingSchemeDesignator = value; }
		}

		public QueryData CodingSchemeVersion
		{
			get { return _codingSchemeVersion ?? QueryData.DefaultQueryData; }
			set { _codingSchemeVersion = value; }
		}

		public QueryData Confidence
		{
			get { return _confidence ?? QueryData.DefaultQueryData; }
			set { _confidence = value; }
		}
	}

	public class AimImagingObservationQueryData
	{
		private QueryData _codeValue;
		private QueryData _codeMeaning;
		private QueryData _codingSchemeDesignator;
		private QueryData _codingSchemeVersion;
		private QueryData _confidence;
		private QueryData _comment;

		public AimImagingObservationQueryData()
		{
		}

		internal AimImagingObservationQueryData(AimImagingObservationQueryData queryData)
		{
			_codeValue = queryData._codeValue == null ? null : new QueryData(queryData._codeValue);
			_codeMeaning = queryData._codeMeaning == null ? null : new QueryData(queryData._codeMeaning);
			_codingSchemeDesignator = queryData._codingSchemeDesignator == null ? null : new QueryData(queryData._codingSchemeDesignator);
			_codingSchemeVersion = queryData._codingSchemeVersion == null ? null : new QueryData(queryData._codingSchemeVersion);
			_comment = queryData._comment == null ? null : new QueryData(queryData._comment);
			_confidence = queryData._confidence == null ? null : new QueryData(queryData._confidence);
		}

		public AimImagingObservationQueryData Clone()
		{
			return new AimImagingObservationQueryData(this);
		}

		public QueryData CodeValue
		{
			get { return _codeValue ?? QueryData.DefaultQueryData; }
			set { _codeValue = value; }
		}

		public QueryData CodeMeaning
		{
			get { return _codeMeaning ?? QueryData.DefaultQueryData; }
			set { _codeMeaning = value; }
		}

		public QueryData CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator ?? QueryData.DefaultQueryData; }
			set { _codingSchemeDesignator = value; }
		}

		public QueryData CodingSchemeVersion
		{
			get { return _codingSchemeVersion ?? QueryData.DefaultQueryData; }
			set { _codingSchemeVersion = value; }
		}

		public QueryData Confidence
		{
			get { return _confidence ?? QueryData.DefaultQueryData; }
			set { _confidence = value; }
		}

		public QueryData Comment
		{
			get { return _comment ?? QueryData.DefaultQueryData; }
			set { _comment = value; }
		}
	}

	public class AimImagingObservationCharacteristicQueryData
	{
		private QueryData _codeValue;
		private QueryData _codeMeaning;
		private QueryData _codingSchemeDesignator;
		private QueryData _codingSchemeVersion;
		private QueryData _confidence;
		private QueryData _comment;

		public AimImagingObservationCharacteristicQueryData()
		{
		}

		internal AimImagingObservationCharacteristicQueryData(AimImagingObservationCharacteristicQueryData queryData)
		{
			_codeValue = queryData._codeValue == null ? null : new QueryData(queryData._codeValue);
			_codeMeaning = queryData._codeMeaning == null ? null : new QueryData(queryData._codeMeaning);
			_codingSchemeDesignator = queryData._codingSchemeDesignator == null ? null : new QueryData(queryData._codingSchemeDesignator);
			_codingSchemeVersion = queryData._codingSchemeVersion == null ? null : new QueryData(queryData._codingSchemeVersion);
			_confidence = queryData._confidence == null ? null : new QueryData(queryData._confidence);
			_comment = queryData._comment == null ? null : new QueryData(queryData._comment);
		}

		public AimImagingObservationCharacteristicQueryData Clone()
		{
			return new AimImagingObservationCharacteristicQueryData(this);
		}

		public QueryData CodeValue
		{
			get { return _codeValue ?? QueryData.DefaultQueryData; }
			set { _codeValue = value; }
		}

		public QueryData CodeMeaning
		{
			get { return _codeMeaning ?? QueryData.DefaultQueryData; }
			set { _codeMeaning = value; }
		}

		public QueryData CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator ?? QueryData.DefaultQueryData; }
			set { _codingSchemeDesignator = value; }
		}

		public QueryData CodingSchemeVersion
		{
			get { return _codingSchemeVersion ?? QueryData.DefaultQueryData; }
			set { _codingSchemeVersion = value; }
		}

		public QueryData Confidence
		{
			get { return _confidence ?? QueryData.DefaultQueryData; }
			set { _confidence = value; }
		}

		public QueryData Comment
		{
			get { return _comment ?? QueryData.DefaultQueryData; }
			set { _comment = value; }
		}
	}

	public enum AnnotationType
	{
		InvalidAnnotation,
		ImageAnnotation,
		AnnotationOfAnnotation
	}

	public class AIMQueryParameters
	{
		private List<AimAnatomicEntityQueryData> _aeQueryParameters = new List<AimAnatomicEntityQueryData>();
		private List<AimAnatomicEntityCharacteristicQueryData> _aecQueryParameters = new List<AimAnatomicEntityCharacteristicQueryData>();
		private List<AimImagingObservationQueryData> _imQueryParameters = new List<AimImagingObservationQueryData>();
		private List<AimImagingObservationCharacteristicQueryData> _imcQueryParameters = new List<AimImagingObservationCharacteristicQueryData>();
		private List<QueryData> _studyInstanceUidParameters = new List<QueryData>();
		private List<QueryData> _userParameters = new List<QueryData>();
		private List<QueryData> _aecqQueryParameters = new List<QueryData>();
		private List<QueryData> _iocqQueryParameters = new List<QueryData>();

		private AnnotationType _annotationType;

		public AIMQueryParameters()
		{
		}

		protected AIMQueryParameters(AIMQueryParameters queryParameters)
		{
			foreach (AimAnatomicEntityQueryData aeQueryData in queryParameters.AeQueryParameters)
				AeQueryParameters.Add(new AimAnatomicEntityQueryData(aeQueryData));

			foreach (AimImagingObservationQueryData imQueryData in queryParameters.ImQueryParameters)
				ImQueryParameters.Add(new AimImagingObservationQueryData(imQueryData));

			foreach (QueryData queryData in queryParameters.StudyInstanceUidParameters)
				StudyInstanceUidParameters.Add(new QueryData(queryData));

			foreach (QueryData queryData in queryParameters.UserParameters)
				UserParameters.Add(new QueryData(queryData));

			_annotationType = queryParameters._annotationType;
		}

		public List<AimAnatomicEntityQueryData> AeQueryParameters
		{
			get { return _aeQueryParameters; }
			set
			{
				_aeQueryParameters.Clear();
				if (value != null)
					_aeQueryParameters.AddRange(value);
			}
		}

		public List<AimAnatomicEntityCharacteristicQueryData> AecQueryParameters
		{
			get { return _aecQueryParameters; }
			set
			{
				_aecQueryParameters.Clear();
				if (value != null)
					_aecQueryParameters.AddRange(value);
			}
		}

		public List<AimImagingObservationQueryData> ImQueryParameters
		{
			get { return _imQueryParameters; }
			set
			{
				_imQueryParameters.Clear();
				if (value != null)
					_imQueryParameters.AddRange(value);
			}
		}

		public List<AimImagingObservationCharacteristicQueryData> ImcQueryParameters
		{
			get { return _imcQueryParameters; }
			set
			{
				_imcQueryParameters.Clear();
				if (value != null)
					_imcQueryParameters.AddRange(value);
			}
		}

		public List<QueryData> StudyInstanceUidParameters
		{
			get { return _studyInstanceUidParameters; }
			set
			{
				_studyInstanceUidParameters.Clear();
				if (value != null)
					_studyInstanceUidParameters.AddRange(value);
			}
		}

		public List<QueryData> UserParameters
		{
			get { return _userParameters; }
			set
			{
				_userParameters.Clear();
				if (value != null)
					_userParameters.AddRange(value);
			}
		}

		public List<QueryData> AecqQueryParameters
		{
			get { return _aecqQueryParameters; }
			set
			{
				_aecqQueryParameters.Clear();
				if (value != null)
					_aecqQueryParameters.AddRange(value);
			}
		}

		public List<QueryData> IocqQueryParameters
		{
			get { return _aecqQueryParameters; }
			set
			{
				_iocqQueryParameters.Clear();
				if (value != null)
					_iocqQueryParameters.AddRange(value);
			}
		}

		public AnnotationType AnnotationType
		{
			get { return _annotationType; }
			set { _annotationType = value; }
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
		private QueryData _seriesInstanceUID;

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
			_seriesInstanceUID = src._seriesInstanceUID;
		}

		public NBIAQueryParameters Clone()
		{
			return new NBIAQueryParameters(this);
		}

		public QueryData ProjectName
		{
			get { return _projectName ?? QueryData.DefaultQueryData; }
			set { _projectName = value; }
		}

		public QueryData ProtocolId
		{
			get { return _protocolId ?? QueryData.DefaultQueryData; }
			set { _protocolId = value; }
		}

		public QueryData ProtocolName
		{
			get { return _protocolName ?? QueryData.DefaultQueryData; }
			set { _protocolName = value; }
		}

		public QueryData PatientId
		{
			get { return _patientId ?? QueryData.DefaultQueryData; }
			set { _patientId = value; }
		}

		public QueryData PatientName
		{
			get { return _patientName ?? QueryData.DefaultQueryData; }
			set { _patientName = value; }
		}

		public QueryData PatientSex
		{
			get { return _patientSex ?? QueryData.DefaultQueryData; }
			set { _patientSex = value; }
		}

		public QueryData PatientBirthDate
		{
			get { return _patientBirthDate ?? QueryData.DefaultQueryData; }
			set { _patientBirthDate = value; }
		}

		public QueryData SiteName
		{
			get { return _siteName ?? QueryData.DefaultQueryData; }
			set { _siteName = value; }
		}

		public QueryData SiteId
		{
			get { return _siteId ?? QueryData.DefaultQueryData; }
			set { _siteId = value; }
		}

		public QueryData Modality
		{
			get { return _modality ?? QueryData.DefaultQueryData; }
			set { _modality = value; }
		}

		public QueryData SliceThickness
		{
			get { return _sliceThickness ?? QueryData.DefaultQueryData; }
			set { _sliceThickness = value; }
		}

		public QueryData StudyInstanceUID
		{
			get { return _studyInstanceUID ?? QueryData.DefaultQueryData; }
			set { _studyInstanceUID = value; }
		}

		public QueryData SeriesInstanceUID
		{
			get { return _seriesInstanceUID ?? QueryData.DefaultQueryData; }
			set { _seriesInstanceUID = value; }
		}


	}
}
