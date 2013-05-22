/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CstringType
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CstringType



namespace AIMOntology
{

namespace xs
{	

class CstringType : public TypeBase
{
public:
	AIMOntology_EXPORT CstringType(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CstringType(CstringType const& init);
	void operator=(CstringType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CstringType); }
	AIMOntology_EXPORT void operator=(const string_type& value);
	AIMOntology_EXPORT operator string_type();
	AIMOntology_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_xs_ALTOVA_CstringType
