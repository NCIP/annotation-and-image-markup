/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMNodeVector.hpp 676796 2008-07-15 05:04:13Z dbertoni $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMNODEVECTOR_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNODEVECTOR_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMNode;
class DOMDocument;


class  DOMNodeVector {
private:
    DOMNode        **data;
    XMLSize_t       allocatedSize;
    XMLSize_t       nextFreeSlot;
    void           init(DOMDocument *doc, XMLSize_t size);
    void           checkSpace();

    // unimplemented
    DOMNodeVector ( const DOMNodeVector& toCopy);
    DOMNodeVector& operator= (const DOMNodeVector& other);

public:
    DOMNodeVector(DOMDocument *doc);
    DOMNodeVector(DOMDocument *doc, XMLSize_t size);
    ~DOMNodeVector();

    XMLSize_t      size();
    DOMNode*       elementAt(XMLSize_t index);
    DOMNode*       lastElement();
    void           addElement(DOMNode *);
    void           insertElementAt(DOMNode *, XMLSize_t index);
    void           setElementAt(DOMNode *val, XMLSize_t index);
    void           removeElementAt(XMLSize_t index);
    void           reset();
};

inline DOMNode *DOMNodeVector::elementAt(XMLSize_t index) {
    if (index >= nextFreeSlot)
        return 0;
	return data[index];
}

inline DOMNode *DOMNodeVector::lastElement() {
	if (nextFreeSlot == 0)
		return 0;
	return data[nextFreeSlot-1];
}

inline XMLSize_t DOMNodeVector::size() {
	return nextFreeSlot;
}

XERCES_CPP_NAMESPACE_END

#endif
