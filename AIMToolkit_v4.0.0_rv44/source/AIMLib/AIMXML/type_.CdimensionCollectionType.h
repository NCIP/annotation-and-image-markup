/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CdimensionCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CdimensionCollectionType



namespace AIMXML
{

class CdimensionCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CdimensionCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CdimensionCollectionType(CdimensionCollectionType const& init);
	void operator=(CdimensionCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CdimensionCollectionType); }
	MemberElement<CDimension, _altova_mi_altova_CdimensionCollectionType_altova_Dimension> Dimension;
	struct Dimension { typedef Iterator<CDimension> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CdimensionCollectionType
