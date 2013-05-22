/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMNotation.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMNOTATION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNOTATION_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMNode.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
 * This interface represents a notation declared in the DTD. A notation either
 * declares, by name, the format of an unparsed entity (see section 4.7 of
 * the XML 1.0 specification), or is used for formal declaration of
 * Processing Instruction targets (see section 2.6 of the XML 1.0
 * specification). The <code>nodeName</code> attribute inherited from
 * <code>DOMNode</code> is set to the declared name of the notation.
 * <p>The DOM Level 1 does not support editing <code>DOMNotation</code> nodes;
 * they are therefore readonly.
 * <p>A <code>DOMNotation</code> node does not have any parent.
 *
 * @since DOM Level 1
 */
class CDOM_EXPORT DOMNotation: public DOMNode {
protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{    
    DOMNotation() {}
    DOMNotation(const DOMNotation &other) : DOMNode(other) {}
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented operators */
    //@{
    DOMNotation & operator = (const DOMNotation &);
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
    virtual ~DOMNotation() {};
    //@}


    // -----------------------------------------------------------------------
    //  Virtual DOMNotation interface
    // -----------------------------------------------------------------------
    /** @name Functions introduced in DOM Level 1 */
    //@{
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    /**
     * Get the public identifier of this notation.
     *
     * If the  public identifier was not
     * specified, this is <code>null</code>.
     * @return Returns the public identifier of the notation
     * @since DOM Level 1
     */
    virtual const XMLCh *getPublicId() const = 0;

    /**
     * Get the system identifier of this notation.
     *
     * If the  system identifier was not
     * specified, this is <code>null</code>.
     * @return Returns the system identifier of the notation
     * @since DOM Level 1
     */
    virtual const XMLCh *getSystemId() const = 0;


    //@}
};

XERCES_CPP_NAMESPACE_END

#endif


