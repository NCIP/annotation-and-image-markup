/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_CO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_CO

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CUVP_CO : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CUVP_CO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUVP_CO(CUVP_CO const& init);
	void operator=(CUVP_CO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CUVP_CO); }

	MemberAttribute<double,_altova_mi_iso_altova_CUVP_CO_altova_probability, 0, 0> probability;	// probability Cdouble
	MemberElement<iso::CCO, _altova_mi_iso_altova_CUVP_CO_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CCO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CUVP_CO
