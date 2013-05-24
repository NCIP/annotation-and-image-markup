/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedAnnotation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedAnnotation



namespace AIMXML
{

class CReferencedAnnotation : public TypeBase
{
public:
	AIMXML_EXPORT CReferencedAnnotation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CReferencedAnnotation(CReferencedAnnotation const& init);
	void operator=(CReferencedAnnotation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReferencedAnnotation); }

	MemberAttribute<__int64,_altova_mi_altova_CReferencedAnnotation_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CReferencedAnnotation_altova_referencedAnnotationUID, 0, 0> referencedAnnotationUID;	// referencedAnnotationUID Cstring
	MemberElement<CannotationRoleType, _altova_mi_altova_CReferencedAnnotation_altova_annotationRole> annotationRole;
	struct annotationRole { typedef Iterator<CannotationRoleType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedAnnotation
