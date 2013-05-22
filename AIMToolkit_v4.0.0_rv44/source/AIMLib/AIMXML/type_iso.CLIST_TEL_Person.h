/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_TEL_Person
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_TEL_Person

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CLIST_TEL_Person : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CLIST_TEL_Person(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CLIST_TEL_Person(CLIST_TEL_Person const& init);
	void operator=(CLIST_TEL_Person const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CLIST_TEL_Person); }
	MemberElement<iso::CTEL_Person, _altova_mi_iso_altova_CLIST_TEL_Person_altova_item> item;
	struct item { typedef Iterator<iso::CTEL_Person> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_TEL_Person
