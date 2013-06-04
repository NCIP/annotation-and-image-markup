/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotation



namespace AIMXML
{

class CAnnotation : public TypeBase
{
public:
	AIMXML_EXPORT CAnnotation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotation(CAnnotation const& init);
	void operator=(CAnnotation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotation); }

	MemberAttribute<__int64,_altova_mi_altova_CAnnotation_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_aimVersion, 0, 0> aimVersion;	// aimVersion Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_comment, 0, 0> comment;	// comment Cstring

	MemberAttribute<altova::DateTime,_altova_mi_altova_CAnnotation_altova_dateTime, 0, 0> dateTime;	// dateTime CdateTime

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_name, 0, 0> name;	// name Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_uniqueIdentifier, 0, 0> uniqueIdentifier;	// uniqueIdentifier Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_codeValue, 0, 0> codeValue;	// codeValue Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_codeMeaning, 0, 0> codeMeaning;	// codeMeaning Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_codingSchemeDesignator, 0, 0> codingSchemeDesignator;	// codingSchemeDesignator Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_codingSchemeVersion, 0, 0> codingSchemeVersion;	// codingSchemeVersion Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotation_altova_precedentReferencedAnnotationUID, 0, 0> precedentReferencedAnnotationUID;	// precedentReferencedAnnotationUID Cstring
	MemberElement<CcalculationCollectionType, _altova_mi_altova_CAnnotation_altova_calculationCollection> calculationCollection;
	struct calculationCollection { typedef Iterator<CcalculationCollectionType> iterator; };
	MemberElement<CinferenceCollectionType, _altova_mi_altova_CAnnotation_altova_inferenceCollection> inferenceCollection;
	struct inferenceCollection { typedef Iterator<CinferenceCollectionType> iterator; };
	MemberElement<CuserType, _altova_mi_altova_CAnnotation_altova_user> user;
	struct user { typedef Iterator<CuserType> iterator; };
	MemberElement<CequipmentType, _altova_mi_altova_CAnnotation_altova_equipment> equipment;
	struct equipment { typedef Iterator<CequipmentType> iterator; };
	MemberElement<CanatomicEntityCollectionType, _altova_mi_altova_CAnnotation_altova_anatomicEntityCollection> anatomicEntityCollection;
	struct anatomicEntityCollection { typedef Iterator<CanatomicEntityCollectionType> iterator; };
	MemberElement<CimagingObservationCollectionType, _altova_mi_altova_CAnnotation_altova_imagingObservationCollection> imagingObservationCollection;
	struct imagingObservationCollection { typedef Iterator<CimagingObservationCollectionType> iterator; };
	MemberElement<CaimStatusType, _altova_mi_altova_CAnnotation_altova_aimStatus> aimStatus;
	struct aimStatus { typedef Iterator<CaimStatusType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotation
