/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ImagingPhysicalEntityCharacteristic_Class_
#define _AIMLib_ImagingPhysicalEntityCharacteristic_Class_

#include <string>
#include <memory>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ImagingPhysicalEntityCharacteristic
	{
	public:
		ImagingPhysicalEntityCharacteristic(void);
		ImagingPhysicalEntityCharacteristic(const ImagingPhysicalEntityCharacteristic& imagingPhysEntCharacteristic);
		virtual ~ImagingPhysicalEntityCharacteristic(void);
		ImagingPhysicalEntityCharacteristic& operator=(const ImagingPhysicalEntityCharacteristic& imagingPhysEntCharacteristic); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ImagingPhysicalEntityCharacteristic* Clone() const;

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

	typedef std::vector<ImagingPhysicalEntityCharacteristic> ImagingPhysicalEntityCharacteristicVector;
}
#endif // _AIMLib_ImagingPhysicalEntityCharacteristic_Class_
