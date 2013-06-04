/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtaskContextEntityCollectionType2
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtaskContextEntityCollectionType2



namespace AIMXML
{

class CtaskContextEntityCollectionType2 : public TypeBase
{
public:
	AIMXML_EXPORT CtaskContextEntityCollectionType2(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtaskContextEntityCollectionType2(CtaskContextEntityCollectionType2 const& init);
	void operator=(CtaskContextEntityCollectionType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtaskContextEntityCollectionType2); }
	MemberElement<CTaskContextEntity, _altova_mi_altova_CtaskContextEntityCollectionType2_altova_TaskContextEntity> TaskContextEntity;
	struct TaskContextEntity { typedef Iterator<CTaskContextEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtaskContextEntityCollectionType2
