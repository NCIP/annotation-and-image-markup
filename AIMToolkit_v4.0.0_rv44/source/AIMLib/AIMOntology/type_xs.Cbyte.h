#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cbyte
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cbyte



namespace AIMOntology
{

namespace xs
{	

class Cbyte : public TypeBase
{
public:
	AIMOntology_EXPORT Cbyte(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT Cbyte(Cbyte const& init);
	void operator=(Cbyte const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cbyte); }
	void operator= (const int& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator int()
	{
		return CastAs<int >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cbyte
