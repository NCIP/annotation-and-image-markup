/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TS

#include "type_iso.CCOLL_TS.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_TS : public ::AIMXML::iso::CCOLL_TS
{
public:
	AIMXML_EXPORT CBAG_TS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_TS(CBAG_TS const& init);
	void operator=(CBAG_TS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_TS); }
	MemberElement<iso::CTS, _altova_mi_iso_altova_CBAG_TS_altova_item> item;
	struct item { typedef Iterator<iso::CTS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TS
