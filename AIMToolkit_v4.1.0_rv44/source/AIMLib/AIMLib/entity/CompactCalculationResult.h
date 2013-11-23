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
#ifndef _AIMLib_CompactCalculationResult_Class_
#define _AIMLib_CompactCalculationResult_Class_

#include <string>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API CompactCalculationResult : public CalculationResult
	{
	public:
		CompactCalculationResult();
		CompactCalculationResult(const CompactCalculationResult& calculationResult);
		CompactCalculationResult& operator=(const CompactCalculationResult& calculationResult);
		virtual CompactCalculationResult* Clone() const;
		virtual ~CompactCalculationResult();

		const std::string& GetValue() const;
		const iso_21090::CD* GetEncoding() const;
		const iso_21090::CD* GetCompression() const;

		void SetValue(const std::string& newVal);
		void SetEncoding(const iso_21090::CD* newVal);
		void SetCompression(const iso_21090::CD* newVale);

	protected:
		std::string _value;
		std::auto_ptr<iso_21090::CD> _encoding;
		std::auto_ptr<iso_21090::CD> _compression;
	};
}
#endif // _AIMLib_CompactCalculationResult_Class_
