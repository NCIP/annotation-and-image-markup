/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CrenderMultiMediaType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CrenderMultiMediaType



namespace AIMXML
{

class CrenderMultiMediaType : public TypeBase
{
public:
	AIMXML_EXPORT CrenderMultiMediaType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CrenderMultiMediaType(CrenderMultiMediaType const& init);
	void operator=(CrenderMultiMediaType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CrenderMultiMediaType); }

	MemberAttribute<string_type,_altova_mi_altova_CrenderMultiMediaType_altova_referencedObject, 0, 0> referencedObject;	// referencedObject CIDREFS

	MemberAttribute<string_type,_altova_mi_altova_CrenderMultiMediaType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CrenderMultiMediaType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CrenderMultiMediaType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS
	MemberElement<CcaptionType, _altova_mi_altova_CrenderMultiMediaType_altova_caption> caption;
	struct caption { typedef Iterator<CcaptionType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CrenderMultiMediaType
