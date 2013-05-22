/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: CMAny.hpp 677396 2008-07-16 19:36:20Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CMANY_HPP)
#define XERCESC_INCLUDE_GUARD_CMANY_HPP

#include <xercesc/validators/common/CMNode.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CMStateSet;

class CMAny : public CMNode
{
public :
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    CMAny
    (
        ContentSpecNode::NodeTypes      type
        , unsigned int                  URI
        , unsigned int                  position
        , unsigned int                  maxStates
        ,       MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
    );
    ~CMAny();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    unsigned int getURI() const;

    unsigned int getPosition() const;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setPosition(const unsigned int newPosition);

    // -----------------------------------------------------------------------
    //  Implementation of the public CMNode virtual interface
    // -----------------------------------------------------------------------
    virtual void orphanChild();


protected :
    // -----------------------------------------------------------------------
    //  Implementation of the protected CMNode virtual interface
    // -----------------------------------------------------------------------
    void calcFirstPos(CMStateSet& toSet) const;
    void calcLastPos(CMStateSet& toSet) const;

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fURI;
    //  URI of the any content model. This value is set if the type is
    //  of the following:
    //  XMLContentSpec.CONTENTSPECNODE_ANY,
    //  XMLContentSpec.CONTENTSPECNODE_ANY_OTHER.
    //
    //  fPosition
    //  Part of the algorithm to convert a regex directly to a DFA
    //  numbers each leaf sequentially. If its -1, that means its an
    //  epsilon node. Zero and greater are non-epsilon positions.
    // -----------------------------------------------------------------------
    unsigned int fURI;
    unsigned int fPosition;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CMAny(const CMAny&);
    CMAny& operator=(const CMAny&);
};

XERCES_CPP_NAMESPACE_END

#endif
