/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLib_NonQuantifiable_Class)
#define _AIMLib_NonQuantifiable_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API NonQuantifiable : public CharacteristicQuantification
	{
	public:
		NonQuantifiable(void);
		NonQuantifiable(const NonQuantifiable& nonQuantifiable);
		virtual ~NonQuantifiable(void);
		NonQuantifiable& operator=(const NonQuantifiable& nonQuantifiable);
		virtual NonQuantifiable* Clone() const;

		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);

	protected:
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
	};
}
#endif // _AIMLib_NonQuantifiable_Class
