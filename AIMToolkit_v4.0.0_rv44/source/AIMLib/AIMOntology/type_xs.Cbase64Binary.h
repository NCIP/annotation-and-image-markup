#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cbase64Binary
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cbase64Binary



namespace AIMOntology
{

namespace xs
{	

class Cbase64Binary : public TypeBase
{
public:
	AIMOntology_EXPORT Cbase64Binary(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT Cbase64Binary(Cbase64Binary const& init);
	void operator=(Cbase64Binary const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cbase64Binary); }
	void operator= (const std::vector<unsigned char>& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator std::vector<unsigned char>()
	{
		return CastAs<std::vector<unsigned char> >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cbase64Binary
