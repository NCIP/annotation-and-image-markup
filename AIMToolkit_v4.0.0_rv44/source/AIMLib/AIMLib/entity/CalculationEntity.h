/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_CalculationEntity_Class_
#define _AIMLib_CalculationEntity_Class_

#include <string>
#include <memory>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API CalculationEntity : public Entity
	{
	public:
		CalculationEntity();
		CalculationEntity(const CalculationEntity& calculationEntity);
		CalculationEntity& operator=(const CalculationEntity& calculationEntity);
		virtual ~CalculationEntity();

		const iso_21090::CDVector& GetTypeCode() const;
		const iso_21090::CDVector& GetQuestionTypeCode() const;
		const std::string& GetDescription() const;
		const std::string& GetMathML() const;
		int GetQuestionIndex() const;
		const Algorithm* GetAlgorithm() const;
		const CalculationResultPtrVector& GetCalculationResultCollection() const;

		void SetTypeCode(const iso_21090::CDVector& newVal);
		void SetQuestionTypeCode(const iso_21090::CDVector& newVal);
		void SetDescription(const std::string& newVal);
		void SetMathML(const std::string& newVal);
		void SetQuestionIndex(int newVal);
		void SetAlgorithm(const Algorithm* newVal);
		void SetCalculationResultCollection(const CalculationResultPtrVector& calculationResults);

	private:
		iso_21090::CDVector _typeCode;
		iso_21090::CDVector _questionTypeCode;
		std::string _description;
		std::string _mathML;
		int _questionIndex;
		std::auto_ptr<Algorithm> _algorithm;

		CalculationResultPtrVector _calculationResultCollection;
	};

	typedef std::vector<CalculationEntity> CalculationEntityVector;
}
#endif // _AIMLib_CalculationEntity_Class_
