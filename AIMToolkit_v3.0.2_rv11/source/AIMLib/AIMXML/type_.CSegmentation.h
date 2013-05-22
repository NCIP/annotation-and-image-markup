/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSegmentation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSegmentation



namespace AIMXML
{

class CSegmentation : public TypeBase
{
public:
	AIMXML_EXPORT CSegmentation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CSegmentation(CSegmentation const& init);
	void operator=(CSegmentation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSegmentation); }

	MemberAttribute<__int64,_altova_mi_altova_CSegmentation_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CSegmentation_altova_sopInstanceUID, 0, 0> sopInstanceUID;	// sopInstanceUID Cstring

	MemberAttribute<string_type,_altova_mi_altova_CSegmentation_altova_sopClassUID, 0, 0> sopClassUID;	// sopClassUID Cstring

	MemberAttribute<string_type,_altova_mi_altova_CSegmentation_altova_referencedSopInstanceUID, 0, 0> referencedSopInstanceUID;	// referencedSopInstanceUID Cstring

	MemberAttribute<__int64,_altova_mi_altova_CSegmentation_altova_segmentNumber, 0, 0> segmentNumber;	// segmentNumber Cinteger
	MemberElement<CimagingObservationType, _altova_mi_altova_CSegmentation_altova_imagingObservation> imagingObservation;
	struct imagingObservation { typedef Iterator<CimagingObservationType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSegmentation
