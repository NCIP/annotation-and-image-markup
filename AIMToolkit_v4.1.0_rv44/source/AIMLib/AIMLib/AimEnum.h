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

#if !defined(_AIMLIB_AIM_ENUM_INCLUDED_)
#define _AIMLIB_AIM_ENUM_INCLUDED_

#include <string>
#include <map>

namespace aim_lib
{
	enum AIMLIB_API AimVersion
	{
		AIMv1_0,
		AIMv2_0,
		AIMv3_0_1,
		AIMv3_0_2,
		AIMv4_0
	};

	enum AIMLIB_API ComparisonOperatorType
	{
		InvalidComparisonOperatorType = -1,
		None = 0,
		Equal = 1,
		NotEqual = 2,
		LessThan = 3,
		LessThanEqual = 4,
		GreaterThan = 5,
		GreaterThanEqual = 6
	};

	class AIMLIB_API AimEnum
	{
	public:
		static const std::string ComparisonOperatorTypeToString(const ComparisonOperatorType& type);
		static const ComparisonOperatorType StringToComparisonOperatorType(const std::string& stringType);

		static const std::string GetAimVersionString(AimVersion aimVersion);

	protected:
		AimEnum();
	};
}
#endif // !define(_AIMLIB_AIM_ENUM_INCLUDED_)
