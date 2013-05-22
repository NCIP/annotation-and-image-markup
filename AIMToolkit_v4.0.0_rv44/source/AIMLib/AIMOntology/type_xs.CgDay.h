/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CgDay
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CgDay



namespace AIMOntology
{

namespace xs
{	

class CgDay : public TypeBase
{
public:
	AIMOntology_EXPORT CgDay(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CgDay(CgDay const& init);
	void operator=(CgDay const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgDay); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GDayFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CgDay
