/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: Match.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_MATCH_HPP)
#define XERCESC_INCLUDE_GUARD_MATCH_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/ArrayIndexOutOfBoundsException.hpp>
#include <xercesc/util/RuntimeException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * An instance of this class has ranges captured in matching
  */
  class XMLUTIL_EXPORT Match : public XMemory
{
public:

    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    Match(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    
    /**
    * Copy constructor
    */
    Match(const Match& toCopy);
    Match& operator=(const Match& toAssign);

    virtual ~Match();

    // -----------------------------------------------------------------------
    // Getter functions
    // -----------------------------------------------------------------------
    int getNoGroups() const;
    int getStartPos(int index) const;
    int getEndPos(int index) const;

    // -----------------------------------------------------------------------
    // Setter functions
    // -----------------------------------------------------------------------
    void setNoGroups(const int n);
    void setStartPos(const int index, const int value);
    void setEndPos(const int index, const int value);

private:
    // -----------------------------------------------------------------------
    // Initialize/Clean up methods
    // -----------------------------------------------------------------------
    void initialize(const Match& toCopy);
    void cleanUp();

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fNoGroups
    //  Represents no of regular expression groups
    //        
    //  fStartPositions
    //  Array of start positions in the target text matched to specific
    //        regular expression group
    //
    //    fEndPositions
    //        Array of end positions in the target text matched to specific
    //        regular expression group
    //
    //    fPositionsSize
    //        Actual size of Start/EndPositions array.
    // -----------------------------------------------------------------------
    int fNoGroups;
    int fPositionsSize;
    int* fStartPositions;
    int* fEndPositions;
    MemoryManager* fMemoryManager;
};

/**
  * Inline Methods
  */

// ---------------------------------------------------------------------------
//  Match: getter methods
// ---------------------------------------------------------------------------
inline int Match::getNoGroups() const {

    if (fNoGroups < 0)
        ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::Regex_Result_Not_Set, fMemoryManager);

    return fNoGroups;
}

inline int Match::getStartPos(int index) const {

    if (!fStartPositions)
        ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::Regex_Result_Not_Set, fMemoryManager);

    if (index < 0 || fNoGroups <= index)
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::Array_BadIndex, fMemoryManager);

    return fStartPositions[index];
}

inline int Match::getEndPos(int index) const {

    if (!fEndPositions)
        ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::Regex_Result_Not_Set, fMemoryManager);

    if (index < 0 || fNoGroups <= index)
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::Array_BadIndex, fMemoryManager);

    return fEndPositions[index];
}

// ---------------------------------------------------------------------------
//  Match: setter methods
// ---------------------------------------------------------------------------
inline void Match::setStartPos(const int index, const int value) {

    if (!fStartPositions)
        ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::Regex_Result_Not_Set, fMemoryManager);

    if (index < 0 || fNoGroups <= index)
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::Array_BadIndex, fMemoryManager);

    fStartPositions[index] = value;
}

inline void Match::setEndPos(const int index, const int value) {

    if (!fEndPositions)
        ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::Regex_Result_Not_Set, fMemoryManager);

    if (index < 0 || fNoGroups <= index)
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::Array_BadIndex, fMemoryManager);

    fEndPositions[index] = value;
}

XERCES_CPP_NAMESPACE_END

#endif
