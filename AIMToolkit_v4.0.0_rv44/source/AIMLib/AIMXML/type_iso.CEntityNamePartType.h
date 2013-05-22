/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEntityNamePartType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEntityNamePartType



namespace AIMXML
{

namespace iso
{	

class CEntityNamePartType : public TypeBase
{
public:
	AIMXML_EXPORT CEntityNamePartType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEntityNamePartType(CEntityNamePartType const& init);
	void operator=(CEntityNamePartType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CEntityNamePartType); }

	enum EnumValues {
		Invalid = -1,
		k_FAM = 0, // FAM
		k_GIV = 1, // GIV
		k_PFX = 2, // PFX
		k_SFX = 3, // SFX
		k_DEL = 4, // DEL
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEntityNamePartType
