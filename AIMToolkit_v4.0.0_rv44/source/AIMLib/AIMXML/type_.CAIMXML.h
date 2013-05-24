/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAIMXML
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAIMXML



namespace AIMXML
{

class CAIMXML : public TypeBase
{
public:
	AIMXML_EXPORT CAIMXML(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAIMXML(CAIMXML const& init);
	void operator=(CAIMXML const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAIMXML); }
	MemberElement<CAnnotationOfAnnotationCollection, _altova_mi_altova_CAIMXML_altova_AnnotationOfAnnotationCollection> AnnotationOfAnnotationCollection;
	struct AnnotationOfAnnotationCollection { typedef Iterator<CAnnotationOfAnnotationCollection> iterator; };
	MemberElement<CImageAnnotationCollection, _altova_mi_altova_CAIMXML_altova_ImageAnnotationCollection> ImageAnnotationCollection;
	struct ImageAnnotationCollection { typedef Iterator<CImageAnnotationCollection> iterator; };
	MemberElement<CbrType, _altova_mi_altova_CAIMXML_altova_br> br;
	struct br { typedef Iterator<CbrType> iterator; };
	MemberElement<CcaptionType, _altova_mi_altova_CAIMXML_altova_caption> caption;
	struct caption { typedef Iterator<CcaptionType> iterator; };
	MemberElement<CcolType, _altova_mi_altova_CAIMXML_altova_col> col;
	struct col { typedef Iterator<CcolType> iterator; };
	MemberElement<CcolgroupType, _altova_mi_altova_CAIMXML_altova_colgroup> colgroup;
	struct colgroup { typedef Iterator<CcolgroupType> iterator; };
	MemberElement<CcontentType, _altova_mi_altova_CAIMXML_altova_content> content;
	struct content { typedef Iterator<CcontentType> iterator; };
	MemberElement<CfootnoteType, _altova_mi_altova_CAIMXML_altova_footnote> footnote;
	struct footnote { typedef Iterator<CfootnoteType> iterator; };
	MemberElement<CfootnoteRefType, _altova_mi_altova_CAIMXML_altova_footnoteRef> footnoteRef;
	struct footnoteRef { typedef Iterator<CfootnoteRefType> iterator; };
	MemberElement<CitemType, _altova_mi_altova_CAIMXML_altova_item> item;
	struct item { typedef Iterator<CitemType> iterator; };
	MemberElement<ClinkHtmlType, _altova_mi_altova_CAIMXML_altova_linkHtml> linkHtml;
	struct linkHtml { typedef Iterator<ClinkHtmlType> iterator; };
	MemberElement<ClistType, _altova_mi_altova_CAIMXML_altova_list> list;
	struct list { typedef Iterator<ClistType> iterator; };
	MemberElement<CparagraphType, _altova_mi_altova_CAIMXML_altova_paragraph> paragraph;
	struct paragraph { typedef Iterator<CparagraphType> iterator; };
	MemberElement<CrenderMultiMediaType, _altova_mi_altova_CAIMXML_altova_renderMultiMedia> renderMultiMedia;
	struct renderMultiMedia { typedef Iterator<CrenderMultiMediaType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAIMXML_altova_sub> sub;
	struct sub { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAIMXML_altova_sup> sup;
	struct sup { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CtableType, _altova_mi_altova_CAIMXML_altova_table> table;
	struct table { typedef Iterator<CtableType> iterator; };
	MemberElement<CtbodyType, _altova_mi_altova_CAIMXML_altova_tbody> tbody;
	struct tbody { typedef Iterator<CtbodyType> iterator; };
	MemberElement<CtdType, _altova_mi_altova_CAIMXML_altova_td> td;
	struct td { typedef Iterator<CtdType> iterator; };
	MemberElement<iso::CNarrative, _altova_mi_altova_CAIMXML_altova_text> text;
	struct text { typedef Iterator<iso::CNarrative> iterator; };
	MemberElement<CtfootType, _altova_mi_altova_CAIMXML_altova_tfoot> tfoot;
	struct tfoot { typedef Iterator<CtfootType> iterator; };
	MemberElement<CthType, _altova_mi_altova_CAIMXML_altova_th> th;
	struct th { typedef Iterator<CthType> iterator; };
	MemberElement<CtheadType, _altova_mi_altova_CAIMXML_altova_thead> thead;
	struct thead { typedef Iterator<CtheadType> iterator; };
	MemberElement<CtrType, _altova_mi_altova_CAIMXML_altova_tr> tr;
	struct tr { typedef Iterator<CtrType> iterator; };
	AIMXML_EXPORT void SetXsiType();

	// document functions
	AIMXML_EXPORT static CAIMXML LoadFromFile(const string_type& fileName);
	AIMXML_EXPORT static CAIMXML LoadFromString(const string_type& xml);
	AIMXML_EXPORT static CAIMXML LoadFromBinary(const std::vector<unsigned char>& data);
	AIMXML_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint );
	AIMXML_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding );
	AIMXML_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM );
	AIMXML_EXPORT string_type SaveToString(bool prettyPrint);
	AIMXML_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint);
	AIMXML_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding);
	AIMXML_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM);
 	AIMXML_EXPORT static CAIMXML CreateDocument();
	AIMXML_EXPORT void DestroyDocument();
	AIMXML_EXPORT void SetDTDLocation(const string_type& dtdLocation);
	AIMXML_EXPORT void SetSchemaLocation(const string_type& schemaLocation);
protected:
	XercesTreeOperations::DocumentType GetDocumentNode() { return (XercesTreeOperations::DocumentType)m_node; }
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAIMXML
