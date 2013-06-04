/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageAnnotationStatementCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageAnnotationStatementCollectionType



namespace AIMXML
{

class CimageAnnotationStatementCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CimageAnnotationStatementCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimageAnnotationStatementCollectionType(CimageAnnotationStatementCollectionType const& init);
	void operator=(CimageAnnotationStatementCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimageAnnotationStatementCollectionType); }
	MemberElement<CAnnotationStatement, _altova_mi_altova_CimageAnnotationStatementCollectionType_altova_ImageAnnotationStatement> ImageAnnotationStatement;
	struct ImageAnnotationStatement { typedef Iterator<CAnnotationStatement> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageAnnotationStatementCollectionType
