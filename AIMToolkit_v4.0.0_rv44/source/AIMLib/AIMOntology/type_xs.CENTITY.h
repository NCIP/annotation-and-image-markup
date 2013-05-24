#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CENTITY
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CENTITY



namespace AIMOntology
{

namespace xs
{	

class CENTITY : public TypeBase
{
public:
	AIMOntology_EXPORT CENTITY(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CENTITY(CENTITY const& init);
	void operator=(CENTITY const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CENTITY); }
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

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CENTITY
