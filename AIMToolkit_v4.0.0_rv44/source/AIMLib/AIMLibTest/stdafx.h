/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#ifndef AIMLIBTEST_STDAFX_H_INCLUDED
#define AIMLIBTEST_STDAFX_H_INCLUDED

#if !defined( __GNUC__ )

#include <tchar.h>

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#endif // __GNUC__

#if defined(_MSC_VER)
// warning C4231: nonstandard extension used : 'extern' before template explicit instantiation
#pragma warning (disable : 4231) // see http://support.microsoft.com/kb/168958/en-us
#endif // _MSC_VER

#include <stdio.h>

#endif // AIMLIBTEST_STDAFX_H_INCLUDED
