/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

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
		//#define EXPIMP_TEMPLATE
	#else
		#define AIMLIB_API __declspec(dllimport)
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

#endif // _AIMLib_AIMCommon_Include