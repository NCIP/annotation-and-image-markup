/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_MO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_MO

#include "type_iso.CCOLL_MO.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_MO : public ::AIMXML::iso::CCOLL_MO
{
public:
	AIMXML_EXPORT CBAG_MO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_MO(CBAG_MO const& init);
	void operator=(CBAG_MO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_MO); }
	MemberElement<iso::CMO, _altova_mi_iso_altova_CBAG_MO_altova_item> item;
	struct item { typedef Iterator<iso::CMO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_MO
