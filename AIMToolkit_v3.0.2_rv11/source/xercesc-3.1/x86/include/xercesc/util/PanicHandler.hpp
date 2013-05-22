/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: PanicHandler.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_PANICHANDLER_HPP)
#define XERCESC_INCLUDE_GUARD_PANICHANDLER_HPP

#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * Receive notification of panic.
  *
  * <p>This is the interface, through which the Xercesc reports
  *    a panic to the application. 
  * </p>
  *
  * <p>Application may implement this interface, instantiate an
  *    object of the derivative, and plug it to Xercesc in the
  *    invocation to XMLPlatformUtils::Initialize(), if it prefers 
  *    to handling panic itself rather than Xercesc doing it.
  * </p>
  *
  */

class XMLUTIL_EXPORT PanicHandler
{
public:

    /** @name Public Types */
    //@{
    enum PanicReasons
    {
          Panic_NoTransService
        , Panic_NoDefTranscoder
        , Panic_CantFindLib
        , Panic_UnknownMsgDomain
        , Panic_CantLoadMsgDomain
        , Panic_SynchronizationErr
        , Panic_SystemInit
        , Panic_AllStaticInitErr
        , Panic_MutexErr
        , PanicReasons_Count
    };
    //@}

protected:

    /** @name hidden Constructors */
    //@{
    /** Default constructor */
    PanicHandler(){};

public:

    /** Destructor */
    virtual ~PanicHandler(){};   
    //@}

    /** @name The virtual panic handler interface */
    //@{
   /**
    * Receive notification of panic
    *
    * This method is called when an unrecoverable error has occurred in the Xerces library.  
    *
    * This method must not return normally, otherwise, the results are undefined. 
    * 
    * Ways of handling this call could include throwing an exception or exiting the process.
    *
    * Once this method has been called, the results of calling any other Xerces API, 
    * or using any existing Xerces objects are undefined.    
    *
    * @param reason The reason of panic
    *
    */
    virtual void panic(const PanicHandler::PanicReasons reason) = 0;
    //@}

    static const char* getPanicReasonString(const PanicHandler::PanicReasons reason);
    
private:

    /* Unimplemented Constructors and operators */
    /* Copy constructor */
    PanicHandler(const PanicHandler&);
    
    /** Assignment operator */
    PanicHandler& operator=(const PanicHandler&);
};

XERCES_CPP_NAMESPACE_END

#endif
