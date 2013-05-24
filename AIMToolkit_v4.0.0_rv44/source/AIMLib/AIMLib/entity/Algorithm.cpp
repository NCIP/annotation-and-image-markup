/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/


#include "../stdafx.h"
#include "Parameter.h"
#include "Algorithm.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

Algorithm::Algorithm(void){
}

Algorithm::Algorithm(const Algorithm& algorithm){
	_name			= algorithm._name;
	_version		= algorithm._version;
	_description	= algorithm._description;
	SetType(algorithm.GetType());
	SetUniqueIdentifier(algorithm.GetUniqueIdentifier());
	SetParameterCollection(algorithm.GetParameterCollection());
}

Algorithm::~Algorithm(void){
}

const string& Algorithm::GetName() const {
	return _name;
}

const CDVector& Algorithm::GetType() const {
	return _type;
}

const II* Algorithm::GetUniqueIdentifier() const {
	return _uniqueIdentifier.get();
}

const string& Algorithm::GetVersion() const {
	return _version;
}

const string& Algorithm::GetDescription() const{
	return _description;
}

const ParameterVector& Algorithm::GetParameterCollection() const{
	return _parameterCollection;
}

void Algorithm::SetName(const std::string& newVal){
	_name = newVal;
}

void Algorithm::SetType(const iso_21090::CDVector& newVal){
	_type.assign(newVal.begin(), newVal.end());
}

void Algorithm::SetUniqueIdentifier(const iso_21090::II* newVal){
	_uniqueIdentifier.reset(newVal ? new II(*newVal) : NULL);
}

void Algorithm::SetVersion(const std::string& newVal){
	_version = newVal;
}

void Algorithm::SetDescription(const std::string& newVal){
	_description = newVal;
}

void Algorithm::SetParameterCollection(const ParameterVector& parameters){
	_parameterCollection.assign(parameters.begin(), parameters.end());
}
