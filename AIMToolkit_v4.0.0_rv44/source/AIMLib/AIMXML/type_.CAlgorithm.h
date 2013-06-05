/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAlgorithm
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAlgorithm



namespace AIMXML
{

class CAlgorithm : public TypeBase
{
public:
	AIMXML_EXPORT CAlgorithm(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAlgorithm(CAlgorithm const& init);
	void operator=(CAlgorithm const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAlgorithm); }
	MemberElement<iso::CST, _altova_mi_altova_CAlgorithm_altova_name> name;
	struct name { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CAlgorithm_altova_type> type;
	struct type { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CAlgorithm_altova_uniqueIdentifier> uniqueIdentifier;
	struct uniqueIdentifier { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAlgorithm_altova_version> version;
	struct version { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAlgorithm_altova_description> description;
	struct description { typedef Iterator<iso::CST> iterator; };
	MemberElement<CparameterCollectionType, _altova_mi_altova_CAlgorithm_altova_parameterCollection> parameterCollection;
	struct parameterCollection { typedef Iterator<CparameterCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAlgorithm
