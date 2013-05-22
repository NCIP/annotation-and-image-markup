/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CInferenceEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CInferenceEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CInferenceEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CInferenceEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CInferenceEntity(CInferenceEntity const& init);
	void operator=(CInferenceEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CInferenceEntity); }
	MemberElement<iso::CBL, _altova_mi_altova_CInferenceEntity_altova_imageEvidence> imageEvidence;
	struct imageEvidence { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CInferenceEntity_altova_isPresent> isPresent;
	struct isPresent { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CInferenceEntity_altova_typeCode> typeCode;
	struct typeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CInferenceEntity_altova_questionTypeCode> questionTypeCode;
	struct questionTypeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CInferenceEntity_altova_annotatorConfidence> annotatorConfidence;
	struct annotatorConfidence { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CInferenceEntity_altova_description> description;
	struct description { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CInferenceEntity_altova_label> label;
	struct label { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CInferenceEntity_altova_questionIndex> questionIndex;
	struct questionIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CInferenceEntity_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CInferenceEntity
