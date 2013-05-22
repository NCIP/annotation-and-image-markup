/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "AimBase.h"
#include "DateTime.h"
#include "ImageReference.h"
#include "Image.h"
#include "ImageSeries.h"
#include "ImageStudy.h"
#include "PresentationState.h"
#include "DICOMImageReference.h"

#include "../memdebug.h"

using namespace aim_lib;

DICOMImageReference::DICOMImageReference() : ImageReference(C_DICOM_IMAGE_NAME){

}

DICOMImageReference::DICOMImageReference(const DICOMImageReference& imageReference) : ImageReference (imageReference){
	
	_study	 = imageReference._study;

	SetPresentationStateCollection(imageReference.GetPresentationStateCollection());
}

DICOMImageReference::~DICOMImageReference(){

}

ImageReference* DICOMImageReference::Clone() const{
	return new DICOMImageReference(*this);
}

const ImageStudy& DICOMImageReference::GetStudy() const{

	return _study;
}

const PresentationStateVector& DICOMImageReference::GetPresentationStateCollection() const{
	return _presentationStateCollection;
}

void DICOMImageReference::SetStudy(const ImageStudy& study){

	_study = study;
}

void DICOMImageReference::SetPresentationStateCollection(const PresentationStateVector& presentationStates)
{
	_presentationStateCollection.assign(presentationStates.begin(), presentationStates.end());
}
