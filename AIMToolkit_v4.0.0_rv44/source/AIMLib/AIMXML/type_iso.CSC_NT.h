/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSC_NT
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSC_NT



namespace AIMXML
{

namespace iso
{	

class CSC_NT : public TypeBase
{
public:
	AIMXML_EXPORT CSC_NT(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CSC_NT(CSC_NT const& init);
	void operator=(CSC_NT const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CSC_NT); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CSC_NT_altova_language, 0, 0> language;	// language CCode
	MemberElement<iso::CST, _altova_mi_iso_altova_CSC_NT_altova_translation> translation;
	struct translation { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_iso_altova_CSC_NT_altova_code> code;
	struct code { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSC_NT
