/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CPresentationState
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CPresentationState



namespace AIMXML
{

class CPresentationState : public TypeBase
{
public:
	AIMXML_EXPORT CPresentationState(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CPresentationState(CPresentationState const& init);
	void operator=(CPresentationState const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPresentationState); }

	MemberAttribute<__int64,_altova_mi_altova_CPresentationState_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CPresentationState_altova_sopInstanceUID, 0, 0> sopInstanceUID;	// sopInstanceUID Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CPresentationState
