/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUpdateMode
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUpdateMode



namespace AIMXML
{

namespace iso
{	

class CUpdateMode : public TypeBase
{
public:
	AIMXML_EXPORT CUpdateMode(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUpdateMode(CUpdateMode const& init);
	void operator=(CUpdateMode const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CUpdateMode); }

	enum EnumValues {
		Invalid = -1,
		k_A = 0, // A
		k_AU = 1, // AU
		k_U = 2, // U
		k_R = 3, // R
		k_I = 4, // I
		k_D = 5, // D
		k_REF = 6, // REF
		k_K = 7, // K
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUpdateMode
