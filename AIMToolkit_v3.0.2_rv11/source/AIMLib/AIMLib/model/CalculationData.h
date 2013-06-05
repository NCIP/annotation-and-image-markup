/*
  Classname: CalculationData

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_CALCULATION_DATA_INCLUDED_)
#define _AIMLib_CALCULATION_DATA_INCLUDED_

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

		double GetValue() const;
		const CoordinateVector& GetCoordinateCollection() const;

		void SetValue(double newValue);
		void SetCoordinateCollection(const CoordinateVector& coordinateCollection);

	private:
		int _cagridId;
		double _value;

		CoordinateVector _coordinateCollection;
	};
	
	typedef std::vector<CalculationData> CalculationDataVector;
}
#endif // !defined(_AIMLib_CALCULATION_DATA_INCLUDED_)
