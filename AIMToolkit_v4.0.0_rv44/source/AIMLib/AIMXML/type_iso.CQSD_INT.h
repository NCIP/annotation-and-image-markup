/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_INT
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_INT

#include "type_iso.CQSET_INT.h"


namespace AIMXML
{

namespace iso
{	

class CQSD_INT : public ::AIMXML::iso::CQSET_INT
{
public:
	AIMXML_EXPORT CQSD_INT(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSD_INT(CQSD_INT const& init);
	void operator=(CQSD_INT const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSD_INT); }
	MemberElement<iso::CQSET_INT, _altova_mi_iso_altova_CQSD_INT_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_INT> iterator; };
	MemberElement<iso::CQSET_INT, _altova_mi_iso_altova_CQSD_INT_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_INT> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_INT
