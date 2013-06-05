/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CScaleType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CScaleType



namespace AIMXML
{

class CScaleType : public TypeBase
{
public:
	AIMXML_EXPORT CScaleType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CScaleType(CScaleType const& init);
	void operator=(CScaleType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CScaleType); }

	enum EnumValues {
		Invalid = -1,
		k_Nominal = 0, // Nominal
		k_Ordinal = 1, // Ordinal
		k_Ratio = 2, // Ratio
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CScaleType
