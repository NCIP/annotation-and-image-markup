/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLInternalErrorHandler.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLINTERNALERRORHANDLER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLINTERNALERRORHANDLER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLInternalErrorHandler : public ErrorHandler
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XMLInternalErrorHandler(ErrorHandler* userHandler = 0) :
       fSawWarning(false),
       fSawError(false),
       fSawFatal(false),
       fUserErrorHandler(userHandler)
    {
    }

    ~XMLInternalErrorHandler()
    {
    }

    // -----------------------------------------------------------------------
    //  Implementation of the error handler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& toCatch);
    void error(const SAXParseException& toCatch);
    void fatalError(const SAXParseException& toCatch);
    void resetErrors();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getSawWarning() const;
    bool getSawError() const;
    bool getSawFatal() const;

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSawWarning
    //      This is set if we get any warning, and is queryable via a getter
    //      method.
    //
    //  fSawError
    //      This is set if we get any errors, and is queryable via a getter
    //      method.
    //
    //  fSawFatal
    //      This is set if we get any fatal, and is queryable via a getter
    //      method.
    //
    //  fUserErrorHandler
    //      This is the error handler from user
    // -----------------------------------------------------------------------
    bool    fSawWarning;
    bool    fSawError;
    bool    fSawFatal;
    ErrorHandler* fUserErrorHandler;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLInternalErrorHandler(const XMLInternalErrorHandler&);
    XMLInternalErrorHandler& operator=(const XMLInternalErrorHandler&);
};

inline bool XMLInternalErrorHandler::getSawWarning() const
{
    return fSawWarning;
}

inline bool XMLInternalErrorHandler::getSawError() const
{
    return fSawError;
}

inline bool XMLInternalErrorHandler::getSawFatal() const
{
    return fSawFatal;
}

inline void XMLInternalErrorHandler::warning(const SAXParseException& toCatch)
{
    fSawWarning = true;
    if (fUserErrorHandler)
        fUserErrorHandler->warning(toCatch);
}

inline void XMLInternalErrorHandler::error(const SAXParseException& toCatch)
{
    fSawError = true;
    if (fUserErrorHandler)
        fUserErrorHandler->error(toCatch);
}

inline void XMLInternalErrorHandler::fatalError(const SAXParseException& toCatch)
{
    fSawFatal = true;
    if (fUserErrorHandler)
        fUserErrorHandler->fatalError(toCatch);
}

inline void XMLInternalErrorHandler::resetErrors()
{
    fSawWarning = false;
    fSawError = false;
    fSawFatal = false;
}

XERCES_CPP_NAMESPACE_END

#endif
