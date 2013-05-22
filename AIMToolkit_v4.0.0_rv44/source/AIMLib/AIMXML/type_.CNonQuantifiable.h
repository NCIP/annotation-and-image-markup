/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CNonQuantifiable
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CNonQuantifiable

#include "type_.CCharacteristicQuantification.h"


namespace AIMXML
{

class CNonQuantifiable : public ::AIMXML::CCharacteristicQuantification
{
public:
	AIMXML_EXPORT CNonQuantifiable(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNonQuantifiable(CNonQuantifiable const& init);
	void operator=(CNonQuantifiable const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CNonQuantifiable); }
	MemberElement<iso::CCD, _altova_mi_altova_CNonQuantifiable_altova_typeCode> typeCode;
	struct typeCode { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CNonQuantifiable
