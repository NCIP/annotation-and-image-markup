/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLMsgLoader.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLMSGLOADER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLMSGLOADER_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This header defines an abstract message loading API. This is the API via
//  which the parser system loads translatable text, and there can be multiple
//  actual implementations of this mechanism. The API is very simple because
//  there can be many kinds of underlying systems on which implementations are
//  based and we don't want to get into portability trouble by being overly
//  smart.
//
//  Each instance of the message loader loads a file of messages, which are
//  accessed by key and which are associated with a particular language. The
//  actual source information may be in many forms, but by the time it is
//  extracted for use it will be in Unicode format. The language is always
//  the default language for the local machine.
//
//  Msg loader derivatives are not required to be thread safe. The parser will
//  never use a single instance in more than one thread.
//
class XMLUTIL_EXPORT XMLMsgLoader : public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Class specific types
    //
    //  XMLMsgId
    //      A simple typedef to give us flexibility about the representation
    //      of a message id.
    // -----------------------------------------------------------------------
    typedef unsigned int    XMLMsgId;


    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    virtual ~XMLMsgLoader();


    // -----------------------------------------------------------------------
    //  The virtual message loader API
    // -----------------------------------------------------------------------
    virtual bool loadMsg
    (
        const   XMLMsgId        msgToLoad
        ,       XMLCh* const    toFill
        , const XMLSize_t       maxChars
    ) = 0;

    virtual bool loadMsg
    (
        const   XMLMsgId        msgToLoad
        ,       XMLCh* const    toFill
        , const XMLSize_t       maxChars
        , const XMLCh* const    repText1
        , const XMLCh* const    repText2 = 0
        , const XMLCh* const    repText3 = 0
        , const XMLCh* const    repText4 = 0
        , MemoryManager* const  manager   = XMLPlatformUtils::fgMemoryManager
    ) = 0;

    virtual bool loadMsg
    (
        const   XMLMsgId        msgToLoad
        ,       XMLCh* const    toFill
        , const XMLSize_t       maxChars
        , const char* const     repText1
        , const char* const     repText2 = 0
        , const char* const     repText3 = 0
        , const char* const     repText4 = 0
        , MemoryManager* const  manager  = XMLPlatformUtils::fgMemoryManager
    ) = 0;

    /** @name Locale Handling  */
    //@{
    /**
      * This function enables set the locale information which
      * all concrete message loaders shall refer to during instantiation.
      *
      * Note: for detailed discussion, refer to PlatformUtils::initialize()
      */
    static void           setLocale(const char* const localeToAdopt);

    /**
      * For the derived to retrieve locale info during construction
      */
    static const char*    getLocale();

    //@}

    /** @name NLSHome Handling  */
    //@{
    /**
      * This function enables set the NLSHome information which
      * all concrete message loaders shall refer to during instantiation.
      *
      * Note: for detailed discussion, refer to PlatformUtils::initialize()
      */
    static void           setNLSHome(const char* const nlsHomeToAdopt);

    /**
      * For the derived to retrieve NLSHome info during construction
      */
    static const char*    getNLSHome();

    //@}

protected :
    // -----------------------------------------------------------------------
    //  Hidden Constructors
    // -----------------------------------------------------------------------
    XMLMsgLoader();

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLMsgLoader(const XMLMsgLoader&);
    XMLMsgLoader& operator=(const XMLMsgLoader&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocale
    //      Locale info set through PlatformUtils::init().
    //      The derived class may refer to this for locale information.
    //
    //  fPath
    //      NLSHome info set through PlatformUtils::init().
    //      The derived class may refer to this for NLSHome information.
    //
    // -----------------------------------------------------------------------
    static char*    fLocale;
    static char*    fPath;
};


// ---------------------------------------------------------------------------
//  XMLMsgLoader: Public Constructors and Destructor
// ---------------------------------------------------------------------------
inline XMLMsgLoader::~XMLMsgLoader()
{
}


// ---------------------------------------------------------------------------
//  XMLMsgLoader: Hidden Constructors
// ---------------------------------------------------------------------------
inline XMLMsgLoader::XMLMsgLoader()
{
}

XERCES_CPP_NAMESPACE_END

#endif
