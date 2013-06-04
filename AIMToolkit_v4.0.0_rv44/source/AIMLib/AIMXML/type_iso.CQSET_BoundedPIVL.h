/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_BoundedPIVL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_BoundedPIVL



namespace AIMXML
{

namespace iso
{	

class CQSET_BoundedPIVL : public TypeBase
{
public:
	AIMXML_EXPORT CQSET_BoundedPIVL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSET_BoundedPIVL(CQSET_BoundedPIVL const& init);
	void operator=(CQSET_BoundedPIVL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSET_BoundedPIVL); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CQSET_BoundedPIVL_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CQSET_BoundedPIVL_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CQSET_BoundedPIVL_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CQSET_BoundedPIVL_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CQSET_BoundedPIVL_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CQSET_BoundedPIVL_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CQSET_BoundedPIVL_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CQSET_BoundedPIVL_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	MemberElement<iso::CQSET_TS, _altova_mi_iso_altova_CQSET_BoundedPIVL_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_TS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_BoundedPIVL
