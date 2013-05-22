/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_0C674ED5_7DF6_4921_A6FA_D30AFDE3161F__INCLUDED_)
#define EA_0C674ED5_7DF6_4921_A6FA_D30AFDE3161F__INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API CalculationResult
	{

	public:
		CalculationResult();
		CalculationResult(const CalculationResult& calculationResult);
		CalculationResult& operator=(const CalculationResult& calculationResult);
		virtual ~CalculationResult();

		CalculationResultType GetType() const;
		int GetNumberOfDimensions() const;
		const std::string& GetUnitOfMeasure() const;
		const DimensionVector& GetDimensionCollection() const;
		const CalculationDataVector& GetCalculationDataCollection() const;

		void SetType(CalculationResultType newVal);
		void SetUnitOfMeasure(const std::string& newVal);
		void SetNumberOfDimensions(int newVal);
		void SetDimensionCollection(const DimensionVector& dimensionCollection);
		void SetCalculationDataCollection(const CalculationDataVector& dataCollection);

		static const std::string CalculationResultTypeToString(const CalculationResultType& type);
		static const CalculationResultType StringToCalculationResultType(const std::string& stringType);

	protected:
		int _cagridId;
		CalculationResultType _type;
		int _numberOfDimensions;
		std::string _unitOfMeasure;

		DimensionVector _dimensionCollection;
		CalculationDataVector _calculationDataCollection;
	};

	typedef std::vector<CalculationResult> CalcResultVector;
}
#endif // !defined(EA_0C674ED5_7DF6_4921_A6FA_D30AFDE3161F__INCLUDED_)
