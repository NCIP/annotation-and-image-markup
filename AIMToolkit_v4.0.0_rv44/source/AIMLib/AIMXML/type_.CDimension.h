/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDimension
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDimension



namespace AIMXML
{

class CDimension : public TypeBase
{
public:
	AIMXML_EXPORT CDimension(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDimension(CDimension const& init);
	void operator=(CDimension const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDimension); }
	MemberElement<iso::CINT, _altova_mi_altova_CDimension_altova_index> index;
	struct index { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CDimension_altova_size> size;
	struct size { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CDimension_altova_label> label;
	struct label { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDimension
