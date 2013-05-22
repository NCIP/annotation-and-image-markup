/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMImplementationListImpl.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMIMPLEMENTATIONLISTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMIMPLEMENTATIONLISTIMPL_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/RefVectorOf.hpp>
#include <xercesc/dom/DOMImplementationList.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMImplementation;

class CDOM_EXPORT DOMImplementationListImpl: public DOMImplementationList
{
protected:
    RefVectorOf<DOMImplementation>   *fList;

private:
    // Unused, and unimplemented constructors, operators, etc.
    DOMImplementationListImpl(const DOMImplementationListImpl & other);
    DOMImplementationListImpl & operator = (const DOMImplementationListImpl & other);

public:
    DOMImplementationListImpl();
    void add(DOMImplementation* impl);

    virtual             ~DOMImplementationListImpl();
    virtual DOMImplementation *  item(XMLSize_t index) const;
    virtual XMLSize_t            getLength() const;
    virtual void                 release();
};

XERCES_CPP_NAMESPACE_END

#endif
