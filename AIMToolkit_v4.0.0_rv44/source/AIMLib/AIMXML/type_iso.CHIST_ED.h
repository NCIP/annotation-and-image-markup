/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED

#include "type_iso.CLIST_ED.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_ED : public ::AIMXML::iso::CLIST_ED
{
public:
	AIMXML_EXPORT CHIST_ED(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_ED(CHIST_ED const& init);
	void operator=(CHIST_ED const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_ED); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED
