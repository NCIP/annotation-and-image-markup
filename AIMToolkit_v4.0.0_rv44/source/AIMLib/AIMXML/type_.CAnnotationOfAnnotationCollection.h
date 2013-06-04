/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationCollection
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationCollection

#include "type_.CAnnotationCollection.h"


namespace AIMXML
{

class CAnnotationOfAnnotationCollection : public ::AIMXML::CAnnotationCollection
{
public:
	AIMXML_EXPORT CAnnotationOfAnnotationCollection(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationOfAnnotationCollection(CAnnotationOfAnnotationCollection const& init);
	void operator=(CAnnotationOfAnnotationCollection const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationOfAnnotationCollection); }
	MemberElement<CannotationOfAnnotationsType, _altova_mi_altova_CAnnotationOfAnnotationCollection_altova_annotationOfAnnotations> annotationOfAnnotations;
	struct annotationOfAnnotations { typedef Iterator<CannotationOfAnnotationsType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationCollection
