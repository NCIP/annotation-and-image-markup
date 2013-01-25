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

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPQ

#include "type_iso.CQTY.h"


namespace AIMXML
{

namespace iso
{	

class CPQ : public ::AIMXML::iso::CQTY
{
public:
	AIMXML_EXPORT CPQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CPQ(CPQ const& init);
	void operator=(CPQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CPQ); }

	MemberAttribute<double,_altova_mi_iso_altova_CPQ_altova_value2, 0, 0> value2;	// value Cdouble

	MemberAttribute<int,_altova_mi_iso_altova_CPQ_altova_precision, 0, 0> precision;	// precision Cint

	MemberAttribute<string_type,_altova_mi_iso_altova_CPQ_altova_unit, 0, 0> unit;	// unit CCode
	MemberAttribute<string_type,_altova_mi_iso_altova_CPQ_altova_codingRationale, 1, 4> codingRationale;	// codingRationale Cset_CodingRationale
	MemberElement<iso::CPQR, _altova_mi_iso_altova_CPQ_altova_translation> translation;
	struct translation { typedef Iterator<iso::CPQR> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPQ
