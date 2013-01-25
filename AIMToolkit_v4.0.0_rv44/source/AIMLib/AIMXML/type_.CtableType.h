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

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtableType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtableType



namespace AIMXML
{

class CtableType : public TypeBase
{
public:
	AIMXML_EXPORT CtableType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtableType(CtableType const& init);
	void operator=(CtableType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtableType); }

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_summary, 0, 0> summary;	// summary Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_width, 0, 0> width;	// width Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_border, 0, 0> border;	// border Cstring
	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_frame, 0, 9> frame;	// frame CframeType
	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_rules, 0, 5> rules;	// rules CrulesType

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_cellspacing, 0, 0> cellspacing;	// cellspacing Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_cellpadding, 0, 0> cellpadding;	// cellpadding Cstring
	MemberElement<CcaptionType, _altova_mi_altova_CtableType_altova_caption> caption;
	struct caption { typedef Iterator<CcaptionType> iterator; };
	MemberElement<CcolType, _altova_mi_altova_CtableType_altova_col> col;
	struct col { typedef Iterator<CcolType> iterator; };
	MemberElement<CcolgroupType, _altova_mi_altova_CtableType_altova_colgroup> colgroup;
	struct colgroup { typedef Iterator<CcolgroupType> iterator; };
	MemberElement<CtheadType, _altova_mi_altova_CtableType_altova_thead> thead;
	struct thead { typedef Iterator<CtheadType> iterator; };
	MemberElement<CtfootType, _altova_mi_altova_CtableType_altova_tfoot> tfoot;
	struct tfoot { typedef Iterator<CtfootType> iterator; };
	MemberElement<CtbodyType, _altova_mi_altova_CtableType_altova_tbody> tbody;
	struct tbody { typedef Iterator<CtbodyType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtableType
