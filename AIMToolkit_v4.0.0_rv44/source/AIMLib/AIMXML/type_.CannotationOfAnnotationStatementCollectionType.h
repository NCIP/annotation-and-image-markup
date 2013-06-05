/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CannotationOfAnnotationStatementCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CannotationOfAnnotationStatementCollectionType



namespace AIMXML
{

class CannotationOfAnnotationStatementCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CannotationOfAnnotationStatementCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CannotationOfAnnotationStatementCollectionType(CannotationOfAnnotationStatementCollectionType const& init);
	void operator=(CannotationOfAnnotationStatementCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CannotationOfAnnotationStatementCollectionType); }
	MemberElement<CAnnotationStatement, _altova_mi_altova_CannotationOfAnnotationStatementCollectionType_altova_AnnotationOfAnnotationStatement> AnnotationOfAnnotationStatement;
	struct AnnotationOfAnnotationStatement { typedef Iterator<CAnnotationStatement> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CannotationOfAnnotationStatementCollectionType
