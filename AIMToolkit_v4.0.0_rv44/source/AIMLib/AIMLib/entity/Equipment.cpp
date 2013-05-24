/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Equipment.h"

#include "../memdebug.h"

using namespace aim_lib;

Equipment::Equipment() {
}

Equipment::Equipment(const Equipment& equipment) {
	_manufacturerName		= equipment._manufacturerName;
	_manufacturerModelName	= equipment._manufacturerModelName;
	_softwareVersion		= equipment._softwareVersion;
	_deviceSerialNumber		= equipment._deviceSerialNumber;
}

Equipment::~Equipment() {
}

Equipment* Equipment::Clone() const {
	return new Equipment(*this);
}

const std::string& Equipment::GetManufacturerName() const {
	return _manufacturerName;
}

const std::string& Equipment::GetManufacturerModelName() const {
	return _manufacturerModelName;
}

const std::string& Equipment::GetSoftwareVersion() const {
	return _softwareVersion;
}

const std::string& Equipment::GetDeviceSerialNumber() const {
	return _deviceSerialNumber;
}

void Equipment::SetManufacturerName(const std::string& newVal) {
	_manufacturerName = newVal;
}

void Equipment::SetManufacturerModelName(const std::string& newVal) {
	_manufacturerModelName = newVal;
}

void Equipment::SetSoftwareVersion(const std::string& newVal) {
	_softwareVersion = newVal;
}

void Equipment::SetDeviceSerialNumber(const std::string& newVal) {
	_deviceSerialNumber = newVal;
}
