/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedAnnotationCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedAnnotationCollectionType



namespace AIMXML
{

class CreferencedAnnotationCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CreferencedAnnotationCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CreferencedAnnotationCollectionType(CreferencedAnnotationCollectionType const& init);
	void operator=(CreferencedAnnotationCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CreferencedAnnotationCollectionType); }
	MemberElement<CReferencedAnnotation, _altova_mi_altova_CreferencedAnnotationCollectionType_altova_ReferencedAnnotation> ReferencedAnnotation;
	struct ReferencedAnnotation { typedef Iterator<CReferencedAnnotation> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedAnnotationCollectionType
