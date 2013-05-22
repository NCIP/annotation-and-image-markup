/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CScale
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CScale

#include "type_.CCharacteristicQuantification.h"


namespace AIMXML
{

class CScale : public ::AIMXML::CCharacteristicQuantification
{
public:
	AIMXML_EXPORT CScale(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CScale(CScale const& init);
	void operator=(CScale const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CScale); }

	MemberAttribute<string_type,_altova_mi_altova_CScale_altova_comment, 0, 0> comment;	// comment Cstring

	MemberAttribute<string_type,_altova_mi_altova_CScale_altova_description, 0, 0> description;	// description Cstring

	MemberAttribute<string_type,_altova_mi_altova_CScale_altova_value2, 0, 0> scaleValue;	// value Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CScale
