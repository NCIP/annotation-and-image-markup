/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
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

	MemberAttribute<__int64,_altova_mi_altova_CDimension_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<__int64,_altova_mi_altova_CDimension_altova_index, 0, 0> index;	// index Cinteger

	MemberAttribute<__int64,_altova_mi_altova_CDimension_altova_size, 0, 0> size;	// size Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CDimension_altova_label, 0, 0> label;	// label Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDimension
