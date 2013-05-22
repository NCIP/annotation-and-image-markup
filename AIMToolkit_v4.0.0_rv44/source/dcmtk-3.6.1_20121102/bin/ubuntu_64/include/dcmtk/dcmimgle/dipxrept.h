/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIPXREPT_H
#define DIPXREPT_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/diutils.h"

#ifdef HAVE_EXPLICIT_TEMPLATE_SPECIALIZATION
#define EXPLICIT_SPECIALIZATION template<>
#else
#define EXPLICIT_SPECIALIZATION
#endif


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Template class to determine pixel representation.
 *  Size of basic structure, sign-extension
 */
template<class T>
class DiPixelRepresentationTemplate
{

 public:

    /// default constructor
    DiPixelRepresentationTemplate() {}

    /// destructor
    virtual ~DiPixelRepresentationTemplate() {}

    /** check whether template type T is signed or not
     *
     ** @return true if signed, false otherwise
     */
    inline int isSigned() const;

 protected:

    /** determine integer representation for template type T
     *
     ** @return integer representation
     */
    virtual inline EP_Representation getRepresentation() const;
};


/********************************************************************/


EXPLICIT_SPECIALIZATION
inline EP_Representation DiPixelRepresentationTemplate<Uint8>::getRepresentation() const
{
    return EPR_Uint8;
}


EXPLICIT_SPECIALIZATION
inline EP_Representation DiPixelRepresentationTemplate<Sint8>::getRepresentation() const
{
    return EPR_Sint8;
}


EXPLICIT_SPECIALIZATION
inline EP_Representation DiPixelRepresentationTemplate<Uint16>::getRepresentation() const
{
    return EPR_Uint16;
}


EXPLICIT_SPECIALIZATION
inline EP_Representation DiPixelRepresentationTemplate<Sint16>::getRepresentation() const
{
    return EPR_Sint16;
}


EXPLICIT_SPECIALIZATION
inline EP_Representation DiPixelRepresentationTemplate<Uint32>::getRepresentation() const
{
    return EPR_Uint32;
}


EXPLICIT_SPECIALIZATION
inline EP_Representation DiPixelRepresentationTemplate<Sint32>::getRepresentation() const
{
    return EPR_Sint32;
}


EXPLICIT_SPECIALIZATION
inline int DiPixelRepresentationTemplate<Uint8>::isSigned() const
{
    return 0;
}


EXPLICIT_SPECIALIZATION
inline int DiPixelRepresentationTemplate<Uint16>::isSigned() const
{
    return 0;
}


EXPLICIT_SPECIALIZATION
inline int DiPixelRepresentationTemplate<Uint32>::isSigned() const
{
    return 0;
}


EXPLICIT_SPECIALIZATION
inline int DiPixelRepresentationTemplate<Sint8>::isSigned() const
{
    return 1;
}


EXPLICIT_SPECIALIZATION
inline int DiPixelRepresentationTemplate<Sint16>::isSigned() const
{
    return 1;
}


EXPLICIT_SPECIALIZATION
inline int DiPixelRepresentationTemplate<Sint32>::isSigned() const
{
    return 1;
}


#endif
