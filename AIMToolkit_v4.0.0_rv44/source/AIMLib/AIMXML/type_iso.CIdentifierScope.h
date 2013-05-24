/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIdentifierScope
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIdentifierScope



namespace AIMXML
{

namespace iso
{	

class CIdentifierScope : public TypeBase
{
public:
	AIMXML_EXPORT CIdentifierScope(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIdentifierScope(CIdentifierScope const& init);
	void operator=(CIdentifierScope const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CIdentifierScope); }

	enum EnumValues {
		Invalid = -1,
		k_BUSN = 0, // BUSN
		k_OBJ = 1, // OBJ
		k_VER = 2, // VER
		k_VW = 3, // VW
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



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIdentifierScope
