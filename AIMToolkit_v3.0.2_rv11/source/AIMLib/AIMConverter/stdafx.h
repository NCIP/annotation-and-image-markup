/*
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
#ifndef AIMCONVERTER_STDAFX_H_INCLUDED
#define AIMCONVERTER_STDAFX_H_INCLUDED

#if !defined( __GNUC__ )

#include <tchar.h>

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#endif // __GNUC__

#include <stdio.h>

#endif // AIMCONVERTER_STDAFX_H_INCLUDED
