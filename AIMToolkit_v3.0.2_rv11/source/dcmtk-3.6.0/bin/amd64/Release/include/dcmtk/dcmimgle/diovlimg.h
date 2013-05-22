/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIOVLIMG_H
#define DIOVLIMG_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/dimo2img.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for standalone overlay images
 */
class DiOverlayImage
  : public DiMono2Image
{

 public:

    /** constructor
     *
     ** @param  docu    pointer to dataset (encapsulated)
     *  @param  status  current image status
     */
    DiOverlayImage(const DiDocument *docu,
                   const EI_Status status);

    /** destructor
     */
    virtual ~DiOverlayImage();
};


#endif


/*
 *
 * CVS/RCS Log:
 * $Log: diovlimg.h,v $
 * Revision 1.8  2010-10-14 13:16:26  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.7  2005-12-08 16:48:02  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.6  2003/12/09 10:06:26  joergr
 * Removed leading underscore characters from preprocessor symbols (reserved
 * symbols). Updated copyright header.
 *
 * Revision 1.5  2001/06/01 15:49:49  meichel
 * Updated copyright header
 *
 * Revision 1.4  2000/03/08 16:24:22  meichel
 * Updated copyright header.
 *
 * Revision 1.3  1999/09/17 12:46:58  joergr
 * Added/changed/completed DOC++ style comments in the header files.
 *
 * Revision 1.2  1999/03/24 17:20:20  joergr
 * Added/Modified comments and formatting.
 *
 * Revision 1.1  1998/11/27 15:43:13  joergr
 * Added copyright message.
 *
 * Revision 1.2  1998/05/11 14:53:25  joergr
 * Added CVS/RCS header to each file.
 *
 *
 */
