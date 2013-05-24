/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_CD
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_CD

#include "type_iso.CLIST_CD.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_CD : public ::AIMXML::iso::CLIST_CD
{
public:
	AIMXML_EXPORT CHIST_CD(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_CD(CHIST_CD const& init);
	void operator=(CHIST_CD const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_CD); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_CD
