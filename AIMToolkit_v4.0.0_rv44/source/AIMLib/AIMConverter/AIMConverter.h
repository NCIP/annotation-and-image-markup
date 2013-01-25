/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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