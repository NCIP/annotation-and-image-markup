/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_INT
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_INT

#include "type_iso.CLIST_INT.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_INT : public ::AIMXML::iso::CLIST_INT
{
public:
	AIMXML_EXPORT CHIST_INT(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_INT(CHIST_INT const& init);
	void operator=(CHIST_INT const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_INT); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_INT
