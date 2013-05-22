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
class DCMTK_DCMIMGLE_EXPORT DiOverlayImage
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
