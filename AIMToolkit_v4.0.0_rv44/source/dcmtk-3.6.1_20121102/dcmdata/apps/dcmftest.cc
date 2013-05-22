/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#define INCLUDE_CSTDLIB
#define INCLUDE_CSTDIO
#define INCLUDE_CSTRING
#define INCLUDE_LIBC
#define INCLUDE_UNISTD
#include "dcmtk/ofstd/ofstdinc.h"

#include "dcmtk/dcmdata/dcmetinf.h"
#include "dcmtk/ofstd/ofconapp.h"
#include "dcmtk/dcmdata/dcuid.h"    /* for dcmtk version name */

#define OFFIS_CONSOLE_APPLICATION "dcmftest"

static char rcsid[] = "$dcmtk: " OFFIS_CONSOLE_APPLICATION " v"
  OFFIS_DCMTK_VERSION " " OFFIS_DCMTK_RELEASEDATE " $";

// ********************************************

int main(int argc, char *argv[])
{
    OFConsoleApplication app(OFFIS_CONSOLE_APPLICATION , "Test if file uses DICOM part 10 format", rcsid);
    OFCommandLine cmd;

    /* evaluate command line */
    cmd.addParam("file", OFCmdParam::PM_MultiMandatory);
    app.parseCommandLine(cmd, argc, argv);

    int badCount = 0;
    int count = cmd.getParamCount();
    const char *fname = NULL;
    for (int i=1; i<=count; i++) {
        cmd.getParam(i, fname);
        OFBool ok = OFFalse;
        FILE* f = NULL;

        if (fname && (strlen(fname) > 0)) f = fopen(fname, "rb");
        if (f == 0) {
            ok = OFFalse;
        } else {
            char signature[4];
            if ((fseek(f, DCM_PreambleLen, SEEK_SET) < 0) ||
                (fread(signature, 1, DCM_MagicLen, f) != DCM_MagicLen)) {
                ok = OFFalse;
            } else if (strncmp(signature, DCM_Magic, DCM_MagicLen) != 0) {
                ok = OFFalse;
            } else {
                /* looks ok */
                ok = OFTrue;
            }
            fclose(f);
        }
        if (ok) {
            COUT << "yes: " << fname << OFendl;
        } else {
            COUT << "no: " << fname << OFendl;
            badCount++;
        }
    }

    /*
    ** if all files are ok then return zero, otherwise the
    ** number of non-dicom files.
    */
    return badCount;
}
