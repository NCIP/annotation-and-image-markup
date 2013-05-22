/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CrulesType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CrulesType



namespace AIMXML
{

class CrulesType : public TypeBase
{
public:
	AIMXML_EXPORT CrulesType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CrulesType(CrulesType const& init);
	void operator=(CrulesType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CrulesType); }

	enum EnumValues {
		Invalid = -1,
		k_none = 0, // none
		k_groups = 1, // groups
		k_rows = 2, // rows
		k_cols = 3, // cols
		k_all = 4, // all
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CrulesType
