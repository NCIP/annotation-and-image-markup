/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSDLocator.hpp 672273 2008-06-27 13:57:00Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSDLOCATOR_HPP)
#define XERCESC_INCLUDE_GUARD_XSDLOCATOR_HPP

/**
  * A Locator implementation
  */

#include <xercesc/util/XMemory.hpp>
#include <xercesc/sax/Locator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT XSDLocator: public XMemory, public Locator
{
public:

    /** @name Constructors and Destructor */
    //@{
    /** Default constructor */
    XSDLocator();

    /** Destructor */
    virtual ~XSDLocator()
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
    virtual const XMLCh* getPublicId() const;

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
    virtual const XMLCh* getSystemId() const;

  /**
    * Return the line number where the current document event ends.
    * Note that this is the line position of the first character
    * after the text associated with the document event.
    * @return The line number, or 0 if none is available.
    * @see #getColumnNumber
    */
    virtual XMLFileLoc getLineNumber() const;

  /**
    * Return the column number where the current document event ends.
    * Note that this is the column number of the first
    * character after the text associated with the document
    * event.  The first column in a line is position 1.
    * @return The column number, or 0 if none is available.
    * @see #getLineNumber
    */
    virtual XMLFileLoc getColumnNumber() const;
    //@}

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setValues(const XMLCh* const systemId,
                   const XMLCh* const publicId,
                   const XMLFileLoc lineNo, const XMLFileLoc columnNo);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and destructor
    // -----------------------------------------------------------------------
    XSDLocator(const XSDLocator&);
    XSDLocator& operator=(const XSDLocator&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    XMLFileLoc fLineNo;
    XMLFileLoc fColumnNo;
    const XMLCh* fSystemId;
    const XMLCh* fPublicId;
};

// ---------------------------------------------------------------------------
//  XSDLocator: Getter methods
// ---------------------------------------------------------------------------
inline XMLFileLoc XSDLocator::getLineNumber() const
{
    return fLineNo;
}

inline XMLFileLoc XSDLocator::getColumnNumber() const
{
    return fColumnNo;
}

inline const XMLCh* XSDLocator::getPublicId() const
{
    return fPublicId;
}

inline const XMLCh* XSDLocator::getSystemId() const
{
    return fSystemId;
}

XERCES_CPP_NAMESPACE_END

#endif
