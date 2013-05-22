/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: WinSockNetAccessor.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_WINSOCKNETACCESSOR_HPP)
#define XERCESC_INCLUDE_GUARD_WINSOCKNETACCESSOR_HPP


#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/util/XMLNetAccessor.hpp>


XERCES_CPP_NAMESPACE_BEGIN

//
// This class is the wrapper for the WinSock library which provides
// support for sockets. Its being used here to add the ability to
// use HTTP URL's as the system id's in the XML decl clauses.
//

class XMLUTIL_EXPORT WinSockNetAccessor : public XMLNetAccessor
{
public :
    WinSockNetAccessor();
    ~WinSockNetAccessor();

    virtual BinInputStream* makeNew(const XMLURL&  urlSource, const XMLNetHTTPInfo* httpInfo=0);
    virtual const XMLCh* getId() const;

private :
    static const XMLCh fgMyName[];

    WinSockNetAccessor(const WinSockNetAccessor&);
    WinSockNetAccessor& operator=(const WinSockNetAccessor&);

}; // WinSockNetAccessor

inline const XMLCh* WinSockNetAccessor::getId() const
{
    return fgMyName;
}

XERCES_CPP_NAMESPACE_END


#endif // WINSOCKNETACCESSOR_HPP
