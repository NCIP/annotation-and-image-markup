/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CAddressPartType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CAddressPartType



namespace AIMXML
{

namespace iso
{	

class CAddressPartType : public TypeBase
{
public:
	AIMXML_EXPORT CAddressPartType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAddressPartType(CAddressPartType const& init);
	void operator=(CAddressPartType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CAddressPartType); }

	enum EnumValues {
		Invalid = -1,
		k_AL = 0, // AL
		k_ADL = 1, // ADL
		k_UNID = 2, // UNID
		k_UNIT = 3, // UNIT
		k_DAL = 4, // DAL
		k_DINST = 5, // DINST
		k_DINSTA = 6, // DINSTA
		k_DINSTQ = 7, // DINSTQ
		k_DMOD = 8, // DMOD
		k_DMODID = 9, // DMODID
		k_SAL = 10, // SAL
		k_BNR = 11, // BNR
		k_BNN = 12, // BNN
		k_BNS = 13, // BNS
		k_STR = 14, // STR
		k_STB = 15, // STB
		k_STTYP = 16, // STTYP
		k_DIR = 17, // DIR
		k_CAR = 18, // CAR
		k_CEN = 19, // CEN
		k_CNT = 20, // CNT
		k_CPA = 21, // CPA
		k_CTY = 22, // CTY
		k_DEL = 23, // DEL
		k_POB = 24, // POB
		k_PRE = 25, // PRE
		k_STA = 26, // STA
		k_ZIP = 27, // ZIP
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CAddressPartType
