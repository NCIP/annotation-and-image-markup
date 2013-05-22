/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TS

#include "type_iso.CCOLL_TS.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_TS : public ::AIMXML::iso::CCOLL_TS
{
public:
	AIMXML_EXPORT CDSET_TS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_TS(CDSET_TS const& init);
	void operator=(CDSET_TS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_TS); }
	MemberElement<iso::CTS, _altova_mi_iso_altova_CDSET_TS_altova_item> item;
	struct item { typedef Iterator<iso::CTS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TS
