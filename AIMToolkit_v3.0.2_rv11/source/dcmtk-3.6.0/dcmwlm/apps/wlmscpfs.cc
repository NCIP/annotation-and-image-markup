/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmnet/dicom.h"
#include "dcmtk/ofstd/ofcmdln.h"
#include "dcmtk/dcmwlm/wltypdef.h"
#include "dcmtk/dcmdata/dcxfer.h"
#include "dcmtk/ofstd/ofconapp.h"
#include "wlcefs.h"
#include "dcmtk/dcmwlm/wlds.h"
#include "dcmtk/dcmwlm/wldsfs.h"

#define OFFIS_CONSOLE_APPLICATION "wlmscpfs"

int main( int argc, char *argv[] )
{
  // Initialize object which provides a connection to the data source
  WlmDataSourceFileSystem *dataSource = new WlmDataSourceFileSystem();

  // Initialize and provide service. After having terminated free memory.
  WlmConsoleEngineFileSystem *consoleEngine = new WlmConsoleEngineFileSystem( argc, argv, OFFIS_CONSOLE_APPLICATION, dataSource );
  int result = consoleEngine->StartProvidingService();

  // Free memory
  delete consoleEngine;
  delete dataSource;

  return( result );
}

/*
** CVS Log
** $Log: wlmscpfs.cc,v $
** Revision 1.6  2010-10-14 13:13:53  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.5  2005/12/08 15:48:31  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.4  2002/08/05 09:09:29  wilkens
** Modfified the project's structure in order to be able to create a new
** application which contains both wlmscpdb and ppsscpdb.
**
** Revision 1.3  2002/04/18 14:19:57  wilkens
** Modified Makefiles. Updated latest changes again. These are the latest
** sources. Added configure file.
**
** Revision 1.2  2002/01/08 17:44:45  joergr
** Reformatted source files (replaced Windows newlines by Unix ones, replaced
** tabulator characters by spaces, etc.)
**
** Revision 1.1  2002/01/08 16:29:51  joergr
** Added new module "dcmwlm" developed by Thomas Wilkens (initial release for
** Windows, dated 2001-12-20).
**
**
*/
