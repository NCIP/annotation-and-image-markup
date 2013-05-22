/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XPathSymbols.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XPATHSYMBOLS_HPP)
#define XERCESC_INCLUDE_GUARD_XPATHSYMBOLS_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/*
 * Collection of symbols used to parse a Schema Grammar
 */

class VALIDATORS_EXPORT XPathSymbols
{
public :
    // -----------------------------------------------------------------------
    // Constant data
    // -----------------------------------------------------------------------
    static const XMLCh fgSYMBOL_AND[];
    static const XMLCh fgSYMBOL_OR[];
    static const XMLCh fgSYMBOL_MOD[];
    static const XMLCh fgSYMBOL_DIV[];
    static const XMLCh fgSYMBOL_COMMENT[];
    static const XMLCh fgSYMBOL_TEXT[];
    static const XMLCh fgSYMBOL_PI[];
    static const XMLCh fgSYMBOL_NODE[];
    static const XMLCh fgSYMBOL_ANCESTOR[];
    static const XMLCh fgSYMBOL_ANCESTOR_OR_SELF[];
    static const XMLCh fgSYMBOL_ATTRIBUTE[];
    static const XMLCh fgSYMBOL_CHILD[];
    static const XMLCh fgSYMBOL_DESCENDANT[];
    static const XMLCh fgSYMBOL_DESCENDANT_OR_SELF[];
    static const XMLCh fgSYMBOL_FOLLOWING[];
    static const XMLCh fgSYMBOL_FOLLOWING_SIBLING[];
    static const XMLCh fgSYMBOL_NAMESPACE[];
    static const XMLCh fgSYMBOL_PARENT[];
    static const XMLCh fgSYMBOL_PRECEDING[];
    static const XMLCh fgSYMBOL_PRECEDING_SIBLING[];
    static const XMLCh fgSYMBOL_SELF[];

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XPathSymbols();
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file XPathSymbols.hpp
  */

