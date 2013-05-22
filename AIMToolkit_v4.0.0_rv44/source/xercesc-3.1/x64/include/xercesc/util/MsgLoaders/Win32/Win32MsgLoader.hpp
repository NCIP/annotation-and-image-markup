/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: Win32MsgLoader.hpp 570552 2007-08-28 19:57:36Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_WIN32MSGLOADER_HPP)
#define XERCESC_INCLUDE_GUARD_WIN32MSGLOADER_HPP

#include <windows.h>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLMsgLoader.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This is a simple in Win32 RC message loader implementation.
//
class XMLUTIL_EXPORT Win32MsgLoader : public XMLMsgLoader
{
public :
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    Win32MsgLoader(const XMLCh* const msgDomain);
    ~Win32MsgLoader();


    // -----------------------------------------------------------------------
    //  Implementation of the virtual message loader API
    // -----------------------------------------------------------------------
    virtual bool loadMsg
    (
        const   XMLMsgLoader::XMLMsgId  msgToLoad
        ,       XMLCh* const            toFill
        , const XMLSize_t               maxChars
    );

    virtual bool loadMsg
    (
        const   XMLMsgLoader::XMLMsgId  msgToLoad
        ,       XMLCh* const            toFill
        , const XMLSize_t               maxChars
        , const XMLCh* const            repText1
        , const XMLCh* const            repText2 = 0
        , const XMLCh* const            repText3 = 0
        , const XMLCh* const            repText4 = 0
        , MemoryManager* const          manger   = XMLPlatformUtils::fgMemoryManager
    );

    virtual bool loadMsg
    (
        const   XMLMsgLoader::XMLMsgId  msgToLoad
        ,       XMLCh* const            toFill
        , const XMLSize_t               maxChars
        , const char* const             repText1
        , const char* const             repText2 = 0
        , const char* const             repText3 = 0
        , const char* const             repText4 = 0
        , MemoryManager* const          manager  = XMLPlatformUtils::fgMemoryManager
    );


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    Win32MsgLoader();
    Win32MsgLoader(const Win32MsgLoader&);
    Win32MsgLoader& operator=(const Win32MsgLoader&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fDomainOfs
    //      This is the id offset for the current domain. Its used to bias
    //      the zero based id of each domain, since they are stored in the
    //      same file and have to have unique ids internally. This is set
    //      in the ctor from the domain name. We just have to agree with
    //      what our formatter in the NLSXlat program does.
    //
    //  fModHandle
    //      This is our DLL module handle that we need in order to load
    //      resource messages. This is set during construction.
    //
    //  fMsgDomain
    //      This is the name of the error domain that this loader is for.
    // -----------------------------------------------------------------------
    unsigned int    fDomainOfs;
    HINSTANCE       fModHandle;
    XMLCh*          fMsgDomain;
};

XERCES_CPP_NAMESPACE_END

#endif
