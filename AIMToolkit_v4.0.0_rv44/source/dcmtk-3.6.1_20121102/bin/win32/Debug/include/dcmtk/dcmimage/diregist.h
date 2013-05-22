/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIREGIST_H
#define DIREGIST_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/diregbas.h"

#include "dcmtk/dcmimage/dicdefin.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class to register color support to dcmimgle library
 */
class DCMTK_DCMIMAGE_EXPORT DiRegister
  : public DiRegisterBase
{

 public:

    /** constructor
     */
    DiRegister();

    /** destructor
     */
    virtual ~DiRegister();

    /** create color image representation
     *
     ** @param  docu    pointer to dataset (encapsulated)
     *  @param  status  image status
     *  @param  photo   photometric interpretation
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    virtual DiImage *createImage(const DiDocument *docu,
                                 const EI_Status status,
                                 const EP_Interpretation photo);

    /** create monochrome pixel data from color image
     *
     ** @param  image  pointer to color image
     *  @param  red    coefficient by which the red component is weighted
     *  @param  green  coefficient by which the green component is weighted
     *  @param  blue   coefficient by which the blue component is weighted
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    virtual DiMonoPixel *createMonoImageData(const DiColorImage *image,
                                             const double red,
                                             const double green,
                                             const double blue);
};


/*------------------*
 *  initialization  *
 *------------------*/

static DiRegister Init_dcmimage_Module;        // registration pointer is initialized in class constructor


#endif
