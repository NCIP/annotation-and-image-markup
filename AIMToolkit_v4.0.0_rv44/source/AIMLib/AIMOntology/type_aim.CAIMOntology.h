#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAIMOntology
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAIMOntology



namespace AIMOntology
{

namespace aim
{	

class CAIMOntology : public TypeBase
{
public:
	AIMOntology_EXPORT CAIMOntology(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CAIMOntology(CAIMOntology const& init);
	void operator=(CAIMOntology const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CAIMOntology); }
	MemberElement<aim::CAnnotationDescriptionXML, _altova_mi_aim_altova_CAIMOntology_altova_AnnotationDescriptionXML> AnnotationDescriptionXML;
	struct AnnotationDescriptionXML { typedef Iterator<aim::CAnnotationDescriptionXML> iterator; };
	AIMOntology_EXPORT void SetXsiType();

	// document functions
	AIMOntology_EXPORT static CAIMOntology LoadFromFile(const string_type& fileName);
	AIMOntology_EXPORT static CAIMOntology LoadFromString(const string_type& xml);
	AIMOntology_EXPORT static CAIMOntology LoadFromBinary(const std::vector<unsigned char>& data);
	AIMOntology_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint );
	AIMOntology_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding );
	AIMOntology_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM );
	AIMOntology_EXPORT string_type SaveToString(bool prettyPrint);
	AIMOntology_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint);
	AIMOntology_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding);
	AIMOntology_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM);
 	AIMOntology_EXPORT static CAIMOntology CreateDocument();
	AIMOntology_EXPORT void DestroyDocument();
	AIMOntology_EXPORT void SetDTDLocation(const string_type& dtdLocation);
	AIMOntology_EXPORT void SetSchemaLocation(const string_type& schemaLocation);
protected:
	XercesTreeOperations::DocumentType GetDocumentNode() { return (XercesTreeOperations::DocumentType)m_node; }
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAIMOntology
