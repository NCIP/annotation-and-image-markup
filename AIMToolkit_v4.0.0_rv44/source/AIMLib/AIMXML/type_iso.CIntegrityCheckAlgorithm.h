/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIntegrityCheckAlgorithm
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIntegrityCheckAlgorithm



namespace AIMXML
{

namespace iso
{	

class CIntegrityCheckAlgorithm : public TypeBase
{
public:
	AIMXML_EXPORT CIntegrityCheckAlgorithm(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIntegrityCheckAlgorithm(CIntegrityCheckAlgorithm const& init);
	void operator=(CIntegrityCheckAlgorithm const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_iso_altova_CIntegrityCheckAlgorithm); }

	enum EnumValues {
		Invalid = -1,
		k_SHA1 = 0, // SHA1
		k_SHA256 = 1, // SHA256
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIntegrityCheckAlgorithm
