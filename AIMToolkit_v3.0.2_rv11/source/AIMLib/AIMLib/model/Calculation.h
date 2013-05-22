/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_B93F2FE1_A5C5_49b6_877B_C7476B5848A6__INCLUDED_)
#define EA_B93F2FE1_A5C5_49b6_877B_C7476B5848A6__INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API Calculation
	{
	public:
		Calculation();
		Calculation(const Calculation& calculation);
		Calculation& operator=(const Calculation& calculation);
		virtual ~Calculation();

		const std::string& GetUID() const;
		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		const std::string& GetDescription() const;
		const std::string& GetMathML() const;
		const std::string& GetAlgorithmName() const;
		const std::string& GetAlgorithmVersion() const;
		const CalcResultVector& GetCalculationResultCollection() const;
		const ReferencedCalcVector& GetReferencedCalculationCollection() const;
		const ReferencedGeometricShapeVector& GetReferencedGeometricShapeCollection() const;

		void SetUID(const std::string& newVal);
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetDescription(const std::string& newVal);
		void SetMathML(const std::string& newVal);
		void SetAlgorithmName(const std::string& newVal);
		void SetAlgorithmVersion(const std::string& newVal);
		void SetCalculationResultCollection(const CalcResultVector& calculationResults);
		void SetReferencedCalculationCollection(const ReferencedCalcVector& referencedCalculations);
		void SetReferencedGeometricShapeCollection(const ReferencedGeometricShapeVector& referencedGeoShapes);

	private:
		int _cagridId;
		std::string _uid;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		std::string _description;
		std::string _mathML;
		std::string _algorithmName;
		std::string _algorithmVersion;

		CalcResultVector _calculationResultCollection;
		ReferencedCalcVector _referencedCalculationCollection;
		ReferencedGeometricShapeVector _referencedGeoShapeCollection;

	};

	typedef std::vector<Calculation> CalculationVector;
}
#endif // !defined(EA_B93F2FE1_A5C5_49b6_877B_C7476B5848A6__INCLUDED_)
