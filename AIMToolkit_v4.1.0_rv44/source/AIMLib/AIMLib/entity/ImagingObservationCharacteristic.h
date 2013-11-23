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
#ifndef _AIMLib_ImagingObservationCharacteristic_Class_
#define _AIMLib_ImagingObservationCharacteristic_Class_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ImagingObservationCharacteristic
	{
	public:
		ImagingObservationCharacteristic();
		ImagingObservationCharacteristic(const ImagingObservationCharacteristic& imgObsCharacteristics);
		virtual ~ImagingObservationCharacteristic();
		ImagingObservationCharacteristic& operator=(const ImagingObservationCharacteristic& pImgObsCharacteristic); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ImagingObservationCharacteristic* Clone() const;

		const iso_21090::CDVector& GetTypeCode() const;
		const iso_21090::CDVector& GetQuestionTypeCode() const;
		double* GetAnnotatorConfidence() const;
		const std::string& GetLabel() const;
		const std::string& GetComment() const;
		int GetQuestionIndex() const;
		const CharacteristicQuantificationPtrVector& GetCharacteristicQuantificationCollection() const;

		void SetTypeCode(const iso_21090::CDVector& typeCode);
		void SetQuestionTypeCode(const iso_21090::CDVector& questionTypeCode);
		void SetAnnotatorConfidence(double* annotatorConfidence);
		void SetLabel(const std::string& label);
		void SetComment(const std::string& newVal);
		void SetQuestionIndex(int questionIndex);
		void SetCharacteristicQuantificationCollection(const CharacteristicQuantificationPtrVector& charachteristicQuantifications);

	protected:
		void FreeAllCharacteristicQuantifications();

		iso_21090::CDVector _typeCode;
		iso_21090::CDVector _questionTypeCode;
		std::auto_ptr<double> _annotatorConfidence;
		std::string _label;
		std::string _comment;
		int _questionIndex; // default: -1

		CharacteristicQuantificationPtrVector _characteristicQuantificationCollection;
	};

	typedef std::vector<ImagingObservationCharacteristic> ImagingObservationCharacteristicVector;
}
#endif // _AIMLib_ImagingObservationCharacteristic_Class_
