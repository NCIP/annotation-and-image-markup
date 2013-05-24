/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "AimUidGenerator.h"

#include "dcmtk/dcmdata/dcuid.h" // old
#include "dcmtk/ofstd/ofuuid.h"  // new

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
std::string AimUidGenerator::GenerateNewUid(const std::string& prefix)
{
	if (prefix.empty())
	{
		// DCMTK 3.6.1 feature: use OFUUID class with ER_RepresentationOID representation
		OFUUID ofUid;

		std::string newUid;
		ofUid.toString(newUid, OFUUID::ER_RepresentationOID);
		return newUid;
	}
	else
	{
		char buf[70];  // UID is 64 chars or less

		return dcmGenerateUniqueIdentifier(buf, prefix.c_str());
	}
}
