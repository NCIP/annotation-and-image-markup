/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageStudyType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageStudyType



namespace AIMXML
{

class CimageStudyType : public TypeBase
{
public:
	AIMXML_EXPORT CimageStudyType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimageStudyType(CimageStudyType const& init);
	void operator=(CimageStudyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimageStudyType); }
	MemberElement<CImageStudy, _altova_mi_altova_CimageStudyType_altova_ImageStudy> ImageStudy;
	struct ImageStudy { typedef Iterator<CImageStudy> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageStudyType
