/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AnnotationRole.h"
#include "ReferencedAnnotation.h"

using std::string;
using namespace aim_lib;

ReferencedAnnotation::ReferencedAnnotation(){

}

ReferencedAnnotation::ReferencedAnnotation(const ReferencedAnnotation& referencedAnnotation){
	*this = referencedAnnotation;
}

ReferencedAnnotation::~ReferencedAnnotation(){

}

ReferencedAnnotation& ReferencedAnnotation::operator =(const ReferencedAnnotation &referencedAnnotation){
	_cagridId					= referencedAnnotation._cagridId;
	_referencedAnnotationUID	= referencedAnnotation._referencedAnnotationUID;
	SetAnnotationRole(referencedAnnotation.GetAnnotationRole());

	return *this;
}

const string& ReferencedAnnotation::GetReferencedAnnotationUID() const{

	return _referencedAnnotationUID;
}

AnnotationRole* ReferencedAnnotation::GetAnnotationRole() const{
	return _annotationRole.get();
}

void ReferencedAnnotation::SetReferencedAnnotationUID(const string& newVal){

	_referencedAnnotationUID = newVal;
}

void ReferencedAnnotation::SetAnnotationRole(const AnnotationRole* pAnnotationRole){
	if (pAnnotationRole == NULL)
		_annotationRole.reset();
	else
		_annotationRole.reset(pAnnotationRole->Clone());
}
