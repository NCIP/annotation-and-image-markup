/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtheadType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtheadType



namespace AIMXML
{

class CtheadType : public TypeBase
{
public:
	AIMXML_EXPORT CtheadType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtheadType(CtheadType const& init);
	void operator=(CtheadType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtheadType); }

	MemberAttribute<string_type,_altova_mi_altova_CtheadType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CtheadType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CtheadType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS
	MemberAttribute<string_type,_altova_mi_altova_CtheadType_altova_align, 0, 5> align;	// align CalignType7

	MemberAttribute<string_type,_altova_mi_altova_CtheadType_altova_char2, 0, 0> char2;	// char Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtheadType_altova_charoff, 0, 0> charoff;	// charoff Cstring
	MemberAttribute<string_type,_altova_mi_altova_CtheadType_altova_valign, 0, 4> valign;	// valign CvalignType7
	MemberElement<CtrType, _altova_mi_altova_CtheadType_altova_tr> tr;
	struct tr { typedef Iterator<CtrType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtheadType
