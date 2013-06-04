/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtextAnnotationCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtextAnnotationCollectionType



namespace AIMXML
{

class CtextAnnotationCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CtextAnnotationCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtextAnnotationCollectionType(CtextAnnotationCollectionType const& init);
	void operator=(CtextAnnotationCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtextAnnotationCollectionType); }
	MemberElement<CTextAnnotation, _altova_mi_altova_CtextAnnotationCollectionType_altova_TextAnnotation> TextAnnotation;
	struct TextAnnotation { typedef Iterator<CTextAnnotation> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtextAnnotationCollectionType
