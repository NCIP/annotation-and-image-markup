/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CsegmentationCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CsegmentationCollectionType



namespace AIMXML
{

class CsegmentationCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CsegmentationCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CsegmentationCollectionType(CsegmentationCollectionType const& init);
	void operator=(CsegmentationCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CsegmentationCollectionType); }
	MemberElement<CSegmentation, _altova_mi_altova_CsegmentationCollectionType_altova_Segmentation> Segmentation;
	struct Segmentation { typedef Iterator<CSegmentation> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CsegmentationCollectionType
