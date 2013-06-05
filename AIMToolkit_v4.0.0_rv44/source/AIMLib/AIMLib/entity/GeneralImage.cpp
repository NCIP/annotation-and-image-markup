/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "GeneralImage.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

GeneralImage::GeneralImage(void){
}

GeneralImage::GeneralImage(const GeneralImage& generalImage){
	*this = generalImage;
}

GeneralImage::~GeneralImage(void){
}

GeneralImage& GeneralImage::operator=(const GeneralImage& generalImage){
	if (this != &generalImage)
	{
		_patientOrientationColumn	= generalImage._patientOrientationColumn;
		_patientOrientationRow		= generalImage._patientOrientationRow;
	}
	return *this;
}

GeneralImage* GeneralImage::Clone() const{
	return new GeneralImage(*this);
}

const string& GeneralImage::GetPatientOrientationColumn() const{
	return _patientOrientationColumn;
}

const string& GeneralImage::GetPatientOrientationRow() const{
	return _patientOrientationRow;
}

void GeneralImage::SetPatientOrientationColumn(const string& newVal){
	_patientOrientationColumn = newVal;
}

void GeneralImage::SetPatientOrientationRow(const string&  newVal){
	_patientOrientationRow = newVal;
}
