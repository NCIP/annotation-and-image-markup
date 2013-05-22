/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: Locator.hpp 672273 2008-06-27 13:57:00Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_LOCATOR_HPP)
#define XERCESC_INCLUDE_GUARD_LOCATOR_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * Interface for associating a SAX event with a document location.
  *
  * <p>If a SAX parser provides location information to the SAX
  * application, it does so by implementing this interface and then
  * passing an instance to the application using the document
  * handler's setDocumentLocator method.  The application can use the
  * object to obtain the location of any other document handler event
  * in the XML source document.</p>
  *
  * <p>Note that the results returned by the object will be valid only
  * during the scope of each document handler method: the application
  * will receive unpredictable results if it attempts to use the
  * locator at any other time.</p>
  *
  * <p>SAX parsers are not required to supply a locator, but they are
  * very strong encouraged to do so.  If the parser supplies a
  * locator, it must do so before reporting any other document events.
  * If no locator has been set by the time the application receives
  * the startDocument event, the application should assume that a
  * locator is not available.</p>
  *
  * @see DocumentHandler#setDocumentLocator
  */

class SAX_EXPORT Locator
{
public:

    /** @name Constructors and Destructor */
    //@{
    /** Default constructor */
    Locator()
    {
    }

    /** Destructor */
    virtual ~Locator()
    {
    }

    //@}

    /** @name The locator interface */
    //@{
  /**
    * Return the public identifier for the current document event.
    * <p>This will be the public identifier
    * @return A string containing the public identifier, or
    *         null if none is available.
    * @see #getSystemId
    */
    virtual const XMLCh* getPublicId() const = 0;

  /**
    * Return the system identifier for the current document event.
    *
    * <p>If the system identifier is a URL, the parser must resolve it
    * fully before passing it to the application.</p>
    *
    * @return A string containing the system identifier, or null
    *         if none is available.
    * @see #getPublicId
    */
    virtual const XMLCh* getSystemId() const = 0;

  /**
    * Return the line number where the current document event ends.
    * Note that this is the line position of the first character
    * after the text associated with the document event.
    * @return The line number, or 0 if none is available.
    * @see #getColumnNumber
    */
    virtual XMLFileLoc getLineNumber() const = 0;

  /**
    * Return the column number where the current document event ends.
    * Note that this is the column number of the first
    * character after the text associated with the document
    * event.  The first column in a line is position 1.
    * @return The column number, or 0 if none is available.
    * @see #getLineNumber
    */
    virtual XMLFileLoc getColumnNumber() const = 0;
    //@}

private :
    /* Copy constructor */
    Locator(const Locator&);

    /* Assignment operator */
    Locator& operator=(const Locator&);
};

XERCES_CPP_NAMESPACE_END

#endif
