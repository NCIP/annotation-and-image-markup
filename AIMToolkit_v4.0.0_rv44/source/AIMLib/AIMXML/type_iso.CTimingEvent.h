/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CTimingEvent
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CTimingEvent



namespace AIMXML
{

namespace iso
{	

class CTimingEvent : public TypeBase
{
public:
	AIMXML_EXPORT CTimingEvent(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTimingEvent(CTimingEvent const& init);
	void operator=(CTimingEvent const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CTimingEvent); }

	enum EnumValues {
		Invalid = -1,
		k_C = 0, // C
		k_CD = 1, // CD
		k_CM = 2, // CM
		k_CV = 3, // CV
		k_HS = 4, // HS
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CTimingEvent
