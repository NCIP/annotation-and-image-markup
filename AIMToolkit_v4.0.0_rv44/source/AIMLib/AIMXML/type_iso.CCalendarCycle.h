/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCalendarCycle
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCalendarCycle



namespace AIMXML
{

namespace iso
{	

class CCalendarCycle : public TypeBase
{
public:
	AIMXML_EXPORT CCalendarCycle(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalendarCycle(CCalendarCycle const& init);
	void operator=(CCalendarCycle const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CCalendarCycle); }

	enum EnumValues {
		Invalid = -1,
		k_CY = 0, // CY
		k_MY = 1, // MY
		k_CM = 2, // CM
		k_CW = 3, // CW
		k_WY = 4, // WY
		k_DM = 5, // DM
		k_CD = 6, // CD
		k_DY = 7, // DY
		k_DW = 8, // DW
		k_HD = 9, // HD
		k_CH = 10, // CH
		k_NH = 11, // NH
		k_CN = 12, // CN
		k_SN = 13, // SN
		k_CS = 14, // CS
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCalendarCycle
