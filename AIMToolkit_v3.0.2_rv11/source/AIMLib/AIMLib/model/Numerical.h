/*
  Classname: Numerical

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_Numerical_Class)
#define _AIMLib_Numerical_Class

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
#endif // _AIMLib_Numerical_Class