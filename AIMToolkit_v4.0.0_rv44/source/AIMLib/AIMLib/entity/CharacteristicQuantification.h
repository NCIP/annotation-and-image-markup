/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
