/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "AimBase.h"

using namespace aim_lib;

AimBase::AimBase(const std::string& typeName)
{
	_typeName = typeName;
}

AimBase::AimBase(const AimBase& aimObj)
{
	_typeName = aimObj._typeName;
}

AimBase::~AimBase(void)
{
}

const std::string& AimBase::GetTypeName() const
{
	return _typeName;
}
