/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMLocatorImpl.hpp 676853 2008-07-15 09:58:05Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMLOCATORIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMLOCATORIMPL_HPP

#include <xercesc/dom/DOMLocator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * Introduced in DOM Level 3
  *
  * Implementation of a DOMLocator interface.
  *
  * @see DOMLocator#DOMLocator
  */

class CDOM_EXPORT DOMLocatorImpl : public DOMLocator
{
public:
    /** @name Constructors and Destructor */
    //@{

    /** Constructor */
    DOMLocatorImpl();

    DOMLocatorImpl
    (
          const XMLFileLoc lineNum
        , const XMLFileLoc columnNum
        , DOMNode* const errorNode
        , const XMLCh* const uri
        , const XMLFilePos offset = ~(XMLFilePos(0))
        , const XMLFilePos utf16Offset = ~(XMLFilePos(0))
    );

    /** Desctructor */
    virtual ~DOMLocatorImpl();

    //@}

    // DOMLocator interface
    virtual XMLFileLoc getLineNumber() const;
    virtual XMLFileLoc getColumnNumber() const;
    virtual XMLFilePos getByteOffset() const;
    virtual XMLFilePos getUtf16Offset() const;
    virtual DOMNode* getRelatedNode() const;
    virtual const XMLCh* getURI() const;

    // Setter functions
    void setLineNumber(const XMLFileLoc lineNumber);
    void setColumnNumber(const XMLFileLoc columnNumber);
    void setByteOffset(const XMLFilePos offset);
    void setUtf16Offset(const XMLFilePos offset);
    void setRelatedNode(DOMNode* const errorNode);
    void setURI(const XMLCh* const uri);


private :
    /* Unimplemented constructors and operators */

    /* Copy constructor */
    DOMLocatorImpl(const DOMLocatorImpl&);

    /* Assignment operator */
    DOMLocatorImpl& operator=(const DOMLocatorImpl&);

protected:
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLineNum
    //  fColumnNum
    //      Track line/column number of where the error occured
    //
    //  fByteOffset
    //      Track byte offset in the input source where the error
    //      occured
    //
    //  fUtf16Offset
    //      Track character offset in the input source where the error
    //      occured
    //
    //  fRelatedNode
    //      Current node where the error occured
    //
    //  fURI
    //      The uri where the error occured
    // -----------------------------------------------------------------------
    XMLFileLoc       fLineNum;
    XMLFileLoc       fColumnNum;
    XMLFilePos      fByteOffset;
    XMLFilePos      fUtf16Offset;
    DOMNode*        fRelatedNode;
    const XMLCh*    fURI;
};


// ---------------------------------------------------------------------------
//  DOMLocatorImpl: Getter methods
// ---------------------------------------------------------------------------
inline XMLFileLoc DOMLocatorImpl::getLineNumber() const
{
    return fLineNum;
}

inline XMLFileLoc DOMLocatorImpl::getColumnNumber() const
{
    return fColumnNum;
}

inline XMLFilePos DOMLocatorImpl::getByteOffset() const
{
    return fByteOffset;
}

inline XMLFilePos DOMLocatorImpl::getUtf16Offset() const
{
    return fUtf16Offset;
}

inline DOMNode* DOMLocatorImpl::getRelatedNode() const
{
    return fRelatedNode;
}

inline const XMLCh* DOMLocatorImpl::getURI() const
{
    return fURI;
}


// ---------------------------------------------------------------------------
//  DOMLocatorImpl: Setter methods
// ---------------------------------------------------------------------------
inline void DOMLocatorImpl::setLineNumber(const XMLFileLoc lineNumber)
{
    fLineNum = lineNumber;
}

inline void DOMLocatorImpl::setColumnNumber(const XMLFileLoc columnNumber)
{
    fColumnNum = columnNumber;
}

inline void DOMLocatorImpl::setByteOffset(const XMLFilePos offset)
{
    fByteOffset = offset;
}

inline void DOMLocatorImpl::setUtf16Offset(const XMLFilePos offset)
{
    fUtf16Offset = offset;
}

inline void DOMLocatorImpl::setRelatedNode(DOMNode* const errorNode)
{
    fRelatedNode = errorNode;
}

inline void DOMLocatorImpl::setURI(const XMLCh* const uri)
{
    fURI = uri;
}

XERCES_CPP_NAMESPACE_END

#endif
