/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: StDOMNode.hpp 570480 2007-08-28 16:36:34Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_STDOMNODE_HPP)
#define XERCESC_INCLUDE_GUARD_STDOMNODE_HPP

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMElement.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/* This class is a smart pointer implementation over DOMNode interface and
** classes derived from it. It takes care of reference counting automatically.
** Reference counting is optional so use of this class is experimental.
*/
template <class T> class StDOMNode {
	T* m_node;

	static inline void INCREFCOUNT(T *x) { if (x != (T*)0) x->incRefCount(); }
	static inline void DECREFCOUNT(T *x) { if (x != (T*)0) x->decRefCount(); }

public:
	inline StDOMNode(T* node = (T*)0) : m_node(node) { INCREFCOUNT(m_node); }
	inline StDOMNode(const StDOMNode& stNode) : m_node(stNode.m_node) { INCREFCOUNT(m_node); }
	inline ~StDOMNode() { DECREFCOUNT(m_node); }

	inline T* operator= (T *node)
	{
		if (m_node != node) {
			DECREFCOUNT(m_node);
			m_node = node;
			INCREFCOUNT(m_node);
		}
		return (m_node);
	}

	inline bool operator!= (T* node) const { return (m_node != node); }
	inline bool operator== (T* node) const { return (m_node == node); }

	inline T& operator* () { return (*m_node); }
	inline const T& operator* () const { return (*m_node); }
	inline T* operator-> () const { return (m_node); }
	inline operator T*() const { return (m_node); }
	inline void ClearNode() { operator=((T*)(0)); }
};

#if defined(XML_DOMREFCOUNT_EXPERIMENTAL)
    typedef StDOMNode<DOMNode> DOMNodeSPtr;
#else
    typedef DOMNode* DOMNodeSPtr;
#endif

/* StDOMNode is a smart pointer implementation over DOMNode interface and
** classes derived from it. It takes care of reference counting automatically.
** Reference counting is optional so use of this class is experimental.
*/
#if defined(XML_DOMREFCOUNT_EXPERIMENTAL)
    typedef StDOMNode<DOMAttr> DOMAttrSPtr;
#else
    typedef DOMAttr* DOMAttrSPtr;
#endif

/* StDOMNode is a smart pointer implementation over DOMNode interface and
** classes derived from it. It takes care of reference counting automatically.
** Reference counting is optional so use of this class is experimental.
*/
#if defined(XML_DOMREFCOUNT_EXPERIMENTAL)
    typedef StDOMNode<DOMElement> DOMElementSPtr;
#else
    typedef DOMElement* DOMElementSPtr;
#endif

XERCES_CPP_NAMESPACE_END

#endif

