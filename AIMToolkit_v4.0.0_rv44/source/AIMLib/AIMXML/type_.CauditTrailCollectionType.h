/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CauditTrailCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CauditTrailCollectionType



namespace AIMXML
{

class CauditTrailCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CauditTrailCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CauditTrailCollectionType(CauditTrailCollectionType const& init);
	void operator=(CauditTrailCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CauditTrailCollectionType); }
	MemberElement<CAuditTrail, _altova_mi_altova_CauditTrailCollectionType_altova_AuditTrail> AuditTrail;
	struct AuditTrail { typedef Iterator<CAuditTrail> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CauditTrailCollectionType
