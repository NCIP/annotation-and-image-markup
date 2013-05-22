/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/ofstream.h"

#define INCLUDE_CSTDIO
#include "dcmtk/ofstd/ofstdinc.h"

BEGIN_EXTERN_C
#include <fcntl.h>
END_EXTERN_C

int main()
{
#ifdef __MINGW32__
  /* MinGW does not support flock, there is no way to make this work. */
  printf("die \"Sorry, this application is not supported on the MinGW platform\";\n");
#else
  struct flock lockdata;
  unsigned int i;
  unsigned char *c;

  /* first, we initialize the data */
  c = (unsigned char *)(&lockdata);
  for (i=0; i<sizeof(struct flock); i++) c[i]=0;

  lockdata.l_whence=0;
  lockdata.l_start=0;
  lockdata.l_len=0;

  /* now we create the output */
  printf("$const_F_SETLKW = %ld;\n",(long)F_SETLKW);

  lockdata.l_type = F_RDLCK;
  printf("$const_RDLCK_STRUCT = pack(\"");
  for (i=0; i<sizeof(struct flock); i++) printf("c");
  printf("\"");
  for (i=0; i<sizeof(struct flock); i++) printf(",%d",(int)(c[i]));
  printf(");\n");

  lockdata.l_type = F_WRLCK;
  printf("$const_WRLCK_STRUCT = pack(\"");
  for (i=0; i<sizeof(struct flock); i++) printf("c");
  printf("\"");
  for (i=0; i<sizeof(struct flock); i++) printf(",%d",(int)(c[i]));
  printf(");\n");

  lockdata.l_type = F_UNLCK;
  printf("$const_UNLCK_STRUCT = pack(\"");
  for (i=0; i<sizeof(struct flock); i++) printf("c");
  printf("\"");
  for (i=0; i<sizeof(struct flock); i++) printf(",%d",(int)(c[i]));
  printf(");\n");

#endif
  return 0;
}

/*
 * CVS/RCS Log
 *   $Log: preplock.cc,v $
 *   Revision 1.6  2010-12-17 10:07:45  joergr
 *   Include another system header (stdio.h) needed for IRIX 6.3 with gcc 2.95.3.
 *
 *   Revision 1.5  2010-10-14 13:20:03  joergr
 *   Updated copyright header. Added reference to COPYRIGHT file.
 *
 *   Revision 1.4  2009-08-19 11:55:44  meichel
 *   Added additional includes needed for Sun Studio 11 on Solaris.
 *
 *   Revision 1.3  2005-12-08 15:48:37  meichel
 *   Changed include path schema for all DCMTK header files
 *
 *   Revision 1.2  2003/07/03 14:26:57  meichel
 *   When compiling on MinGW, only issues "die" command since the flock
 *     family of functions is not available on this platform and, therefore,
 *     preplock cannot be made to work.
 *
 *   Revision 1.1  2002/12/03 12:17:35  wilkens
 *   Added files und functionality from the dcmtk/wlisctn folder to dcmtk/dcmwlm
 *   so that dcmwlm can now completely replace wlistctn in the public domain part
 *   of dcmtk. Pertaining to this replacement requirement, another optional return
 *   key attribute was integrated into the wlm utilities.
 *
 *
 */
