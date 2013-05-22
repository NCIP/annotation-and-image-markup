/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: LocalFileFormatTarget.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_LOCALFILEFORMATTARGET_HPP)
#define XERCESC_INCLUDE_GUARD_LOCALFILEFORMATTARGET_HPP

#include <xercesc/framework/XMLFormatter.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLPARSER_EXPORT LocalFileFormatTarget : public XMLFormatTarget {
public:

    /** @name constructors and destructor */
    //@{
    LocalFileFormatTarget
    (
        const XMLCh* const
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    LocalFileFormatTarget
    (
        const char* const
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    ~LocalFileFormatTarget();
    //@}

    // -----------------------------------------------------------------------
    //  Implementations of the format target interface
    // -----------------------------------------------------------------------
    virtual void writeChars(const XMLByte* const toWrite
                          , const XMLSize_t      count
                          , XMLFormatter* const  formatter);

    virtual void flush();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented methods.
    // -----------------------------------------------------------------------
    LocalFileFormatTarget(const LocalFileFormatTarget&);
    LocalFileFormatTarget& operator=(const LocalFileFormatTarget&);

    // -----------------------------------------------------------------------
    //  Private helpers
    // -----------------------------------------------------------------------
    void ensureCapacity(const XMLSize_t extraNeeded);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSource
    //      The source file that we represent. The FileHandle type is defined
    //      per platform.
    //
    //  fDataBuf
    //      The pointer to the buffer data. Its always
    //      one larger than fCapacity, to leave room for the null terminator.
    //
    //  fIndex
    //      The current index into the buffer, as characters are appended
    //      to it. If its zero, then the buffer is empty.
    //
    //  fCapacity
    //      The current capacity of the buffer. Its actually always one
    //      larger, to leave room for the null terminator.
    // -----------------------------------------------------------------------
    FileHandle      fSource;
    XMLByte*        fDataBuf;
    XMLSize_t       fIndex;
    XMLSize_t       fCapacity;
    MemoryManager*  fMemoryManager;
};


XERCES_CPP_NAMESPACE_END

#endif
