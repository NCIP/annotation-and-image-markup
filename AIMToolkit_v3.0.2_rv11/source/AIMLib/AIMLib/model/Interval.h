/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLib_Interval_Class)
#define _AIMLib_Interval_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API Interval : public CharacteristicQuantification
	{
	public:
		Interval(void);
		Interval(const Interval& interval);
		virtual ~Interval(void);
		Interval& operator=(const Interval& interval);
		virtual Interval* Clone() const;

		double GetMinValue() const;
		double GetMaxValue() const;
		ComparisonOperatorType GetMinOperator() const;
		ComparisonOperatorType GetMaxOperator() const;
		const std::string& GetUcumString() const;
		void SetMinValue(double newVal);
		void SetMaxValue(double newVal);
		void SetMinOperator(ComparisonOperatorType newVal);
		void SetMaxOperator(ComparisonOperatorType newVal);
		void SetUcumString(const std::string& newVal);

	protected:
		double _minValue;
		double _maxValue;
		ComparisonOperatorType _minOperator;
		ComparisonOperatorType _maxOperator;
		std::string _ucumString;
	};
}
#endif // _AIMLib_Interval_Class
