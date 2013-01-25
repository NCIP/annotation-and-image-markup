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
#ifndef _AIMLib_CalculationResult_Class_
#define _AIMLib_CalculationResult_Class_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API CalculationResult
	{
	public:
		enum CalculationResultType
		{
			InvalidCalculationResultType = -1,
			Scalar = 0,
			Vector = 1,
			Histogram = 2,
			Matrix = 3,
			Array = 4,
			Binary = 5 // Very special case. You should probably not use it.
		};

	public:
		CalculationResult& operator=(const CalculationResult& calculationResult);
		virtual CalculationResult* Clone() const = 0;
		virtual ~CalculationResult();

		CalculationResultType GetType() const;
		const std::string& GetUnitOfMeasure() const;
		const iso_21090::CD& GetDataType() const;
		const DimensionVector& GetDimensionCollection() const;

		void SetType(CalculationResultType newVal);
		void SetUnitOfMeasure(const std::string& newVal);
		void SetDataType(const iso_21090::CD& newVal);
		void SetDimensionCollection(const DimensionVector& dimensionCollection);

		static const std::string CalculationResultTypeToString(const CalculationResultType& type);
		static const CalculationResultType StringToCalculationResultType(const std::string& stringType);

	protected:
		CalculationResult();
		CalculationResult(const CalculationResult& calculationResult);

		CalculationResultType _type;
		iso_21090::CD _dataType;
		std::string _unitOfMeasure;

		DimensionVector _dimensionCollection;
	};

	typedef std::vector<CalculationResult*> CalculationResultPtrVector;
}
#endif // _AIMLib_CalculationResult_Class_
