/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "ReferencedDicomObject.h"

#include "../memdebug.h"

using namespace aim_lib;
using namespace iso_21090;

ReferencedDicomObject::ReferencedDicomObject(void){
}

ReferencedDicomObject::ReferencedDicomObject(const ReferencedDicomObject& refDicomObject){
	*this = refDicomObject;
}

ReferencedDicomObject::~ReferencedDicomObject(void){
}

ReferencedDicomObject& ReferencedDicomObject::operator=(const ReferencedDicomObject& refDicomObject){
	if (this != &refDicomObject)
	{
		_modality		= refDicomObject._modality;
		_sopInstanceUid	= refDicomObject._sopInstanceUid;
	}
	return *this;
}

ReferencedDicomObject* ReferencedDicomObject::Clone() const{
	return new ReferencedDicomObject(*this);
}

const CD& ReferencedDicomObject::GetModality() const{
	return _modality;
}
const II& ReferencedDicomObject::GetSopInstanceUid() const{
	return _sopInstanceUid;
}

void ReferencedDicomObject::SetModality(const CD& newVal){
	_modality = newVal;
}

void ReferencedDicomObject::SetSopInstanceUid(const II& newVal){
	_sopInstanceUid = newVal;
}
