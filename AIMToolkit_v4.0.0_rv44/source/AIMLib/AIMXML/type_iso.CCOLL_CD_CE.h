/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_CD_CE
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_CD_CE

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CCOLL_CD_CE : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CCOLL_CD_CE(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCOLL_CD_CE(CCOLL_CD_CE const& init);
	void operator=(CCOLL_CD_CE const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCOLL_CD_CE); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_CD_CE
