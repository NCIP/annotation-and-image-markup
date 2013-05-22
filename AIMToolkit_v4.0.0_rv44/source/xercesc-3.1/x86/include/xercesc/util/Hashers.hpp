/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: Hashers.hpp 679382 2008-07-24 12:09:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_HASHERS_HPP)
#define XERCESC_INCLUDE_GUARD_HASHERS_HPP

#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
// Common hashers. Only widely-used hashers should be placed here.
//

/**
 * Hasher for keys that are const XMLCh*.
 */
struct StringHasher
{
  /**
   * Returns a hash value based on the key
   *
   * @param key the key to be hashed
   * @param mod the modulus the hasher should use
   */
  XMLSize_t getHashVal(const void* key, XMLSize_t mod) const
  {
    return XMLString::hash ((const XMLCh*)key, mod);
  }

  /**
   * Compares two keys and determines if they are semantically equal
   *
   * @param key1 the first key to be compared
   * @param key2 the second key to be compared
   *
   * @return true if they are equal
   */
  bool equals(const void *const key1, const void *const key2) const
  {
    return XMLString::equals ((const XMLCh*)key1, (const XMLCh*)key2);
  }
};

/**
 * Hasher for keys that are pointers.
 */
struct PtrHasher
{
  /**
   * Returns a hash value based on the key
   *
   * @param key the key to be hashed
   * @param mod the modulus the hasher should use
   */
  XMLSize_t getHashVal(const void* key, XMLSize_t mod) const
  {
    return ((XMLSize_t)key) % mod;
  }

  /**
   * Compares two keys and determines if they are semantically equal
   *
   * @param key1 the first key to be compared
   * @param key2 the second key to be compared
   *
   * @return true if they are equal
   */
  bool equals(const void *const key1, const void *const key2) const
  {
    return key1 == key2;
  }
};

XERCES_CPP_NAMESPACE_END

#endif
