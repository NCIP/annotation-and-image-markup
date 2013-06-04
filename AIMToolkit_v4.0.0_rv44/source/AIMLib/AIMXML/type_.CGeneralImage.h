/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralImage
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralImage



namespace AIMXML
{

class CGeneralImage : public TypeBase
{
public:
	AIMXML_EXPORT CGeneralImage(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CGeneralImage(CGeneralImage const& init);
	void operator=(CGeneralImage const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGeneralImage); }
	MemberElement<iso::CST, _altova_mi_altova_CGeneralImage_altova_patientOrientationColumn> patientOrientationColumn;
	struct patientOrientationColumn { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeneralImage_altova_patientOrientationRow> patientOrientationRow;
	struct patientOrientationRow { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralImage
