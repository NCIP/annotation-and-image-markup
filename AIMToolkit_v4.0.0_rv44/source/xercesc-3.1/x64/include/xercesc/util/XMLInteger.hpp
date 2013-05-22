/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLInteger.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XML_INTEGER_HPP)
#define XERCESC_INCLUDE_GUARD_XML_INTEGER_HPP

#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT XMLInteger : public XMemory
{
public:

	/**
	 * Constructs a newly allocated <code>XMLInteger</code> object
     *
	 * @param      intVal   the <code>integer</code>
	 */

	XMLInteger(const int intVal);

	~XMLInteger();

	/**
	 * Returns the built in integer value.
	 */
    int intValue() const;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLInteger(const XMLInteger&);
    XMLInteger& operator=(const XMLInteger&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
	//  fData
    //     the value
    //
    // -----------------------------------------------------------------------
    int         fData;

};

inline XMLInteger::XMLInteger(const int intVal)
:fData(intVal)
{
}

inline XMLInteger::~XMLInteger()
{
}

inline int XMLInteger::intValue() const
{
    return fData;
}

XERCES_CPP_NAMESPACE_END

#endif
