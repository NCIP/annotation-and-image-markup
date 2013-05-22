/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#include <string.h>

int main()
{
    // We can't test "char *p = strerror_r()" because that only causes a
    // compiler warning when strerror_r returns an integer.
    char *buf = 0;
    int i = strerror_r(0, buf, 100);
    return i;
}
