/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageSeries
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageSeries



namespace AIMXML
{

class CImageSeries : public TypeBase
{
public:
	AIMXML_EXPORT CImageSeries(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageSeries(CImageSeries const& init);
	void operator=(CImageSeries const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageSeries); }
	MemberElement<iso::CII, _altova_mi_altova_CImageSeries_altova_instanceUid> instanceUid;
	struct instanceUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CImageSeries_altova_modality> modality;
	struct modality { typedef Iterator<iso::CCD> iterator; };
	MemberElement<CimageCollectionType, _altova_mi_altova_CImageSeries_altova_imageCollection> imageCollection;
	struct imageCollection { typedef Iterator<CimageCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageSeries
