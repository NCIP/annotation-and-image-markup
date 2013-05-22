/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationResultIdentifier
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationResultIdentifier



namespace AIMXML
{

class CCalculationResultIdentifier : public TypeBase
{
public:
	AIMXML_EXPORT CCalculationResultIdentifier(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalculationResultIdentifier(CCalculationResultIdentifier const& init);
	void operator=(CCalculationResultIdentifier const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CCalculationResultIdentifier); }

	enum EnumValues {
		Invalid = -1,
		k_Scalar = 0, // Scalar
		k_Vector = 1, // Vector
		k_Histogram = 2, // Histogram
		k_Matrix = 3, // Matrix
		k_Array = 4, // Array
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

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationResultIdentifier
