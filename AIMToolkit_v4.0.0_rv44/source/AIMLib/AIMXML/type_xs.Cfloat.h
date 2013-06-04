/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_Cfloat
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_Cfloat



namespace AIMXML
{

namespace xs
{	

class Cfloat : public TypeBase
{
public:
	AIMXML_EXPORT Cfloat(xercesc::DOMNode* const& init);
	AIMXML_EXPORT Cfloat(Cfloat const& init);
	void operator=(Cfloat const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cfloat); }
	void operator= (const double& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DoubleFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator double()
	{
		return CastAs<double >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_Cfloat
