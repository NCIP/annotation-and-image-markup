/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationIsComparedWithImageAnnotationStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationIsComparedWithImageAnnotationStatement

#include "type_.CAnnotationOfAnnotationStatement.h"


namespace AIMXML
{

class CImageAnnotationIsComparedWithImageAnnotationStatement : public ::AIMXML::CAnnotationOfAnnotationStatement
{
public:
	AIMXML_EXPORT CImageAnnotationIsComparedWithImageAnnotationStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageAnnotationIsComparedWithImageAnnotationStatement(CImageAnnotationIsComparedWithImageAnnotationStatement const& init);
	void operator=(CImageAnnotationIsComparedWithImageAnnotationStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageAnnotationIsComparedWithImageAnnotationStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationIsComparedWithImageAnnotationStatement
