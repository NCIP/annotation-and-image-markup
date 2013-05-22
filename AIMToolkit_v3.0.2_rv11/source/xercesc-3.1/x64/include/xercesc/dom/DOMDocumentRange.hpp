/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMDocumentRange.hpp 527149 2007-04-10 14:56:39Z amassari $
*/

#if !defined(XERCESC_INCLUDE_GUARD_DOMDOCUMENTRANGE_HPP)
#define XERCESC_INCLUDE_GUARD_DOMDOCUMENTRANGE_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMRange;


/**
 * <p>See also the <a href='http://www.w3.org/TR/2000/REC-DOM-Level-2-Traversal-Range-20001113'>Document Object Model (DOM) Level 2 Traversal and Range Specification</a>.
 * @since DOM Level 2
 */
class CDOM_EXPORT DOMDocumentRange {

protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{    
    DOMDocumentRange() {};
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented constructors and operators */
    //@{
    DOMDocumentRange(const DOMDocumentRange &);
    DOMDocumentRange & operator = (const DOMDocumentRange &);
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
    virtual ~DOMDocumentRange() {};
    //@}

    // -----------------------------------------------------------------------
    //  Virtual DOMDocumentRange interface
    // -----------------------------------------------------------------------
    /** @name Functions introduced in DOM Level 2 */
    //@{
    /**
	  * To create the range  consisting of boundary-points and offset of the
     * selected contents
     *
     * @return The initial state of the Range such that both the boundary-points
     * are positioned at the beginning of the corresponding DOMDOcument, before
     * any content. The range returned can only be used to select content
     * associated with this document, or with documentFragments and Attrs for
     * which this document is the ownerdocument
     * @since DOM Level 2
	  */
    virtual DOMRange    *createRange() = 0;

    //@}
};


XERCES_CPP_NAMESPACE_END

#endif
