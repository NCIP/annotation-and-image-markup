/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CannotationRoleEntityCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CannotationRoleEntityCollectionType



namespace AIMXML
{

class CannotationRoleEntityCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CannotationRoleEntityCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CannotationRoleEntityCollectionType(CannotationRoleEntityCollectionType const& init);
	void operator=(CannotationRoleEntityCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CannotationRoleEntityCollectionType); }
	MemberElement<CAnnotationRoleEntity, _altova_mi_altova_CannotationRoleEntityCollectionType_altova_AnnotationRoleEntity> AnnotationRoleEntity;
	struct AnnotationRoleEntity { typedef Iterator<CAnnotationRoleEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CannotationRoleEntityCollectionType
