/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHXIT
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHXIT



namespace AIMXML
{

namespace iso
{	

class CHXIT : public TypeBase
{
public:
	AIMXML_EXPORT CHXIT(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHXIT(CHXIT const& init);
	void operator=(CHXIT const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHXIT); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CHXIT_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CHXIT_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CHXIT_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CHXIT_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHXIT
