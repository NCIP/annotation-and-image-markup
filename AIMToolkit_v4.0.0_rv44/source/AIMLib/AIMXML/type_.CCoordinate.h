/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCoordinate
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCoordinate



namespace AIMXML
{

class CCoordinate : public TypeBase
{
public:
	AIMXML_EXPORT CCoordinate(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCoordinate(CCoordinate const& init);
	void operator=(CCoordinate const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCoordinate); }
	MemberElement<iso::CINT, _altova_mi_altova_CCoordinate_altova_dimensionIndex> dimensionIndex;
	struct dimensionIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CCoordinate_altova_position> position;
	struct position { typedef Iterator<iso::CINT> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCoordinate
