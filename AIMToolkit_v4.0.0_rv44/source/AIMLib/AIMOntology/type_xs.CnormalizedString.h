/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CnormalizedString
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CnormalizedString



namespace AIMOntology
{

namespace xs
{	

class CnormalizedString : public TypeBase
{
public:
	AIMOntology_EXPORT CnormalizedString(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CnormalizedString(CnormalizedString const& init);
	void operator=(CnormalizedString const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnormalizedString); }
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

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CnormalizedString
