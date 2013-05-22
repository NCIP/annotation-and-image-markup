/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLNumber.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLNUMBER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLNUMBER_HPP

#include <xercesc/internal/XSerializable.hpp>
#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT XMLNumber : public XSerializable, public XMemory
{
public:

    enum
    {
        LESS_THAN     = -1,
        EQUAL         = 0,
        GREATER_THAN  = 1,
        INDETERMINATE = 2
    };

    enum NumberType {
        Float,
        Double,
        BigDecimal,
        DateTime,
        UnKnown
    };

    virtual ~XMLNumber();
    
	/**
	 *  Return string representation of the decimal value.
     *  A decimal point will be included as necessary.
     *  Similar to toString above, but the internal buffer is
     *  returned directly, user is not required to delete
     *  the returned buffer
	 */
    virtual XMLCh*     getRawData() const = 0;    

    /**
     *  Return the original and converted value of the original data.
     *  (applicable to double/float)
     *
     *  The internal buffer is returned directly, user is not required 
     *  to delete the returned buffer
     */
    virtual const XMLCh*     getFormattedString() const = 0;    

	/**
	 * Returns the sign of this number
     *
     * -1   negative
     *  0   zero
     *  1   positive
	 *
	 */
    virtual int        getSign() const = 0;

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLNumber)

    static XMLNumber*          loadNumber(XMLNumber::NumberType   numType
                                        , XSerializeEngine&       serEng);

protected:

    XMLNumber();
    XMLNumber(const XMLNumber&);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented operators
    // -----------------------------------------------------------------------
    XMLNumber& operator=(const XMLNumber&);
};

XERCES_CPP_NAMESPACE_END

#endif
