
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
