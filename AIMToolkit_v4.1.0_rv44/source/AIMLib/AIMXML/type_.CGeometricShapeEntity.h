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

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShapeEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShapeEntity

#include "type_.CMarkupEntity.h"


namespace AIMXML
{

class CGeometricShapeEntity : public ::AIMXML::CMarkupEntity
{
public:
	AIMXML_EXPORT CGeometricShapeEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CGeometricShapeEntity(CGeometricShapeEntity const& init);
	void operator=(CGeometricShapeEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGeometricShapeEntity); }
	MemberElement<iso::CCD, _altova_mi_altova_CGeometricShapeEntity_altova_questionTypeCode> questionTypeCode;
	struct questionTypeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CGeometricShapeEntity_altova_shapeIdentifier> shapeIdentifier;
	struct shapeIdentifier { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_label> label;
	struct label { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_description> description;
	struct description { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CGeometricShapeEntity_altova_includeFlag> includeFlag;
	struct includeFlag { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineColor> lineColor;
	struct lineColor { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineOpacity> lineOpacity;
	struct lineOpacity { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineStyle> lineStyle;
	struct lineStyle { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineThickness> lineThickness;
	struct lineThickness { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CGeometricShapeEntity_altova_questionIndex> questionIndex;
	struct questionIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CGeometricShapeEntity_altova_interpolationMethod> interpolationMethod;
	struct interpolationMethod { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShapeEntity
