/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: PSVIDefs.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_PSVIDEFS_HPP)
#define XERCESC_INCLUDE_GUARD_PSVIDEFS_HPP

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT PSVIDefs
{
public:
    enum PSVIScope
    {
        SCP_ABSENT    // declared in group/attribute group
	    , SCP_GLOBAL  // global declaration or ref
	    , SCP_LOCAL   // local declaration
    };
};

XERCES_CPP_NAMESPACE_END

#endif
