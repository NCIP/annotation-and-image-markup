/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CnonNegativeInteger
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CnonNegativeInteger



namespace AIMXML
{

namespace xs
{	

class CnonNegativeInteger : public TypeBase
{
public:
	AIMXML_EXPORT CnonNegativeInteger(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CnonNegativeInteger(CnonNegativeInteger const& init);
	void operator=(CnonNegativeInteger const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnonNegativeInteger); }
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_CnonNegativeInteger
