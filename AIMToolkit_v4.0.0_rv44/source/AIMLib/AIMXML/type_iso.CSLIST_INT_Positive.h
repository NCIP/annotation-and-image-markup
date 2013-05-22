/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSLIST_INT_Positive
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSLIST_INT_Positive

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CSLIST_INT_Positive : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CSLIST_INT_Positive(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CSLIST_INT_Positive(CSLIST_INT_Positive const& init);
	void operator=(CSLIST_INT_Positive const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CSLIST_INT_Positive); }
	MemberElement<iso::CINT_Positive, _altova_mi_iso_altova_CSLIST_INT_Positive_altova_origin> origin;
	struct origin { typedef Iterator<iso::CINT_Positive> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CSLIST_INT_Positive_altova_scale> scale;
	struct scale { typedef Iterator<iso::CQTY> iterator; };
	MemberElement<iso::CINT, _altova_mi_iso_altova_CSLIST_INT_Positive_altova_digit> digit;
	struct digit { typedef Iterator<iso::CINT> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CSLIST_INT_Positive
