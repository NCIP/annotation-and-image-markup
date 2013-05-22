/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CQName
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CQName



namespace AIMXML
{

namespace xs
{	

class CQName : public TypeBase
{
public:
	AIMXML_EXPORT CQName(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQName(CQName const& init);
	void operator=(CQName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CQName); }
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



} // namespace xs

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CQName
