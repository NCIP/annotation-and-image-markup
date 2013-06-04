/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcalculationCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcalculationCollectionType



namespace AIMXML
{

class CcalculationCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CcalculationCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CcalculationCollectionType(CcalculationCollectionType const& init);
	void operator=(CcalculationCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CcalculationCollectionType); }
	MemberElement<CCalculation, _altova_mi_altova_CcalculationCollectionType_altova_Calculation> Calculation;
	struct Calculation { typedef Iterator<CCalculation> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcalculationCollectionType
