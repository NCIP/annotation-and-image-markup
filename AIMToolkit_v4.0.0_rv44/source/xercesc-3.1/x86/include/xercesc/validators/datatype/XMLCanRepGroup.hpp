/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLCanRepGroup.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLCANREPGROUP_HPP)
#define XERCESC_INCLUDE_GUARD_XMLCANREPGROUP_HPP

#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT XMLCanRepGroup : public XMemory
{
public:

    enum CanRepGroup {
        Boolean,
        DoubleFloat,
        DateTime,
        Time,
        Decimal,
        Decimal_Derived_signed,
        Decimal_Derived_unsigned,
        Decimal_Derived_npi,
        String
    };

    ~XMLCanRepGroup();

    XMLCanRepGroup(CanRepGroup val);

    inline CanRepGroup    getGroup() const;

private:

    CanRepGroup    fData;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLCanRepGroup(const XMLCanRepGroup&);
	XMLCanRepGroup& operator=(const XMLCanRepGroup&);

};

inline XMLCanRepGroup::CanRepGroup XMLCanRepGroup::getGroup() const
{
    return fData;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file XMLCanRepGroup.hpp
  */

