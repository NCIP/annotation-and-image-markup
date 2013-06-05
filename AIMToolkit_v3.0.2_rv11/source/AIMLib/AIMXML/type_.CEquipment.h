/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CEquipment
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CEquipment



namespace AIMXML
{

class CEquipment : public TypeBase
{
public:
	AIMXML_EXPORT CEquipment(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEquipment(CEquipment const& init);
	void operator=(CEquipment const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEquipment); }

	MemberAttribute<__int64,_altova_mi_altova_CEquipment_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CEquipment_altova_manufacturerName, 0, 0> manufacturerName;	// manufacturerName Cstring

	MemberAttribute<string_type,_altova_mi_altova_CEquipment_altova_manufacturerModelName, 0, 0> manufacturerModelName;	// manufacturerModelName Cstring

	MemberAttribute<string_type,_altova_mi_altova_CEquipment_altova_softwareVersion, 0, 0> softwareVersion;	// softwareVersion Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CEquipment
