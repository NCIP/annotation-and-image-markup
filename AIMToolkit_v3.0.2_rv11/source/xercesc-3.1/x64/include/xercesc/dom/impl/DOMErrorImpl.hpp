/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMErrorImpl.hpp 676853 2008-07-15 09:58:05Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMERRORIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMERRORIMPL_HPP

#include <xercesc/dom/DOMError.hpp>
#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
  * Introduced in DOM Level 3
  * Implementation of a DOMError interface.
  *
  * @see DOMError#DOMError
  */

class CDOM_EXPORT DOMErrorImpl : public DOMError
{
public:
    /** @name Constructors and Destructor */
    //@{

    /** Constructors */
    DOMErrorImpl(const ErrorSeverity severity);

    DOMErrorImpl
    (
        const ErrorSeverity severity
        , const XMLCh* const message
        , DOMLocator* const location
    );

    DOMErrorImpl
    (
        const ErrorSeverity severity
        , const XMLCh* type
        , const XMLCh* message
        , void* relatedData
    );

    /** Desctructor */
    virtual ~DOMErrorImpl();

    //@}

    // DOMError interface
    virtual ErrorSeverity getSeverity() const;
    virtual const XMLCh* getMessage() const;
    virtual DOMLocator* getLocation() const;
    virtual void* getRelatedException() const;
    virtual const XMLCh* getType() const;
    virtual void* getRelatedData() const;

    // Setters
    void setSeverity(const ErrorSeverity severity);
    void setMessage(const XMLCh* const message);
    void setLocation(DOMLocator* const location);
    void setAdoptLocation(const bool value);
    void setRelatedException(void* exc) const;
    void setType(const XMLCh* type);
    void setRelatedData(void* relatedData);

private:
    /* Unimplemented constructors and operators */

    /* Copy constructor */
    DOMErrorImpl(const DOMErrorImpl&);

    /* Assignment operator */
    DOMErrorImpl& operator=(const DOMErrorImpl&);

protected:
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fAdoptLocation
    //      Indicates whether we own the DOMLocator object or not.
    //
    //  fSeverity
    //      The type of the error.
    //
    //  fMessage
    //      The error message.
    //
    //  fLocation
    //      The location info of the error.
    //
    //  fType
    //      The type of the error.
    //
    //  fRelatedData
    //      The data related to this error.
    //
    // -----------------------------------------------------------------------
    bool          fAdoptLocation;
    ErrorSeverity fSeverity;
    const XMLCh*  fMessage;
    DOMLocator*   fLocation;
    const XMLCh*  fType;
    void*         fRelatedData;
};

// ---------------------------------------------------------------------------
//  DOMErrorImpl: Getter methods
// ---------------------------------------------------------------------------
inline DOMError::ErrorSeverity DOMErrorImpl::getSeverity() const
{
    return fSeverity;
}

inline const XMLCh* DOMErrorImpl::getMessage() const
{
    return fMessage;
}

inline DOMLocator* DOMErrorImpl::getLocation() const
{
    return fLocation;
}

inline void* DOMErrorImpl::getRelatedException() const
{
    return 0;
}

inline const XMLCh* DOMErrorImpl::getType() const
{
    return fType;
}

inline void* DOMErrorImpl::getRelatedData() const
{
    return fRelatedData;
}

// ---------------------------------------------------------------------------
//  DOMErrorImpl: Setter methods
// ---------------------------------------------------------------------------
inline void DOMErrorImpl::setSeverity(const ErrorSeverity severity)
{
    fSeverity = severity;
}

inline void DOMErrorImpl::setMessage(const XMLCh* const message)
{
    fMessage = message;
}

inline void DOMErrorImpl::setAdoptLocation(const bool value)
{
    fAdoptLocation = value;
}

inline void DOMErrorImpl::setType(const XMLCh* type)
{
    fType = type;
}

inline void DOMErrorImpl::setRelatedData(void* relatedData)
{
    fRelatedData = relatedData;
}


XERCES_CPP_NAMESPACE_END

#endif
