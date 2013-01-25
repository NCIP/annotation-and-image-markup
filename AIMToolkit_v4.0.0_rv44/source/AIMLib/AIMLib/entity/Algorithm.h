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
#ifndef _AIMLib_Algorithm_Class_
#define _AIMLib_Algorithm_Class_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API Algorithm
	{
	public:
		Algorithm(void);
		Algorithm(const Algorithm& algorithm);
		virtual ~Algorithm(void);

		const std::string& GetName() const;
		const iso_21090::CDVector& GetType() const;
		const iso_21090::II* GetUniqueIdentifier() const;
		const std::string& GetVersion() const;
		const std::string& GetDescription() const;
		const ParameterVector& GetParameterCollection() const;

		void SetName(const std::string& newVal);
		void SetType(const iso_21090::CDVector& newVal);
		void SetUniqueIdentifier(const iso_21090::II* newVal);
		void SetVersion(const std::string& newVal);
		void SetDescription(const std::string& newVal);
		void SetParameterCollection(const ParameterVector& parameters);
	protected:
		std::string _name;
		iso_21090::CDVector _type;
		std::auto_ptr<iso_21090::II> _uniqueIdentifier;
		std::string _version;
		std::string _description;

		ParameterVector _parameterCollection;
	};
}
#endif // _AIMLib_Algorithm_Class_