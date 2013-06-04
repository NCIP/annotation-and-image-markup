/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationHasImageAnnotationStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationHasImageAnnotationStatement

#include "type_.CAnnotationOfAnnotationStatement.h"


namespace AIMXML
{

class CAnnotationOfAnnotationHasImageAnnotationStatement : public ::AIMXML::CAnnotationOfAnnotationStatement
{
public:
	AIMXML_EXPORT CAnnotationOfAnnotationHasImageAnnotationStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationOfAnnotationHasImageAnnotationStatement(CAnnotationOfAnnotationHasImageAnnotationStatement const& init);
	void operator=(CAnnotationOfAnnotationHasImageAnnotationStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationOfAnnotationHasImageAnnotationStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationOfAnnotationHasImageAnnotationStatement
