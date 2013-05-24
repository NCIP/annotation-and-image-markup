/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
