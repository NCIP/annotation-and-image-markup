/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
