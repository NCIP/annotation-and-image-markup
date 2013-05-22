/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCharacteristicCollectionType2
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCharacteristicCollectionType2



namespace AIMXML
{

class CimagingObservationCharacteristicCollectionType2 : public TypeBase
{
public:
	AIMXML_EXPORT CimagingObservationCharacteristicCollectionType2(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimagingObservationCharacteristicCollectionType2(CimagingObservationCharacteristicCollectionType2 const& init);
	void operator=(CimagingObservationCharacteristicCollectionType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimagingObservationCharacteristicCollectionType2); }
	MemberElement<CImagingObservationCharacteristic, _altova_mi_altova_CimagingObservationCharacteristicCollectionType2_altova_ImagingObservationCharacteristic> ImagingObservationCharacteristic;
	struct ImagingObservationCharacteristic { typedef Iterator<CImagingObservationCharacteristic> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCharacteristicCollectionType2
