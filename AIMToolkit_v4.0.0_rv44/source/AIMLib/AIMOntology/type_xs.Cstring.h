#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cstring
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cstring



namespace AIMOntology
{

namespace xs
{	

class Cstring : public TypeBase
{
public:
	AIMOntology_EXPORT Cstring(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT Cstring(Cstring const& init);
	void operator=(Cstring const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cstring); }
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

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cstring
