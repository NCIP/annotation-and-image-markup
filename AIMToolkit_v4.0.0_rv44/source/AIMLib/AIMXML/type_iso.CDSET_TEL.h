/*
*  2007 � 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TEL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TEL

#include "type_iso.CCOLL_TEL.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_TEL : public ::AIMXML::iso::CCOLL_TEL
{
public:
	AIMXML_EXPORT CDSET_TEL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_TEL(CDSET_TEL const& init);
	void operator=(CDSET_TEL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_TEL); }
	MemberElement<iso::CTEL, _altova_mi_iso_altova_CDSET_TEL_altova_item> item;
	struct item { typedef Iterator<iso::CTEL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TEL
