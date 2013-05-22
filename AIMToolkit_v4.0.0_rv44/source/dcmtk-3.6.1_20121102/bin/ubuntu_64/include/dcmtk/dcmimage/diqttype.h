/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIQTTYPE_H
#define DIQTTYPE_H


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimage/dicdefin.h"

/// the basic type for pixel color components
typedef unsigned char DcmQuantComponent;

/// size of color hash table. Don't touch this.
#define DcmQuantHashSize 20023UL

/** maximum number of colors we count in a color histogram.
 *  If the number of colors turns out to be larger than this,
 *  then the image bit depth is reduced until the number
 *  of colors becomes smaller than this maximum.
 */
#define DcmQuantMaxColors 65536


/** defines the algorithm used for determining the
 *  largest dimension in the Median Cut algorithm
 */
enum DcmLargestDimensionType
{
  /// determine dimension by comparing the range in RGB space (default)
  DcmLargestDimensionType_default,

  /// determine dimension by transforming into luminance before comparison
  DcmLargestDimensionType_luminance
};


/** defines the algorithm for choosing a representative color for each
 *  box in the Median Cut algorithm
 */
enum DcmRepresentativeColorType
{
  /// average all the colors in the box (as specified in Heckbert's paper; this is the default)
  DcmRepresentativeColorType_default,

  /// average all pixels in the box
  DcmRepresentativeColorType_averagePixels,

  /// choose center of the box, ignoring any structure within the boxes
  DcmRepresentativeColorType_centerOfBox

};

#endif
