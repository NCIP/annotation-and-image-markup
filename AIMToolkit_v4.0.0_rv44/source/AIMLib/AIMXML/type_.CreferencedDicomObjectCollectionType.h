/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedDicomObjectCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedDicomObjectCollectionType



namespace AIMXML
{

class CreferencedDicomObjectCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CreferencedDicomObjectCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CreferencedDicomObjectCollectionType(CreferencedDicomObjectCollectionType const& init);
	void operator=(CreferencedDicomObjectCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CreferencedDicomObjectCollectionType); }
	MemberElement<CReferencedDicomObject, _altova_mi_altova_CreferencedDicomObjectCollectionType_altova_ReferencedDicomObject> ReferencedDicomObject;
	struct ReferencedDicomObject { typedef Iterator<CReferencedDicomObject> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedDicomObjectCollectionType
