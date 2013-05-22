/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

 /*
 * $Id: XMLErrorReporter.hpp 672273 2008-06-27 13:57:00Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLERRORREPORTER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLERRORREPORTER_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
 *  This abstract class defines a callback mechanism for the scanner. By
 *  creating a class that implements this interface and plugging an instance
 *  of that class into the scanner, the scanner will call back on the object's
 *  virtual methods to report error events. This class is also used with the
 *  validator, to allow it to report errors.
 *
 *  This class is primarily for use by those writing their own parser classes.
 *  If you use the standard parser classes, DOMParser and SAXParser, you won't
 *  use this API. You will instead use a similar mechanism defined by the SAX
 *  API, called ErrorHandler.
 */
class XMLPARSER_EXPORT XMLErrorReporter
{
public:
    // -----------------------------------------------------------------------
    //  The types of errors we can issue
    // -----------------------------------------------------------------------
    enum ErrTypes
    {
        ErrType_Warning
        , ErrType_Error
        , ErrType_Fatal

        , ErrTypes_Unknown
    };


    // -----------------------------------------------------------------------
    //  Constructors are hidden, only the virtual destructor is exposed
    // -----------------------------------------------------------------------

    /** @name Destructor */
    //@{

    /**
      *   Default destructor
      */
    virtual ~XMLErrorReporter()
    {
    }
    //@}


    // -----------------------------------------------------------------------
    //  The error handler interface
    // -----------------------------------------------------------------------

    /** @name Error Handler interface */
    //@{

    /** Called to report errors from the scanner or validator
      *
      * This method is called back on by the scanner or validator (or any other
      * internal parser component which might need to report an error in the
      * future.) It contains all the information that the client code might
      * need to report or log the error.
      *
      * @param  errCode     The error code of the error being reported. What
      *                     this means is dependent on the domain it is from.
      *
      * @param  errDomain   The domain from which the error occured. The domain
      *                     is a means of providing a hierarchical layering to
      *                     the error system, so that a single set of error id
      *                     numbers don't have to be split up.
      *
      * @param  type        The error type, which is defined mostly by XML which
      *                     categorizes errors into warning, errors and validity
      *                     constraints.
      *
      * @param  errorText   The actual text of the error. This is translatable,
      *                     so can possibly be in the local language if a
      *                     translation has been provided.
      *
      * @param  systemId    The system id of the entity where the error occured,
      *                     fully qualified.
      *
      * @param  publicId    The optional public id of the entity were the error
      *                     occured. It can be an empty string if non was provided.
      *
      * @param  lineNum     The line number within the source XML of the error.
      *
      * @param  colNum      The column number within the source XML of the error.
      *                     Because of the parsing style, this is usually just
      *                     after the actual offending text.
      */
    virtual void error
    (
        const   unsigned int        errCode
        , const XMLCh* const        errDomain
        , const ErrTypes            type
        , const XMLCh* const        errorText
        , const XMLCh* const        systemId
        , const XMLCh* const        publicId
        , const XMLFileLoc          lineNum
        , const XMLFileLoc          colNum
    ) = 0;

    /** Called before a new parse event to allow the handler to reset
      *
      * This method is called by the scanner before a new parse event is
      * about to start. It gives the error handler a chance to reset its
      * internal state.
      */
    virtual void resetErrors() = 0;

    //@}


protected :

    /** @name Constructor */
    //@{

    /**
      *   Default constructor
      */
    XMLErrorReporter()
    {
    }
    //@}

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and destructor
    // -----------------------------------------------------------------------
    XMLErrorReporter(const XMLErrorReporter&);
    XMLErrorReporter& operator=(const XMLErrorReporter&);
};

XERCES_CPP_NAMESPACE_END

#endif
