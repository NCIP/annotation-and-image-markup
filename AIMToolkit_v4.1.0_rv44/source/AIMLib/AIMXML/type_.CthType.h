/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CthType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CthType



namespace AIMXML
{

class CthType : public TypeBase
{
public:
	AIMXML_EXPORT CthType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CthType(CthType const& init);
	void operator=(CthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CthType); }
	AIMXML_EXPORT void operator=(const string_type& value);
	AIMXML_EXPORT operator string_type();

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_abbr, 0, 0> abbr;	// abbr Cstring

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_axis, 0, 0> axis;	// axis Cstring

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_headers, 0, 0> headers;	// headers CIDREFS
	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_scope, 0, 4> scope;	// scope CscopeType2

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_rowspan, 0, 0> rowspan;	// rowspan Cstring

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_colspan, 0, 0> colspan;	// colspan Cstring
	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_align, 0, 5> align;	// align CalignType6

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_char2, 0, 0> char2;	// char Cstring

	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_charoff, 0, 0> charoff;	// charoff Cstring
	MemberAttribute<string_type,_altova_mi_altova_CthType_altova_valign, 0, 4> valign;	// valign CvalignType6
	MemberElement<CcontentType, _altova_mi_altova_CthType_altova_content> content;
	struct content { typedef Iterator<CcontentType> iterator; };
	MemberElement<ClinkHtmlType, _altova_mi_altova_CthType_altova_linkHtml> linkHtml;
	struct linkHtml { typedef Iterator<ClinkHtmlType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CthType_altova_sub> sub;
	struct sub { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CthType_altova_sup> sup;
	struct sup { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CbrType, _altova_mi_altova_CthType_altova_br> br;
	struct br { typedef Iterator<CbrType> iterator; };
	MemberElement<CfootnoteType, _altova_mi_altova_CthType_altova_footnote> footnote;
	struct footnote { typedef Iterator<CfootnoteType> iterator; };
	MemberElement<CfootnoteRefType, _altova_mi_altova_CthType_altova_footnoteRef> footnoteRef;
	struct footnoteRef { typedef Iterator<CfootnoteRefType> iterator; };
	MemberElement<CrenderMultiMediaType, _altova_mi_altova_CthType_altova_renderMultiMedia> renderMultiMedia;
	struct renderMultiMedia { typedef Iterator<CrenderMultiMediaType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CthType
