/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ImagingPhysicalEntity_Class_
#define _AIMLib_ImagingPhysicalEntity_Class_

#include <memory>
#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ImagingPhysicalEntity : public Entity
	{

	public:
		ImagingPhysicalEntity();
		ImagingPhysicalEntity(const ImagingPhysicalEntity& imagingPhysicalEntity);
		virtual ~ImagingPhysicalEntity();
		ImagingPhysicalEntity& operator=(const ImagingPhysicalEntity& pImagingPhysicalEntity); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ImagingPhysicalEntity* Clone() const;

		const iso_21090::CDVector& GetTypeCode() const;
		const iso_21090::CDVector& GetQuestionTypeCode() const;
		double* GetAnnotatorConfidence() const;
		const std::string& GetLabel() const;
		const std::string& GetComment() const;
		bool* GetIsPresent() const;
		int GetQuestionIndex() const;
		const ImagingObservationCharacteristicVector& GetImagingObservationCharacteristicCollection() const;
		const ImagingPhysicalEntityCharacteristicVector& GetImagingPhysicalEntityCharacteristicCollection() const;

		void SetTypeCode(const iso_21090::CDVector& typeCode);
		void SetQuestionTypeCode(const iso_21090::CDVector& questionTypeCode);
		void SetAnnotatorConfidence(double* annotatorConfidence);
		void SetLabel(const std::string& label);
		void SetComment(const std::string& newVal);
		void SetIsPresent(bool* isPresent);
		void SetQuestionIndex(int questionIndex);
		void SetImagingObservationCharacteristicCollection(const ImagingObservationCharacteristicVector& newVal);
		void SetImagingPhysicalEntityCharacteristicCollection(const ImagingPhysicalEntityCharacteristicVector& newVal);

	private:
		iso_21090::CDVector _typeCode;
		iso_21090::CDVector _questionTypeCode;
		std::auto_ptr<double> _annotatorConfidence;
		std::string _label;
		std::string _comment;
		std::auto_ptr<bool> _isPresent;
		int _questionIndex; // default: -1

		ImagingObservationCharacteristicVector _imagingObservationCharachteristicCollection;
		ImagingPhysicalEntityCharacteristicVector _imagingPhysicalEntityCharacteristicCollection;
	};

	typedef std::vector<ImagingPhysicalEntity> ImagingPhysicalEntityVector;
}
#endif // _AIMLib_ImagingPhysicalEntity_Class_
