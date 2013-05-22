/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: BinFileOutputStream.hpp 553915 2007-07-06 14:57:08Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_BINFILEOUTPUTSTREAM_HPP)
#define XERCESC_INCLUDE_GUARD_BINFILEOUTPUTSTREAM_HPP

#include <xercesc/framework/BinOutputStream.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT BinFileOutputStream : public BinOutputStream
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    ~BinFileOutputStream();

    BinFileOutputStream
    (
        const   XMLCh* const    fileName
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    BinFileOutputStream
    (
         const   char* const     fileName
       , MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
    );

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

    virtual void writeBytes
    (
          const XMLByte* const      toGo
        , const XMLSize_t        maxToWrite
    );


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    BinFileOutputStream(const BinFileOutputStream&);
    BinFileOutputStream& operator=(const BinFileOutputStream&); 

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
//  BinFileOutputStream: Getter methods
// ---------------------------------------------------------------------------
inline bool BinFileOutputStream::getIsOpen() const
{
    return (fSource != (FileHandle) XERCES_Invalid_File_Handle);
}

XERCES_CPP_NAMESPACE_END

#endif
