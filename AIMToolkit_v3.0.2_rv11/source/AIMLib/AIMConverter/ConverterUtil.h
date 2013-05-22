/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _AIMConverter_ConverterUtil_Class
#define _AIMConverter_ConverterUtil_Class

#include <string>

class ConverterUtil
{
public:
	ConverterUtil(void);
	~ConverterUtil(void);

	static int nocase_cmp(const std::string & s1, const std::string& s2);
};

#endif // _AIMConverter_ConverterUtil_Class
