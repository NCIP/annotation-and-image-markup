/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_CompactCalculationResult_Class_
#define _AIMLib_CompactCalculationResult_Class_

#include <string>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API CompactCalculationResult : public CalculationResult
	{
	public:
		CompactCalculationResult();
		CompactCalculationResult(const CompactCalculationResult& calculationResult);
		CompactCalculationResult& operator=(const CompactCalculationResult& calculationResult);
		virtual CompactCalculationResult* Clone() const;
		virtual ~CompactCalculationResult();

		const std::string& GetValue() const;
		const iso_21090::CD* GetEncoding() const;
		const iso_21090::CD* GetCompression() const;

		void SetValue(const std::string& newVal);
		void SetEncoding(const iso_21090::CD* newVal);
		void SetCompression(const iso_21090::CD* newVale);

	protected:
		std::string _value;
		std::auto_ptr<iso_21090::CD> _encoding;
		std::auto_ptr<iso_21090::CD> _compression;
	};
}
#endif // _AIMLib_CompactCalculationResult_Class_
