/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMCharacterDataImpl.hpp 678709 2008-07-22 10:56:56Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMCHARACTERDATAIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCHARACTERDATAIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMNode;
class DOMDocument;
class DOMDocumentImpl;
class DOMBuffer;

// Instances of DOMCharacterDataImpl appear as members of node types
//   that implement the DOMCharacterData interfaces.
//   Operations in those classes are delegated to this class.
//
class CDOM_EXPORT DOMCharacterDataImpl
{
public:
    DOMBuffer* fDataBuf;
    // for the buffer bid
    DOMDocumentImpl* fDoc;

public:
                   DOMCharacterDataImpl(DOMDocument *doc, const XMLCh *dat);
                   DOMCharacterDataImpl(DOMDocument *doc, const XMLCh* data, XMLSize_t n);
                   DOMCharacterDataImpl(const DOMCharacterDataImpl &other);
                   ~DOMCharacterDataImpl();
    const          XMLCh * getNodeValue() const;
    void           setNodeValue(const XMLCh * value);
    void           appendData(const DOMNode *node, const  XMLCh *data);
    void           appendData(const DOMNode *node, const  XMLCh *data, XMLSize_t n);
    void           deleteData(const DOMNode *node, XMLSize_t offset, XMLSize_t count);
    const XMLCh*   getData() const;
    XMLSize_t      getLength() const;
    void           insertData(const DOMNode *node, XMLSize_t offset, const XMLCh * data);
    void           replaceData(const DOMNode *node, XMLSize_t offset, XMLSize_t count, const XMLCh * data);
    void           setData(const DOMNode *node, const XMLCh * arg);
    void           setNodeValue(const DOMNode *node, const XMLCh *value);


    const XMLCh*   substringData(const DOMNode *node, XMLSize_t offset, XMLSize_t count) const;
    void           releaseBuffer();

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMCharacterDataImpl & operator = (const DOMCharacterDataImpl &);
};

#define GetDOMCharacterDataImplMemoryManager GET_DIRECT_MM(fDoc)

XERCES_CPP_NAMESPACE_END


#endif
