/*L
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLib_AimStatus_Class)
#define _AIMLib_AimStatus_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API AimStatus
	{
	public:
		AimStatus(void);
		AimStatus(const AimStatus& aimStatus);
		virtual ~AimStatus(void);
		AimStatus* Clone() const;

		double GetAnnotationVersion() const;
		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		const std::string& GetAuthorizedBy() const;
		void SetAnnotationVersion(double newVal);
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetAuthorizedBy(const std::string& newVal);

	protected:
		int _cagridId;
		double _annotationVersion;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		std::string _authorizedBy;
	};
}
#endif // _AIMLib_AimStatus_Class
