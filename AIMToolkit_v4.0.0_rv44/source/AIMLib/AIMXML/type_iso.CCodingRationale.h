/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCodingRationale
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCodingRationale



namespace AIMXML
{

namespace iso
{	

class CCodingRationale : public TypeBase
{
public:
	AIMXML_EXPORT CCodingRationale(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCodingRationale(CCodingRationale const& init);
	void operator=(CCodingRationale const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CCodingRationale); }

	enum EnumValues {
		Invalid = -1,
		k_O = 0, // O
		k_P = 1, // P
		k_R = 2, // R
		k_S = 3, // S
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCodingRationale
