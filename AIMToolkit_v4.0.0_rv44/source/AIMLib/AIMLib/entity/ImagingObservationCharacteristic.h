/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
