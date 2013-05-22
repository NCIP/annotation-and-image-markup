/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"
#include "../AimHeaders.h"

#include "BaseModel.h"

#include "../memdebug.h"

// Model Validator
#include "ModelValidator.h"
#include <stdexcept>
#include <sstream>
#include <ostream>

using namespace aim_lib;

#define model_ver_func( ver ) # ver

// Version of the AIM model
const char BaseModel::AIM_MODEL_VERSION[] = model_ver_func(AIMv4);

BaseModel::BaseModel(void){
}

BaseModel::~BaseModel(void){
}

void BaseModel::ValidateCollection(const AnnotationCollection& annotationCollection){

	ModelValidator modelValidator;
	if (!modelValidator.isValid(annotationCollection, true))
	{
		std::ostringstream errors;
		errors << "Annotation Collection Validation Errors:" << std::endl;
		// Errors are given in the reverse order
		for (std::vector<std::string>::const_reverse_iterator iter = modelValidator.GetValidationErrors().rbegin();
			iter < modelValidator.GetValidationErrors().rend(); iter++)
			errors << *iter << std::endl;

		throw std::invalid_argument(errors.str());
	}
}
