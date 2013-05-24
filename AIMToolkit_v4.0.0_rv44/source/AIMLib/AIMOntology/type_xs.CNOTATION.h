#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CNOTATION
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CNOTATION



namespace AIMOntology
{

namespace xs
{	

class CNOTATION : public TypeBase
{
public:
	AIMOntology_EXPORT CNOTATION(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CNOTATION(CNOTATION const& init);
	void operator=(CNOTATION const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CNOTATION); }
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

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CNOTATION
