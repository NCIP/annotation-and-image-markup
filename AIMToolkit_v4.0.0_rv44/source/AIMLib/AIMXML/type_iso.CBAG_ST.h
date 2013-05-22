/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ST
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ST

#include "type_iso.CCOLL_ST.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_ST : public ::AIMXML::iso::CCOLL_ST
{
public:
	AIMXML_EXPORT CBAG_ST(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_ST(CBAG_ST const& init);
	void operator=(CBAG_ST const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_ST); }
	MemberElement<iso::CST, _altova_mi_iso_altova_CBAG_ST_altova_item> item;
	struct item { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ST
