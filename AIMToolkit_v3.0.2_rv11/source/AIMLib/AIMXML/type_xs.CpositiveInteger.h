/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CpositiveInteger
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CpositiveInteger



namespace AIMXML
{

namespace xs
{	

class CpositiveInteger : public TypeBase
{
public:
	AIMXML_EXPORT CpositiveInteger(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CpositiveInteger(CpositiveInteger const& init);
	void operator=(CpositiveInteger const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CpositiveInteger); }
	void operator= (const unsigned __int64& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator unsigned __int64()
	{
		return CastAs<unsigned __int64 >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CpositiveInteger
