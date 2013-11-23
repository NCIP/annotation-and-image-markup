/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#ifndef _AIMLib_AIMCommon_Include
#define _AIMLib_AIMCommon_Include


// VK:
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the AIMLIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AIMLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef WIN32
	#ifdef AIMLIB_EXPORTS
		#define AIMLIB_API __declspec(dllexport)
		#define AIMLIB_EXPIMP_TEMPLATE
		//#define EXPIMP_TEMPLATE
	#else
		#define AIMLIB_API __declspec(dllimport)
		 #define AIMLIB_EXPIMP_TEMPLATE extern
		// #define EXPIMP_TEMPLATE extern
	#endif
#else
	// no export for non-Windows platforms
	#define AIMLIB_API
#endif

//#include <string>
//
//EXPIMP_TEMPLATE template class AIMLIB_API std::string;


// Disable warnings on std:string. If we ever use any other std:: types besides string, we have to fix the code!
// See: http://support.microsoft.com/kb/168958
#pragma warning (disable : 4251)

// Include ISO 21090 data type definitions for now
#include "external/CD.h"
#include "external/II.h"

#endif // _AIMLib_AIMCommon_Include