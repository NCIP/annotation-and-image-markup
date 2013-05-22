/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLib_AimUidGenerator_Class)
#define _AIMLib_AimUidGenerator_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API AimUidGenerator
	{
	public:

		static std::string GenerateNewUID(const std::string& prefix);

	protected:
		AimUidGenerator(void);
		~AimUidGenerator(void);
	};
}

#endif // _AIMLib_AimUidGenerator_Class
