/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLFloat.hpp 673155 2008-07-01 17:55:39Z dbertoni $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XML_FLOAT_HPP)
#define XERCESC_INCLUDE_GUARD_XML_FLOAT_HPP

#include <xercesc/util/XMLAbstractDoubleFloat.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT XMLFloat : public XMLAbstractDoubleFloat
{
public:

	/**
	 * Constructs a newly allocated <code>XMLFloat</code> object that
	 * represents the value represented by the string.
	 *
	 * @param      strValue the <code>String</code> to be converted to an
	 *                      <code>XMLFloat</code>.
         * @param manager    Pointer to the memory manager to be used to
         *                   allocate objects.
	 * @exception  NumberFormatException  if the <code>String</code> does not
	 *               contain a parsable XMLFloat.
	 */

    XMLFloat(const XMLCh* const strValue,
             MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    ~XMLFloat();

	/**
	 * Compares the two specified XMLFloat objects.
	 * The result is <code>true</code> if and only if the argument is not
	 * <code>null</code> and that contains the same <code>int</code> value.
	 *
	 * @param   lValue the object to compare with.
	 * @param   rValue the object to compare against.
	 * @return  <code>true</code> if the objects are the same;
	 *          <code>false</code> otherwise.
	 */

    inline static int            compareValues(const XMLFloat* const lValue
                                             , const XMLFloat* const rValue);

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLFloat)

    XMLFloat(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

protected:

    virtual void          checkBoundary(char* const strValue);

private:
    //
    // Unimplemented
    //
    // copy ctor
    // assignment ctor
    //
    XMLFloat(const XMLFloat& toCopy);
    XMLFloat& operator=(const XMLFloat& toAssign);

};

inline int XMLFloat::compareValues(const XMLFloat* const lValue
                                 , const XMLFloat* const rValue)
{
    return XMLAbstractDoubleFloat::compareValues((const XMLAbstractDoubleFloat*) lValue,
                                                 (const XMLAbstractDoubleFloat*) rValue 
                                                 , ((XMLAbstractDoubleFloat*)lValue)->getMemoryManager());
}

XERCES_CPP_NAMESPACE_END

#endif
