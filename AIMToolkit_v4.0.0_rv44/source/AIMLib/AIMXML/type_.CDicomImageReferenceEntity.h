/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDicomImageReferenceEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDicomImageReferenceEntity

#include "type_.CImageReferenceEntity.h"


namespace AIMXML
{

class CDicomImageReferenceEntity : public ::AIMXML::CImageReferenceEntity
{
public:
	AIMXML_EXPORT CDicomImageReferenceEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDicomImageReferenceEntity(CDicomImageReferenceEntity const& init);
	void operator=(CDicomImageReferenceEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDicomImageReferenceEntity); }
	MemberElement<CImageStudy, _altova_mi_altova_CDicomImageReferenceEntity_altova_imageStudy> imageStudy;
	struct imageStudy { typedef Iterator<CImageStudy> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDicomImageReferenceEntity
