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
#ifndef _AIMLib_CalculationEntity_Class_
#define _AIMLib_CalculationEntity_Class_

#include <string>
#include <memory>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API CalculationEntity : public Entity
	{
	public:
		CalculationEntity();
		CalculationEntity(const CalculationEntity& calculationEntity);
		CalculationEntity& operator=(const CalculationEntity& calculationEntity);
		virtual ~CalculationEntity();

		const iso_21090::CDVector& GetTypeCode() const;
		const iso_21090::CDVector& GetQuestionTypeCode() const;
		const std::string& GetDescription() const;
		const std::string& GetMathML() const;
		int GetQuestionIndex() const;
		const Algorithm* GetAlgorithm() const;
		const CalculationResultPtrVector& GetCalculationResultCollection() const;

		void SetTypeCode(const iso_21090::CDVector& newVal);
		void SetQuestionTypeCode(const iso_21090::CDVector& newVal);
		void SetDescription(const std::string& newVal);
		void SetMathML(const std::string& newVal);
		void SetQuestionIndex(int newVal);
		void SetAlgorithm(const Algorithm* newVal);
		void SetCalculationResultCollection(const CalculationResultPtrVector& calculationResults);

	private:
		iso_21090::CDVector _typeCode;
		iso_21090::CDVector _questionTypeCode;
		std::string _description;
		std::string _mathML;
		int _questionIndex;
		std::auto_ptr<Algorithm> _algorithm;

		CalculationResultPtrVector _calculationResultCollection;
	};

	typedef std::vector<CalculationEntity> CalculationEntityVector;
}
#endif // _AIMLib_CalculationEntity_Class_
