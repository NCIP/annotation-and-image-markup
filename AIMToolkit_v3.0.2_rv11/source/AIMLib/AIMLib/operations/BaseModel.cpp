/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"
#include "../model/AimHeaders.h"

#include "BaseModel.h"

using namespace aim_lib;

// Version of the AIM model
const char BaseModel::AIM_MODEL_VERSION[] = "3.0";

BaseModel::BaseModel(void)
{
}

BaseModel::~BaseModel(void)
{
	this->ClearAnnotations();
}

void BaseModel::ClearAnnotations(void)
{
	for (AnnotationPtrVector::iterator iter = _annotations.begin(); iter < _annotations.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	_annotations.clear();
	//_currentAnnotation = 0;
}
