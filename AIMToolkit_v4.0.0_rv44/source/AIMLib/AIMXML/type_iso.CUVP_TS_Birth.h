/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_TS_Birth
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_TS_Birth

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CUVP_TS_Birth : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CUVP_TS_Birth(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUVP_TS_Birth(CUVP_TS_Birth const& init);
	void operator=(CUVP_TS_Birth const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CUVP_TS_Birth); }

	MemberAttribute<double,_altova_mi_iso_altova_CUVP_TS_Birth_altova_probability, 0, 0> probability;	// probability Cdouble
	MemberElement<iso::CTS_Birth, _altova_mi_iso_altova_CUVP_TS_Birth_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CTS_Birth> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_TS_Birth
