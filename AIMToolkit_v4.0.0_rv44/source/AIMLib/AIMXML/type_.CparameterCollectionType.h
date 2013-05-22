/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CparameterCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CparameterCollectionType



namespace AIMXML
{

class CparameterCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CparameterCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CparameterCollectionType(CparameterCollectionType const& init);
	void operator=(CparameterCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CparameterCollectionType); }
	MemberElement<CParameter, _altova_mi_altova_CparameterCollectionType_altova_Parameter> Parameter;
	struct Parameter { typedef Iterator<CParameter> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CparameterCollectionType
