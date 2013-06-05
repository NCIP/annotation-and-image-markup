/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_REAL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_REAL

#include "type_iso.CQSET_REAL.h"


namespace AIMXML
{

namespace iso
{	

class CQSI_REAL : public ::AIMXML::iso::CQSET_REAL
{
public:
	AIMXML_EXPORT CQSI_REAL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSI_REAL(CQSI_REAL const& init);
	void operator=(CQSI_REAL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSI_REAL); }
	MemberElement<iso::CQSET_REAL, _altova_mi_iso_altova_CQSI_REAL_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_REAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_REAL
