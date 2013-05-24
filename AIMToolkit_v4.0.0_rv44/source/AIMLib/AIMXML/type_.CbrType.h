/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CbrType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CbrType



namespace AIMXML
{

class CbrType : public TypeBase
{
public:
	AIMXML_EXPORT CbrType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CbrType(CbrType const& init);
	void operator=(CbrType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CbrType); }
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CbrType
