/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: Win32TransService.hpp 676954 2008-07-15 16:29:19Z dbertoni $
 */

#if !defined(XERCESC_INCLUDE_GUARD_WIN32TRANSSERVICE_HPP)
#define XERCESC_INCLUDE_GUARD_WIN32TRANSSERVICE_HPP

#include <xercesc/util/TransService.hpp>
#include <xercesc/util/RefHashTableOf.hpp>
#include <windows.h>

XERCES_CPP_NAMESPACE_BEGIN

class CPMapEntry;



//---------------------------------------------------------------------------
//
//  class Win32TransService
//
//---------------------------------------------------------------------------
class XMLUTIL_EXPORT Win32TransService : public XMLTransService
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    Win32TransService(MemoryManager* manager);
    virtual ~Win32TransService();


    // -----------------------------------------------------------------------
    //  Implementation of the virtual transcoding service API
    // -----------------------------------------------------------------------
    virtual int compareIString
    (
        const   XMLCh* const    comp1
        , const XMLCh* const    comp2
    );

    virtual int compareNIString
    (
        const   XMLCh* const    comp1
        , const XMLCh* const    comp2
        , const XMLSize_t       maxChars
    );

    virtual const XMLCh* getId() const;

    virtual XMLLCPTranscoder* makeNewLCPTranscoder(MemoryManager* manager);

    virtual bool supportsSrcOfs() const;

    virtual void upperCase(XMLCh* const toUpperCase);
    virtual void lowerCase(XMLCh* const toLowerCase);


protected :
    // -----------------------------------------------------------------------
    //  Protected virtual methods
    // -----------------------------------------------------------------------
    virtual XMLTranscoder* makeNewXMLTranscoder
    (
        const   XMLCh* const            encodingName
        ,       XMLTransService::Codes& resValue
        , const XMLSize_t               blockSize
        ,       MemoryManager* const    manager
    );


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    Win32TransService(const Win32TransService&);
    Win32TransService& operator=(const Win32TransService&);

    //      This is a hash table of entries which map encoding names to their
    //      Windows specific code pages. The code page allows us to create
    //      transcoders for those encodings. The encoding names come from XML
    //      files.
    //
    //      This map is shared unsynchronized among all threads of the process,
    //      which is cool since it will be read only once its initialized.

    RefHashTableOf<CPMapEntry>    *fCPMap;
    MemoryManager*  fManager;
};







//---------------------------------------------------------------------------
//
//  class Win32Transcoder
//
//---------------------------------------------------------------------------

class XMLUTIL_EXPORT Win32Transcoder : public XMLTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    Win32Transcoder
    (
        const   XMLCh* const    encodingName
        , const unsigned int    ieCP
        , const XMLSize_t       blockSize
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager);
    ~Win32Transcoder();


    // -----------------------------------------------------------------------
    //  Implementation of the virtual transcoder interface
    // -----------------------------------------------------------------------
    virtual XMLSize_t transcodeFrom
    (
        const   XMLByte* const          srcData
        , const XMLSize_t               srcCount
        ,       XMLCh* const            toFill
        , const XMLSize_t               maxChars
        ,       XMLSize_t&              bytesEaten
        ,       unsigned char* const    charSizes
    );

    virtual XMLSize_t transcodeTo
    (
        const   XMLCh* const    srcData
        , const XMLSize_t       srcCount
        ,       XMLByte* const  toFill
        , const XMLSize_t       maxBytes
        ,       XMLSize_t&      charsEaten
        , const UnRepOpts       options
    );

    virtual bool canTranscodeTo
    (
        const   unsigned int    toCheck
    );


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    Win32Transcoder(const Win32Transcoder&);
    Win32Transcoder& operator=(const Win32Transcoder&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fIECP
    //      This is the code page for this encoding.
    //
    //  fUsedDef
    //      A flag passed into the conversions routines that is set to
    //      TRUE when a default character was substituted for the actual
    //      character.
    //
    //  fPtrUsedDef
    //      A pointer to fUsedDef or a null pointer if the code page does not
    //      support the parameter that returns whether or not a default
    //      character was substituted.
    //
    //  fFromFlags
    //      These are the flags passed to MultiByteToWideChar.  For some
    //      code pages, this must be 0.  See the documentation of the function
    //      for more details.
    //
    //  fToFlags
    //      These are the flags passed to WideCharToMultiByte.  For some
    //      code pages, this must be 0.  See the documentation of the function
    //      for more details.
    //
    // -----------------------------------------------------------------------
    UINT    fIECP;

    BOOL    fUsedDef;

    BOOL*   fPtrUsedDef;

    DWORD   fFromFlags;

    DWORD   fToFlags;
};





//---------------------------------------------------------------------------
//
//  class Win32LCPTranscoder
//
//---------------------------------------------------------------------------
class XMLUTIL_EXPORT Win32LCPTranscoder : public XMLLCPTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    Win32LCPTranscoder();
    ~Win32LCPTranscoder();


    // -----------------------------------------------------------------------
    //  Implementation of the virtual transcoder interface
    // -----------------------------------------------------------------------
    virtual char* transcode(const XMLCh* const toTranscode,
                            MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    virtual XMLCh* transcode(const char* const toTranscode,
                             MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);


    // -----------------------------------------------------------------------
    //  DEPRECATED old transcode interface
    // -----------------------------------------------------------------------
    virtual XMLSize_t calcRequiredSize(const char* const srcText
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    virtual XMLSize_t calcRequiredSize(const XMLCh* const srcText
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    virtual bool transcode
    (
        const   char* const     toTranscode
        ,       XMLCh* const    toFill
        , const XMLSize_t       maxChars
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual bool transcode
    (
        const   XMLCh* const    toTranscode
        ,       char* const     toFill
        , const XMLSize_t       maxChars
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    Win32LCPTranscoder(const Win32LCPTranscoder&);
    Win32LCPTranscoder& operator=(const Win32LCPTranscoder&);

    MemoryManager*  fManager;
};

XERCES_CPP_NAMESPACE_END

#endif
