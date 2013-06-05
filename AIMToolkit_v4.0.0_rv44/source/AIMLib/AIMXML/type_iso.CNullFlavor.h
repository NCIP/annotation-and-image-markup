/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNullFlavor
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNullFlavor



namespace AIMXML
{

namespace iso
{	

class CNullFlavor : public TypeBase
{
public:
	AIMXML_EXPORT CNullFlavor(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNullFlavor(CNullFlavor const& init);
	void operator=(CNullFlavor const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CNullFlavor); }

	enum EnumValues {
		Invalid = -1,
		k_NI = 0, // NI
		k_INV = 1, // INV
		k_OTH = 2, // OTH
		k_NINF = 3, // NINF
		k_PINF = 4, // PINF
		k_UNC = 5, // UNC
		k_DER = 6, // DER
		k_UNK = 7, // UNK
		k_ASKU = 8, // ASKU
		k_NAV = 9, // NAV
		k_QS = 10, // QS
		k_NASK = 11, // NASK
		k_TRC = 12, // TRC
		k_MSK = 13, // MSK
		k_NA = 14, // NA
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNullFlavor
