/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED_Image
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED_Image

#include "type_iso.CLIST_ED_Image.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_ED_Image : public ::AIMXML::iso::CLIST_ED_Image
{
public:
	AIMXML_EXPORT CHIST_ED_Image(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_ED_Image(CHIST_ED_Image const& init);
	void operator=(CHIST_ED_Image const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_ED_Image); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED_Image
