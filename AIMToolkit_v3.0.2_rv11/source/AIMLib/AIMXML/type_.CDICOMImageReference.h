/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDICOMImageReference
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDICOMImageReference

#include "type_.CImageReference.h"


namespace AIMXML
{

class CDICOMImageReference : public ::AIMXML::CImageReference
{
public:
	AIMXML_EXPORT CDICOMImageReference(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDICOMImageReference(CDICOMImageReference const& init);
	void operator=(CDICOMImageReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDICOMImageReference); }
	MemberElement<CimageStudyType, _altova_mi_altova_CDICOMImageReference_altova_imageStudy> imageStudy;
	struct imageStudy { typedef Iterator<CimageStudyType> iterator; };
	MemberElement<CpresentationStateCollectionType, _altova_mi_altova_CDICOMImageReference_altova_presentationStateCollection> presentationStateCollection;
	struct presentationStateCollection { typedef Iterator<CpresentationStateCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDICOMImageReference
