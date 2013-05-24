/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_Cbase64BinaryType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_Cbase64BinaryType



namespace AIMXML
{

namespace xs
{	

class Cbase64BinaryType : public TypeBase
{
public:
	AIMXML_EXPORT Cbase64BinaryType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT Cbase64BinaryType(Cbase64BinaryType const& init);
	void operator=(Cbase64BinaryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Cbase64BinaryType); }
	AIMXML_EXPORT void operator=(const std::vector<unsigned char>& value);
	AIMXML_EXPORT operator std::vector<unsigned char>();
	AIMXML_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_xs_ALTOVA_Cbase64BinaryType
