/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimBase.h"
#include "SpatialCoordinate.h"
#include "GeometricShape.h"
#include "MultiPoint.h"
#include "TextAnnotation.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

TextAnnotation::TextAnnotation(){

}

TextAnnotation::TextAnnotation(const TextAnnotation& textAnnotation){
	*this = textAnnotation;
}

TextAnnotation& TextAnnotation::operator= (const TextAnnotation& textAnnotation){
	_cagridId		= textAnnotation._cagridId;
	_text			= textAnnotation._text;
	_textJustify	= textAnnotation._textJustify;
	_font			= textAnnotation._font;
	_fontColor		= textAnnotation._fontColor;
	_fontEffect		= textAnnotation._fontEffect;
	_fontOpacity	= textAnnotation._fontOpacity;
	_fontSize		= textAnnotation._fontSize;
	_fontStyle		= textAnnotation._fontStyle;
	TextAnnotation* pTextAnnotation = const_cast<TextAnnotation*>(&textAnnotation);
	this->SetConnectorPoints(pTextAnnotation->GetConnectorPoints());

	return *this;
}

TextAnnotation::~TextAnnotation(){

}

TextAnnotation* TextAnnotation::Clone() const{
	return new TextAnnotation(*this);
}

const string& TextAnnotation::GetFont() const{

	return _font;
}

const string& TextAnnotation::GetFontColor() const{

	return _fontColor;
}

const string& TextAnnotation::GetFontEffect() const{

	return _fontEffect;
}

const string& TextAnnotation::GetFontOpacity() const{

	return _fontOpacity;
}

const string& TextAnnotation::GetFontSize() const{

	return _fontSize;
}

const string& TextAnnotation::GetFontStyle() const{

	return _fontStyle;
}

const string& TextAnnotation::GetText() const{

	return _text;
}

const string& TextAnnotation::GetTextJustify() const{

	return _textJustify;
}

const MultiPoint* TextAnnotation::GetConnectorPoints() const{

	return _connectorPoints.get();
}

void TextAnnotation::SetFont(const string& newVal){

	_font = newVal;
}

void TextAnnotation::SetFontColor(const string& newVal){

	_fontColor = newVal;
}

void TextAnnotation::SetFontEffect(const string& newVal){

	_fontEffect = newVal;
}

void TextAnnotation::SetFontOpacity(const string& newVal){

	_fontOpacity = newVal;
}

void TextAnnotation::SetFontSize(const string& newVal){

	_fontSize = newVal;
}

void TextAnnotation::SetFontStyle(const string& newVal){

	_fontStyle = newVal;
}

void TextAnnotation::SetText(const string& newVal){

	_text = newVal;
}

void TextAnnotation::SetTextJustify(const string& newVal){

	_textJustify = newVal;
}

void TextAnnotation::SetConnectorPoints(const MultiPoint* connectorPoints){

	if (connectorPoints == NULL)
		_connectorPoints.reset();
	else
		_connectorPoints.reset(static_cast<MultiPoint*>(connectorPoints->Clone()));
}