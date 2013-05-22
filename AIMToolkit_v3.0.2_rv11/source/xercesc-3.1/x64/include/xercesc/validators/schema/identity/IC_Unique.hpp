/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: IC_Unique.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_IC_UNIQUE_HPP)
#define XERCESC_INCLUDE_GUARD_IC_UNIQUE_HPP


/**
  * Schema unique identity constraint
  */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/IdentityConstraint.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT IC_Unique: public IdentityConstraint
{
public:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    IC_Unique(const XMLCh* const identityConstraintName,
              const XMLCh* const elemName,
              MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
	~IC_Unique();

	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    short getType() const;

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(IC_Unique)

    IC_Unique(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    IC_Unique(const IC_Unique& other);
    IC_Unique& operator= (const IC_Unique& other);
};


// ---------------------------------------------------------------------------
//  IC_Unique: Getter methods
// ---------------------------------------------------------------------------
inline short IC_Unique::getType() const {

    return IdentityConstraint::ICType_UNIQUE;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file IC_Unique.hpp
  */

