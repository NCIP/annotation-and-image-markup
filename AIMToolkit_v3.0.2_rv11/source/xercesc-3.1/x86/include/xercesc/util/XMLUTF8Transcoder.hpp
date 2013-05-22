/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLUTF8Transcoder.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLUTF8TRANSCODER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLUTF8TRANSCODER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/UTFDataFormatException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This class provides an implementation of the XMLTranscoder interface
//  for a simple UTF8 transcoder. The parser does some encodings
//  intrinsically without depending upon external transcoding services.
//  To make everything more orthogonal, we implement these internal
//  transcoders using the same transcoder abstraction as the pluggable
//  transcoding services do.
//
class XMLUTIL_EXPORT XMLUTF8Transcoder : public XMLTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Public constructors and destructor
    // -----------------------------------------------------------------------
    XMLUTF8Transcoder
    (
        const   XMLCh* const   encodingName
        , const XMLSize_t      blockSize
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual ~XMLUTF8Transcoder();


    // -----------------------------------------------------------------------
    //  Implementation of the XMLTranscoder interface
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

    inline void checkTrailingBytes(
                                    const XMLByte      toCheck
                                  , const unsigned int trailingBytes
                                  , const unsigned int position       
                                  ) const;

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLUTF8Transcoder(const XMLUTF8Transcoder&);
    XMLUTF8Transcoder& operator=(const XMLUTF8Transcoder&);
};

inline 
void XMLUTF8Transcoder::checkTrailingBytes(const XMLByte      toCheck
                                          , const unsigned int trailingBytes
                                          , const unsigned int position) const
{

    if((toCheck & 0xC0) != 0x80) 
    {
        char len[2]  = {(char)(trailingBytes+0x31), 0};
        char pos[2]  = {(char)(position+0x31), 0};
        char byte[2] = {toCheck,0};
        ThrowXMLwithMemMgr3(UTFDataFormatException, XMLExcepts::UTF8_FormatError, pos, byte, len, getMemoryManager());
    }

}

XERCES_CPP_NAMESPACE_END

#endif
