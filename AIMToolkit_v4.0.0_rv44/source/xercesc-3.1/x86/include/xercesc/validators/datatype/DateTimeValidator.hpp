/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DateTimeValidator.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DATETIME_VALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_DATETIME_VALIDATOR_HPP

#include <xercesc/validators/datatype/AbstractNumericFacetValidator.hpp>
#include <xercesc/util/XMLDateTime.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT DateTimeValidator : public AbstractNumericFacetValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public dtor
    // -----------------------------------------------------------------------
	/** @name Constructor. */
    //@{

    virtual ~DateTimeValidator();

	//@}

	virtual void validate
                 (
                  const XMLCh*             const content
                ,       ValidationContext* const context = 0
                ,       MemoryManager*     const manager = XMLPlatformUtils::fgMemoryManager
                  );

    virtual int  compare(const XMLCh* const value1
                       , const XMLCh* const value2
                       , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
                       );

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(DateTimeValidator)

protected:

    // -----------------------------------------------------------------------
    //  ctor used by derived class
    // -----------------------------------------------------------------------
    DateTimeValidator
    (
        DatatypeValidator* const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , const int finalSet
        , const ValidatorType type
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //
    // Abstract interface
    //

    virtual int  compareValues(const XMLNumber* const lValue
                             , const XMLNumber* const rValue);

    virtual void checkContent(const XMLCh*             const content
                            ,       ValidationContext* const context
                            , bool                           asBase
                            ,       MemoryManager*     const manager);

    virtual void  setMaxInclusive(const XMLCh* const);

    virtual void  setMaxExclusive(const XMLCh* const);

    virtual void  setMinInclusive(const XMLCh* const);

    virtual void  setMinExclusive(const XMLCh* const);

    virtual void  setEnumeration(MemoryManager* const manager);

protected:

    // -----------------------------------------------------------------------
    //  helper interface: to be implemented/overwritten by derived class
    // -----------------------------------------------------------------------
    virtual XMLDateTime*   parse(const XMLCh* const, MemoryManager* const manager) = 0;
    virtual void parse(XMLDateTime* const) = 0;

    // to be overwritten by duration
    virtual int            compareDates(const XMLDateTime* const lValue
                                      , const XMLDateTime* const rValue
                                      , bool strict);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DateTimeValidator(const DateTimeValidator&);
    DateTimeValidator& operator=(const DateTimeValidator&);
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file DateTimeValidator.hpp
  */


