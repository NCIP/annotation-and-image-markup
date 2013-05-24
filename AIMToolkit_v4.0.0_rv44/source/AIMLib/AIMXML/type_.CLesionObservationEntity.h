/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CLesionObservationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CLesionObservationEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CLesionObservationEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CLesionObservationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CLesionObservationEntity(CLesionObservationEntity const& init);
	void operator=(CLesionObservationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLesionObservationEntity); }
	MemberElement<iso::CII, _altova_mi_altova_CLesionObservationEntity_altova_lesionUniqueIdentifier> lesionUniqueIdentifier;
	struct lesionUniqueIdentifier { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CLesionObservationEntity_altova_isAdditionalObservation> isAdditionalObservation;
	struct isAdditionalObservation { typedef Iterator<iso::CBL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CLesionObservationEntity
