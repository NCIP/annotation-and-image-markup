/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CQuantile
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CQuantile

#include "type_.CCharacteristicQuantification.h"


namespace AIMXML
{

class CQuantile : public ::AIMXML::CCharacteristicQuantification
{
public:
	AIMXML_EXPORT CQuantile(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQuantile(CQuantile const& init);
	void operator=(CQuantile const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CQuantile); }
	MemberElement<iso::CINT, _altova_mi_altova_CQuantile_altova_bins> bins;
	struct bins { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CQuantile_altova_selectedBin> selectedBin;
	struct selectedBin { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CQuantile_altova_minValue> minValue;
	struct minValue { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CQuantile_altova_maxValue> maxValue;
	struct maxValue { typedef Iterator<iso::CREAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CQuantile
