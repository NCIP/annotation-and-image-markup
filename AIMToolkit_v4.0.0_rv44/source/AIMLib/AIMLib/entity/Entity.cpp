/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "Entity.h"

#include "../memdebug.h"

using namespace aim_lib;

Entity::Entity() : _uniqueIdentifier(iso_21090::II::generate()){
}

Entity::Entity(const Entity& entity){
	*this = entity;
}

Entity& Entity::operator=(const Entity& entity){
	if (this != &entity)
	{
		_uniqueIdentifier = entity._uniqueIdentifier;
	}
	return *this;
}

Entity::~Entity(void){
}

const iso_21090::II Entity::GetUniqueIdentifier() const{
	return _uniqueIdentifier;
}

void Entity::SetUniqueIdentifier(const iso_21090::II& uniqueIdentifier){
	_uniqueIdentifier = uniqueIdentifier;
}
