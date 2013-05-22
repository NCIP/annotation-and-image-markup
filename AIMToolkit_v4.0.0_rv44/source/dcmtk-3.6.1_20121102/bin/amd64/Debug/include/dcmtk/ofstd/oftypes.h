/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef OFTYPES_H
#define OFTYPES_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>                /* Needed for int64_t */
#endif

#ifdef __CHAR_UNSIGNED__
typedef signed char     Sint8;
#else 
typedef char            Sint8;
#endif

typedef unsigned char   Uint8;

#if SIZEOF_LONG == 8
typedef signed int      Sint32;
typedef unsigned int    Uint32;
#else
typedef signed long     Sint32;
typedef unsigned long   Uint32;
#endif

typedef signed short    Sint16;
typedef unsigned short  Uint16;

typedef float           Float32;    /* 32 Bit Floating Point Single */
typedef double          Float64;    /* 64 Bit Floating Point Double */

// Definition of type OFBool

#ifdef HAVE_CXX_BOOL

#define OFBool bool
#define OFTrue true
#define OFFalse false

#else

/** the boolean type used throughout the DCMTK project. Mapped to the 
 *  built-in type "bool" if the current C++ compiler supports it. Mapped 
 *  to int for old-fashioned compilers which do not yet support bool.
 */
typedef int OFBool;

#ifndef OFTrue 
#define OFTrue (1)
#endif

#ifndef OFFalse 
#define OFFalse (0)
#endif

#endif

#if defined(HAVE_TYPENAME)
#define OFTypename typename
#else
#define OFTypename
#endif

#endif
