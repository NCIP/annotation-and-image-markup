/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CANY
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CANY

#include "type_iso.CHXIT.h"


namespace AIMXML
{

namespace iso
{	

class CANY : public ::AIMXML::iso::CHXIT
{
public:
	AIMXML_EXPORT CANY(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CANY(CANY const& init);
	void operator=(CANY const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CANY); }
	MemberAttribute<string_type,_altova_mi_iso_altova_CANY_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CANY_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CANY_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CANY
