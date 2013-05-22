/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLIB_ANNOTATION_ROLE_INCLUDED_)
#define _AIMLIB_ANNOTATION_ROLE_INCLUDED_

#include <string>

namespace aim_lib
{
	class AIMLIB_API AnnotationRole
	{
	public:
		AnnotationRole(void);
		AnnotationRole(const AnnotationRole& annotationRole);
		virtual ~AnnotationRole(void);
		AnnotationRole& operator=(const AnnotationRole& annotationRole); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		AnnotationRole* Clone(void) const;

		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		int GetRoleSequenceNumber() const;

		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetRoleSequenceNumber(int newVal);

	protected:
		int _cagridId;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		int _roleSequenceNumber;
	};
}
#endif // !defined(_AIMLIB_ANNOTATION_ROLE_INCLUDED_)
