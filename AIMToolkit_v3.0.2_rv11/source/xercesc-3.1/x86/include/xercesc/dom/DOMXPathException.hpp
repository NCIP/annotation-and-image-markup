/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMXPathException.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMXPATHEXCEPTION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMXPATHEXCEPTION_HPP

#include <xercesc/dom/DOMException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * @since DOM Level 3
 */
class CDOM_EXPORT DOMXPathException : public DOMException
{
public:
    //@{
    /**
     * ExceptionCode
     * <br>INVALID_EXPRESSION_ERR The expression has a syntax error or otherwise
     * is not a legal expression according to the rules of the specific
     * <code>DOMXPathEvaluator</code> or contains specialized extension functions
     * or variables not supported by this implementation.
     * <br>TYPE_ERR The expression cannot be converted to return the specified type.
     * <br>NO_RESULT_ERROR There is no current result in the result object.
     */
	enum ExceptionCode {
		INVALID_EXPRESSION_ERR = 51,
		TYPE_ERR = 52,
                NO_RESULT_ERROR = 53
	};
    //@}

public:
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{
    /**
      * Default constructor for DOMXPathException.
      *
      */
    DOMXPathException();

    /**
      * Constructor which takes an error code and a message.
      *
      * @param code The error code which indicates the exception
      * @param messageCode    The string containing the error message
      * @param memoryManager  The memory manager used to (de)allocate memory
      */
    DOMXPathException(short code,
                      short messageCode = 0,
                      MemoryManager* const  memoryManager = XMLPlatformUtils::fgMemoryManager);

    /**
      * Copy constructor.
      *
      * @param other The object to be copied.
      */
    DOMXPathException(const DOMXPathException  &other);

    //@}

    // -----------------------------------------------------------------------
    //  Destructors
    // -----------------------------------------------------------------------
    /** @name Destructor. */
    //@{
	 /**
	  * Destructor for DOMXPathException.
	  *
	  */
    virtual ~DOMXPathException();
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMXPathException& operator = (const DOMXPathException&);
};

XERCES_CPP_NAMESPACE_END

#endif
