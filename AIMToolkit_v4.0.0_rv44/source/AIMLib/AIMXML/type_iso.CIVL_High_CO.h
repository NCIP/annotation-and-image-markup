/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_High_CO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_High_CO



namespace AIMXML
{

namespace iso
{	

class CIVL_High_CO : public TypeBase
{
public:
	AIMXML_EXPORT CIVL_High_CO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_High_CO(CIVL_High_CO const& init);
	void operator=(CIVL_High_CO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_High_CO); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_High_CO_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_High_CO_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_High_CO_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_High_CO_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_High_CO_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_High_CO_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_High_CO_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_High_CO_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_High_CO_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CIVL_High_CO_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	MemberElement<iso::CCO, _altova_mi_iso_altova_CIVL_High_CO_altova_low> low;
	struct low { typedef Iterator<iso::CCO> iterator; };
	MemberElement<iso::CCO, _altova_mi_iso_altova_CIVL_High_CO_altova_high> high;
	struct high { typedef Iterator<iso::CCO> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_High_CO_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_High_CO
