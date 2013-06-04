/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageReference
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageReference



namespace AIMXML
{

class CImageReference : public TypeBase
{
public:
	AIMXML_EXPORT CImageReference(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageReference(CImageReference const& init);
	void operator=(CImageReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageReference); }

	MemberAttribute<__int64,_altova_mi_altova_CImageReference_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageReference
