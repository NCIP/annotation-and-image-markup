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

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

GeometricShapeEntity::GeometricShapeEntity(const string& typeName) :
		_shapeTypeName(typeName), _shapeIdetifier(-1), _questionIndex(-1), _includeFlag(true){
}

GeometricShapeEntity::GeometricShapeEntity(const GeometricShapeEntity& shape) : MarkupEntity(shape){
	*this = shape;
}

GeometricShapeEntity& GeometricShapeEntity::operator =(const GeometricShapeEntity& shape){

	if (this != &shape)
	{
		MarkupEntity::operator=(shape);

		_shapeTypeName		= shape._shapeTypeName;
		_shapeIdetifier		= shape._shapeIdetifier;
		_label				= shape._label;
		_description		= shape._description;
		_includeFlag		= shape._includeFlag;
		_comment			= shape._comment;
		_lineColor			= shape._lineColor;
		_lineOpacity		= shape._lineOpacity;
		_lineStyle			= shape._lineStyle;
		_lineThickness		= shape._lineThickness;
		_questionIndex		= shape._questionIndex;

		SetQuestionTypeCode(shape.GetQuestionTypeCode());
		SetInterpolationMethod(shape.GetInterpolationMethod());
	}

	return *this;
}

GeometricShapeEntity::~GeometricShapeEntity(){
}

int GeometricShapeEntity::GetShapeIdentifier() const {
	return _shapeIdetifier;
}

const CDVector& GeometricShapeEntity::GetQuestionTypeCode() const {
	return _questionTypeCode;
}

const string& GeometricShapeEntity::GetLabel() const {
	return _label;
}

const string& GeometricShapeEntity::GetDescription() const {
	return _description;
}

bool GeometricShapeEntity::GetIncludeFlag() const {
	return _includeFlag;
}

const string& GeometricShapeEntity::GetComment() const {
	return _comment;
}

const string& GeometricShapeEntity::GetLineColor() const {
	return _lineColor;
}

const string& GeometricShapeEntity::GetLineOpacity() const {
	return _lineOpacity;
}

const string& GeometricShapeEntity::GetLineStyle() const {
	return _lineStyle;
}

const string& GeometricShapeEntity::GetLineThickness() const {
	return _lineThickness;
}

int GeometricShapeEntity::GetQuestionIndex() const {
	return _questionIndex;
}

const CD* GeometricShapeEntity::GetInterpolationMethod() const {
	return _interpolationMethod.get();
}

void GeometricShapeEntity::SetShapeIdentifier(int newVal){
	_shapeIdetifier = newVal;
}

void GeometricShapeEntity::SetQuestionTypeCode(const CDVector& newVal){
	_questionTypeCode.assign(newVal.begin(), newVal.end());
}

void GeometricShapeEntity::SetLabel(const string& newVal){
	_label = newVal;
}

void GeometricShapeEntity::SetDescription(const string& newVal){
	_description = newVal;
}

void GeometricShapeEntity::SetIncludeFlag(bool newVal){
	_includeFlag = newVal;
}

void GeometricShapeEntity::SetComment(const string& newVal){
	_comment = newVal;
}

void GeometricShapeEntity::SetLineColor(const string& newVal){
	_lineColor = newVal;
}

void GeometricShapeEntity::SetLineOpacity(const string& newVal){
	_lineOpacity = newVal;
}

void GeometricShapeEntity::SetLineStyle(const string& newVal){
	_lineStyle = newVal;
}

void GeometricShapeEntity::SetLineThickness(const string& newVal){
	_lineThickness = newVal;
}

void GeometricShapeEntity::SetQuestionIndex(int newVal){
	_questionIndex = newVal;
}

void GeometricShapeEntity::SetInterpolationMethod(const CD* newVal){
	_interpolationMethod.reset(newVal ? new CD(*newVal) : NULL);
}
