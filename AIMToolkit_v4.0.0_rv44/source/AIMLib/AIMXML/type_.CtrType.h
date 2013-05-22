/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtrType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtrType



namespace AIMXML
{

class CtrType : public TypeBase
{
public:
	AIMXML_EXPORT CtrType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtrType(CtrType const& init);
	void operator=(CtrType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtrType); }

	MemberAttribute<string_type,_altova_mi_altova_CtrType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CtrType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CtrType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS
	MemberAttribute<string_type,_altova_mi_altova_CtrType_altova_align, 0, 5> align;	// align CalignType8

	MemberAttribute<string_type,_altova_mi_altova_CtrType_altova_char2, 0, 0> char2;	// char Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtrType_altova_charoff, 0, 0> charoff;	// charoff Cstring
	MemberAttribute<string_type,_altova_mi_altova_CtrType_altova_valign, 0, 4> valign;	// valign CvalignType8
	MemberElement<CthType, _altova_mi_altova_CtrType_altova_th> th;
	struct th { typedef Iterator<CthType> iterator; };
	MemberElement<CtdType, _altova_mi_altova_CtrType_altova_td> td;
	struct td { typedef Iterator<CtdType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtrType
