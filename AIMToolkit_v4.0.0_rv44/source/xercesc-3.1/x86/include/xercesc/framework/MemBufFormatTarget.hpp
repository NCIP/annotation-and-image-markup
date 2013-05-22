/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: MemBufFormatTarget.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_MEMBUFFORMATTARGET_HPP)
#define XERCESC_INCLUDE_GUARD_MEMBUFFORMATTARGET_HPP

#include <xercesc/framework/XMLFormatter.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/*
 * The MemBufFormatTarget is a derivative from XMLFormatTarget, which user code
 * may plug into DOMLSSerializer to retrieve the serialized XML stream (from DOM Tree)
 * in a memory buffer.
 *
 * The MemBufFormatTarget is initialized to have a memory buffer of 1023 upon
 * construction, which grows as needed. The buffer will be deleted when
 * MemBufFormatTarget is destructed; or will be reset when the reset() function
 * is called.
 *
 * The MemBufFormatTarget returns a NULL terminated XMLByte stream upon request,
 * through the method getRawBuffer(), and user should make its own copy of the
 * returned buffer if it intends to keep it independent on the state of the
 * MemBufFormatTarget.
 */

class XMLPARSER_EXPORT MemBufFormatTarget : public XMLFormatTarget {
public:

    /** @name constructors and destructor */
    //@{
    MemBufFormatTarget
    (
          XMLSize_t            initCapacity = 1023
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    ) ;
    ~MemBufFormatTarget();
    //@}

    // -----------------------------------------------------------------------
    //  Implementations of the format target interface
    // -----------------------------------------------------------------------
    virtual void writeChars(const XMLByte* const toWrite
                          , const XMLSize_t      count
                          , XMLFormatter* const  formatter);

    // -----------------------------------------------------------------------
    //  Getter
    // -----------------------------------------------------------------------
    /** @name getRawBuffer */
    //@{
    /**
     * Returned the internal raw buffer.
     *
     */
    //@}
    const XMLByte* getRawBuffer() const;

    /** @name getLen */
    //@{
    /**
     * Returned the length of the raw buffer.
     *
     */
    //@}
    XMLSize_t getLen() const
    {
        return fIndex;
    }

    /** @name reset */
    //@{
    /**
     * Reset the internal string buffer.
     *
     */
    void reset();
    //@}

private:
    // -----------------------------------------------------------------------
    //  Unimplemented methods.
    // -----------------------------------------------------------------------
    MemBufFormatTarget(const MemBufFormatTarget&);
    MemBufFormatTarget& operator=(const MemBufFormatTarget&);

    // -----------------------------------------------------------------------
    //  Private helpers
    // -----------------------------------------------------------------------
    void ensureCapacity(const XMLSize_t extraNeeded);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fDataBuf
    //      The pointer to the buffer data. Its grown as needed. Its always
    //      one larger than fCapacity, to leave room for the null terminator.
    //
    //  fIndex
    //      The current index into the buffer, as characters are appended
    //      to it. If its zero, then the buffer is empty.
    //
    //  fCapacity
    //      The current capacity of the buffer. Its actually always one
    //      larger, to leave room for the null terminator.
    //
    // -----------------------------------------------------------------------
    MemoryManager*  fMemoryManager;
    XMLByte*        fDataBuf;
    XMLSize_t       fIndex;
    XMLSize_t       fCapacity;

};

XERCES_CPP_NAMESPACE_END

#endif

