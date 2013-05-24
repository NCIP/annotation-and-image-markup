/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_CharacteristicQuantification_Class_
#define _AIMLib_CharacteristicQuantification_Class_

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

	class AIMLIB_API CharacteristicQuantification
	{
	public:
		enum QuantificationType
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

		const std::string& GetLabel() const;
		double* GetAnnotatorConfidence() const;
		int GetCharacteristicQuantificationIndex() const;
		const std::string& GetQuantificationTypeName() const;
		const std::string& GetValueLabel() const;
		const std::string& GetValueDescription() const;
		const std::string& GetComment() const;

		void SetLabel(const std::string& newVal);
		void SetAnnotatorConfidence(double* newVal);
		void SetCharacteristicQuantificationIndex(int newVal);
		void SetValueLabel(const std::string& newVal);
		void SetValueDescription(const std::string& newVal);
		void SetComment(const std::string& newVal);

		virtual const QuantificationType GetQuantificationType() const = 0;

	protected:
		CharacteristicQuantification(const std::string& typeName);
		CharacteristicQuantification(const CharacteristicQuantification& quantification);

		std::string _label;
		std::auto_ptr<double> _annotatorConfidence;
		std::string _quantificationTypeName; // name of the specified quantification. one of the names from the defined list above.
		int _characteristicQuantificationIndex; // default: -1
		std::string _valueLabel;
		std::string _valueDescription;
		std::string _comment;
	};
	
	typedef std::vector<CharacteristicQuantification*> CharacteristicQuantificationPtrVector;
}
#endif // _AIMLib_CharacteristicQuantification_Class_
