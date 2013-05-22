/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DefaultPanicHandler.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DEFAULT_PANICHANDLER_HPP)
#define XERCESC_INCLUDE_GUARD_DEFAULT_PANICHANDLER_HPP

#include <xercesc/util/PanicHandler.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * Receive notification of panic.
  *
  * <p>This is Xerces' default implementation of the PanicHanlder 
  *    interface, which will be instantiated and used in the 
  *    absence of an application's panic handler.
  * </p>
  */

class XMLUTIL_EXPORT DefaultPanicHandler : public XMemory, public PanicHandler
{
public:

    /** @name hidden Constructors */
    //@{
    /** Default constructor */
    DefaultPanicHandler(){};

    /** Destructor */
    virtual ~DefaultPanicHandler(){};
    //@}

    /** @name Implement virtual panic handler interface */
    //@{
   /**
    * Receive notification of panic
    *
    * <p>Upon invocation, a corresponding error message will be output 
    *    to the stderr, and program exit.
    * </p>
    *
    * @param reason The reason of panic
    *
    */
    virtual void panic(const PanicHandler::PanicReasons reason);
    //@}

private:

    /* Unimplemented Constructors and operators */
    /* Copy constructor */
    DefaultPanicHandler(const PanicHandler&);
    
    /** Assignment operator */
    DefaultPanicHandler& operator=(const DefaultPanicHandler&);

};

XERCES_CPP_NAMESPACE_END

#endif
