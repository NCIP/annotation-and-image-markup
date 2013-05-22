/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _AIMLib_AimBaseClass
#define _AIMLib_AimBaseClass

#include <string>

namespace aim_lib
{
	class AIMLIB_API AimBase
	{
	public:
		const std::string& GetTypeName() const;

	protected:
		AimBase(const std::string& typeName);
		AimBase(const AimBase& aimObj);
		virtual ~AimBase(void);

		std::string _typeName;
	};
}

#endif // _AIMLib_AimBaseClass
