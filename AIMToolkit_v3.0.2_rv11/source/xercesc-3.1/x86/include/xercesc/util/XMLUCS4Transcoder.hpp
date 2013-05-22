/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLUCS4Transcoder.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLUCS4TRANSCODER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLUCS4TRANSCODER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/TransService.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This class provides an implementation of the XMLTranscoder interface
//  for a simple UCS4 transcoder. The parser does some encodings
//  intrinsically without depending upon external transcoding services.
//  To make everything more orthogonal, we implement these internal
//  transcoders using the same transcoder abstraction as the pluggable
//  transcoding services do.
//
class XMLUTIL_EXPORT XMLUCS4Transcoder : public XMLTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Public constructors and destructor
    // -----------------------------------------------------------------------
    XMLUCS4Transcoder
    (
        const   XMLCh* const    encodingName
        , const XMLSize_t       blockSize
        , const bool            swapped
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual ~XMLUCS4Transcoder();


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
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLUCS4Transcoder(const XMLUCS4Transcoder&);
    XMLUCS4Transcoder& operator=(const XMLUCS4Transcoder&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSwapped
    //      This tells us if our input is going to be in the same endianness
    //      as the local host or swapped.
    // -----------------------------------------------------------------------
    bool    fSwapped;
};

XERCES_CPP_NAMESPACE_END

#endif
