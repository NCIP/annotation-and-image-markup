/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_MO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_MO

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CQSET_MO : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CQSET_MO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSET_MO(CQSET_MO const& init);
	void operator=(CQSET_MO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSET_MO); }
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CQSET_MO_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_MO
