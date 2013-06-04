/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
