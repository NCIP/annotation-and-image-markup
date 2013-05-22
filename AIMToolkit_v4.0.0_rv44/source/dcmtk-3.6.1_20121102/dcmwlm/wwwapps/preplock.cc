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
