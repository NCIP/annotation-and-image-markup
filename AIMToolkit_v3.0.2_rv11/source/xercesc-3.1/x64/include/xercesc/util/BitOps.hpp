/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: BitOps.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_BITOPS_HPP)
#define XERCESC_INCLUDE_GUARD_BITOPS_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT BitOps
{
public:
    // -----------------------------------------------------------------------
    //  Public static methods
    // -----------------------------------------------------------------------
    static inline XMLCh swapBytes(const XMLUInt16 toSwap)
    {
        //The mask is required to overcome a compiler error on solaris
        return XMLCh(((toSwap >> 8) | (toSwap << 8)) & 0xFFFF);
    }

    static inline unsigned int swapBytes(const XMLUInt32 toSwap)
    {
        return
        (
            (toSwap >> 24)
            | (toSwap << 24)
            | ((toSwap & 0xFF00) << 8)
            | ((toSwap & 0xFF0000) >> 8)
        );
    }



protected :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators.  (These ought to be private,
    //                                  but that produces spurious compiler warnings
    //                                  on some platforms.)
    // -----------------------------------------------------------------------
    BitOps();
    BitOps(const BitOps&);
    BitOps& operator=(const BitOps&);
};

XERCES_CPP_NAMESPACE_END

#endif
