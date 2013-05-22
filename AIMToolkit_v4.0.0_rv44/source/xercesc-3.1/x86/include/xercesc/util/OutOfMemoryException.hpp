/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: OutOfMemoryException.hpp 673960 2008-07-04 08:50:12Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_OUT_OF_MEMORY_EXCEPTION_HPP)
#define XERCESC_INCLUDE_GUARD_OUT_OF_MEMORY_EXCEPTION_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>
#include <xercesc/util/XMLUniDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

static const XMLCh gDefOutOfMemoryErrMsg[] =
{
        chLatin_O, chLatin_u, chLatin_t, chLatin_O
    ,   chLatin_f, chLatin_M, chLatin_e, chLatin_m
    ,   chLatin_o, chLatin_r, chLatin_y, chNull
};

class XMLUTIL_EXPORT OutOfMemoryException : public XMemory
{
public:

    OutOfMemoryException();
    ~OutOfMemoryException();
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XMLExcepts::Codes getCode() const;
    const XMLCh* getMessage() const;
    const XMLCh* getType() const;
    const char* getSrcFile() const;
    XMLFileLoc getSrcLine() const;

    OutOfMemoryException(const OutOfMemoryException& toCopy);
    OutOfMemoryException& operator=(const OutOfMemoryException& toAssign);
};

// constructors/destructors...
inline OutOfMemoryException::OutOfMemoryException() {}
inline OutOfMemoryException::~OutOfMemoryException() {}
inline OutOfMemoryException::OutOfMemoryException(const OutOfMemoryException& other) : XMemory(other) {}
inline OutOfMemoryException& OutOfMemoryException::operator=(const OutOfMemoryException&)
{
    return *this;
}

// ---------------------------------------------------------------------------
//  OutOfMemoryException: Getter methods
// ---------------------------------------------------------------------------
inline XMLExcepts::Codes OutOfMemoryException::getCode() const
{
    return XMLExcepts::Out_Of_Memory;
}

inline const XMLCh* OutOfMemoryException::getMessage() const
{
    return gDefOutOfMemoryErrMsg;
}

inline const XMLCh* OutOfMemoryException::getType() const
{
    return gDefOutOfMemoryErrMsg;
}

inline const char* OutOfMemoryException::getSrcFile() const
{
    return "";
}

inline XMLFileLoc OutOfMemoryException::getSrcLine() const {
    return 0;
}

XERCES_CPP_NAMESPACE_END

#endif
