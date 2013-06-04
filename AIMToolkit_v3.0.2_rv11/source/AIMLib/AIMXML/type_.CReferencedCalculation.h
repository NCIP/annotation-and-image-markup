/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedCalculation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedCalculation



namespace AIMXML
{

class CReferencedCalculation : public TypeBase
{
public:
	AIMXML_EXPORT CReferencedCalculation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CReferencedCalculation(CReferencedCalculation const& init);
	void operator=(CReferencedCalculation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReferencedCalculation); }

	MemberAttribute<__int64,_altova_mi_altova_CReferencedCalculation_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CReferencedCalculation_altova_uniqueIdentifier, 0, 0> uniqueIdentifier;	// uniqueIdentifier Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedCalculation
