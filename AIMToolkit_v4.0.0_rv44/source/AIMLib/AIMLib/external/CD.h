/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_external_CD
#define _AIMLib_external_CD

#include <string>
#include <vector>

namespace aim_lib
{
	namespace iso_21090
	{
		class AIMLIB_API CD
		{
		public:
			CD(void);
			CD(const std::string& codeValue, const std::string& codeMeaning, const std::string& codingSchemeDesignator, const std::string& codingSchemeVersion = "");
			CD(const CD& cd);
			virtual ~CD(void);

			CD& operator=(const CD& ii);
			bool operator==(const CD& ii) const;

			const std::string& GetCodeValue() const;
			const std::string& GetCodeMeaning() const;
			const std::string& GetCodingSchemeDesignator() const;
			const std::string& GetCodingSchemeVersion() const;

			void SetCodeValue(const std::string& newVal);
			void SetCodeMeaning(const std::string& newVal);
			void SetCodingSchemeDesignator(const std::string& newVal);
			void SetCodingSchemeVersion(const std::string& newVal);
		protected:
			std::string _codeValue;
			std::string _codeMeaning;
			std::string _codingSchemeDesignator;
			std::string _codingSchemeVersion;
		};

		typedef std::vector<CD> CDVector;
	}
}

#endif // _AIMLib_external_CD
