/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_SC
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_SC

#include "type_iso.CCOLL_SC.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_SC : public ::AIMXML::iso::CCOLL_SC
{
public:
	AIMXML_EXPORT CDSET_SC(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_SC(CDSET_SC const& init);
	void operator=(CDSET_SC const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_SC); }
	MemberElement<iso::CSC, _altova_mi_iso_altova_CDSET_SC_altova_item> item;
	struct item { typedef Iterator<iso::CSC> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_SC
