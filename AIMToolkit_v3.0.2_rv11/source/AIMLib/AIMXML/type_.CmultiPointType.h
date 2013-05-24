/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CmultiPointType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CmultiPointType



namespace AIMXML
{

class CmultiPointType : public TypeBase
{
public:
	AIMXML_EXPORT CmultiPointType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CmultiPointType(CmultiPointType const& init);
	void operator=(CmultiPointType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CmultiPointType); }
	MemberElement<CMultiPoint, _altova_mi_altova_CmultiPointType_altova_MultiPoint> MultiPoint;
	struct MultiPoint { typedef Iterator<CMultiPoint> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CmultiPointType
