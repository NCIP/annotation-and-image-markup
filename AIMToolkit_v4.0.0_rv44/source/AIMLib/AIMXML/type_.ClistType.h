/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClistType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClistType



namespace AIMXML
{

class ClistType : public TypeBase
{
public:
	AIMXML_EXPORT ClistType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT ClistType(ClistType const& init);
	void operator=(ClistType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_ClistType); }

	MemberAttribute<string_type,_altova_mi_altova_ClistType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_ClistType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_ClistType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS
	MemberAttribute<string_type,_altova_mi_altova_ClistType_altova_listType, 0, 2> listType;	// listType ClistTypeType
	MemberElement<CcaptionType, _altova_mi_altova_ClistType_altova_caption> caption;
	struct caption { typedef Iterator<CcaptionType> iterator; };
	MemberElement<CitemType, _altova_mi_altova_ClistType_altova_item> item;
	struct item { typedef Iterator<CitemType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClistType
