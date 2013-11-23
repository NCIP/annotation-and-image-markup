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

#include "II.h"

#include "../util/AimUidGenerator.h"

#include <sstream>

using namespace aim_lib::iso_21090;

II::II(void){
}

II::II(const std::string& uid){
	_uid = uid;
}

II::II(const II& ii){
	*this = ii;
}

II::~II(void){
}

II& II::operator=(const II& ii){
	if (this != &ii) {
		// TODO - copy class members
		_uid = ii._uid;
	}

	return *this;
}

bool II::operator==(const II& ii) const{
	// TODO - proper comparison
	return _uid == ii._uid;
}

bool II::operator!=(const II& ii) const{
	return !operator==(ii);
}

const std::string II::toString() const{
	std::stringstream sstream;
	//sstream << *this;
	sstream << _uid;

	return sstream.str();
}

const II II::generate(bool createUid /*= true*/){
	if (createUid)
		return II(aim_lib::AimUidGenerator::GenerateNewUid());

	return II();
}

//std::ostream& operator<<(std::ostream &strm, const II& ii) {
//	return strm << ii._uid;
//}
