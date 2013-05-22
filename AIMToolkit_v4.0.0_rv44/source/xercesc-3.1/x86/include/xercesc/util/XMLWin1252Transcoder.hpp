/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLWin1252Transcoder.hpp 570552 2007-08-28 19:57:36Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLWIN1252TRANSCODER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLWIN1252TRANSCODER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XML256TableTranscoder.hpp>

XERCES_CPP_NAMESPACE_BEGIN


//
//  This class provides an implementation of the XMLTranscoder interface
//  for the Windows variant of Latin1, called Windows-1252. Its close to
//  Latin1, but is somewhat different.
//
class XMLUTIL_EXPORT XMLWin1252Transcoder : public XML256TableTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Public constructors and destructor
    // -----------------------------------------------------------------------
    XMLWin1252Transcoder
    (
        const   XMLCh* const   encodingName
        , const XMLSize_t      blockSize
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual ~XMLWin1252Transcoder();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLWin1252Transcoder();
    XMLWin1252Transcoder(const XMLWin1252Transcoder&);
    XMLWin1252Transcoder& operator=(const XMLWin1252Transcoder&);
};

XERCES_CPP_NAMESPACE_END

#endif
