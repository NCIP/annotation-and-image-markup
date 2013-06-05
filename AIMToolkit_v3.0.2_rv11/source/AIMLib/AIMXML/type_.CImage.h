/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImage
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImage



namespace AIMXML
{

class CImage : public TypeBase
{
public:
	AIMXML_EXPORT CImage(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImage(CImage const& init);
	void operator=(CImage const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImage); }

	MemberAttribute<__int64,_altova_mi_altova_CImage_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CImage_altova_sopClassUID, 0, 0> sopClassUID;	// sopClassUID Cstring

	MemberAttribute<string_type,_altova_mi_altova_CImage_altova_sopInstanceUID, 0, 0> sopInstanceUID;	// sopInstanceUID Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImage
