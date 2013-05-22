/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMErrorHandler.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMERRORHANDLER_HPP)
#define XERCESC_INCLUDE_GUARD_DOMERRORHANDLER_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMError;

/**
  * Basic interface for DOM error handlers.
  *
  * <p>DOMErrorHandler is a callback interface that the DOM implementation
  * can call when reporting errors that happens while processing XML data, or
  * when doing some other processing (e.g. validating a document).</p>
  *
  * <p>The application that is using the DOM implementation is expected to
  * implement this interface.</p>
  *
  * @see DOMLSParser#getDomConfig
  * @since DOM Level 3
  */

class CDOM_EXPORT DOMErrorHandler
{
protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{    
    DOMErrorHandler() {};
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented constructors and operators */
    //@{
    DOMErrorHandler(const DOMErrorHandler &);
    DOMErrorHandler & operator = (const DOMErrorHandler &);
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
    virtual ~DOMErrorHandler() {};
    //@}

    // -----------------------------------------------------------------------
    //  Virtual DOMErrorHandler interface
    // -----------------------------------------------------------------------
    /** @name Functions introduced in DOM Level 3 */
    //@{
    /**
     * This method is called on the error handler when an error occurs.
     * If an exception is thrown from this method, it is considered to be equivalent of returning <code>true</code>.
     *
     * @param domError The error object that describes the error, this object
     *                 may be reused by the DOM implementation across multiple
     *                 calls to the handleError method.
     * @return If the handleError method returns <code>true</code> the DOM
     *         implementation should continue as if the error didn't happen
     *         when possible, if the method returns <code>false</code> then the
     *         DOM implementation should stop the current processing when
     *         possible.
     *
     * @since DOM Level 3
     */
    virtual bool handleError(const DOMError& domError) = 0;
    //@}

};

XERCES_CPP_NAMESPACE_END

#endif
