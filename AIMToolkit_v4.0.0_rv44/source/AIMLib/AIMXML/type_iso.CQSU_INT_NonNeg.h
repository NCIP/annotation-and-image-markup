/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_INT_NonNeg
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_INT_NonNeg

#include "type_iso.CQSET_INT_NonNeg.h"


namespace AIMXML
{

namespace iso
{	

class CQSU_INT_NonNeg : public ::AIMXML::iso::CQSET_INT_NonNeg
{
public:
	AIMXML_EXPORT CQSU_INT_NonNeg(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSU_INT_NonNeg(CQSU_INT_NonNeg const& init);
	void operator=(CQSU_INT_NonNeg const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSU_INT_NonNeg); }
	MemberElement<iso::CQSET_INT_NonNeg, _altova_mi_iso_altova_CQSU_INT_NonNeg_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_INT_NonNeg> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_INT_NonNeg
