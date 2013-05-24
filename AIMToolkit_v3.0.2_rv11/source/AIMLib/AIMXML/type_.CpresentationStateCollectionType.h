/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CpresentationStateCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CpresentationStateCollectionType



namespace AIMXML
{

class CpresentationStateCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CpresentationStateCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CpresentationStateCollectionType(CpresentationStateCollectionType const& init);
	void operator=(CpresentationStateCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CpresentationStateCollectionType); }
	MemberElement<CPresentationState, _altova_mi_altova_CpresentationStateCollectionType_altova_PresentationState> PresentationState;
	struct PresentationState { typedef Iterator<CPresentationState> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CpresentationStateCollectionType
