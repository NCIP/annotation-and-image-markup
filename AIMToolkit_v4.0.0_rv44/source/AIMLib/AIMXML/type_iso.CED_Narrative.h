/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Narrative
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Narrative



namespace AIMXML
{

namespace iso
{	

class CED_Narrative : public TypeBase
{
public:
	AIMXML_EXPORT CED_Narrative(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CED_Narrative(CED_Narrative const& init);
	void operator=(CED_Narrative const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CED_Narrative); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_mediaType, 0, 0> mediaType;	// mediaType Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_charset, 0, 0> charset;	// charset CCode

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_language, 0, 0> language;	// language CCode
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_compression, 0, 4> compression;	// compression CCompression
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Narrative_altova_integrityCheckAlgorithm, 0, 2> integrityCheckAlgorithm;	// integrityCheckAlgorithm CIntegrityCheckAlgorithm
	MemberElement<xs::Cbase64BinaryType, _altova_mi_iso_altova_CED_Narrative_altova_data> data;
	struct data { typedef Iterator<xs::Cbase64BinaryType> iterator; };
	MemberElement<iso::CNarrative, _altova_mi_iso_altova_CED_Narrative_altova_xml> xml;
	struct xml { typedef Iterator<iso::CNarrative> iterator; };
	MemberElement<iso::CTEL, _altova_mi_iso_altova_CED_Narrative_altova_reference> reference;
	struct reference { typedef Iterator<iso::CTEL> iterator; };
	MemberElement<xs::Cbase64BinaryType, _altova_mi_iso_altova_CED_Narrative_altova_integrityCheck> integrityCheck;
	struct integrityCheck { typedef Iterator<xs::Cbase64BinaryType> iterator; };
	MemberElement<iso::CED, _altova_mi_iso_altova_CED_Narrative_altova_thumbnail> thumbnail;
	struct thumbnail { typedef Iterator<iso::CED> iterator; };
	MemberElement<iso::CED, _altova_mi_iso_altova_CED_Narrative_altova_translation> translation;
	struct translation { typedef Iterator<iso::CED> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Narrative
