/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLIB_AIM_ENUM_INCLUDED_)
#define _AIMLIB_AIM_ENUM_INCLUDED_

#include <string>

namespace aim_lib
{
	enum AIMLIB_API CalculationResultType
	{
		InvalidCalculationResultType = -1,
		Scalar = 0,
		Vector = 1,
		Histogram = 2,
		Matrix = 3,
		Array = 4
	};

	enum AIMLIB_API ComparisonOperatorType
	{
		InvalidComparisonOperatorType = -1,
		None = 0,
		Equal = 1,
		NotEqual = 2,
		LessThan = 3,
		LessThanEqual = 4,
		GreaterThan = 5,
		GreaterThanEqual = 6
	};

	class AIMLIB_API AimEnum
	{
	public:
		static const std::string ComparisonOperatorTypeToString(const ComparisonOperatorType& type);
		static const ComparisonOperatorType StringToComparisonOperatorType(const std::string& stringType);

	protected:
		AimEnum();
	};
}
#endif // !define(_AIMLIB_AIM_ENUM_INCLUDED_)
