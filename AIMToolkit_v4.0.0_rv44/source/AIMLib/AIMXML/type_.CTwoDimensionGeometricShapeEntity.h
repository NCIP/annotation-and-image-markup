/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionGeometricShapeEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionGeometricShapeEntity

#include "type_.CGeometricShapeEntity.h"


namespace AIMXML
{

class CTwoDimensionGeometricShapeEntity : public ::AIMXML::CGeometricShapeEntity
{
public:
	AIMXML_EXPORT CTwoDimensionGeometricShapeEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTwoDimensionGeometricShapeEntity(CTwoDimensionGeometricShapeEntity const& init);
	void operator=(CTwoDimensionGeometricShapeEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTwoDimensionGeometricShapeEntity); }
	MemberElement<iso::CII, _altova_mi_altova_CTwoDimensionGeometricShapeEntity_altova_imageReferenceUid> imageReferenceUid;
	struct imageReferenceUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CTwoDimensionGeometricShapeEntity_altova_referencedFrameNumber> referencedFrameNumber;
	struct referencedFrameNumber { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTwoDimensionGeometricShapeEntity_altova_uri> uri;
	struct uri { typedef Iterator<iso::CST> iterator; };
	MemberElement<CtwoDimensionSpatialCoordinateCollectionType, _altova_mi_altova_CTwoDimensionGeometricShapeEntity_altova_twoDimensionSpatialCoordinateCollection> twoDimensionSpatialCoordinateCollection;
	struct twoDimensionSpatialCoordinateCollection { typedef Iterator<CtwoDimensionSpatialCoordinateCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionGeometricShapeEntity
