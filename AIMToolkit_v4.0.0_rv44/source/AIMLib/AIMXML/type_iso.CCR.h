/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCR
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCR



namespace AIMXML
{

namespace iso
{	

class CCR : public TypeBase
{
public:
	AIMXML_EXPORT CCR(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCR(CCR const& init);
	void operator=(CCR const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCR); }

	MemberAttribute<bool,_altova_mi_iso_altova_CCR_altova_inverted, 0, 0> inverted;	// inverted Cboolean
	MemberElement<iso::CCD_CV, _altova_mi_iso_altova_CCR_altova_name> name;
	struct name { typedef Iterator<iso::CCD_CV> iterator; };
	MemberElement<iso::CCD, _altova_mi_iso_altova_CCR_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCR
