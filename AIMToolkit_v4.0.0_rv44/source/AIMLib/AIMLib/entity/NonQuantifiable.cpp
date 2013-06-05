/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "CharacteristicQuantification.h"
#include "NonQuantifiable.h"

#include "../memdebug.h"

using namespace aim_lib;
using iso_21090::CD;

NonQuantifiable::NonQuantifiable(void) : CharacteristicQuantification(C_QUANTIFICATION_NON_QUANTIFIABLE_NAME){
}

NonQuantifiable::NonQuantifiable(const NonQuantifiable& nonQuantifiable) : CharacteristicQuantification(nonQuantifiable){
	*this = nonQuantifiable;
}

NonQuantifiable::~NonQuantifiable(void){
}

NonQuantifiable& NonQuantifiable::operator=(const NonQuantifiable& nonQuantifiable){
	if (this != &nonQuantifiable)
	{
		CharacteristicQuantification::operator=(nonQuantifiable);
		_typeCode = nonQuantifiable._typeCode;
	}
	return *this;
}

NonQuantifiable* NonQuantifiable::Clone() const{
	return new NonQuantifiable(*this);
}

const CharacteristicQuantification::QuantificationType NonQuantifiable::GetQuantificationType() const{
	return QT_Non_Quantifiable;
}

const CD& NonQuantifiable::GetTypeCode() const{
	return _typeCode;
}

void NonQuantifiable::SetTypeCode(const CD& newVal){
	_typeCode = newVal;
}
