/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_MO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_MO

#include "type_iso.CQSET_MO.h"


namespace AIMXML
{

namespace iso
{	

class CQSI_MO : public ::AIMXML::iso::CQSET_MO
{
public:
	AIMXML_EXPORT CQSI_MO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSI_MO(CQSI_MO const& init);
	void operator=(CQSI_MO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSI_MO); }
	MemberElement<iso::CQSET_MO, _altova_mi_iso_altova_CQSI_MO_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_MO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_MO
