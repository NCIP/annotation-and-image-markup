/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CEntity



namespace AIMXML
{

class CEntity : public TypeBase
{
public:
	AIMXML_EXPORT CEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEntity(CEntity const& init);
	void operator=(CEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEntity); }
	MemberElement<iso::CII, _altova_mi_altova_CEntity_altova_uniqueIdentifier> uniqueIdentifier;
	struct uniqueIdentifier { typedef Iterator<iso::CII> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CEntity
