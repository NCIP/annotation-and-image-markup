/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: QNameDatatypeValidator.hpp 577322 2007-09-19 14:58:04Z cargilld $
 */

#if !defined(XERCESC_INCLUDE_GUARD_QNAME_DATATYPEVALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_QNAME_DATATYPEVALIDATOR_HPP

#include <xercesc/validators/datatype/AbstractStringValidator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT QNameDatatypeValidator : public AbstractStringValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public ctor/dtor
    // -----------------------------------------------------------------------
	/** @name Constructors and Destructor */
    //@{

    QNameDatatypeValidator
    (
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    QNameDatatypeValidator
    (
        DatatypeValidator*            const baseValidator
        , RefHashTableOf<KVStringPair>* const facets
        , RefArrayVectorOf<XMLCh>*           const enums
        , const int                           finalSet
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    virtual ~QNameDatatypeValidator();

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
    DECL_XSERIALIZABLE(QNameDatatypeValidator)

protected:

    virtual void checkValueSpace(const XMLCh* const content
                                , MemoryManager* const manager);

    virtual void checkContent(const XMLCh*             const content
                            ,       ValidationContext* const context
                            , bool                           asBase
                            , MemoryManager* const manager);

    virtual void inspectFacetBase(MemoryManager* const manager);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    QNameDatatypeValidator(const QNameDatatypeValidator&);
    QNameDatatypeValidator& operator=(const QNameDatatypeValidator&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
	//		Nil
    // -----------------------------------------------------------------------

};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file QNameDatatypeValidator.hpp
  */

