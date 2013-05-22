/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_PQ_Time
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_PQ_Time

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CQSET_PQ_Time : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CQSET_PQ_Time(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSET_PQ_Time(CQSET_PQ_Time const& init);
	void operator=(CQSET_PQ_Time const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSET_PQ_Time); }
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CQSET_PQ_Time_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_PQ_Time
