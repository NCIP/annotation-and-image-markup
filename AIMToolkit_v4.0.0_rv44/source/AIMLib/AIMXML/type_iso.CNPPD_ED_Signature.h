/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_ED_Signature
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_ED_Signature

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CNPPD_ED_Signature : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CNPPD_ED_Signature(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNPPD_ED_Signature(CNPPD_ED_Signature const& init);
	void operator=(CNPPD_ED_Signature const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CNPPD_ED_Signature); }
	MemberElement<iso::CUVP_ED_Signature, _altova_mi_iso_altova_CNPPD_ED_Signature_altova_item> item;
	struct item { typedef Iterator<iso::CUVP_ED_Signature> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_ED_Signature
