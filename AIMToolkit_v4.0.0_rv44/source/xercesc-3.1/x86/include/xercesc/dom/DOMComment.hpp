/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMComment.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMCOMMENT_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCOMMENT_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMCharacterData.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
 * This interface inherits from <code>CharacterData</code> and represents the
 * content of a comment, i.e., all the characters between the starting '
 * <code>&lt;!--</code>' and ending '<code>--&gt;</code>'.
 * <p>See also the <a href='http://www.w3.org/TR/2000/REC-DOM-Level-2-Core-20001113'>Document Object Model (DOM) Level 2 Core Specification</a>.
 *
 * @since DOM Level 1
 */
class CDOM_EXPORT DOMComment: public DOMCharacterData {
protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{    
    DOMComment() {};
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented constructors and operators */
    //@{
    DOMComment(const DOMComment &);
    DOMComment & operator = (const DOMComment &);
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
    virtual ~DOMComment() {};
    //@}
};

XERCES_CPP_NAMESPACE_END

#endif

