/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralLesionObservationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralLesionObservationEntity

#include "type_.CLesionObservationEntity.h"


namespace AIMXML
{

class CGeneralLesionObservationEntity : public ::AIMXML::CLesionObservationEntity
{
public:
	AIMXML_EXPORT CGeneralLesionObservationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CGeneralLesionObservationEntity(CGeneralLesionObservationEntity const& init);
	void operator=(CGeneralLesionObservationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGeneralLesionObservationEntity); }
	MemberElement<iso::CST, _altova_mi_altova_CGeneralLesionObservationEntity_altova_trackingIdentifier> trackingIdentifier;
	struct trackingIdentifier { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CGeneralLesionObservationEntity_altova_lesionType> lesionType;
	struct lesionType { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CGeneralLesionObservationEntity_altova_reconstructionInterval> reconstructionInterval;
	struct reconstructionInterval { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CGeneralLesionObservationEntity_altova_laterality> laterality;
	struct laterality { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralLesionObservationEntity
