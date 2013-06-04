/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCharacteristicQuantification
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCharacteristicQuantification



namespace AIMXML
{

class CCharacteristicQuantification : public TypeBase
{
public:
	AIMXML_EXPORT CCharacteristicQuantification(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCharacteristicQuantification(CCharacteristicQuantification const& init);
	void operator=(CCharacteristicQuantification const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCharacteristicQuantification); }
	MemberElement<iso::CREAL, _altova_mi_altova_CCharacteristicQuantification_altova_annotatorConfidence> annotatorConfidence;
	struct annotatorConfidence { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CCharacteristicQuantification_altova_characteristicQuantificationIndex> characteristicQuantificationIndex;
	struct characteristicQuantificationIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CCharacteristicQuantification_altova_label> label;
	struct label { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CCharacteristicQuantification_altova_valueLabel> valueLabel;
	struct valueLabel { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CCharacteristicQuantification_altova_valueDescription> valueDescription;
	struct valueDescription { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CCharacteristicQuantification_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCharacteristicQuantification
