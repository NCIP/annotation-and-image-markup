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

#include "../stdafx.h"

#include "Entity.h"
#include "MarkupEntity.h"
#include "GeometricShapeEntity.h"
#include "TextAnnotationEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

TextAnnotationEntity::TextAnnotationEntity(){
}

TextAnnotationEntity::TextAnnotationEntity(const TextAnnotationEntity& textAnnotationEntity) : MarkupEntity(textAnnotationEntity){
	*this = textAnnotationEntity;
}

TextAnnotationEntity& TextAnnotationEntity::operator= (const TextAnnotationEntity& textAnnotationEntity){
	if (this != &textAnnotationEntity)
	{
		_text			= textAnnotationEntity._text;
		_textJustify	= textAnnotationEntity._textJustify;
		_font			= textAnnotationEntity._font;
		_fontColor		= textAnnotationEntity._fontColor;
		_fontEffect		= textAnnotationEntity._fontEffect;
		_fontOpacity	= textAnnotationEntity._fontOpacity;
		_fontSize		= textAnnotationEntity._fontSize;
		_fontStyle		= textAnnotationEntity._fontStyle;
		SetGeometricShapeEntity(textAnnotationEntity.GetGeometricShapeEntity());
	}
	return *this;
}

TextAnnotationEntity::~TextAnnotationEntity(){
}

TextAnnotationEntity* TextAnnotationEntity::Clone() const{
	return new TextAnnotationEntity(*this);
}

const string& TextAnnotationEntity::GetText() const{
	return _text;
}

const string& TextAnnotationEntity::GetFont() const{
	return _font;
}

const string& TextAnnotationEntity::GetFontColor() const{
	return _fontColor;
}

const string& TextAnnotationEntity::GetFontEffect() const{
	return _fontEffect;
}

const string& TextAnnotationEntity::GetFontOpacity() const{
	return _fontOpacity;
}

const string& TextAnnotationEntity::GetFontSize() const{
	return _fontSize;
}

const string& TextAnnotationEntity::GetFontStyle() const{
	return _fontStyle;
}

const string& TextAnnotationEntity::GetTextJustify() const{
	return _textJustify;
}

const GeometricShapeEntity* TextAnnotationEntity::GetGeometricShapeEntity() const{
	return _geometricShapeEntity.get();
}

void TextAnnotationEntity::SetText(const string& newVal){
	_text = newVal;
}

void TextAnnotationEntity::SetFont(const string& newVal){
	_font = newVal;
}

void TextAnnotationEntity::SetFontColor(const string& newVal){
	_fontColor = newVal;
}

void TextAnnotationEntity::SetFontEffect(const string& newVal){
	_fontEffect = newVal;
}

void TextAnnotationEntity::SetFontOpacity(const string& newVal){
	_fontOpacity = newVal;
}

void TextAnnotationEntity::SetFontSize(const string& newVal){
	_fontSize = newVal;
}

void TextAnnotationEntity::SetFontStyle(const string& newVal){
	_fontStyle = newVal;
}

void TextAnnotationEntity::SetTextJustify(const string& newVal){
	_textJustify = newVal;
}

void TextAnnotationEntity::SetGeometricShapeEntity(const GeometricShapeEntity* newVal){
	_geometricShapeEntity.reset(newVal ? newVal->Clone() : NULL);
}
