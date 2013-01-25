#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAnatomicEntityXML
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAnatomicEntityXML



namespace AIMOntology
{

namespace aim
{	

class CAnatomicEntityXML : public TypeBase
{
public:
	AIMOntology_EXPORT CAnatomicEntityXML(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CAnatomicEntityXML(CAnatomicEntityXML const& init);
	void operator=(CAnatomicEntityXML const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CAnatomicEntityXML); }
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CAnatomicEntityXML_altova_codeMeaning> codeMeaning;
	struct codeMeaning { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CAnatomicEntityXML_altova_codingSchemeDesignator> codingSchemeDesignator;
	struct codingSchemeDesignator { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CAnatomicEntityXML_altova_codeValue> codeValue;
	struct codeValue { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CAnatomicEntityXML_altova_relationship> relationship;
	struct relationship { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<aim::CrelatedAnatomicEntityXMLType, _altova_mi_aim_altova_CAnatomicEntityXML_altova_relatedAnatomicEntityXML> relatedAnatomicEntityXML;
	struct relatedAnatomicEntityXML { typedef Iterator<aim::CrelatedAnatomicEntityXMLType> iterator; };
	AIMOntology_EXPORT void SetXsiType();
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAnatomicEntityXML
