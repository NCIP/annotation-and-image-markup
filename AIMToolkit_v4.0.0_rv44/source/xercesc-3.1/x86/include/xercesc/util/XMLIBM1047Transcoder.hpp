/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLIBM1047Transcoder.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLIBM1047TRANSCODER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLIBM1047TRANSCODER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XML256TableTranscoder.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This class provides an implementation of the XMLTranscoder interface
//  for a simple 1047-US transcoder. The parser does some encodings
//  intrinsically without depending upon external transcoding services.
//  To make everything more orthogonal, we implement these internal
//  transcoders using the same transcoder abstraction as the pluggable
//  transcoding services do.
//
//
class XMLUTIL_EXPORT XMLIBM1047Transcoder : public XML256TableTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Public, static methods
    // -----------------------------------------------------------------------
    static XMLCh xlatThisOne(const XMLByte toXlat);


    // -----------------------------------------------------------------------
    //  Public constructors and destructor
    // -----------------------------------------------------------------------
    XMLIBM1047Transcoder
    (
        const   XMLCh* const   encodingName
        , const XMLSize_t      blockSize
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual ~XMLIBM1047Transcoder();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLIBM1047Transcoder();
    XMLIBM1047Transcoder(const XMLIBM1047Transcoder&);
    void operator=(const XMLIBM1047Transcoder&);
};

XERCES_CPP_NAMESPACE_END

#endif
