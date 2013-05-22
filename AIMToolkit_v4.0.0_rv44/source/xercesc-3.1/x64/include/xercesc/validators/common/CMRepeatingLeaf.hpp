/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: CMRepeatingLeaf.hpp 677396 2008-07-16 19:36:20Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CMREPEATINGLEAF_HPP)
#define XERCESC_INCLUDE_GUARD_CMREPEATINGLEAF_HPP

#include <xercesc/validators/common/CMLeaf.hpp>


XERCES_CPP_NAMESPACE_BEGIN

//
//  A compound content model leaf node which carries occurence information.
//
class CMRepeatingLeaf : public CMLeaf
{
public :
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    CMRepeatingLeaf
    (
          QName* const         element
        , int                  minOccurs
        , int                  maxOccurs
        , unsigned int         position
        , unsigned int         maxStates
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    CMRepeatingLeaf
    (
          QName* const         element
        , int                  minOccurs
        , int                  maxOccurs
        , unsigned int         position
        , bool                 adopt
        , unsigned int         maxStates
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    int getMinOccurs() const;
    int getMaxOccurs() const;

    virtual bool isRepeatableLeaf() const;

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fMinOccurs
    //  fMaxOccurs
    //      The cardinality of the repeating leaf
    //
    // -----------------------------------------------------------------------
    int             fMinOccurs;
    int             fMaxOccurs;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CMRepeatingLeaf(const CMRepeatingLeaf&);
    CMRepeatingLeaf& operator=(const CMRepeatingLeaf&);
};


// -----------------------------------------------------------------------
//  Constructors
// -----------------------------------------------------------------------
inline CMRepeatingLeaf::CMRepeatingLeaf(   QName* const               element
                                         , int                        minOccurs
                                         , int                        maxOccurs
                                         , unsigned int               position
                                         , unsigned int               maxStates
                                         ,       MemoryManager* const manager) :
    CMLeaf(element, position, maxStates, manager)
    , fMinOccurs(minOccurs)
    , fMaxOccurs(maxOccurs)
{
}

inline CMRepeatingLeaf::CMRepeatingLeaf(   QName* const               element
                                         , int                        minOccurs
                                         , int                        maxOccurs
                                         , unsigned int               position
                                         , bool                       adopt
                                         , unsigned int               maxStates
                                         ,       MemoryManager* const manager) :
    CMLeaf(element, position, adopt, maxStates, manager)
    , fMinOccurs(minOccurs)
    , fMaxOccurs(maxOccurs)
{
}

// ---------------------------------------------------------------------------
//  Getter methods
// ---------------------------------------------------------------------------
inline int CMRepeatingLeaf::getMinOccurs() const
{
    return fMinOccurs;
}

inline int CMRepeatingLeaf::getMaxOccurs() const
{
    return fMaxOccurs;
}

inline bool CMRepeatingLeaf::isRepeatableLeaf() const
{
    return true;
}

XERCES_CPP_NAMESPACE_END

#endif
