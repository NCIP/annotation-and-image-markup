#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cinteger
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cinteger



namespace AIMOntology
{

namespace xs
{	

class Cinteger : public TypeBase
{
public:
	AIMOntology_EXPORT Cinteger(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT Cinteger(Cinteger const& init);
	void operator=(Cinteger const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cinteger); }
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

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cinteger
