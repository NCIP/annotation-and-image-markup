/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef AIMOntology_STDAFX_H_INCLUDED
#define AIMOntology_STDAFX_H_INCLUDED

#if _MSC_VER > 1000
	#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER < 1300
#pragma warning ( disable : 4786 )	// identifier was truncated to '255' characters in the debug information
#endif


#include <windows.h>
#include <tchar.h>



#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#ifdef _DEBUG
	#pragma comment(lib, "xerces-c_3D")
#else
	#pragma comment(lib, "xerces-c_3")
#endif



#pragma warning ( disable : 4786 )	// identifier was truncated to '255' characters in the debug information



#include <iostream>
#include <string>


#include <Altova.h>
#include <SchemaTypes.h>
#include <AltovaException.h>
#include <XmlException.h>
#include <Node.h>
using namespace altova;


//{{AFX_INSERT_LOCATION}}

#endif // AIMOntology_STDAFX_H_INCLUDED
