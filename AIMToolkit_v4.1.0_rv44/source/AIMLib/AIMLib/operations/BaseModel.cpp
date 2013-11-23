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