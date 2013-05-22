/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMStringListImpl.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMSTRINGLISTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMSTRINGLISTIMPL_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/RefVectorOf.hpp>
#include <xercesc/dom/DOMStringList.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMStringListImpl: public XMemory,
                                     public DOMStringList
{
protected:
    RefVectorOf<XMLCh>   *fList;

private:
    // Unused, and unimplemented constructors, operators, etc.
    DOMStringListImpl(const DOMStringListImpl & other);
    DOMStringListImpl & operator = (const DOMStringListImpl & other);

public:
    DOMStringListImpl(int nInitialSize, MemoryManager* manager);
    void add(const XMLCh* impl);

    virtual ~DOMStringListImpl();
    virtual const XMLCh* item(XMLSize_t index) const;
    virtual XMLSize_t    getLength() const;
    virtual bool         contains(const XMLCh* str) const;
    virtual void         release();
};

XERCES_CPP_NAMESPACE_END

#endif
