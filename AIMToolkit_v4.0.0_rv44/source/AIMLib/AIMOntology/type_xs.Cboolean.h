#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cboolean
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cboolean



namespace AIMOntology
{

namespace xs
{	

class Cboolean : public TypeBase
{
public:
	AIMOntology_EXPORT Cboolean(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT Cboolean(Cboolean const& init);
	void operator=(Cboolean const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cboolean); }
	void operator= (const bool& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator bool()
	{
		return CastAs<bool >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_Cboolean
