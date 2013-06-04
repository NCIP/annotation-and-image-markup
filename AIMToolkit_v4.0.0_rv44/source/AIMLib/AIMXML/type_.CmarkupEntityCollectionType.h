/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CmarkupEntityCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CmarkupEntityCollectionType



namespace AIMXML
{

class CmarkupEntityCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CmarkupEntityCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CmarkupEntityCollectionType(CmarkupEntityCollectionType const& init);
	void operator=(CmarkupEntityCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CmarkupEntityCollectionType); }
	MemberElement<CMarkupEntity, _altova_mi_altova_CmarkupEntityCollectionType_altova_MarkupEntity> MarkupEntity;
	struct MarkupEntity { typedef Iterator<CMarkupEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CmarkupEntityCollectionType
