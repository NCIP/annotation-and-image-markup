/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMProcessingInstruction.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMPROCESSINGINSTRUCTION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMPROCESSINGINSTRUCTION_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMNode.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
 * The <code>DOMProcessingInstruction</code> interface represents a  "processing
 * instruction", used in XML as a way to keep processor-specific information
 * in the text of the document.
 *
 * @since DOM Level 1
 */
class  CDOM_EXPORT DOMProcessingInstruction: public DOMNode {
protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{    
    DOMProcessingInstruction() {}
    DOMProcessingInstruction(const DOMProcessingInstruction &other) : DOMNode(other) {}
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented operators */
    //@{
    DOMProcessingInstruction & operator = (const DOMProcessingInstruction &);
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
    virtual ~DOMProcessingInstruction() {};
    //@}

    // -----------------------------------------------------------------------
    //  Virtual DOMProcessingInstruction interface
    // -----------------------------------------------------------------------
    /** @name Functions introduced in DOM Level 1 */
    //@{
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    /**
     * The target of this processing instruction.
     *
     * XML defines this as being the
     * first token following the markup that begins the processing instruction.
     *
     * @since DOM Level 1
     */
    virtual const XMLCh *        getTarget() const = 0;

    /**
     * The content of this processing instruction.
     *
     * This is from the first non
     * white space character after the target to the character immediately
     * preceding the <code>?&gt;</code>.
     * @exception DOMException
     *   NO_MODIFICATION_ALLOWED_ERR: Raised when the node is readonly.
     * @since DOM Level 1
     */
    virtual const XMLCh *        getData() const = 0;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    /**
     * Sets the content of this processing instruction.
     *
     * This is from the first non
     * white space character after the target to the character immediately
     * preceding the <code>?&gt;</code>.
     * @param data The string containing the processing instruction
     * @since DOM Level 1
     */
    virtual void             setData(const XMLCh * data) = 0;
    //@}

};

XERCES_CPP_NAMESPACE_END

#endif

