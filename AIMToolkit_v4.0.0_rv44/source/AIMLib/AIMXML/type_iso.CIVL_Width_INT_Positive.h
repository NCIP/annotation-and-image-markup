/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_Width_INT_Positive
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_Width_INT_Positive



namespace AIMXML
{

namespace iso
{	

class CIVL_Width_INT_Positive : public TypeBase
{
public:
	AIMXML_EXPORT CIVL_Width_INT_Positive(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_Width_INT_Positive(CIVL_Width_INT_Positive const& init);
	void operator=(CIVL_Width_INT_Positive const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_Width_INT_Positive); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	MemberElement<iso::CINT_Positive, _altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_low> low;
	struct low { typedef Iterator<iso::CINT_Positive> iterator; };
	MemberElement<iso::CINT_Positive, _altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_high> high;
	struct high { typedef Iterator<iso::CINT_Positive> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_Width_INT_Positive_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_Width_INT_Positive
