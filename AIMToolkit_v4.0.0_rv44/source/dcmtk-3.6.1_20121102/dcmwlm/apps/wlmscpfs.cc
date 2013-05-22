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
