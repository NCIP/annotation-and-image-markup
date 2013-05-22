/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMXPathResultImpl.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMXPATHRESULTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMXPATHRESULTIMPL_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/dom/DOMXPathResult.hpp>
#include <xercesc/util/RefVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CDOM_EXPORT DOMXPathResultImpl :  public XMemory,
                                        public DOMXPathResult
{
public:
    DOMXPathResultImpl(ResultType type, MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~DOMXPathResultImpl();

    virtual ResultType getResultType() const;
    virtual const DOMTypeInfo *getTypeInfo() const;
    virtual bool isNode() const;
    virtual bool getBooleanValue() const;
    virtual int getIntegerValue() const;
    virtual double getNumberValue() const;
    virtual const XMLCh* getStringValue() const;
    virtual DOMNode* getNodeValue() const;
    virtual bool iterateNext();
    virtual bool getInvalidIteratorState() const;
    virtual bool snapshotItem(XMLSize_t);
    virtual XMLSize_t getSnapshotLength() const;

    virtual void release();

public:
    void reset(ResultType type);
    void addResult(DOMNode* node);

protected:
    ResultType              fType;
    MemoryManager* const    fMemoryManager;
    RefVectorOf<DOMNode>*   fSnapshot;
    XMLSize_t               fIndex;
};

XERCES_CPP_NAMESPACE_END

#endif
