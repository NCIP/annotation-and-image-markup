/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: CMBinaryOp.hpp 677396 2008-07-16 19:36:20Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CMBINARYOP_HPP)
#define XERCESC_INCLUDE_GUARD_CMBINARYOP_HPP

#include <xercesc/validators/common/CMNode.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CMStateSet;

class CMBinaryOp : public CMNode
{
public :
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    CMBinaryOp
    (
        ContentSpecNode::NodeTypes  type
        , CMNode* const             leftToAdopt
        , CMNode* const             rightToAdopt
        , unsigned int              maxStates
        , MemoryManager* const      manager = XMLPlatformUtils::fgMemoryManager
    );
    ~CMBinaryOp();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const CMNode* getLeft() const;
    CMNode* getLeft();
    const CMNode* getRight() const;
    CMNode* getRight();


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
    //  fLeftChild
    //  fRightChild
    //      These are the references to the two nodes that are on either side
    //      of this binary operation. We own them both.
    // -----------------------------------------------------------------------
    CMNode* fLeftChild;
    CMNode* fRightChild;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CMBinaryOp(const CMBinaryOp&);
    CMBinaryOp& operator=(const CMBinaryOp&);
};

XERCES_CPP_NAMESPACE_END

#endif
