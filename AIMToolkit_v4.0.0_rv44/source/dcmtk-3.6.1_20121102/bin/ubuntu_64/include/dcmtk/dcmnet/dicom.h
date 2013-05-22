/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DICOM_H
#define DICOM_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#define INCLUDE_CSTDLIB
#define INCLUDE_CSTDIO
#define INCLUDE_LIBC
#define INCLUDE_UNISTD
#include "dcmtk/ofstd/ofstdinc.h"

#include "dcmtk/dcmnet/cond.h"		/* condition typedefs */
#include "dcmtk/dcmnet/dcompat.h"	/* compatability routines */
#include "dcmtk/dcmdata/dctypes.h"	/* dcmdata toolkit basic types */
#include "dcmtk/dcmdata/dcuid.h"	/* dcmdata UID definitions */

/*
 * Useful Types
 */

/* these types are for backwards compatibility */
typedef Uint16	U_SHORT;	/* normal unsigned short*/
typedef Uint32	U_LONG;		/* normal unsigned long */
typedef Uint32	MASK_32;	/* for bit masks */


#define DICOM_STDAPPLICATIONCONTEXT UID_StandardApplicationContext
#define DICOM_NET_IMPLEMENTATIONCLASSUID OFFIS_IMPLEMENTATION_CLASS_UID
#define DICOM_NET_IMPLEMENTATIONVERSIONNAME OFFIS_DTK_IMPLEMENTATION_VERSION_NAME

/* network type constants as used by the DUL layer */
#define	DICOM_APPLICATION_ACCEPTOR	0x01
#define	DICOM_APPLICATION_REQUESTOR	0x02

/*
** The following defines are used in some levels of the network code.
*/

#define DIC_US_LEN		sizeof(DIC_US)
#define DIC_UL_LEN		sizeof(DIC_UL)
#define DIC_UI_LEN		64
#define DIC_AE_LEN		16
#define DIC_SH_LEN		16
#define DIC_PN_LEN		64
#define DIC_LO_LEN		64
#define DIC_CS_LEN		16
#define DIC_DS_LEN		16
#define DIC_IS_LEN		12
#define DIC_AT_LEN		(2*sizeof(DIC_US))
#define DIC_NODENAME_LEN	128

#define DICOM_UI_LENGTH DIC_UI_LEN

typedef Uint16	DIC_US;
typedef Uint32	DIC_UL;
typedef char 	DIC_UI[DIC_UI_LEN + 1];
typedef char	DIC_AE[DIC_AE_LEN + 1];
typedef char	DIC_SH[DIC_SH_LEN + 1];
typedef char	DIC_PN[DIC_PN_LEN + 1];
typedef char	DIC_LO[DIC_LO_LEN + 1];
typedef char	DIC_CS[DIC_CS_LEN + 1];
typedef char	DIC_DS[DIC_DS_LEN + 1];
typedef char	DIC_IS[DIC_IS_LEN + 1];
typedef char	DIC_NODENAME[DIC_NODENAME_LEN + 1];


/*
 * Useful Macros
 */

#ifndef MAX
#define MAX(x, y) (((x) < (y)) ? (y) : (x))
#endif
#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif
#ifndef IS_EVEN
#define IS_EVEN(i) (~(i) & 0x01)
#endif
#ifndef DIM_OF
#define DIM_OF(a) (sizeof(a) / sizeof(a[0]))
#endif
#ifndef IN_RANGE
#define IN_RANGE(n, lo, hi) ((lo) <= n && (n) <= (hi))
#endif

#endif
