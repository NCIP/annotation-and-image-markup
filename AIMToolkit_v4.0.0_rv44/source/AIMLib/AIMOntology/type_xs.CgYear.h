#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CgYear
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CgYear



namespace AIMOntology
{

namespace xs
{	

class CgYear : public TypeBase
{
public:
	AIMOntology_EXPORT CgYear(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CgYear(CgYear const& init);
	void operator=(CgYear const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgYear); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GYearFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CgYear
