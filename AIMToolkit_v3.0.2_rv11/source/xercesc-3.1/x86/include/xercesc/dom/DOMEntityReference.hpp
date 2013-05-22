/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMEntityReference.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMENTITYREFERENCE_HPP)
#define XERCESC_INCLUDE_GUARD_DOMENTITYREFERENCE_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMNode.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
 * <code>DOMEntityReference</code> objects may be inserted into the structure
 * model when an entity reference is in the source document, or when the
 * user wishes to insert an entity reference. Note that character references
 * and references to predefined entities are considered to be expanded by
 * the HTML or XML processor so that characters are represented by their
 * Unicode equivalent rather than by an entity reference. Moreover, the XML
 * processor may completely expand references to entities while building the
 * structure model, instead of providing <code>DOMEntityReference</code>
 * objects. If it does provide such objects, then for a given
 * <code>DOMEntityReference</code> node, it may be that there is no
 * <code>DOMEntity</code> node representing the referenced entity. If such an
 * <code>DOMEntity</code> exists, then the subtree of the
 * <code>DOMEntityReference</code> node is in general a copy of the
 * <code>DOMEntity</code> node subtree. However, this may not be true when an
 * entity contains an unbound namespace prefix. In such a case, because the
 * namespace prefix resolution depends on where the entity reference is, the
 * descendants of the <code>DOMEntityReference</code> node may be bound to
 * different namespace URIs.
 * <p>As for <code>DOMEntity</code> nodes, <code>DOMEntityReference</code> nodes and
 * all their descendants are readonly.
 * <p>See also the <a href='http://www.w3.org/TR/2000/REC-DOM-Level-2-Core-20001113'>Document Object Model (DOM) Level 2 Core Specification</a>.
 *
 * @since DOM Level 1
 */

class CDOM_EXPORT DOMEntityReference: public DOMNode {
protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{    
    DOMEntityReference() {}
    DOMEntityReference(const DOMEntityReference &other) : DOMNode(other) {}
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented operators */
    //@{
    DOMEntityReference & operator = (const DOMEntityReference &);
    //@}

public:
    // -----------------------------------------------------------------------
    //  All constructors are hidden, just the destructor is available
    // -----------------------------------------------------------------------
    /** @name Destructor */
    //@{
    /**
     * Destructor
     *
     */
    virtual ~DOMEntityReference() {};
    //@}

};

XERCES_CPP_NAMESPACE_END

#endif


