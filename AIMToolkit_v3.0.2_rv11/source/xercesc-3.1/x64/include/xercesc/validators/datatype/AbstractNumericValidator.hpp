/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: AbstractNumericValidator.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_ABSTRACT_NUMERIC_VALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_ABSTRACT_NUMERIC_VALIDATOR_HPP

#include <xercesc/validators/datatype/AbstractNumericFacetValidator.hpp>
#include <xercesc/util/RefVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT AbstractNumericValidator : public AbstractNumericFacetValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public ctor/dtor
    // -----------------------------------------------------------------------
	/** @name Constructor. */
    //@{

    virtual ~AbstractNumericValidator();

	//@}

	virtual void validate
                 (
                  const XMLCh*             const content
                ,       ValidationContext* const context = 0
                ,       MemoryManager*     const manager = XMLPlatformUtils::fgMemoryManager
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
    DECL_XSERIALIZABLE(AbstractNumericValidator)

protected:

    AbstractNumericValidator
    (
        DatatypeValidator* const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , const int finalSet
        , const ValidatorType type
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    inline void init(RefArrayVectorOf<XMLCh>*  const enums
        , MemoryManager* const manager);

    //
    // Abstract interface
    //
    virtual void checkContent(const XMLCh*             const content
                            ,       ValidationContext* const context
                            , bool                           asBase
                            , MemoryManager* const manager) = 0;

    void boundsCheck(const XMLNumber* const
                    , MemoryManager* const manager);

private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    AbstractNumericValidator(const AbstractNumericValidator&);
    AbstractNumericValidator& operator=(const AbstractNumericValidator&);
};

inline void AbstractNumericValidator::init(RefArrayVectorOf<XMLCh>*  const enums
                                           , MemoryManager* const manager)
{
    AbstractNumericFacetValidator::init(enums, manager);
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file AbstractNumericValidator.hpp
  */
