/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedAnatomicEntityXMLType
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedAnatomicEntityXMLType



namespace AIMOntology
{

namespace aim
{	

class CrelatedAnatomicEntityXMLType : public TypeBase
{
public:
	AIMOntology_EXPORT CrelatedAnatomicEntityXMLType(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CrelatedAnatomicEntityXMLType(CrelatedAnatomicEntityXMLType const& init);
	void operator=(CrelatedAnatomicEntityXMLType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CrelatedAnatomicEntityXMLType); }
	MemberElement<aim::CAnatomicEntityXML, _altova_mi_aim_altova_CrelatedAnatomicEntityXMLType_altova_AnatomicEntityXML> AnatomicEntityXML;
	struct AnatomicEntityXML { typedef Iterator<aim::CAnatomicEntityXML> iterator; };
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedAnatomicEntityXMLType
