/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "AimBase.h"
#include "ReferencedGeometricShape.h"
#include "CharacteristicQuantification.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingObservation.h"
#include "Segmentation.h"

using namespace aim_lib;

Segmentation::Segmentation(){
}

Segmentation::Segmentation(const Segmentation& segmentation){
	*this = segmentation;
}

Segmentation& Segmentation::operator= (const Segmentation &segmentation){
	_cagridId					= segmentation._cagridId;
	_sopInstanceUID				= segmentation._sopInstanceUID;
	_sopClassUID				= segmentation._sopClassUID;
	_referencedSopInstanceUID	= segmentation._referencedSopInstanceUID;
	_segmentNumber				= segmentation._segmentNumber;
	
	this->SetImagingObservation(segmentation.GetImagingObservation());

	return *this;
}

Segmentation::~Segmentation(){
}

const std::string& Segmentation::GetSopInstanceUID() const{
	return _sopInstanceUID;
}

const std::string& Segmentation::GetSopClassUID() const{
	return _sopClassUID;
}

const std::string& Segmentation::GetReferencedSopInstanceUID() const{
	return _referencedSopInstanceUID;
}

int Segmentation::GetSegmentNumber() const{
	return _segmentNumber;
}

const ImagingObservation* Segmentation::GetImagingObservation() const{
	return _imagingObservation.get();
}

void Segmentation::SetSopInstanceUID(const std::string& newVal){
	_sopInstanceUID = newVal;
}

void Segmentation::SetSopClassUID(const std::string& newVal){
	_sopClassUID = newVal;
}

void Segmentation::SetReferencedSopInstanceUID(const std::string& newVal){
	_referencedSopInstanceUID = newVal;
}

void Segmentation::SetSegmentNumber(int newVal){
	_segmentNumber = newVal;
}

void Segmentation::SetImagingObservation(const ImagingObservation* pImagingObservation){
	if (pImagingObservation == NULL)
		_imagingObservation.reset();
	else
		_imagingObservation.reset(pImagingObservation->Clone());
}
