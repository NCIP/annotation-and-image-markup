/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_CO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_CO

#include "type_iso.CQSET_CO.h"


namespace AIMXML
{

namespace iso
{	

class CQSP_CO : public ::AIMXML::iso::CQSET_CO
{
public:
	AIMXML_EXPORT CQSP_CO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSP_CO(CQSP_CO const& init);
	void operator=(CQSP_CO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSP_CO); }
	MemberElement<iso::CQSET_CO, _altova_mi_iso_altova_CQSP_CO_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_CO> iterator; };
	MemberElement<iso::CQSET_CO, _altova_mi_iso_altova_CQSP_CO_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_CO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_CO
