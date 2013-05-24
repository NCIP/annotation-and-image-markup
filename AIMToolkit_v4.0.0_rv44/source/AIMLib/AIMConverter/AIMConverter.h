/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _AIMConverter_AIMConverter_Class
#define _AIMConverter_AIMConverter_Class

#include <string>

// AIM includes
#include "../AIMLib/AIMCommon.h"
#include "../AIMLib/AimHeaders.h"

#include "../AIMLib/Operations/BaseModel.h"
#include "../AIMLib/Operations/DcmModel.h"
#include "../AIMLib/Operations/XmlModel.h"

class AIMConverter
{
public:
	enum AIM_FILE_TYPE
	{
		AFT_AIM_XML,
		AFT_DICOM_SR,
		AFT_HL7_CDA,
		AFT_UNKNOWN
	};

	AIMConverter();
	~AIMConverter();

	std::string DoConversion(const std::string& inFileName, AIM_FILE_TYPE inFileType, const std::string& outFileName, AIM_FILE_TYPE outFileType);

protected:

	std::string CreateModel(AIM_FILE_TYPE modelType, aim_lib::BaseModel** pModel);

};

#endif // _AIMConverter_AIMConverter_Class