/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationCollection
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationCollection



namespace AIMXML
{

class CAnnotationCollection : public TypeBase
{
public:
	AIMXML_EXPORT CAnnotationCollection(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationCollection(CAnnotationCollection const& init);
	void operator=(CAnnotationCollection const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationCollection); }
	MemberAttribute<string_type,_altova_mi_altova_CAnnotationCollection_altova_aimVersion, 0, 5> aimVersion;	// aimVersion CAimVersion
	MemberElement<iso::CII, _altova_mi_altova_CAnnotationCollection_altova_uniqueIdentifier> uniqueIdentifier;
	struct uniqueIdentifier { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAnnotationCollection_altova_description> description;
	struct description { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CAnnotationCollection_altova_dateTime> dateTime;
	struct dateTime { typedef Iterator<iso::CTS> iterator; };
	MemberElement<CUser, _altova_mi_altova_CAnnotationCollection_altova_user> user;
	struct user { typedef Iterator<CUser> iterator; };
	MemberElement<CEquipment, _altova_mi_altova_CAnnotationCollection_altova_equipment> equipment;
	struct equipment { typedef Iterator<CEquipment> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationCollection
