/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: HexBinaryDatatypeValidator.hpp 695949 2008-09-16 15:57:44Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_HEXBINARY_DATATYPEVALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_HEXBINARY_DATATYPEVALIDATOR_HPP

#include <xercesc/validators/datatype/AbstractStringValidator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT HexBinaryDatatypeValidator : public AbstractStringValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public ctor/dtor
    // -----------------------------------------------------------------------
	/** @name Constructors and Destructor */
    //@{

    HexBinaryDatatypeValidator
    (
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    HexBinaryDatatypeValidator
    (
        DatatypeValidator* const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , RefArrayVectorOf<XMLCh>* const enums
        , const int finalSet
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual ~HexBinaryDatatypeValidator();

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
    DECL_XSERIALIZABLE(HexBinaryDatatypeValidator)

protected:

    virtual void checkValueSpace(const XMLCh* const content
                                , MemoryManager* const manager);

    virtual XMLSize_t  getLength(const XMLCh* const content
                       , MemoryManager* const manager) const;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    HexBinaryDatatypeValidator(const HexBinaryDatatypeValidator&);
    HexBinaryDatatypeValidator& operator=(const HexBinaryDatatypeValidator&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
	//		Nil.
    // -----------------------------------------------------------------------
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file HexBinaryDatatypeValidator.hpp
  */
