/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: BinOutputStream.hpp 553915 2007-07-06 14:57:08Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_BIN_OUTPUT_STREAM_HPP)
#define XERCESC_INCLUDE_GUARD_BIN_OUTPUT_STREAM_HPP

#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT BinOutputStream : public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Virtual destructor for derived classes
    // -----------------------------------------------------------------------
    virtual ~BinOutputStream();

    // -----------------------------------------------------------------------
    //  The virtual output stream interface
    // -----------------------------------------------------------------------
    virtual XMLFilePos curPos() const = 0;

    virtual void writeBytes
    (
          const XMLByte* const      toGo
        , const XMLSize_t           maxToWrite
    ) = 0;

protected :
    // -----------------------------------------------------------------------
    //  Hidden Constructors
    // -----------------------------------------------------------------------
    BinOutputStream();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented Constructors
    // -----------------------------------------------------------------------
    BinOutputStream(const BinOutputStream&);
    BinOutputStream& operator=(const BinOutputStream&);
};

XERCES_CPP_NAMESPACE_END

#endif
