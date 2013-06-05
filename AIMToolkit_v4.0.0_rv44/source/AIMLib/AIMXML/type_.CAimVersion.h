/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAimVersion
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAimVersion



namespace AIMXML
{

class CAimVersion : public TypeBase
{
public:
	AIMXML_EXPORT CAimVersion(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAimVersion(CAimVersion const& init);
	void operator=(CAimVersion const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CAimVersion); }

	enum EnumValues {
		Invalid = -1,
		k_AIMv1_0 = 0, // AIMv1_0
		k_AIMv2_0 = 1, // AIMv2_0
		k_AIMv3_0_1 = 2, // AIMv3_0_1
		k_AIMv3_0_2 = 3, // AIMv3_0_2
		k_AIMv4_0 = 4, // AIMv4_0
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


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAimVersion
