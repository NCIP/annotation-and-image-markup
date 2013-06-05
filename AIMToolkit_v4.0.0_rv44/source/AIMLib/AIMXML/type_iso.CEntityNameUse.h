/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEntityNameUse
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEntityNameUse



namespace AIMXML
{

namespace iso
{	

class CEntityNameUse : public TypeBase
{
public:
	AIMXML_EXPORT CEntityNameUse(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEntityNameUse(CEntityNameUse const& init);
	void operator=(CEntityNameUse const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CEntityNameUse); }

	enum EnumValues {
		Invalid = -1,
		k_C = 0, // C
		k_I = 1, // I
		k_L = 2, // L
		k_P = 3, // P
		k_A = 4, // A
		k_R = 5, // R
		k_PHON = 6, // PHON
		k_SNDX = 7, // SNDX
		k_ABC = 8, // ABC
		k_SYL = 9, // SYL
		k_IDE = 10, // IDE
		k_ASGN = 11, // ASGN
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEntityNameUse
