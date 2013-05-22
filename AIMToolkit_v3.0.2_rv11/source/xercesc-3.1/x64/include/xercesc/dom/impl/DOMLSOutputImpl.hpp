/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMLSOutputImpl.hpp 641193 2008-03-26 08:06:57Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMLSOUTPUTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMLSOUTPUTIMPL_HPP

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CDOM_EXPORT DOMLSOutputImpl : public XMemory, public DOMLSOutput
{

public:

    DOMLSOutputImpl(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~DOMLSOutputImpl();

    virtual XMLFormatTarget* getByteStream() const;
    virtual const XMLCh* getEncoding() const;
    virtual const XMLCh* getSystemId() const;

    virtual void setByteStream(XMLFormatTarget* stream);
    virtual void setEncoding(const XMLCh* const encodingStr);
    virtual void setSystemId(const XMLCh* const systemId);

    virtual void release();

private:

    /** unimplemented copy ctor and assignment operator */
    DOMLSOutputImpl(const DOMLSOutputImpl&);
    DOMLSOutputImpl & operator = (const DOMLSOutputImpl&);

protected:
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fByteStream
    //    We don't own it
    //
    //  fEncoding
    //    We own it
    //
    //  fSystemId
    //    We own it
    // 
    // -----------------------------------------------------------------------

    XMLFormatTarget              *fByteStream;
    XMLCh                        *fEncoding;
    XMLCh                        *fSystemId;
    MemoryManager*               fMemoryManager;
};

inline XMLFormatTarget* DOMLSOutputImpl::getByteStream() const
{
    return fByteStream;
}

inline const XMLCh* DOMLSOutputImpl::getEncoding() const
{
    return fEncoding;
}

inline const XMLCh* DOMLSOutputImpl::getSystemId() const
{
    return fSystemId;
}

XERCES_CPP_NAMESPACE_END

#endif
