/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"
#include "Entity.h"
#include "SegmentationEntity.h"

using namespace aim_lib;

SegmentationEntity::SegmentationEntity(void) : Entity(){
}

SegmentationEntity::SegmentationEntity(const SegmentationEntity& segmentationEnity) : Entity(segmentationEnity){
	*this = segmentationEnity;
}

SegmentationEntity& SegmentationEntity::operator=(const SegmentationEntity &segmentationEntity){
	if (this != &segmentationEntity)
	{
		Entity::operator=(segmentationEntity);
	}
	return *this;
}

SegmentationEntity::~SegmentationEntity(void){
}
