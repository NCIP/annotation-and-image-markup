/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "DateTime.h"
#include "Image.h"
#include "ImageSeries.h"
#include "ImageStudy.h"

using namespace aim_lib;

ImageStudy::ImageStudy()
{
}

ImageStudy::ImageStudy(const ImageStudy& study)
{
	_cagridId		= study._cagridId;
	_instanceUID	= study._instanceUID;
	_startDate		= study._startDate;
	_startTime		= study._startTime;
	_series			= study._series;
}

ImageStudy::~ImageStudy()
{
}

const std::string& ImageStudy::GetInstanceUID() const
{
	return _instanceUID;
}

const Date& ImageStudy::GetStartDate() const
{
	return _startDate;
}

const Time& ImageStudy::GetStartTime() const
{
	return _startTime;
}

const ImageSeries& ImageStudy::GetSeries() const
{
	return _series;
}

void ImageStudy::SetInstanceUID(const std::string& newVal)
{
	_instanceUID = newVal;
}

void ImageStudy::SetSeries(const ImageSeries& series)
{
	_series = series;
}

void ImageStudy::SetStartDate(const Date& newVal)
{
	_startDate = newVal;
}

void ImageStudy::SetStartTime(const Time& newVal)
{
	_startTime = newVal;
}

const Image* ImageStudy::GetImage(const std::string &sopInstanceUID) const
{
	const ImageVector& imgVector = _series.GetImageCollection();
	for(ImageVector::const_iterator imageIter = imgVector.begin(); imageIter < imgVector.end(); imageIter++)
	{
		if (imageIter->GetSopInstanceUID() == sopInstanceUID)
			return &imageIter[0];
	}


	return NULL;
}
