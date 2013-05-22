/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationStatement



namespace AIMXML
{

class CAnnotationStatement : public TypeBase
{
public:
	AIMXML_EXPORT CAnnotationStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationStatement(CAnnotationStatement const& init);
	void operator=(CAnnotationStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationStatement); }
	MemberElement<iso::CII, _altova_mi_altova_CAnnotationStatement_altova_subjectUniqueIdentifier> subjectUniqueIdentifier;
	struct subjectUniqueIdentifier { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CAnnotationStatement_altova_objectUniqueIdentifier> objectUniqueIdentifier;
	struct objectUniqueIdentifier { typedef Iterator<iso::CII> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationStatement
