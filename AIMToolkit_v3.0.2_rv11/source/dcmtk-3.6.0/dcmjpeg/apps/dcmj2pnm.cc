/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


// compile "dcm2pnm" with dcmjpeg support
#define BUILD_DCM2PNM_AS_DCMJ2PNM

// include full implementation of "dcm2pnm"
#include "../../dcmimage/apps/dcm2pnm.cc"


/*
 * CVS/RCS Log:
 * $Log: dcmj2pnm.cc,v $
 * Revision 1.5  2010-10-14 13:13:38  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.4  2006-07-27 14:04:37  joergr
 * Updated copyright date.
 *
 * Revision 1.3  2005/12/08 15:43:22  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.2  2004/01/16 14:28:01  joergr
 * Updated copyright header.
 *
 * Revision 1.1  2001/11/19 13:08:37  joergr
 * Added new tool dcmj2pnm which supports all features of dcm2pnm and in
 * addition also JPEG compressed images.
 *
 *
 */
