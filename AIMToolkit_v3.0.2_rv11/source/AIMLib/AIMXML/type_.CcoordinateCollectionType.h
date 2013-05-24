/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcoordinateCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcoordinateCollectionType



namespace AIMXML
{

class CcoordinateCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CcoordinateCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CcoordinateCollectionType(CcoordinateCollectionType const& init);
	void operator=(CcoordinateCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CcoordinateCollectionType); }
	MemberElement<CCoordinate, _altova_mi_altova_CcoordinateCollectionType_altova_Coordinate> Coordinate;
	struct Coordinate { typedef Iterator<CCoordinate> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcoordinateCollectionType
