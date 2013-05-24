/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

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
