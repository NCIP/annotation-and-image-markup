/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMRangeException.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMRANGEEXCEPTION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMRANGEEXCEPTION_HPP

#include <xercesc/dom/DOMException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * Range operations may throw a <code>DOMRangeException</code> as specified in
 * their method descriptions.
 * <p>See also the <a href='http://www.w3.org/TR/2000/REC-DOM-Level-2-Traversal-Range-20001113'>Document Object Model (DOM) Level 2 Traversal and Range Specification</a>.
 * @since DOM Level 2
 */

class CDOM_EXPORT DOMRangeException  : public DOMException {
public:
    // -----------------------------------------------------------------------
    //  Class Types
    // -----------------------------------------------------------------------
    /** @name Public Constants */
    //@{
    /**
     * Enumerators for DOM Range Exceptions
     *
     * <p><code>BAD_BOUNDARYPOINTS_ERR:</code>
     * If the boundary-points of a Range do not meet specific requirements.</p>
     *
     * <p><code>INVALID_NODE_TYPE_ERR:</code>
     * If the container of an boundary-point of a Range is being set to either
     * a node of an invalid type or a node with an ancestor of an invalid
     * type.</p>
     *
     * @since DOM Level 2
     */
        enum RangeExceptionCode {
                BAD_BOUNDARYPOINTS_ERR  = 111,
                INVALID_NODE_TYPE_ERR   = 112
        };
    //@}

public:
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{
    /**
      * Default constructor for DOMRangeException.
      *
      */
    DOMRangeException();

    /**
      * Constructor which takes an error code and a message.
      *
      * @param code           The error code which indicates the exception
      * @param messageCode    The string containing the error message
      * @param memoryManager  The memory manager used to (de)allocate memory
      */
    DOMRangeException(short code,
                      short messageCode,
                      MemoryManager*     const memoryManager);

    /**
      * Copy constructor.
      *
      * @param other The object to be copied.
      */
    DOMRangeException(const DOMRangeException &other);
    //@}

    // -----------------------------------------------------------------------
    //  Destructors
    // -----------------------------------------------------------------------
    /** @name Destructor. */
    //@{
	 /**
	  * Destructor for DOMRangeException.
	  *
	  */
    virtual ~DOMRangeException();
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMRangeException & operator = (const DOMRangeException &);
};

XERCES_CPP_NAMESPACE_END

#endif
