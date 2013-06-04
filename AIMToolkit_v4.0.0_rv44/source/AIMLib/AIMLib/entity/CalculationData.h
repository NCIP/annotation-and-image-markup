/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_CalculationData_Class_
#define _AIMLib_CalculationData_Class_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API CalculationData
	{
	public:
		CalculationData();
		CalculationData(const CalculationData& data);
		CalculationData& operator=(const CalculationData& data);
		virtual ~CalculationData();

		const std::string& GetValue() const;
		const CoordinateVector& GetCoordinateCollection() const;

		void SetValue(const std::string& newValue);
		void SetCoordinateCollection(const CoordinateVector& coordinateCollection);

	private:
		std::string _value;

		CoordinateVector _coordinateCollection;
	};
	
	typedef std::vector<CalculationData> CalculationDataVector;
}
#endif // _AIMLib_CalculationData_Class_
