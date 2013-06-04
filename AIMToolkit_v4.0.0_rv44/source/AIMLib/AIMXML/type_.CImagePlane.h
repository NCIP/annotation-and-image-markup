/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagePlane
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagePlane



namespace AIMXML
{

class CImagePlane : public TypeBase
{
public:
	AIMXML_EXPORT CImagePlane(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImagePlane(CImagePlane const& init);
	void operator=(CImagePlane const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImagePlane); }
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_rowImageOrientationX> rowImageOrientationX;
	struct rowImageOrientationX { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_rowImageOrientationY> rowImageOrientationY;
	struct rowImageOrientationY { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_rowImageOrientationZ> rowImageOrientationZ;
	struct rowImageOrientationZ { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_columnImageOrientationX> columnImageOrientationX;
	struct columnImageOrientationX { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_columnImageOrientationY> columnImageOrientationY;
	struct columnImageOrientationY { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_columnImageOrientationZ> columnImageOrientationZ;
	struct columnImageOrientationZ { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_verticalPixelSpacing> verticalPixelSpacing;
	struct verticalPixelSpacing { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_horizontalPixelSpacing> horizontalPixelSpacing;
	struct horizontalPixelSpacing { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_sliceThickness> sliceThickness;
	struct sliceThickness { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_imagePositionX> imagePositionX;
	struct imagePositionX { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_imagePositionY> imagePositionY;
	struct imagePositionY { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagePlane_altova_imagePositionZ> imagePositionZ;
	struct imagePositionZ { typedef Iterator<iso::CREAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagePlane
