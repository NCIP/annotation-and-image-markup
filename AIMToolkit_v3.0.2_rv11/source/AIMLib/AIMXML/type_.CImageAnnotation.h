/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotation

#include "type_.CAnnotation.h"


namespace AIMXML
{

class CImageAnnotation : public ::AIMXML::CAnnotation
{
public:
	AIMXML_EXPORT CImageAnnotation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageAnnotation(CImageAnnotation const& init);
	void operator=(CImageAnnotation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageAnnotation); }
	MemberElement<CsegmentationCollectionType, _altova_mi_altova_CImageAnnotation_altova_segmentationCollection> segmentationCollection;
	struct segmentationCollection { typedef Iterator<CsegmentationCollectionType> iterator; };
	MemberElement<CimageReferenceCollectionType, _altova_mi_altova_CImageAnnotation_altova_imageReferenceCollection> imageReferenceCollection;
	struct imageReferenceCollection { typedef Iterator<CimageReferenceCollectionType> iterator; };
	MemberElement<CgeometricShapeCollectionType, _altova_mi_altova_CImageAnnotation_altova_geometricShapeCollection> geometricShapeCollection;
	struct geometricShapeCollection { typedef Iterator<CgeometricShapeCollectionType> iterator; };
	MemberElement<CpersonType, _altova_mi_altova_CImageAnnotation_altova_person> person;
	struct person { typedef Iterator<CpersonType> iterator; };
	MemberElement<CtextAnnotationCollectionType, _altova_mi_altova_CImageAnnotation_altova_textAnnotationCollection> textAnnotationCollection;
	struct textAnnotationCollection { typedef Iterator<CtextAnnotationCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotation
