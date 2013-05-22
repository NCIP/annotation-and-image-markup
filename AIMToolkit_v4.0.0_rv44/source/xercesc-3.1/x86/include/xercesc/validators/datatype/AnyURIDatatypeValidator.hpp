/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: AnyURIDatatypeValidator.hpp 608951 2008-01-04 18:21:22Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_ANYURI_DATATYPEVALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_ANYURI_DATATYPEVALIDATOR_HPP

#include <xercesc/validators/datatype/AbstractStringValidator.hpp>
#include <xercesc/util/XMLUri.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLBuffer;

class VALIDATORS_EXPORT AnyURIDatatypeValidator : public AbstractStringValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public ctor/dtor
    // -----------------------------------------------------------------------
	/** @name Constructors and Destructor */
    //@{

    AnyURIDatatypeValidator
    (
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    AnyURIDatatypeValidator
    (
        DatatypeValidator* const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , RefArrayVectorOf<XMLCh>* const enums
        , const int finalSet
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    virtual ~AnyURIDatatypeValidator();

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
    DECL_XSERIALIZABLE(AnyURIDatatypeValidator)

protected:

    virtual void checkValueSpace(const XMLCh* const content
        , MemoryManager* const manager);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    AnyURIDatatypeValidator(const AnyURIDatatypeValidator&);
    AnyURIDatatypeValidator& operator=(const AnyURIDatatypeValidator&);    
    void encode(const XMLCh* const content, const XMLSize_t len, XMLBuffer& encoded, MemoryManager* const manager);
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file AnyURIDatatypeValidator.hpp
  */
