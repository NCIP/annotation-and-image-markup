/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUncertaintyType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUncertaintyType



namespace AIMXML
{

namespace iso
{	

class CUncertaintyType : public TypeBase
{
public:
	AIMXML_EXPORT CUncertaintyType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUncertaintyType(CUncertaintyType const& init);
	void operator=(CUncertaintyType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CUncertaintyType); }

	enum EnumValues {
		Invalid = -1,
		k_U = 0, // U
		k_N = 1, // N
		k_LN = 2, // LN
		k_G = 3, // G
		k_E = 4, // E
		k_X2 = 5, // X2
		k_T = 6, // T
		k_F = 7, // F
		k_B = 8, // B
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUncertaintyType
