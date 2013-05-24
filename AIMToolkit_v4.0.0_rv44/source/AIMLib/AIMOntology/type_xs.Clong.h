#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Clong
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Clong



namespace AIMOntology
{

namespace xs
{	

class Clong : public TypeBase
{
public:
	AIMOntology_EXPORT Clong(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT Clong(Clong const& init);
	void operator=(Clong const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Clong); }
	void operator= (const __int64& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator __int64()
	{
		return CastAs<__int64 >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Clong
