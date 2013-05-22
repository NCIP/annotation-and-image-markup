/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DateTimeDatatypeValidator.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DATETIME_DATATYPE_VALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_DATETIME_DATATYPE_VALIDATOR_HPP

#include <xercesc/validators/datatype/DateTimeValidator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT DateTimeDatatypeValidator : public DateTimeValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public ctor/dtor
    // -----------------------------------------------------------------------
	/** @name Constructors and Destructor */
    //@{

    DateTimeDatatypeValidator
    (
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    DateTimeDatatypeValidator
    (
        DatatypeValidator* const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , RefArrayVectorOf<XMLCh>* const enums
        , const int finalSet
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    ~DateTimeDatatypeValidator();

	//@}

    /**
      * Returns an instance of the base datatype validator class
	  * Used by the DatatypeValidatorFactory.
      */
    virtual DatatypeValidator* newInstance
    (
        RefHashTableOf<KVStringPair>* const facets
        , RefArrayVectorOf<XMLCh>* const enums
        , const int finalSet
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual const XMLCh* getCanonicalRepresentation
                        (
                          const XMLCh*         const rawData
                        ,       MemoryManager* const memMgr = 0
                        ,       bool                 toValidate = false
                        ) const;

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(DateTimeDatatypeValidator)

protected:

    // -----------------------------------------------------------------------
    //  implementation of (DateTimeValidator's) virtual interface
    // -----------------------------------------------------------------------
    virtual XMLDateTime*          parse(const XMLCh* const, MemoryManager* const manager);
    virtual void                  parse(XMLDateTime* const);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DateTimeDatatypeValidator(const DateTimeDatatypeValidator&);
    DateTimeDatatypeValidator& operator=(const DateTimeDatatypeValidator&);
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file DateTimeDatatypeValidator.hpp
  */

