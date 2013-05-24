/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageCollectionType



namespace AIMXML
{

class CimageCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CimageCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimageCollectionType(CimageCollectionType const& init);
	void operator=(CimageCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimageCollectionType); }
	MemberElement<CImage, _altova_mi_altova_CimageCollectionType_altova_Image> Image;
	struct Image { typedef Iterator<CImage> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageCollectionType
