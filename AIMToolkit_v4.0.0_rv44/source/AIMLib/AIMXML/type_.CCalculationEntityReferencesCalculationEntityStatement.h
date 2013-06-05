/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntityReferencesCalculationEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntityReferencesCalculationEntityStatement

#include "type_.CAnnotationStatement.h"


namespace AIMXML
{

class CCalculationEntityReferencesCalculationEntityStatement : public ::AIMXML::CAnnotationStatement
{
public:
	AIMXML_EXPORT CCalculationEntityReferencesCalculationEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalculationEntityReferencesCalculationEntityStatement(CCalculationEntityReferencesCalculationEntityStatement const& init);
	void operator=(CCalculationEntityReferencesCalculationEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalculationEntityReferencesCalculationEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationEntityReferencesCalculationEntityStatement
