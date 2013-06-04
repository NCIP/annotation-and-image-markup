/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntityUsesCalculationEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntityUsesCalculationEntityStatement

#include "type_.CAnnotationStatement.h"


namespace AIMXML
{

class CCalculationEntityUsesCalculationEntityStatement : public ::AIMXML::CAnnotationStatement
{
public:
	AIMXML_EXPORT CCalculationEntityUsesCalculationEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalculationEntityUsesCalculationEntityStatement(CCalculationEntityUsesCalculationEntityStatement const& init);
	void operator=(CCalculationEntityUsesCalculationEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalculationEntityUsesCalculationEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntityUsesCalculationEntityStatement
