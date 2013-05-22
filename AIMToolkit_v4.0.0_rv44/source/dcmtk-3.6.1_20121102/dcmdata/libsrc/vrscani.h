/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef VRSCANI_H
#define VRSCANI_H

/* This needs its own header because both vrscanl.c and vrscan.cc need it. */

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include <setjmp.h>

struct vrscan_error {
    jmp_buf setjmp_buffer;
    const char *error_msg;
};

#define YY_EXTRA_TYPE struct vrscan_error *
#define YY_FATAL_ERROR(msg) do { \
    yyget_extra(yyscanner)->error_msg = msg; \
    longjmp(yyget_extra(yyscanner)->setjmp_buffer, 1); \
} while (0);

/* Don't try to include unistd.h which doesn't exist on windows */
#define YY_NO_UNISTD_H

#endif /* VRSCANI_H */
