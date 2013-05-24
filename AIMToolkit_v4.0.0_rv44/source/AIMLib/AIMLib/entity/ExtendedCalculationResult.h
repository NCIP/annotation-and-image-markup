/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_ExtendedCalculationResult_Class_
#define _AIMLib_ExtendedCalculationResult_Class_

namespace aim_lib
{
	class AIMLIB_API ExtendedCalculationResult : public CalculationResult
	{

	public:
		ExtendedCalculationResult();
		ExtendedCalculationResult(const ExtendedCalculationResult& calculationResult);
		ExtendedCalculationResult& operator=(const ExtendedCalculationResult& calculationResult);
		virtual ExtendedCalculationResult* Clone() const;
		virtual ~ExtendedCalculationResult();

		const CalculationDataVector& GetCalculationDataCollection() const;

		void SetCalculationDataCollection(const CalculationDataVector& dataCollection);

	protected:
		CalculationDataVector _calculationDataCollection;
	};
}
#endif // _AIMLib_ExtendedCalculationResult_Class_
