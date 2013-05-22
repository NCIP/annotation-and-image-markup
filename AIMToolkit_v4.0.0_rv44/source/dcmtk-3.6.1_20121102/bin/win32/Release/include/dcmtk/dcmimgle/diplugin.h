/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIPLUGIN_H
#define DIPLUGIN_H

#include "dcmtk/config/osconfig.h"

#define INCLUDE_CSTDIO
#include "dcmtk/ofstd/ofstdinc.h"


/*------------------------*
 *  forward declarations  *
 *------------------------*/

class DiImage;


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** abstract interface to plugable image output formats.
 *  This is an abstract base class used as an interface to support multiple
 *  plugable image output formats for the dcmimle/dcmimage library. An example
 *  implementation can be found in dcmjpeg/libsrc/dipijpeg.cc (JPEG plugin).
 */
class DCMTK_DCMIMGLE_EXPORT DiPluginFormat
{

  public:

    /** destructor (virtual)
     */
    virtual ~DiPluginFormat() {}

    /** write given image to a file stream (abstract)
     *
     ** @param  image   pointer to DICOM image object to be written
     *  @param  stream  stream to which the image is written (open in binary mode!)
     *  @param  frame   index of frame used for output (default: first frame = 0)
     *
     ** @return true if successful, false otherwise
     */
    virtual int write(DiImage *image,
                      FILE *stream,
                      const unsigned long frame = 0) const = 0;

  protected:

    /** constructor (protected)
     */
    DiPluginFormat() {}
};


#endif
