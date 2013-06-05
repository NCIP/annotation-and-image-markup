/*
  Classname: CharacteristicQuantification

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_CharacteristicQuantification_Class)
#define _AIMLib_CharacteristicQuantification_Class

#include <memory>
#include <string>
#include <vector>

namespace aim_lib
{
// NOTE: These are internal library definitions and should be treated as such
#define C_QUANTIFICATION_NUMERICAL_NAME			std::string("Numerical")
#define C_QUANTIFICATION_QUANTILE_NAME			std::string("Quantile")
#define C_QUANTIFICATION_NON_QUANTIFIABLE_NAME	std::string("NonQuantifiable")
#define C_QUANTIFICATION_SCALE_NAME				std::string("Scale")
#define C_QUANTIFICATION_INTERVAL_NAME			std::string("Interval")

	class AIMLIB_API CharacteristicQuantification : public AimBase
	{
	public:
		enum E_QuantificationType
		{
			QT_Numerical,
			QT_Quantile,
			QT_Non_Quantifiable,
			QT_Scale,
			QT_Interval,
			QT_Unknown = -1,
		};

	public:
		virtual ~CharacteristicQuantification(void);
		CharacteristicQuantification& operator=(const CharacteristicQuantification& quantification);
		virtual CharacteristicQuantification* Clone() const = 0;

		const std::string& GetName() const;
		double* GetAnnotatorConfidence() const;
		void SetName(const std::string& newVal);
		void SetAnnotatorConfidence(double* newVal);

		const E_QuantificationType GetQuantificationType() const;

	protected:
		CharacteristicQuantification(const std::string& typeName);
		CharacteristicQuantification(const CharacteristicQuantification& quantification);

		int _cagridId;
		std::string _name;
		std::auto_ptr<double> _annotatorConfidence;
	};
	
	typedef std::vector<CharacteristicQuantification*> CharacteristicQuantificationPtrVector;

}
#endif // _AIMLib_CharacteristicQuantification_Class
