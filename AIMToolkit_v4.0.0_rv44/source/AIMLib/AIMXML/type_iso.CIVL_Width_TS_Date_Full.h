/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_Width_TS_Date_Full
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_Width_TS_Date_Full



namespace AIMXML
{

namespace iso
{	

class CIVL_Width_TS_Date_Full : public TypeBase
{
public:
	AIMXML_EXPORT CIVL_Width_TS_Date_Full(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_Width_TS_Date_Full(CIVL_Width_TS_Date_Full const& init);
	void operator=(CIVL_Width_TS_Date_Full const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_Width_TS_Date_Full); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	MemberElement<iso::CTS_Date_Full, _altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_low> low;
	struct low { typedef Iterator<iso::CTS_Date_Full> iterator; };
	MemberElement<iso::CTS_Date_Full, _altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_high> high;
	struct high { typedef Iterator<iso::CTS_Date_Full> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_Width_TS_Date_Full_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_Width_TS_Date_Full
