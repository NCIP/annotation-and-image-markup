/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: BitSet.hpp 676911 2008-07-15 13:27:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_BITSET_HPP)
#define XERCESC_INCLUDE_GUARD_BITSET_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT BitSet : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    BitSet( const XMLSize_t size
          , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    BitSet(const BitSet& toCopy);
    ~BitSet();


    // -----------------------------------------------------------------------
    //  Equality methods
    // -----------------------------------------------------------------------
    bool equals(const BitSet& other) const;


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool allAreCleared() const;
    bool allAreSet() const;
    XMLSize_t size() const;
    bool get(const XMLSize_t index) const;


    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void clear(const XMLSize_t index);
    void clearAll();
    void set(const XMLSize_t index);


    // -----------------------------------------------------------------------
    //  Bitwise logical operations
    // -----------------------------------------------------------------------
    void andWith(const BitSet& other);
    void orWith(const BitSet& other);
    void xorWith(const BitSet& other);


    // -----------------------------------------------------------------------
    //  Miscellaneous
    // -----------------------------------------------------------------------
    XMLSize_t hash(const XMLSize_t hashModulus) const;


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors
    // -----------------------------------------------------------------------
    BitSet();    
    BitSet& operator=(const BitSet&);
    // -----------------------------------------------------------------------
    //  Private methods
    // -----------------------------------------------------------------------
    void ensureCapacity(const XMLSize_t bits);


    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fBits
    //      The array of unsigned longs used to store the bits.
    //
    //  fUnitLen
    //      The length of the storage array, in storage units not bits.
    // -----------------------------------------------------------------------
    MemoryManager*  fMemoryManager;
    unsigned long*  fBits;
    XMLSize_t       fUnitLen;
};

XERCES_CPP_NAMESPACE_END

#endif
