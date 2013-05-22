/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CanatomicEntityCollectionXMLType
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CanatomicEntityCollectionXMLType



namespace AIMOntology
{

namespace aim
{	

class CanatomicEntityCollectionXMLType : public TypeBase
{
public:
	AIMOntology_EXPORT CanatomicEntityCollectionXMLType(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CanatomicEntityCollectionXMLType(CanatomicEntityCollectionXMLType const& init);
	void operator=(CanatomicEntityCollectionXMLType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CanatomicEntityCollectionXMLType); }
	MemberElement<aim::CAnatomicEntityXML, _altova_mi_aim_altova_CanatomicEntityCollectionXMLType_altova_AnatomicEntityXML> AnatomicEntityXML;
	struct AnatomicEntityXML { typedef Iterator<aim::CAnatomicEntityXML> iterator; };
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CanatomicEntityCollectionXMLType
