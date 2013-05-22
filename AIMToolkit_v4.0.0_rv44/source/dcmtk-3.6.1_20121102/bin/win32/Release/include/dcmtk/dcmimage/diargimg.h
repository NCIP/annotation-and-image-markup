/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIARGIMG_H
#define DIARGIMG_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimage/dicoimg.h"


/*------------------------*
 *  forward declarations  *
 *------------------------*/

class DiLookupTable;


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for ARGB images
 */
class DCMTK_DCMIMAGE_EXPORT DiARGBImage
  : public DiColorImage
{

 public:

    /** constructor
     *
     ** @param  docu    pointer to dataset (encapsulated)
     *  @param  status  current image status
     */
    DiARGBImage(const DiDocument *docu,
                const EI_Status status);

    /** destructor
     */
    virtual ~DiARGBImage();

    /** process next couple of frames
     *
     ** @param  fcount  number of frames to be processed (0 = same number as before)
     *
     ** @return status, true if successful, false otherwise
     */
    virtual int processNextFrames(const unsigned long fcount);


 protected:

    /** initialize internal data structures and member variables
     */
    void Init();


 private:

    /// three color palettes for R, G and B
    DiLookupTable *Palette[3];

 // --- declarations to avoid compiler warnings

    DiARGBImage(const DiARGBImage &);
    DiARGBImage &operator=(const DiARGBImage &);
};


#endif
