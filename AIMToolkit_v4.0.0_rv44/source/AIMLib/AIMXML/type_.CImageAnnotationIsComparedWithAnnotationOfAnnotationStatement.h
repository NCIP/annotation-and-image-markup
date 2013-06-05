/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement

#include "type_.CAnnotationStatement.h"


namespace AIMXML
{

class CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement : public ::AIMXML::CAnnotationStatement
{
public:
	AIMXML_EXPORT CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement(CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement const& init);
	void operator=(CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationIsComparedWithAnnotationOfAnnotationStatement
