/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CanatomicEntityCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CanatomicEntityCollectionType



namespace AIMXML
{

class CanatomicEntityCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CanatomicEntityCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CanatomicEntityCollectionType(CanatomicEntityCollectionType const& init);
	void operator=(CanatomicEntityCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CanatomicEntityCollectionType); }
	MemberElement<CAnatomicEntity, _altova_mi_altova_CanatomicEntityCollectionType_altova_AnatomicEntity> AnatomicEntity;
	struct AnatomicEntity { typedef Iterator<CAnatomicEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CanatomicEntityCollectionType
