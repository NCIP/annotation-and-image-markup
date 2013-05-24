/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CanatomicEntityCharacteristicCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CanatomicEntityCharacteristicCollectionType



namespace AIMXML
{

class CanatomicEntityCharacteristicCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CanatomicEntityCharacteristicCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CanatomicEntityCharacteristicCollectionType(CanatomicEntityCharacteristicCollectionType const& init);
	void operator=(CanatomicEntityCharacteristicCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CanatomicEntityCharacteristicCollectionType); }
	MemberElement<CAnatomicEntityCharacteristic, _altova_mi_altova_CanatomicEntityCharacteristicCollectionType_altova_AnatomicEntityCharacteristic> AnatomicEntityCharacteristic;
	struct AnatomicEntityCharacteristic { typedef Iterator<CAnatomicEntityCharacteristic> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CanatomicEntityCharacteristicCollectionType
