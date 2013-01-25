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

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Doc_Ref
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Doc_Ref



namespace AIMXML
{

namespace iso
{	

class CED_Doc_Ref : public TypeBase
{
public:
	AIMXML_EXPORT CED_Doc_Ref(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CED_Doc_Ref(CED_Doc_Ref const& init);
	void operator=(CED_Doc_Ref const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CED_Doc_Ref); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_validTimeLow, 0, 0> validTimeLow;	// validTimeLow Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_validTimeHigh, 0, 0> validTimeHigh;	// validTimeHigh Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_controlActRoot, 0, 0> controlActRoot;	// controlActRoot CUid

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_controlActExtension, 0, 0> controlActExtension;	// controlActExtension Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_nullFlavor, 0, 15> nullFlavor;	// nullFlavor CNullFlavor

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_flavorId, 0, 0> flavorId;	// flavorId Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_updateMode, 0, 8> updateMode;	// updateMode CUpdateMode

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_mediaType, 0, 0> mediaType;	// mediaType Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_charset, 0, 0> charset;	// charset CCode

	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_language, 0, 0> language;	// language CCode
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_compression, 0, 4> compression;	// compression CCompression
	MemberAttribute<string_type,_altova_mi_iso_altova_CED_Doc_Ref_altova_integrityCheckAlgorithm, 0, 2> integrityCheckAlgorithm;	// integrityCheckAlgorithm CIntegrityCheckAlgorithm
	MemberElement<xs::Cbase64BinaryType, _altova_mi_iso_altova_CED_Doc_Ref_altova_data> data;
	struct data { typedef Iterator<xs::Cbase64BinaryType> iterator; };
	MemberElement<xs::CanyType, _altova_mi_iso_altova_CED_Doc_Ref_altova_xml> xml;
	struct xml { typedef Iterator<xs::CanyType> iterator; };
	MemberElement<iso::CTEL, _altova_mi_iso_altova_CED_Doc_Ref_altova_reference> reference;
	struct reference { typedef Iterator<iso::CTEL> iterator; };
	MemberElement<xs::Cbase64BinaryType, _altova_mi_iso_altova_CED_Doc_Ref_altova_integrityCheck> integrityCheck;
	struct integrityCheck { typedef Iterator<xs::Cbase64BinaryType> iterator; };
	MemberElement<iso::CED, _altova_mi_iso_altova_CED_Doc_Ref_altova_thumbnail> thumbnail;
	struct thumbnail { typedef Iterator<iso::CED> iterator; };
	MemberElement<iso::CED, _altova_mi_iso_altova_CED_Doc_Ref_altova_translation> translation;
	struct translation { typedef Iterator<iso::CED> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CED_Doc_Ref
