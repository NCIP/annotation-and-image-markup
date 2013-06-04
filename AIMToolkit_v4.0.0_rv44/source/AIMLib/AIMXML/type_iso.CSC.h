/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSC
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSC

#include "type_iso.CST.h"


namespace AIMXML
{

namespace iso
{	

class CSC : public ::AIMXML::iso::CST
{
public:
	AIMXML_EXPORT CSC(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CSC(CSC const& init);
	void operator=(CSC const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CSC); }
	MemberElement<iso::CCD, _altova_mi_iso_altova_CSC_altova_code> code;
	struct code { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSC
