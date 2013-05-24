/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Image
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Image



namespace AIMXML
{

namespace iso
{	

class CED_Image : public TypeBase
{
public:
	AIMXML_EXPORT CED_Image(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CED_Image(CED_Image const& init);
	void operator=(CED_Image const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CED_Image); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_mediaType, 0, 0> mediaType;	// mediaType Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_charset, 0, 0> charset;	// charset CCode

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_language, 0, 0> language;	// language CCode
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_compression, 0, 4> compression;	// compression CCompression
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Image_altova_integrityCheckAlgorithm, 0, 2> integrityCheckAlgorithm;	// integrityCheckAlgorithm CIntegrityCheckAlgorithm
	MemberElement<xs::Cbase64BinaryType, _altova_mi_iso_altova_CED_Image_altova_data> data;
	struct data { typedef Iterator<xs::Cbase64BinaryType> iterator; };
	MemberElement<xs::CanyType, _altova_mi_iso_altova_CED_Image_altova_xml> xml;
	struct xml { typedef Iterator<xs::CanyType> iterator; };
	MemberElement<iso::CTEL, _altova_mi_iso_altova_CED_Image_altova_reference> reference;
	struct reference { typedef Iterator<iso::CTEL> iterator; };
	MemberElement<xs::Cbase64BinaryType, _altova_mi_iso_altova_CED_Image_altova_integrityCheck> integrityCheck;
	struct integrityCheck { typedef Iterator<xs::Cbase64BinaryType> iterator; };
	MemberElement<iso::CED, _altova_mi_iso_altova_CED_Image_altova_thumbnail> thumbnail;
	struct thumbnail { typedef Iterator<iso::CED> iterator; };
	MemberElement<iso::CED, _altova_mi_iso_altova_CED_Image_altova_translation> translation;
	struct translation { typedef Iterator<iso::CED> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Image
