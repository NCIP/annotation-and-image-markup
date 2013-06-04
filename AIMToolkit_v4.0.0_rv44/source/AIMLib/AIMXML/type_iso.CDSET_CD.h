/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_CD
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_CD

#include "type_iso.CCOLL_CD.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_CD : public ::AIMXML::iso::CCOLL_CD
{
public:
	AIMXML_EXPORT CDSET_CD(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_CD(CDSET_CD const& init);
	void operator=(CDSET_CD const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_CD); }
	MemberElement<iso::CCD, _altova_mi_iso_altova_CDSET_CD_altova_item> item;
	struct item { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_CD
