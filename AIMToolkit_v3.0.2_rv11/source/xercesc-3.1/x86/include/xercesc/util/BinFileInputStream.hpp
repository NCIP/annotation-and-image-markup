/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: BinFileInputStream.hpp 670359 2008-06-22 13:43:45Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_BINFILEINPUTSTREAM_HPP)
#define XERCESC_INCLUDE_GUARD_BINFILEINPUTSTREAM_HPP

#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT BinFileInputStream : public BinInputStream
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    BinFileInputStream
    (
        const   XMLCh* const    fileName
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    BinFileInputStream
    (
        const   char* const     fileName
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    BinFileInputStream
    (
        const   FileHandle      toUse
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual ~BinFileInputStream();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getIsOpen() const;
    XMLFilePos getSize() const;
    void reset();


    // -----------------------------------------------------------------------
    //  Implementation of the input stream interface
    // -----------------------------------------------------------------------
    virtual XMLFilePos curPos() const;

    virtual XMLSize_t readBytes
    (
                XMLByte* const      toFill
        , const XMLSize_t           maxToRead
    );

    virtual const XMLCh* getContentType() const;

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    BinFileInputStream(const BinFileInputStream&);
    BinFileInputStream& operator=(const BinFileInputStream&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSource
    //      The source file that we represent. The FileHandle type is defined
    //      per platform.
    // -----------------------------------------------------------------------
    FileHandle              fSource;
    MemoryManager* const    fMemoryManager;
};


// ---------------------------------------------------------------------------
//  BinFileInputStream: Getter methods
// ---------------------------------------------------------------------------
inline bool BinFileInputStream::getIsOpen() const
{
    return (fSource != (FileHandle) XERCES_Invalid_File_Handle);
}

XERCES_CPP_NAMESPACE_END

#endif
