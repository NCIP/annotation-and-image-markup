/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CParameter
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CParameter



namespace AIMXML
{

class CParameter : public TypeBase
{
public:
	AIMXML_EXPORT CParameter(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CParameter(CParameter const& init);
	void operator=(CParameter const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CParameter); }
	MemberElement<iso::CST, _altova_mi_altova_CParameter_altova_name> name;
	struct name { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CParameter_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CParameter_altova_dataType> dataType;
	struct dataType { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CParameter
