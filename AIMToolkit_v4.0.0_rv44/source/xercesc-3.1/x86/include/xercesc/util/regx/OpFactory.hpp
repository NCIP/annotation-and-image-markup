/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: OpFactory.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_OPFACTORY_HPP)
#define XERCESC_INCLUDE_GUARD_OPFACTORY_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/RefVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class Op;
class CharOp;
class UnionOp;
class ChildOp;
class RangeOp;
class StringOp;
class ModifierOp;
class Token;

/*
 * A Factory class used by 'RegularExpression' to create different types of
 * operations (Op) objects. The class will keep track of all objects created
 * for cleanup purposes. Each 'RegularExpression' object will have its own
 * instance of OpFactory and when a 'RegularExpression' object is deleted
 * all associated Op objects will be deleted.
 */

class XMLUTIL_EXPORT OpFactory : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and destructors
    // -----------------------------------------------------------------------
    OpFactory(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~OpFactory();

    // -----------------------------------------------------------------------
    //  Factory methods
    // -----------------------------------------------------------------------
    Op* createDotOp();
    CharOp* createCharOp(XMLInt32 data);
    CharOp* createAnchorOp(XMLInt32 data);
    CharOp* createCaptureOp(int number, const Op* const next);
    UnionOp* createUnionOp(XMLSize_t size);
    ChildOp* createClosureOp(int id);
    ChildOp* createNonGreedyClosureOp();
    ChildOp* createQuestionOp(bool nonGreedy);
    RangeOp* createRangeOp(const Token* const token);
    CharOp* createBackReferenceOp(int refNo);
    StringOp* createStringOp(const XMLCh* const literal);

    // -----------------------------------------------------------------------
    //  Reset methods
    // -----------------------------------------------------------------------
    /*
     *    Remove all created Op objects from Vector
     */
    void reset();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    OpFactory(const OpFactory&);
    OpFactory& operator=(const OpFactory&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fOpVector
    //      Contains Op objects. Used for memory cleanup.
    // -----------------------------------------------------------------------
    RefVectorOf<Op>* fOpVector;
    MemoryManager*   fMemoryManager;
};

// ---------------------------------------------------------------------------
//  OpFactory - Factory methods
// ---------------------------------------------------------------------------
inline void OpFactory::reset() {

    fOpVector->removeAllElements();
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  *    End file OpFactory
  */
