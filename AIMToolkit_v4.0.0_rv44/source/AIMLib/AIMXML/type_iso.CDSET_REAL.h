/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_REAL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_REAL

#include "type_iso.CCOLL_REAL.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_REAL : public ::AIMXML::iso::CCOLL_REAL
{
public:
	AIMXML_EXPORT CDSET_REAL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_REAL(CDSET_REAL const& init);
	void operator=(CDSET_REAL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_REAL); }
	MemberElement<iso::CREAL, _altova_mi_iso_altova_CDSET_REAL_altova_item> item;
	struct item { typedef Iterator<iso::CREAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_REAL
