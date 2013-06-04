/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN_TN
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN_TN

#include "type_iso.CEN.h"


namespace AIMXML
{

namespace iso
{	

class CEN_TN : public ::AIMXML::iso::CEN
{
public:
	AIMXML_EXPORT CEN_TN(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEN_TN(CEN_TN const& init);
	void operator=(CEN_TN const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CEN_TN); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN_TN
