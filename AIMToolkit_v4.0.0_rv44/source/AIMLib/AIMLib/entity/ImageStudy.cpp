/*
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

using namespace aim_lib;
using iso_21090::II;

ImageStudy::ImageStudy(){
}

ImageStudy::ImageStudy(const ImageStudy& imageStudy){
	_instanceUid			= imageStudy._instanceUid;
	_startDate				= imageStudy._startDate;
	_startTime				= imageStudy._startTime;
	_procedureDecription	= imageStudy._procedureDecription;
	_imageSeries			= imageStudy._imageSeries;
	SetReferencedDicomObjectCollection(imageStudy.GetReferencedDicomObjectCollection());
}

ImageStudy::~ImageStudy(){
}

const II& ImageStudy::GetInstanceUid() const{
	return _instanceUid;
}

const Date& ImageStudy::GetStartDate() const{
	return _startDate;
}

const Time& ImageStudy::GetStartTime() const{
	return _startTime;
}

const std::string& ImageStudy::GetProceduDescription() const{
	return _procedureDecription;
}

const ImageSeries& ImageStudy::GetImageSeries() const{
	return _imageSeries;
}

const ReferencedDicomObjectVector& ImageStudy::GetReferencedDicomObjectCollection() const{
	return _referencedDicomObjectCollection;
}

void ImageStudy::SetInstanceUid(const II& newVal){
	_instanceUid = newVal;
}

void ImageStudy::SetStartDate(const Date& newVal){
	_startDate = newVal;
}

void ImageStudy::SetStartTime(const Time& newVal){
	_startTime = newVal;
}

void ImageStudy::SetProcedureDescription(const std::string& newVal){
	_procedureDecription = newVal;
}

void ImageStudy::SetImageSeries(const ImageSeries& imageSeries){
	_imageSeries = imageSeries;
}

void ImageStudy::SetReferencedDicomObjectCollection(const ReferencedDicomObjectVector& referencedDicomObjects){
	_referencedDicomObjectCollection.assign(referencedDicomObjects.begin(), referencedDicomObjects.end());
}

const Image* ImageStudy::GetImage(const II& sopInstanceUid) const{
	const ImageVector& imgVector = _imageSeries.GetImageCollection();
	for(ImageVector::const_iterator imageIter = imgVector.begin(); imageIter < imgVector.end(); imageIter++)
	{
		if (imageIter->GetSopInstanceUid() == sopInstanceUid)
			return &imageIter[0];
	}

	return NULL;
}
