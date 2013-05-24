/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationRoleEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationRoleEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CAnnotationRoleEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CAnnotationRoleEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationRoleEntity(CAnnotationRoleEntity const& init);
	void operator=(CAnnotationRoleEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationRoleEntity); }
	MemberElement<iso::CCD, _altova_mi_altova_CAnnotationRoleEntity_altova_roleCode> roleCode;
	struct roleCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CAnnotationRoleEntity_altova_questionTypeCode> questionTypeCode;
	struct questionTypeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CAnnotationRoleEntity_altova_roleSequenceNumber> roleSequenceNumber;
	struct roleSequenceNumber { typedef Iterator<iso::CINT> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationRoleEntity
