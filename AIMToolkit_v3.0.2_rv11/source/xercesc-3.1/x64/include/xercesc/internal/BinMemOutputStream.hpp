/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: BinMemOutputStream.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_BINMEMOUTPUTSTREAM_HPP)
#define XERCESC_INCLUDE_GUARD_BINMEMOUTPUTSTREAM_HPP

#include <xercesc/framework/BinOutputStream.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT BinMemOutputStream : public BinOutputStream 
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    ~BinMemOutputStream();

    BinMemOutputStream
    (
         XMLSize_t               initCapacity = 1023
       , MemoryManager* const    manager      = XMLPlatformUtils::fgMemoryManager
    );

    // -----------------------------------------------------------------------
    //  Implementation of the output stream interface
    // -----------------------------------------------------------------------
    virtual XMLFilePos curPos() const;

    virtual void writeBytes
    (
      const XMLByte*     const      toGo
    , const XMLSize_t            maxToWrite
    ) ;

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLByte* getRawBuffer() const;

    XMLFilePos getSize() const;
    void reset();

private :
    // -----------------------------------------------------------------------
    //  Unimplemented methods.
    // -----------------------------------------------------------------------
    BinMemOutputStream(const BinMemOutputStream&);
    BinMemOutputStream& operator=(const BinMemOutputStream&);

    // -----------------------------------------------------------------------
    //  Private helpers
    // -----------------------------------------------------------------------
    void ensureCapacity(const XMLSize_t extraNeeded);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fDataBuf
    //      The pointer to the buffer data. Its grown as needed. Its always
    //      one larger than fCapacity, to leave room for the null terminator.
    //
    //  fIndex
    //      The current index into the buffer, as characters are appended
    //      to it. If its zero, then the buffer is empty.
    //
    //  fCapacity
    //      The current capacity of the buffer. Its actually always one
    //      larger, to leave room for the null terminator.
    //
    // -----------------------------------------------------------------------
    MemoryManager*  fMemoryManager;
    XMLByte*        fDataBuf;
    XMLSize_t       fIndex;
    XMLSize_t       fCapacity;

};


XERCES_CPP_NAMESPACE_END

#endif

