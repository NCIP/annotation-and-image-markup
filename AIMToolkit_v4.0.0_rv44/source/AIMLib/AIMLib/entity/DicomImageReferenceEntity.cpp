/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "../util/DateTime.h"
#include "ReferencedDicomObject.h"
#include "GeneralImage.h"
#include "ImagePlane.h"
#include "Image.h"
#include "ImageSeries.h"
#include "ImageStudy.h"
#include "Entity.h"
#include "ImageReferenceEntity.h"
#include "DicomImageReferenceEntity.h"

#include "../memdebug.h"

using namespace aim_lib;

DicomImageReferenceEntity::DicomImageReferenceEntity() : ImageReferenceEntity(C_DICOM_IMAGE_REFERENCE_NAME){
}

DicomImageReferenceEntity::DicomImageReferenceEntity(const DicomImageReferenceEntity& imageReference) : ImageReferenceEntity(imageReference){
	_imageStudy	= imageReference._imageStudy;
}

DicomImageReferenceEntity::~DicomImageReferenceEntity(){
}

DicomImageReferenceEntity* DicomImageReferenceEntity::Clone() const{
	return new DicomImageReferenceEntity(*this);
}

ImageReferenceEntity::ImageReferenceEntityType DicomImageReferenceEntity::GetImageReferenceEntityType() const{
	return T_DICOM_IMAGE_REF;
}

const ImageStudy& DicomImageReferenceEntity::GetImageStudy() const{
	return _imageStudy;
}

void DicomImageReferenceEntity::SetImageStudy(const ImageStudy& study){
	_imageStudy = study;
}
