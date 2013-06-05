/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CII
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CII

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CII : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CII(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CII(CII const& init);
	void operator=(CII const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CII); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CII_altova_root, 0, 0> root;	// root CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CII_altova_extension, 0, 0> extension;	// extension Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CII_altova_identifierName, 0, 0> identifierName;	// identifierName Cstring

	MemberAttribute<bool,_altova_mi_iso_altova_CII_altova_displayable, 0, 0> displayable;	// displayable Cboolean
	MemberAttribute<string_type,_altova_mi_iso_altova_CII_altova_scope, 0, 4> scope;	// scope CIdentifierScope
	MemberAttribute<string_type,_altova_mi_iso_altova_CII_altova_reliability, 0, 3> reliability;	// reliability CIdentifierReliability
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CII
