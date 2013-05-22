/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMXPathNSResolverImpl.hpp 657774 2008-05-19 09:59:33Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMXPATHNSRESOLVERIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMXPATHNSRESOLVERIMPL_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOMXPathNSResolver.hpp>
#include <xercesc/util/KVStringPair.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class DOMNode;

class CDOM_EXPORT DOMXPathNSResolverImpl : public XMemory,
                                           public DOMXPathNSResolver
{
public:
    DOMXPathNSResolverImpl(const DOMNode* nodeResolver = 0, MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~DOMXPathNSResolverImpl();

    virtual const XMLCh*          lookupNamespaceURI(const XMLCh* prefix) const;
    virtual const XMLCh*          lookupPrefix(const XMLCh* URI) const;
    virtual void                  addNamespaceBinding(const XMLCh* prefix, const XMLCh* uri);

    virtual void                  release();

protected:
    RefHashTableOf<KVStringPair>* fNamespaceBindings;
    const DOMNode*                fResolverNode;
    MemoryManager*                fManager;
};

XERCES_CPP_NAMESPACE_END

#endif


