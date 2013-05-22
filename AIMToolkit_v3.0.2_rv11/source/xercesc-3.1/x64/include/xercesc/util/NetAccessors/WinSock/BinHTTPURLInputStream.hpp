/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: BinHTTPURLInputStream.hpp 670359 2008-06-22 13:43:45Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_BINHTTPURLINPUTSTREAM_HPP)
#define XERCESC_INCLUDE_GUARD_BINHTTPURLINPUTSTREAM_HPP


#include <xercesc/util/NetAccessors/BinHTTPInputStreamCommon.hpp>

#include <winsock2.h>

XERCES_CPP_NAMESPACE_BEGIN

//
// This class implements the BinInputStream interface specified by the XML
// parser.
//
class XMLUTIL_EXPORT BinHTTPURLInputStream : public BinHTTPInputStreamCommon
{
public :
    BinHTTPURLInputStream(const XMLURL&  urlSource, const XMLNetHTTPInfo* httpInfo=0);
    ~BinHTTPURLInputStream();

    virtual bool send(const char *buf, XMLSize_t len);
    virtual int receive(char *buf, XMLSize_t len);

	static void Cleanup();

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    BinHTTPURLInputStream(const BinHTTPURLInputStream&);
    BinHTTPURLInputStream& operator=(const BinHTTPURLInputStream&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSocketHandle
    //      The socket representing the connection to the remote file.
    //      We deliberately did not define the type to be SOCKET, so as to
    //      avoid bringing in any Windows header into this file.
    // -----------------------------------------------------------------------
    SOCKET              fSocketHandle;

    static bool         fInitialized;

    static void Initialize(MemoryManager* const manager  = XMLPlatformUtils::fgMemoryManager);
};

XERCES_CPP_NAMESPACE_END

#endif // BINHTTPURLINPUTSTREAM_HPP
