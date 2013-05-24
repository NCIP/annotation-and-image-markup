/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CscopeType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CscopeType



namespace AIMXML
{

class CscopeType : public TypeBase
{
public:
	AIMXML_EXPORT CscopeType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CscopeType(CscopeType const& init);
	void operator=(CscopeType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CscopeType); }

	enum EnumValues {
		Invalid = -1,
		k_row = 0, // row
		k_col = 1, // col
		k_rowgroup = 2, // rowgroup
		k_colgroup = 3, // colgroup
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CscopeType
