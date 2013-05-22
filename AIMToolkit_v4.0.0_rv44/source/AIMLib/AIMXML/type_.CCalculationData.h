/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationData
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationData



namespace AIMXML
{

class CCalculationData : public TypeBase
{
public:
	AIMXML_EXPORT CCalculationData(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalculationData(CCalculationData const& init);
	void operator=(CCalculationData const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalculationData); }
	MemberElement<iso::CST, _altova_mi_altova_CCalculationData_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CST> iterator; };
	MemberElement<CcoordinateCollectionType, _altova_mi_altova_CCalculationData_altova_coordinateCollection> coordinateCollection;
	struct coordinateCollection { typedef Iterator<CcoordinateCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationData
