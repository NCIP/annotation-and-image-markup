/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_EntityNamePartQualifier
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_EntityNamePartQualifier



namespace AIMXML
{

namespace iso
{	

class Cset_EntityNamePartQualifier : public TypeBase
{
public:
	AIMXML_EXPORT Cset_EntityNamePartQualifier(xercesc::DOMNode* const& init);
	AIMXML_EXPORT Cset_EntityNamePartQualifier(Cset_EntityNamePartQualifier const& init);
	void operator=(Cset_EntityNamePartQualifier const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_Cset_EntityNamePartQualifier); }

	enum EnumValues {
		Invalid = -1,
		k_LS = 0, // LS
		k_AC = 1, // AC
		k_NB = 2, // NB
		k_PR = 3, // PR
		k_VV = 4, // VV
		k_AD = 5, // AD
		k_BR = 6, // BR
		k_SP = 7, // SP
		k_CL = 8, // CL
		k_IN = 9, // IN
		k_TITLE = 10, // TITLE
		EnumValueCount
	};
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_Cset_EntityNamePartQualifier
