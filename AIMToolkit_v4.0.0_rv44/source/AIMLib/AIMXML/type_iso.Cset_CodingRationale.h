/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_CodingRationale
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_CodingRationale



namespace AIMXML
{

namespace iso
{	

class Cset_CodingRationale : public TypeBase
{
public:
	AIMXML_EXPORT Cset_CodingRationale(xercesc::DOMNode* const& init);
	AIMXML_EXPORT Cset_CodingRationale(Cset_CodingRationale const& init);
	void operator=(Cset_CodingRationale const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_Cset_CodingRationale); }

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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_CodingRationale
