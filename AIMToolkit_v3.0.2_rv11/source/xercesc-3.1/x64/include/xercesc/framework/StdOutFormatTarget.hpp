/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: StdOutFormatTarget.hpp 553937 2007-07-06 16:02:19Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_STDOUTFORMATTARGET_HPP)
#define XERCESC_INCLUDE_GUARD_STDOUTFORMATTARGET_HPP

#include <xercesc/framework/XMLFormatter.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLPARSER_EXPORT StdOutFormatTarget : public XMLFormatTarget {
public:

    /** @name constructors and destructor */
    //@{
    StdOutFormatTarget() ;
    ~StdOutFormatTarget();
    //@}

    // -----------------------------------------------------------------------
    //  Implementations of the format target interface
    // -----------------------------------------------------------------------
    virtual void writeChars(const XMLByte* const toWrite
                          , const XMLSize_t      count
                          , XMLFormatter* const  formatter);

    virtual void flush();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented methods.
    // -----------------------------------------------------------------------
    StdOutFormatTarget(const StdOutFormatTarget&);
    StdOutFormatTarget& operator=(const StdOutFormatTarget&);
};

XERCES_CPP_NAMESPACE_END

#endif
