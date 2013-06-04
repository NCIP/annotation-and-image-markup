/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotation

#include "type_.CAnnotationEntity.h"


namespace AIMXML
{

class CImageAnnotation : public ::AIMXML::CAnnotationEntity
{
public:
	AIMXML_EXPORT CImageAnnotation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageAnnotation(CImageAnnotation const& init);
	void operator=(CImageAnnotation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageAnnotation); }
	MemberElement<CsegmentationEntityCollectionType, _altova_mi_altova_CImageAnnotation_altova_segmentationEntityCollection> segmentationEntityCollection;
	struct segmentationEntityCollection { typedef Iterator<CsegmentationEntityCollectionType> iterator; };
	MemberElement<CmarkupEntityCollectionType, _altova_mi_altova_CImageAnnotation_altova_markupEntityCollection> markupEntityCollection;
	struct markupEntityCollection { typedef Iterator<CmarkupEntityCollectionType> iterator; };
	MemberElement<CimageAnnotationStatementCollectionType, _altova_mi_altova_CImageAnnotation_altova_imageAnnotationStatementCollection> imageAnnotationStatementCollection;
	struct imageAnnotationStatementCollection { typedef Iterator<CimageAnnotationStatementCollectionType> iterator; };
	MemberElement<CimageReferenceEntityCollectionType, _altova_mi_altova_CImageAnnotation_altova_imageReferenceEntityCollection> imageReferenceEntityCollection;
	struct imageReferenceEntityCollection { typedef Iterator<CimageReferenceEntityCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotation
