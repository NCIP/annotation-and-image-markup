/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCharacteristicCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCharacteristicCollectionType



namespace AIMXML
{

class CimagingObservationCharacteristicCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CimagingObservationCharacteristicCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimagingObservationCharacteristicCollectionType(CimagingObservationCharacteristicCollectionType const& init);
	void operator=(CimagingObservationCharacteristicCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimagingObservationCharacteristicCollectionType); }
	MemberElement<CImagingObservationCharacteristic, _altova_mi_altova_CimagingObservationCharacteristicCollectionType_altova_ImagingObservationCharacteristic> ImagingObservationCharacteristic;
	struct ImagingObservationCharacteristic { typedef Iterator<CImagingObservationCharacteristic> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCharacteristicCollectionType
