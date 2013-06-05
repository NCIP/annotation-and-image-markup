/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CanyType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CanyType



namespace AIMXML
{

namespace xs
{	

class CanyType : public TypeBase
{
public:
	AIMXML_EXPORT CanyType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CanyType(CanyType const& init);
	void operator=(CanyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CanyType); }
	AIMXML_EXPORT void operator=(const string_type& value);
	AIMXML_EXPORT operator string_type();
	AIMXML_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CanyType
