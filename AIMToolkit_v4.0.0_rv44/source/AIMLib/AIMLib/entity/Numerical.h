/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_Numerical_Class_
#define _AIMLib_Numerical_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API Numerical : public CharacteristicQuantification
	{
	public:
		Numerical(void);
		Numerical(const Numerical& numerical);
		virtual ~Numerical(void);
		Numerical& operator=(const Numerical& numerical);
		virtual Numerical* Clone() const;

		const QuantificationType GetQuantificationType() const;

		double GetValue() const;
		const std::string& GetUcumString() const;
		ComparisonOperatorType GetOperator() const;
		void SetValue(double newVal);
		void SetUcumString(const std::string& newVal);
		void SetOperator(ComparisonOperatorType newVal);

	protected:
		double _value;
		std::string _ucumString;
		ComparisonOperatorType _operator;
	};
}
#endif // _AIMLib_Numerical_Class_