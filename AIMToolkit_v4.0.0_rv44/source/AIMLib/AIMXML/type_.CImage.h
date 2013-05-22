/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImage
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImage



namespace AIMXML
{

class CImage : public TypeBase
{
public:
	AIMXML_EXPORT CImage(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImage(CImage const& init);
	void operator=(CImage const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImage); }
	MemberElement<iso::CII, _altova_mi_altova_CImage_altova_sopClassUid> sopClassUid;
	struct sopClassUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CImage_altova_sopInstanceUid> sopInstanceUid;
	struct sopInstanceUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<CImagePlane, _altova_mi_altova_CImage_altova_imagePlane> imagePlane;
	struct imagePlane { typedef Iterator<CImagePlane> iterator; };
	MemberElement<CGeneralImage, _altova_mi_altova_CImage_altova_generalImage> generalImage;
	struct generalImage { typedef Iterator<CGeneralImage> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImage
