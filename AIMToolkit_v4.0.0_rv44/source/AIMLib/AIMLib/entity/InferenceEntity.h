/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_InferenceEntity_Class_
#define _AIMLib_InferenceEntity_Class_

#include <memory>
#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API InferenceEntity : public Entity
	{
	public:
		InferenceEntity(void);
		InferenceEntity(const InferenceEntity& inferenceEntity);
		InferenceEntity& operator=(const InferenceEntity& inferenceEntity);
		virtual ~InferenceEntity(void);

		const iso_21090::CDVector& GetTypeCode() const;
		const iso_21090::CDVector& GetQuestionTypeCode() const;
		const std::string& GetDescription() const;
		const std::string& GetLabel() const;
		const std::string& GetComment() const;
		double* GetAnnotatorConfidence() const;
		bool GetIsImageEvidence() const;
		bool* GetIsPresent() const;
		int GetQuestionIndex() const;

		void SetTypeCode(const iso_21090::CDVector& typeCode);
		void SetQuestionTypeCode(const iso_21090::CDVector& questionTypeCode);
		void SetDescription(const std::string& description);
		void SetLabel(const std::string& label);
		void SetComment(const std::string& newVal);
		void SetAnnotatorConfidence(double* annotatorConfidence);
		void SetImageEvidence(bool imageEvidence);
		void SetIsPresent(bool* isPresent);
		void SetQuestionIndex(int questionIndex);

	protected:
		iso_21090::CDVector _typeCode;
		iso_21090::CDVector _questionTypeCode;
		std::string _description;
		std::string _label;
		std::string _comment;
		std::auto_ptr<double> _annotatorConfidence;
		bool _imageEvidence;
		std::auto_ptr<bool> _isPresent;
		int _questionIndex; // default: -1
	};

	typedef std::vector<InferenceEntity> InferenceEntityVector;
}
#endif // _AIMLib_InferenceEntity_Class_
