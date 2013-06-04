/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "AimUidGenerator.h"

#include "dcmtk/dcmdata/dcuid.h"

using namespace aim_lib;

AimUidGenerator::AimUidGenerator(void)
{
}

AimUidGenerator::~AimUidGenerator(void)
{
}

/**
 Generates new DICOM UID.
 prefix - vendor-assigned UID prefix.
*/
std::string AimUidGenerator::GenerateNewUID(const std::string& prefix)
{
	char buf[70];  // UID is 64 chars or less

	return dcmGenerateUniqueIdentifier(buf, prefix.c_str());
}
