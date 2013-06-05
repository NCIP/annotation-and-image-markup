/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLib_DicomTagCollection_Class)
#define _AIMLib_DicomTagCollection_Class

#include <string>
#include <map>

namespace aim_lib
{

	class DicomTagCollection
	{
	public:

		// Selected Enums Based on
		// Comprehensive SR IOD Modules (A.35.3-1)
		// NOTE: Commented out tags require further modifications to DCMTK
		enum AIM_DCM_TAG
		{
			// Patient Module - Mandatory
			ADT_PATIENTS_NAME,  // 2
			ADT_PATIENT_ID,  // 2
//			ADT_ISSUER_OF_PATIENT_ID, // 3
			ADT_PATIENTS_BIRTH_DATE, // 2
			ADT_PATIENT_SEX, // 2
			ADT_PATIENT_ETHNIC_GROUP, // 3

			// Clinical Trial Subject Module (C.7-2b) - User Optional
//			ADT_CLINICAL_TRIAL_SPONSOR_NAME, // 1
//			ADT_CLINICAL_TRIAL_PROTOCOL_ID, // 1
//			ADT_CLINICAL_TRIAL_PROTOCOL_NAME, // 2
//			ADT_CLINICAL_TRIAL_SITE_ID, // 2
//			ADT_CLINICAL_TRIAL_SITE_NAME, // 2
//			ADT_CLINICAL_TRIAL_SUBJECT_ID, // 1C
//			ADT_CLINICAL_TRIAL_SBUJECT_READING_ID, // 1C

			// General Study Module (C.7-3) - Mandatory
			ADT_STUDY_INSTANCE_UID, // 1
//			ADT_STUDY_DATE, // 2
//			ADT_STUDY_TIME, // 2
			ADT_REFERRING_PHYSICIANS_NAME, // 2
			ADT_STUDY_ID, // 2
			ADT_ACCESSION_NUMBER, // 2
			ADT_STUDY_DESCRIPTION, // 3

			// Clinical Trial Study Module (C.7-4b) - User Optional
//			ADT_CLINICAL_TRIAL_TIME_POINT_ID, // 2
//			ADT_CLINICAL_TRIAL_TIME_POINT_DESCRIPTION, // 3

			// SR Document Series Module (C.17-1) - Mandatory
/*			- will be auto generated
			ADT_MODALITY, // 1
			ADT_SERIES_INSTANCE_UID, // 1
			ADT_SERIES_NUMBER, // 1
*/
			// Clinical Trial Series Module (C.7-5b) - User Optional
//			ADT_CLINICAL_TRIAL_COORDINATING_CENTER_NAME, // 2

			// General Equipment Module (C.7-8) - Mandatory
			ADT_MANUFACTURE, // 2
//			ADT_INSTITUTION_NAME, // 3
//			ADT_INSTITUTION_ADDRESS, // 3
//			ADT_STATION_NAME, // 3
//			ADT_INSTITUTIONAL_DEPARTMENT_NAME, // 3
			ADT_MANUFACTURES_MODEL_NAME, // 3
			ADT_DEVICE_SERIAL_NUMBER, // 3
			ADT_SOFTWARE_VERSIONS, // 3

			ADT_LAST = ADT_SOFTWARE_VERSIONS
		};

		DicomTagCollection(void);
		DicomTagCollection(const DicomTagCollection& tagCollection);
		~DicomTagCollection(void);

		void SetTagValue(AIM_DCM_TAG tag, const std::string& tagValue);
		const std::string& GetTagValue(AIM_DCM_TAG tag) const;
		void RemoveTag(AIM_DCM_TAG tag);
		bool HasTag(AIM_DCM_TAG tag) const;

	protected:
		
		typedef std::map<AIM_DCM_TAG, std::string> MapDcmValues;
		MapDcmValues _tagValues;

		static const std::string _emptyStr;
	};
}

#endif // _AIMLib_DicomTagCollection_Class