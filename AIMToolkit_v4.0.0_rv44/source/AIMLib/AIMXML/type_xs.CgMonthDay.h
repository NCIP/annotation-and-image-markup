/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CgMonthDay
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CgMonthDay



namespace AIMXML
{

namespace xs
{	

class CgMonthDay : public TypeBase
{
public:
	AIMXML_EXPORT CgMonthDay(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CgMonthDay(CgMonthDay const& init);
	void operator=(CgMonthDay const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgMonthDay); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GMonthDayFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CgMonthDay
