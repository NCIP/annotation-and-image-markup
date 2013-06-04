/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement

#include "type_.CAnnotationOfAnnotationStatement.h"


namespace AIMXML
{

class CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement : public ::AIMXML::CAnnotationOfAnnotationStatement
{
public:
	AIMXML_EXPORT CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement(CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement const& init);
	void operator=(CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationIsComparedWithImageAnnotationStatement
