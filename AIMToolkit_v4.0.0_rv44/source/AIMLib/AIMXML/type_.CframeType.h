/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CframeType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CframeType



namespace AIMXML
{

class CframeType : public TypeBase
{
public:
	AIMXML_EXPORT CframeType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CframeType(CframeType const& init);
	void operator=(CframeType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CframeType); }

	enum EnumValues {
		Invalid = -1,
		k_void = 0, // void
		k_above = 1, // above
		k_below = 2, // below
		k_hsides = 3, // hsides
		k_lhs = 4, // lhs
		k_rhs = 5, // rhs
		k_vsides = 6, // vsides
		k_box = 7, // box
		k_border = 8, // border
		EnumValueCount
	};
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CframeType
