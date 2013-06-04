/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CComparisonOperators
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CComparisonOperators



namespace AIMXML
{

class CComparisonOperators : public TypeBase
{
public:
	AIMXML_EXPORT CComparisonOperators(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CComparisonOperators(CComparisonOperators const& init);
	void operator=(CComparisonOperators const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CComparisonOperators); }

	enum EnumValues {
		Invalid = -1,
		k_Equal = 0, // Equal
		k_NotEqual = 1, // NotEqual
		k_LessThan = 2, // LessThan
		k_LessThanEqual = 3, // LessThanEqual
		k_GreaterThan = 4, // GreaterThan
		k_GreaterThanEqual = 5, // GreaterThanEqual
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CComparisonOperators
