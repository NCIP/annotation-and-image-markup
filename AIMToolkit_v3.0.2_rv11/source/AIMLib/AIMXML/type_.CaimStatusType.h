/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CaimStatusType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CaimStatusType



namespace AIMXML
{

class CaimStatusType : public TypeBase
{
public:
	AIMXML_EXPORT CaimStatusType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CaimStatusType(CaimStatusType const& init);
	void operator=(CaimStatusType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CaimStatusType); }
	MemberElement<CAimStatus, _altova_mi_altova_CaimStatusType_altova_AimStatus> AimStatus;
	struct AimStatus { typedef Iterator<CAimStatus> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CaimStatusType
