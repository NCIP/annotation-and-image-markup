/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_TS_DateTime
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_TS_DateTime

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CUVP_TS_DateTime : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CUVP_TS_DateTime(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUVP_TS_DateTime(CUVP_TS_DateTime const& init);
	void operator=(CUVP_TS_DateTime const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CUVP_TS_DateTime); }

	MemberAttribute<double,_altova_mi_iso_altova_CUVP_TS_DateTime_altova_probability, 0, 0> probability;	// probability Cdouble
	MemberElement<iso::CTS_DateTime, _altova_mi_iso_altova_CUVP_TS_DateTime_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CTS_DateTime> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_TS_DateTime
