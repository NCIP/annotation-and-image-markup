/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageAnnotationsType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageAnnotationsType



namespace AIMXML
{

class CimageAnnotationsType : public TypeBase
{
public:
	AIMXML_EXPORT CimageAnnotationsType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimageAnnotationsType(CimageAnnotationsType const& init);
	void operator=(CimageAnnotationsType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimageAnnotationsType); }
	MemberElement<CImageAnnotation, _altova_mi_altova_CimageAnnotationsType_altova_ImageAnnotation> ImageAnnotation;
	struct ImageAnnotation { typedef Iterator<CImageAnnotation> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimageAnnotationsType
