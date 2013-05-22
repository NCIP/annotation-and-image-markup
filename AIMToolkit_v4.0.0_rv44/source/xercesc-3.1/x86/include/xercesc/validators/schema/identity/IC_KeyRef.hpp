/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: IC_KeyRef.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_IC_KEYREF_HPP)
#define XERCESC_INCLUDE_GUARD_IC_KEYREF_HPP


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/IdentityConstraint.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT IC_KeyRef: public IdentityConstraint
{
public:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    IC_KeyRef(const XMLCh* const identityConstraintName,
              const XMLCh* const elemName,
              IdentityConstraint* const icKey,
              MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
	~IC_KeyRef();

	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    short getType() const;
    IdentityConstraint* getKey() const;

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(IC_KeyRef)

    IC_KeyRef(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    IC_KeyRef(const IC_KeyRef& other);
    IC_KeyRef& operator= (const IC_KeyRef& other);

    // -----------------------------------------------------------------------
    //  Data members
    // -----------------------------------------------------------------------
    IdentityConstraint* fKey;
};


// ---------------------------------------------------------------------------
//  IC_KeyRef: Getter methods
// ---------------------------------------------------------------------------
inline short IC_KeyRef::getType() const {

    return IdentityConstraint::ICType_KEYREF;
}

inline IdentityConstraint* IC_KeyRef::getKey() const {

    return fKey;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file IC_KeyRef.hpp
  */

