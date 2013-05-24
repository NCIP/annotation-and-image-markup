/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#pragma once
#ifndef MEMDEBUG_STDAFX_H_INCLUDED
#define MEMDEBUG_STDAFX_H_INCLUDED

#ifdef _DEBUG

#ifdef WIN32
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#endif

#else 
// __GNUC__
// There is no memory leaks detection on non-Windows as of now.
// If required, use http://wyw.dcweb.cn/leakage.htm and http://sourceforge.net/projects/nvwa/ for cross-platform leaks detection
#endif // WIN32

#endif // MEMDEBUG_STDAFX_H_INCLUDED
