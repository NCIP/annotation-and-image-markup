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

#pragma once
#ifndef _AIMLib_external_CD
#define _AIMLib_external_CD

#include <string>
#include <vector>

namespace aim_lib
{
	namespace iso_21090
	{
		class AIMLIB_API CD
		{
		public:
			CD(void);
			CD(const std::string& codeValue, const std::string& codeMeaning, const std::string& codingSchemeDesignator, const std::string& codingSchemeVersion = "");
			CD(const CD& cd);
			virtual ~CD(void);

			CD& operator=(const CD& ii);
			bool operator==(const CD& ii) const;

			const std::string& GetCodeValue() const;
			const std::string& GetCodeMeaning() const;
			const std::string& GetCodingSchemeDesignator() const;
			const std::string& GetCodingSchemeVersion() const;

			void SetCodeValue(const std::string& newVal);
			void SetCodeMeaning(const std::string& newVal);
			void SetCodingSchemeDesignator(const std::string& newVal);
			void SetCodingSchemeVersion(const std::string& newVal);
		protected:
			std::string _codeValue;
			std::string _codeMeaning;
			std::string _codingSchemeDesignator;
			std::string _codingSchemeVersion;
		};

		typedef std::vector<CD> CDVector;
	}
}

#endif // _AIMLib_external_CD
