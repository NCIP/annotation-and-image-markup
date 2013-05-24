/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClinkHtmlType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClinkHtmlType



namespace AIMXML
{

class ClinkHtmlType : public TypeBase
{
public:
	AIMXML_EXPORT ClinkHtmlType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT ClinkHtmlType(ClinkHtmlType const& init);
	void operator=(ClinkHtmlType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_ClinkHtmlType); }
	AIMXML_EXPORT void operator=(const string_type& value);
	AIMXML_EXPORT operator string_type();

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_name, 0, 0> name;	// name Cstring

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_href, 0, 0> href;	// href Cstring

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_rel, 0, 0> rel;	// rel Cstring

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_rev, 0, 0> rev;	// rev Cstring

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_title, 0, 0> title;	// title Cstring

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_ClinkHtmlType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS
	MemberElement<CfootnoteType, _altova_mi_altova_ClinkHtmlType_altova_footnote> footnote;
	struct footnote { typedef Iterator<CfootnoteType> iterator; };
	MemberElement<CfootnoteRefType, _altova_mi_altova_ClinkHtmlType_altova_footnoteRef> footnoteRef;
	struct footnoteRef { typedef Iterator<CfootnoteRefType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClinkHtmlType
