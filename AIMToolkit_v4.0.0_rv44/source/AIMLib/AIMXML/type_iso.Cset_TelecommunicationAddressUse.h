/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_TelecommunicationAddressUse
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_TelecommunicationAddressUse



namespace AIMXML
{

namespace iso
{	

class Cset_TelecommunicationAddressUse : public TypeBase
{
public:
	AIMXML_EXPORT Cset_TelecommunicationAddressUse(xercesc::DOMNode* const& init);
	AIMXML_EXPORT Cset_TelecommunicationAddressUse(Cset_TelecommunicationAddressUse const& init);
	void operator=(Cset_TelecommunicationAddressUse const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_Cset_TelecommunicationAddressUse); }

	enum EnumValues {
		Invalid = -1,
		k_H = 0, // H
		k_HP = 1, // HP
		k_HV = 2, // HV
		k_WP = 3, // WP
		k_DIR = 4, // DIR
		k_PUB = 5, // PUB
		k_BAD = 6, // BAD
		k_TMP = 7, // TMP
		k_AS = 8, // AS
		k_EC = 9, // EC
		k_MC = 10, // MC
		k_PG = 11, // PG
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_TelecommunicationAddressUse
