/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedDicomObject
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedDicomObject



namespace AIMXML
{

class CReferencedDicomObject : public TypeBase
{
public:
	AIMXML_EXPORT CReferencedDicomObject(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CReferencedDicomObject(CReferencedDicomObject const& init);
	void operator=(CReferencedDicomObject const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReferencedDicomObject); }
	MemberElement<iso::CCD, _altova_mi_altova_CReferencedDicomObject_altova_modality> modality;
	struct modality { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CReferencedDicomObject_altova_sopInstanceUid> sopInstanceUid;
	struct sopInstanceUid { typedef Iterator<iso::CII> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CReferencedDicomObject
