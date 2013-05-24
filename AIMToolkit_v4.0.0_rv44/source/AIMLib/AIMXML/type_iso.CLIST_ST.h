/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_ST
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_ST

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CLIST_ST : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CLIST_ST(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CLIST_ST(CLIST_ST const& init);
	void operator=(CLIST_ST const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CLIST_ST); }
	MemberElement<iso::CST, _altova_mi_iso_altova_CLIST_ST_altova_item> item;
	struct item { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_ST
