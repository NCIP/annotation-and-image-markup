/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


// DCMTK debug helper classes. These classes are used in debug builds instead of the 
// standard DCMTK counterparts.

#include "dcmtk/ofstd/ofcond.h"

#include "AimResultValidator.h"

using namespace aim_lib;

#ifdef _DEBUG

AimOFCondition::AimOFCondition() : _condition(EC_Normal){
}

AimOFCondition::AimOFCondition(const OFCondition& ofCondition) : _condition(ofCondition){
	assert(_condition.good());
}

AimOFCondition::~AimOFCondition(void){
}

AimOFNode::AimOFNode(){
	_nodeId = (size_t)-1;
}

AimOFNode::AimOFNode(size_t nodeId){
	_nodeId = nodeId;
	assert(_nodeId > 0);
}

AimOFNode::~AimOFNode(void){
}

#endif
