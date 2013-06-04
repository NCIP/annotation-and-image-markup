/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAIMXML
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAIMXML



namespace AIMXML
{

class CAIMXML : public TypeBase
{
public:
	AIMXML_EXPORT CAIMXML(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAIMXML(CAIMXML const& init);
	void operator=(CAIMXML const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAIMXML); }
	MemberElement<CAnnotationOfAnnotation, _altova_mi_altova_CAIMXML_altova_AnnotationOfAnnotation> AnnotationOfAnnotation;
	struct AnnotationOfAnnotation { typedef Iterator<CAnnotationOfAnnotation> iterator; };
	MemberElement<CImageAnnotation, _altova_mi_altova_CAIMXML_altova_ImageAnnotation> ImageAnnotation;
	struct ImageAnnotation { typedef Iterator<CImageAnnotation> iterator; };
	AIMXML_EXPORT void SetXsiType();

	// document functions
	AIMXML_EXPORT static CAIMXML LoadFromFile(const string_type& fileName);
	AIMXML_EXPORT static CAIMXML LoadFromString(const string_type& xml);
	AIMXML_EXPORT static CAIMXML LoadFromBinary(const std::vector<unsigned char>& data);
	AIMXML_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint );
	AIMXML_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding );
	AIMXML_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM );
	AIMXML_EXPORT string_type SaveToString(bool prettyPrint);
	AIMXML_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint);
	AIMXML_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding);
	AIMXML_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM);
 	AIMXML_EXPORT static CAIMXML CreateDocument();
	AIMXML_EXPORT void DestroyDocument();
	AIMXML_EXPORT void SetDTDLocation(const string_type& dtdLocation);
	AIMXML_EXPORT void SetSchemaLocation(const string_type& schemaLocation);
protected:
	XercesTreeOperations::DocumentType GetDocumentNode() { return (XercesTreeOperations::DocumentType)m_node; }
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAIMXML
