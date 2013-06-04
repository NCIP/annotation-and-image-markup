/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_PQ_Time
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_PQ_Time

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CUVP_PQ_Time : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CUVP_PQ_Time(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUVP_PQ_Time(CUVP_PQ_Time const& init);
	void operator=(CUVP_PQ_Time const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CUVP_PQ_Time); }

	MemberAttribute<double,_altova_mi_iso_altova_CUVP_PQ_Time_altova_probability, 0, 0> probability;	// probability Cdouble
	MemberElement<iso::CPQ_Time, _altova_mi_iso_altova_CUVP_PQ_Time_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CPQ_Time> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_PQ_Time
