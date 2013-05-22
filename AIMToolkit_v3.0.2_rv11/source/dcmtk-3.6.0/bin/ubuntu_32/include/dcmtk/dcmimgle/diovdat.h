/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIOVDAT_H
#define DIOVDAT_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/diobjcou.h"


/*------------------------*
 *  forward declarations  *
 *------------------------*/

class DiOverlay;
class DiOverlayPlane;


/*-------------------------------*
 *  declaration of helper class  *
 *-------------------------------*/

/** Class to handle overlay pixel data
 */
class DiOverlayData
  : public DiObjectCounter
{

    friend class DiOverlay;

 public:

    /** constructor
     *
     ** @param  entries  number of array entries
     *  @param  count    number of valid overlay planes
     */
    DiOverlayData(unsigned int entries,
                  unsigned int count = 0);

    /** destructor
     */
    virtual ~DiOverlayData();


 private:

    /// number of (valid) overlay planes
    unsigned int Count;
    /// number of array entries (allocated memory)
    unsigned int ArrayEntries;

    /// pointer to an array of planes
    DiOverlayPlane **Planes;
    /// pointer to overlay data (if scaled, flipped or rotated)
    Uint16 *DataBuffer;

 // --- declarations to avoid compiler warnings

    DiOverlayData(const DiOverlayData &);
    DiOverlayData &operator=(const DiOverlayData &);
};


#endif


/*
 *
 * CVS/RCS Log:
 * $Log: diovdat.h,v $
 * Revision 1.7  2010-10-14 13:16:26  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.6  2010-03-01 09:08:47  uli
 * Removed some unnecessary include directives in the headers.
 *
 * Revision 1.5  2005-12-08 16:48:00  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.4  2003/12/09 10:05:22  joergr
 * Removed leading underscore characters from preprocessor symbols (reserved
 * symbols). Updated copyright header.
 *
 * Revision 1.3  2001/06/01 15:49:48  meichel
 * Updated copyright header
 *
 * Revision 1.2  2000/03/08 16:24:22  meichel
 * Updated copyright header.
 *
 * Revision 1.1  1999/09/17 12:46:22  joergr
 * Splitted file diovlay.h into two files (one for each class).
 *
 *
 *
 */
