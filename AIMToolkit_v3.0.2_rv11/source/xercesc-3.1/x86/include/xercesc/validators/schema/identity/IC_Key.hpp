/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: IC_Key.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_IC_KEY_HPP)
#define XERCESC_INCLUDE_GUARD_IC_KEY_HPP


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/IdentityConstraint.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT IC_Key: public IdentityConstraint
{
public:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    IC_Key(const XMLCh* const identityConstraintName,
           const XMLCh* const elemName,
           MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
	~IC_Key();

	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    short getType() const;

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(IC_Key)

    IC_Key(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    IC_Key(const IC_Key& other);
    IC_Key& operator= (const IC_Key& other);
};


// ---------------------------------------------------------------------------
//  IC_Key: Getter methods
// ---------------------------------------------------------------------------
inline short IC_Key::getType() const {

    return IdentityConstraint::ICType_KEY;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file IC_Key.hpp
  */

