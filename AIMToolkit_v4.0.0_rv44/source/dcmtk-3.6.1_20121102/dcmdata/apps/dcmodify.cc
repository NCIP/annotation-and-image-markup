/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"   // make sure OS specific configuration is included first
#include "mdfconen.h"
#include "dcmtk/dcmdata/dcpath.h"

#define OFFIS_CONSOLE_APPLICATION "dcmodify"

static OFLogger dcmodifyLogger = OFLog::getLogger("dcmtk.apps." OFFIS_CONSOLE_APPLICATION);

int main(int argc, char *argv[])
{
  int error_count = 0;
  MdfConsoleEngine engine(argc, argv, OFFIS_CONSOLE_APPLICATION);
  error_count = engine.startProvidingService();
  if (error_count == 1)
    OFLOG_ERROR(dcmodifyLogger, "There was 1 error");
  else if (error_count > 1)
    OFLOG_ERROR(dcmodifyLogger, "There were " << error_count << " errors");
  return(error_count);
}
