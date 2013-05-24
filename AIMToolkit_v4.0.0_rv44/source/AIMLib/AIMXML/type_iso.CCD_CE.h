/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCD_CE
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCD_CE



namespace AIMXML
{

namespace iso
{	

class CCD_CE : public TypeBase
{
public:
	AIMXML_EXPORT CCD_CE(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCD_CE(CCD_CE const& init);
	void operator=(CCD_CE const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCD_CE); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_code, 0, 0> code;	// code Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_codeSystem, 0, 0> codeSystem;	// codeSystem CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_codeSystemName, 0, 0> codeSystemName;	// codeSystemName Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_codeSystemVersion, 0, 0> codeSystemVersion;	// codeSystemVersion Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_valueSet, 0, 0> valueSet;	// valueSet Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_valueSetVersion, 0, 0> valueSetVersion;	// valueSetVersion Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_id, 0, 0> id;	// id CID
	MemberAttribute<string_type,_altova_mi_iso_altova_CCD_CE_altova_codingRationale, 1, 4> codingRationale;	// codingRationale Cset_CodingRationale
	MemberElement<iso::CST, _altova_mi_iso_altova_CCD_CE_altova_displayName> displayName;
	struct displayName { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CCD_CE_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	MemberElement<iso::CCR, _altova_mi_iso_altova_CCD_CE_altova_qualifier> qualifier;
	struct qualifier { typedef Iterator<iso::CCR> iterator; };
	MemberElement<iso::CCDGroup, _altova_mi_iso_altova_CCD_CE_altova_group> group;
	struct group { typedef Iterator<iso::CCDGroup> iterator; };
	MemberElement<iso::CCD, _altova_mi_iso_altova_CCD_CE_altova_translation> translation;
	struct translation { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CXReference, _altova_mi_iso_altova_CCD_CE_altova_source> source;
	struct source { typedef Iterator<iso::CXReference> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCD_CE
