/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMLSInputImpl.hpp 641193 2008-03-26 08:06:57Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMLSINPUTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMLSINPUTIMPL_HPP

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMLSInput.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CDOM_EXPORT DOMLSInputImpl : public XMemory, public DOMLSInput
{

public:

    DOMLSInputImpl(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~DOMLSInputImpl();

    virtual const XMLCh* getStringData() const;
    virtual InputSource* getByteStream() const;
    virtual const XMLCh* getEncoding() const;
    virtual const XMLCh* getPublicId() const;
    virtual const XMLCh* getSystemId() const;
    virtual const XMLCh* getBaseURI() const;

    virtual void setStringData(const XMLCh* data);
    virtual void setByteStream(InputSource* stream);
    virtual void setEncoding(const XMLCh* const encodingStr);
    virtual void setPublicId(const XMLCh* const publicId);
    virtual void setSystemId(const XMLCh* const systemId);
    virtual void setBaseURI(const XMLCh* const baseURI);

    virtual void setIssueFatalErrorIfNotFound(bool flag);
    virtual bool getIssueFatalErrorIfNotFound() const;
    virtual void release();


private:
    /** unimplemented copy ctor and assignment operator */
    DOMLSInputImpl(const DOMLSInputImpl&);
    DOMLSInputImpl & operator = (const DOMLSInputImpl&);

protected:
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fStringData
    //    We don't own it
    //
    //  fByteStream
    //    We don't own it
    //
    //  fEncoding
    //    We own it
    //
    //  fPublicId
    //    We own it
    //
    //  fSystemId
    //    We own it
    //
    //  fBaseURI
    //    We own it
    // 
    // -----------------------------------------------------------------------

    const XMLCh                  *fStringData;
    InputSource                  *fByteStream;
    XMLCh                        *fEncoding;
    XMLCh                        *fPublicId;
    XMLCh                        *fSystemId;
    XMLCh                        *fBaseURI;
    bool                         fIssueFatalErrorIfNotFound;
    MemoryManager*               fMemoryManager;
};

inline const XMLCh* DOMLSInputImpl::getStringData() const
{
    return fStringData;
}

inline InputSource* DOMLSInputImpl::getByteStream() const
{
    return fByteStream;
}

inline const XMLCh* DOMLSInputImpl::getEncoding() const
{
    return fEncoding;
}

inline const XMLCh* DOMLSInputImpl::getPublicId() const
{
    return fPublicId;
}

inline const XMLCh* DOMLSInputImpl::getSystemId() const
{
    return fSystemId;
}

inline const XMLCh* DOMLSInputImpl::getBaseURI() const
{
    return fBaseURI;
}

inline bool DOMLSInputImpl::getIssueFatalErrorIfNotFound() const
{
    return fIssueFatalErrorIfNotFound;
}


XERCES_CPP_NAMESPACE_END

#endif
