/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCDGroup
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCDGroup



namespace AIMXML
{

namespace iso
{	

class CCDGroup : public TypeBase
{
public:
	AIMXML_EXPORT CCDGroup(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCDGroup(CCDGroup const& init);
	void operator=(CCDGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCDGroup); }
	MemberElement<iso::CCR, _altova_mi_iso_altova_CCDGroup_altova_qualifier> qualifier;
	struct qualifier { typedef Iterator<iso::CCR> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCDGroup
