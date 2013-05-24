/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSpatialCoordinate
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSpatialCoordinate



namespace AIMXML
{

class CSpatialCoordinate : public TypeBase
{
public:
	AIMXML_EXPORT CSpatialCoordinate(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CSpatialCoordinate(CSpatialCoordinate const& init);
	void operator=(CSpatialCoordinate const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSpatialCoordinate); }

	MemberAttribute<__int64,_altova_mi_altova_CSpatialCoordinate_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<__int64,_altova_mi_altova_CSpatialCoordinate_altova_coordinateIndex, 0, 0> coordinateIndex;	// coordinateIndex Cinteger
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSpatialCoordinate
