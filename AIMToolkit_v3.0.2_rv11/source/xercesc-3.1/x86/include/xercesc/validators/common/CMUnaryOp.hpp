/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: CMUnaryOp.hpp 677396 2008-07-16 19:36:20Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CMUNARYOP_HPP)
#define XERCESC_INCLUDE_GUARD_CMUNARYOP_HPP

#include <xercesc/validators/common/CMNode.hpp>


XERCES_CPP_NAMESPACE_BEGIN

class CMStateSet;

class CMUnaryOp : public CMNode
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    CMUnaryOp
    (
          ContentSpecNode::NodeTypes    type
        , CMNode* const                 nodeToAdopt
        , unsigned int                  maxStates
        , MemoryManager* const          manager = XMLPlatformUtils::fgMemoryManager
    );
    ~CMUnaryOp();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const CMNode* getChild() const;
    CMNode* getChild();


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
    //  fChild
    //      This is the reference to the one child that we have for this
    //      unary operation. We own it.
    // -----------------------------------------------------------------------
    CMNode*     fChild;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CMUnaryOp(const CMUnaryOp&);
    CMUnaryOp& operator=(const CMUnaryOp&);
};

XERCES_CPP_NAMESPACE_END

#endif
