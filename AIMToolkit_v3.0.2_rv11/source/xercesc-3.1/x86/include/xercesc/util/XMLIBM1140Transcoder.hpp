/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLIBM1140Transcoder.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLIBM1140TRANSCODER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLIBM1140TRANSCODER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XML256TableTranscoder.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This class provides an implementation of the XMLTranscoder interface
//  for a simple IBM-1140 transcoder. The parser does some encodings
//  intrinsically without depending upon external transcoding services.
//  To make everything more orthogonal, we implement these internal
//  transcoders using the same transcoder abstraction as the pluggable
//  transcoding services do.
//
class XMLUTIL_EXPORT XMLIBM1140Transcoder : public XML256TableTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Public, static methods
    // -----------------------------------------------------------------------
    static XMLCh xlatThisOne(const XMLByte toXlat);


    // -----------------------------------------------------------------------
    //  Public constructors and destructor
    // -----------------------------------------------------------------------
    XMLIBM1140Transcoder
    (
        const   XMLCh* const   encodingName
        , const XMLSize_t      blockSize
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual ~XMLIBM1140Transcoder();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLIBM1140Transcoder();
    XMLIBM1140Transcoder(const XMLIBM1140Transcoder&);
    XMLIBM1140Transcoder& operator=(const XMLIBM1140Transcoder&);
};

XERCES_CPP_NAMESPACE_END

#endif
