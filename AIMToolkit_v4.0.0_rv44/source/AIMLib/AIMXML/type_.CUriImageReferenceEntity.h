/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CUriImageReferenceEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CUriImageReferenceEntity

#include "type_.CImageReferenceEntity.h"


namespace AIMXML
{

class CUriImageReferenceEntity : public ::AIMXML::CImageReferenceEntity
{
public:
	AIMXML_EXPORT CUriImageReferenceEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUriImageReferenceEntity(CUriImageReferenceEntity const& init);
	void operator=(CUriImageReferenceEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUriImageReferenceEntity); }
	MemberElement<iso::CST, _altova_mi_altova_CUriImageReferenceEntity_altova_uri> uri;
	struct uri { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CUriImageReferenceEntity_altova_mimeType> mimeType;
	struct mimeType { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CUriImageReferenceEntity
