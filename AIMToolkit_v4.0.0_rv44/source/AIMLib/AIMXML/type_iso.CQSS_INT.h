/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_INT
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_INT

#include "type_iso.CQSET_INT.h"


namespace AIMXML
{

namespace iso
{	

class CQSS_INT : public ::AIMXML::iso::CQSET_INT
{
public:
	AIMXML_EXPORT CQSS_INT(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSS_INT(CQSS_INT const& init);
	void operator=(CQSS_INT const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSS_INT); }
	MemberElement<iso::CINT, _altova_mi_iso_altova_CQSS_INT_altova_term> term;
	struct term { typedef Iterator<iso::CINT> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_INT
