/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CXReference
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CXReference



namespace AIMXML
{

namespace iso
{	

class CXReference : public TypeBase
{
public:
	AIMXML_EXPORT CXReference(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CXReference(CXReference const& init);
	void operator=(CXReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CXReference); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CXReference_altova_xref, 0, 0> xref;	// xref CIDREF
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CXReference
