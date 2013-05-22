/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CCalculationEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CCalculationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalculationEntity(CCalculationEntity const& init);
	void operator=(CCalculationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalculationEntity); }
	MemberElement<iso::CCD, _altova_mi_altova_CCalculationEntity_altova_typeCode> typeCode;
	struct typeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CCalculationEntity_altova_questionTypeCode> questionTypeCode;
	struct questionTypeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CCalculationEntity_altova_description> description;
	struct description { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CCalculationEntity_altova_mathML> mathML;
	struct mathML { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CCalculationEntity_altova_questionIndex> questionIndex;
	struct questionIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<CcalculationResultCollectionType, _altova_mi_altova_CCalculationEntity_altova_calculationResultCollection> calculationResultCollection;
	struct calculationResultCollection { typedef Iterator<CcalculationResultCollectionType> iterator; };
	MemberElement<CAlgorithm, _altova_mi_altova_CCalculationEntity_altova_algorithm> algorithm;
	struct algorithm { typedef Iterator<CAlgorithm> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntity
