/*
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
#include "WebImageReference.h"

using std::string;
using namespace aim_lib;

ImageReference::ImageReference(const std::string& typeName) : AimBase(typeName){

}

ImageReference::ImageReference(const ImageReference& imageReference) : AimBase(imageReference){
	_cagridId = imageReference._cagridId;
}

ImageReference::~ImageReference(){

}

ImageReference::ImageReferenceType ImageReference::GetImageReferenceType() const
{
	if (dynamic_cast<const DICOMImageReference*>(this) != NULL)
		return T_DICOM_IMAGE_REF;

	if (dynamic_cast<const WebImageReference*>(this) != NULL)
		return T_WEB_IMAGE_REF;

	return T_UNDEFINED_IMAGE_REF;
}
