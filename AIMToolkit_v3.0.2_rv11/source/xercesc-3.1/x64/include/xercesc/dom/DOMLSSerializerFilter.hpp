/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMLSSerializerFilter.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMLSSERIALIZERFILTER_HPP)
#define XERCESC_INCLUDE_GUARD_DOMLSSERIALIZERFILTER_HPP

/**
 *
 * DOMLSSerializerFilter.hpp: interface for the DOMLSSerializerFilter class.
 *
 * DOMLSSerializerFilter provide applications the ability to examine nodes
 * as they are being serialized.
 *
 * DOMLSSerializerFilter lets the application decide what nodes should be
 * serialized or not.
 *
 * The DOMDocument, DOMDocumentType, DOMNotation, and DOMEntity nodes are not passed
 * to the filter.
 *
 * @since DOM Level 3
 */


#include <xercesc/dom/DOMNodeFilter.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMLSSerializerFilter : public DOMNodeFilter {
protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{
    DOMLSSerializerFilter() {};
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented constructors and operators */
    //@{
    DOMLSSerializerFilter(const DOMLSSerializerFilter &);
    DOMLSSerializerFilter & operator = (const DOMLSSerializerFilter &);
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
    virtual ~DOMLSSerializerFilter() {};
    //@}

    // -----------------------------------------------------------------------
    //  Virtual DOMLSSerializerFilter interface
    // -----------------------------------------------------------------------
    /** @name Functions introduced in DOM Level 3 */
    //@{
	 /**
     * Interface from <code>DOMNodeFilter</code>,
     * to be implemented by implementation (derived class)
     */
    virtual FilterAction acceptNode(const DOMNode* node) const = 0;

    /**
     * Tells the DOMLSSerializer what types of nodes to show to the filter.
     * See <code>DOMNodeFilter</code> for definition of the constants.
     * The constant SHOW_ATTRIBUTE is meaningless here, attribute nodes will
     * never be passed to a DOMLSSerializerFilter.
     *
     * @return The constants of what types of nodes to show.
     * @since DOM Level 3
     */
    virtual ShowType getWhatToShow() const =0;
    //@}
};

XERCES_CPP_NAMESPACE_END

#endif
