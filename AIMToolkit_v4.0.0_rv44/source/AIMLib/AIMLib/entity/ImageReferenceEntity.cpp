/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Entity.h"
#include "ImageReferenceEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

ImageReferenceEntity::ImageReferenceEntity(const std::string& typeName) : Entity(){
}

ImageReferenceEntity::ImageReferenceEntity(const ImageReferenceEntity& imageReference) : Entity(imageReference){
}

ImageReferenceEntity::~ImageReferenceEntity(){
}
