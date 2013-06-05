/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationCollection
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationCollection

#include "type_.CAnnotationCollection.h"


namespace AIMXML
{

class CImageAnnotationCollection : public ::AIMXML::CAnnotationCollection
{
public:
	AIMXML_EXPORT CImageAnnotationCollection(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageAnnotationCollection(CImageAnnotationCollection const& init);
	void operator=(CImageAnnotationCollection const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageAnnotationCollection); }
	MemberElement<CPerson, _altova_mi_altova_CImageAnnotationCollection_altova_person> person;
	struct person { typedef Iterator<CPerson> iterator; };
	MemberElement<CimageAnnotationsType, _altova_mi_altova_CImageAnnotationCollection_altova_imageAnnotations> imageAnnotations;
	struct imageAnnotations { typedef Iterator<CimageAnnotationsType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationCollection
