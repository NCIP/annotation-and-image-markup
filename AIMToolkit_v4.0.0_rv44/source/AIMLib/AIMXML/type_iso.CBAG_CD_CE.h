/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_CD_CE
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_CD_CE

#include "type_iso.CCOLL_CD_CE.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_CD_CE : public ::AIMXML::iso::CCOLL_CD_CE
{
public:
	AIMXML_EXPORT CBAG_CD_CE(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_CD_CE(CBAG_CD_CE const& init);
	void operator=(CBAG_CD_CE const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_CD_CE); }
	MemberElement<iso::CCD_CE, _altova_mi_iso_altova_CBAG_CD_CE_altova_item> item;
	struct item { typedef Iterator<iso::CCD_CE> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_CD_CE
