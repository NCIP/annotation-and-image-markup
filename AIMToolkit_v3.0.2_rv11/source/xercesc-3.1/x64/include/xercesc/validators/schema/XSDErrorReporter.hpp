/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSDErrorReporter.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSDERRORREPORTER_HPP)
#define XERCESC_INCLUDE_GUARD_XSDERRORREPORTER_HPP

#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class Locator;
class XMLErrorReporter;


/**
 *  This class reports schema errors
 */
class VALIDATORS_EXPORT XSDErrorReporter : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors are hidden, only the virtual destructor is exposed
    // -----------------------------------------------------------------------
    XSDErrorReporter(XMLErrorReporter* const errorReporter = 0);

    virtual ~XSDErrorReporter()
    {
    }

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getExitOnFirstFatal() const;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setErrorReporter(XMLErrorReporter* const errorReporter);
    void setExitOnFirstFatal(const bool newValue);

    // -----------------------------------------------------------------------
    //  Report error methods
    // -----------------------------------------------------------------------
    void emitError(const unsigned int toEmit,
                   const XMLCh* const msgDomain,
                   const Locator* const aLocator);
    void emitError(const unsigned int toEmit,
                   const XMLCh* const msgDomain,
                   const Locator* const aLocator,
                   const XMLCh* const text1,
                   const XMLCh* const text2 = 0,
                   const XMLCh* const text3 = 0,
                   const XMLCh* const text4 = 0,
                   MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
                   );
    void emitError(const XMLException&  except,
                   const Locator* const aLocator);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and destructor
    // -----------------------------------------------------------------------
    XSDErrorReporter(const XSDErrorReporter&);
    XSDErrorReporter& operator=(const XSDErrorReporter&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    bool              fExitOnFirstFatal;
    XMLErrorReporter* fErrorReporter;
};


// ---------------------------------------------------------------------------
//  XSDErrorReporter: Getter methods
// ---------------------------------------------------------------------------
inline bool XSDErrorReporter::getExitOnFirstFatal() const
{
    return fExitOnFirstFatal;
}

// ---------------------------------------------------------------------------
//  XSDErrorReporter: Setter methods
// ---------------------------------------------------------------------------
inline void XSDErrorReporter::setExitOnFirstFatal(const bool newValue)
{
    fExitOnFirstFatal = newValue;
}

inline void XSDErrorReporter::setErrorReporter(XMLErrorReporter* const errorReporter)
{
    fErrorReporter = errorReporter;
}

XERCES_CPP_NAMESPACE_END

#endif
