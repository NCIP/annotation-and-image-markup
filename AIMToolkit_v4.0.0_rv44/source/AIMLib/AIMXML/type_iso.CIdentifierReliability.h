/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIdentifierReliability
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIdentifierReliability



namespace AIMXML
{

namespace iso
{	

class CIdentifierReliability : public TypeBase
{
public:
	AIMXML_EXPORT CIdentifierReliability(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIdentifierReliability(CIdentifierReliability const& init);
	void operator=(CIdentifierReliability const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CIdentifierReliability); }

	enum EnumValues {
		Invalid = -1,
		k_ISS = 0, // ISS
		k_VRF = 1, // VRF
		k_USE = 2, // USE
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIdentifierReliability
