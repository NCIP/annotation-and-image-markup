/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "Entity.h"
#include "AnnotationRoleEntity.h"

#include "../memdebug.h"

using namespace std;
using namespace aim_lib;
using namespace iso_21090;

AnnotationRoleEntity::AnnotationRoleEntity(void) : _roleSequenceNumber(-1){
}

AnnotationRoleEntity::AnnotationRoleEntity(const AnnotationRoleEntity& annotationRoleEntity) : Entity(annotationRoleEntity){
	_roleCode = annotationRoleEntity._roleCode;
	_questionTypeCode = annotationRoleEntity._questionTypeCode;
	_roleSequenceNumber = annotationRoleEntity._roleSequenceNumber;
}

AnnotationRoleEntity::~AnnotationRoleEntity(void){
}

const CD& AnnotationRoleEntity::GetRoleCode() const{
	return _roleCode;
}

const CDVector& AnnotationRoleEntity::GetQuestionTypeCode() const{
	return _questionTypeCode;
}

int AnnotationRoleEntity::GetRoleSequenceNumber() const{
	return _roleSequenceNumber;
}

void AnnotationRoleEntity::SetRoleCode(const CD& roleCode){
	_roleCode = roleCode;
}

void AnnotationRoleEntity::SetQuestionTypeCode(const CDVector& questionTypeCode){
	_questionTypeCode.assign(questionTypeCode.begin(), questionTypeCode.end());
}

void AnnotationRoleEntity::SetRoleSequenceNumber(int roleSequenceNumber){
	_roleSequenceNumber = roleSequenceNumber;
}
