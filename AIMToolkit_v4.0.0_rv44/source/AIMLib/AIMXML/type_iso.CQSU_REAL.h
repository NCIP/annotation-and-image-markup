/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_REAL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_REAL

#include "type_iso.CQSET_REAL.h"


namespace AIMXML
{

namespace iso
{	

class CQSU_REAL : public ::AIMXML::iso::CQSET_REAL
{
public:
	AIMXML_EXPORT CQSU_REAL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSU_REAL(CQSU_REAL const& init);
	void operator=(CQSU_REAL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSU_REAL); }
	MemberElement<iso::CQSET_REAL, _altova_mi_iso_altova_CQSU_REAL_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_REAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_REAL
