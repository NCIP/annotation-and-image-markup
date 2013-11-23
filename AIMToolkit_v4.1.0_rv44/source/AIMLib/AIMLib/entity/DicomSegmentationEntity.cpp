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
#include "Entity.h"
#include "SegmentationEntity.h"
#include "DicomSegmentationEntity.h"

using namespace aim_lib;
using iso_21090::II;

DicomSegmentationEntity::DicomSegmentationEntity(void) : SegmentationEntity(){
}

DicomSegmentationEntity::DicomSegmentationEntity(const DicomSegmentationEntity& segmentationEnity) : SegmentationEntity(segmentationEnity){
	*this = segmentationEnity;
}

DicomSegmentationEntity& DicomSegmentationEntity::operator=(const DicomSegmentationEntity& segmentationEntity){
	if (this != &segmentationEntity)
	{
		SegmentationEntity::operator=(segmentationEntity);
		_sopInstanceUid				= segmentationEntity._sopInstanceUid;
		_sopClassUid				= segmentationEntity._sopClassUid;
		_referencedSopInstanceUid	= segmentationEntity._referencedSopInstanceUid;
		_segmentNumber				= segmentationEntity._segmentNumber;
	}
	return *this;
}

DicomSegmentationEntity* DicomSegmentationEntity::Clone() const{
	return new DicomSegmentationEntity(*this);
}

DicomSegmentationEntity::~DicomSegmentationEntity(void){
}

const II& DicomSegmentationEntity::GetSopInstanceUid() const{
	return _sopInstanceUid;
}

const II& DicomSegmentationEntity::GetSopClassUid() const{
	return _sopClassUid;
}

const II& DicomSegmentationEntity::GetReferencedSopInstanceUid() const{
	return _referencedSopInstanceUid;
}

int DicomSegmentationEntity::GetSegmentNumber() const{
	return _segmentNumber;
}

void DicomSegmentationEntity::SetSopInstanceUid(const II& newVal){
	_sopInstanceUid = newVal;
}

void DicomSegmentationEntity::SetSopClassUid(const II& newVal){
	_sopClassUid = newVal;
}

void DicomSegmentationEntity::SetReferencedSopInstanceUid(const II& newVal){
	_referencedSopInstanceUid = newVal;
}

void DicomSegmentationEntity::SetSegmentNumber(int newVal){
	_segmentNumber = newVal;
}
