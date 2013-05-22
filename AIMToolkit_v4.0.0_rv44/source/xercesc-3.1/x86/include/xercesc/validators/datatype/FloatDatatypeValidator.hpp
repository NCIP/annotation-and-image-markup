/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: FloatDatatypeValidator.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_FLOAT_DATATYPEVALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_FLOAT_DATATYPEVALIDATOR_HPP

#include <xercesc/validators/datatype/AbstractNumericValidator.hpp>
#include <xercesc/util/RefVectorOf.hpp>
#include <xercesc/util/XMLFloat.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT FloatDatatypeValidator : public AbstractNumericValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public ctor/dtor
    // -----------------------------------------------------------------------
	/** @name Constructors and Destructor */
    //@{
    FloatDatatypeValidator
    (
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    FloatDatatypeValidator
    (
        DatatypeValidator* const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , RefArrayVectorOf<XMLCh>* const enums
        , const int finalSet
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    virtual ~FloatDatatypeValidator();

	//@}

    // -----------------------------------------------------------------------
    // Compare methods
    // -----------------------------------------------------------------------
    /** @name Compare Function */
    //@{

    /**
     * Compare two boolean data types
     *
     * @param content1
     * @param content2
     * @return
     */
    virtual int compare(const XMLCh* const, const XMLCh* const
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
        );

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

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(FloatDatatypeValidator)

protected:

    // -----------------------------------------------------------------------
    // ctor provided to be used by derived classes
    // -----------------------------------------------------------------------
    FloatDatatypeValidator
    (
        DatatypeValidator* const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , const int finalSet
        , const ValidatorType type
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    // -----------------------------------------------------------------------
    // Abstract interface from AbstractNumericFacetValidator
    // -----------------------------------------------------------------------

    virtual int  compareValues(const XMLNumber* const lValue
                             , const XMLNumber* const rValue);

    virtual void  setMaxInclusive(const XMLCh* const);

    virtual void  setMaxExclusive(const XMLCh* const);

    virtual void  setMinInclusive(const XMLCh* const);

    virtual void  setMinExclusive(const XMLCh* const);

    virtual void  setEnumeration(MemoryManager* const manager);

// -----------------------------------------------------------------------
// Abstract interface from AbstractNumericValidator
// -----------------------------------------------------------------------

    virtual void checkContent(const XMLCh*             const content
                            ,       ValidationContext* const context
                            , bool                           asBase
                            ,       MemoryManager*     const manager);
private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    FloatDatatypeValidator(const FloatDatatypeValidator&);
    FloatDatatypeValidator& operator = (const  FloatDatatypeValidator&);
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file FloatDatatypeValidator.hpp
  */
