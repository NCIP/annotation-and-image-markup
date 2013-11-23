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
