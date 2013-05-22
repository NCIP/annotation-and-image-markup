/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CTS_Date
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CTS_Date



namespace AIMXML
{

namespace iso
{	

class CTS_Date : public TypeBase
{
public:
	AIMXML_EXPORT CTS_Date(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTS_Date(CTS_Date const& init);
	void operator=(CTS_Date const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CTS_Date); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_expressionLanguage, 0, 0> expressionLanguage;	// expressionLanguage CCode
	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_uncertaintyType, 0, 9> uncertaintyType;	// uncertaintyType CUncertaintyType

	MemberAttribute<string_type,_altova_mi_iso_altova_CTS_Date_altova_value2, 0, 0> value2;	// value Cstring
	MemberElement<iso::CED, _altova_mi_iso_altova_CTS_Date_altova_expression> expression;
	struct expression { typedef Iterator<iso::CED> iterator; };
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CTS_Date_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CTS_Date_altova_uncertainty> uncertainty;
	struct uncertainty { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CTS_Date
