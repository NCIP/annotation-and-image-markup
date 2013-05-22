/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIDISLUT_H
#define DIDISLUT_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/dibaslut.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class to compute and store the Display lookup table
 */
class DCMTK_DCMIMGLE_EXPORT DiDisplayLUT
  : public DiBaseLUT
{

 public:

    /** constructor
     *
     ** @param  count  number of values to be stored
     *  @param  max    maximum value to be stored
     *  @param  amb    ambient light value
     *  @param  illum  illumination value (optional)
     */
    DiDisplayLUT(const unsigned long count,
                 const Uint16 max,
                 const double amb,
                 const double illum = 0);

    /** destructor
     */
    virtual ~DiDisplayLUT();

    /** get ambient light value
     *
     ** @return ambient light value
     */
    inline double getAmbientLightValue() const
    {
        return AmbientLight;
    }

    /** get illumination value
     *
     ** @return illumination value
     */
    inline double getIlluminationValue() const
    {
        return Illumination;
    }


 private:

    /// ambient light value (measured in cd/m^2)
    const double AmbientLight;
    /// illumination value (measured in cd/m^2)
    const double Illumination;
};


#endif
