/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: AllContentModel.hpp 901107 2010-01-20 08:45:02Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_ALLCONTENTMODEL_HPP)
#define XERCESC_INCLUDE_GUARD_ALLCONTENTMODEL_HPP

#include <xercesc/framework/XMLContentModel.hpp>
#include <xercesc/util/ValueVectorOf.hpp>
#include <xercesc/validators/common/ContentLeafNameTypeVector.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class ContentSpecNode;

//
//  AllContentModel is a derivative of the abstract content model base
//  class that handles the special case of <all> feature in schema. If a model
//  is <all>, all non-optional children must appear
//
//  So, all we have to do is to keep an array of the possible children and
//  validate by just looking up each child being validated by looking it up
//  in the list, and make sure all non-optional children appear.
//
class AllContentModel : public XMLContentModel
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    AllContentModel
    (
          ContentSpecNode* const parentContentSpec
		, const bool             isMixed
        , MemoryManager* const   manager = XMLPlatformUtils::fgMemoryManager
    );

    ~AllContentModel();

    // -----------------------------------------------------------------------
    //  Implementation of the ContentModel virtual interface
    // -----------------------------------------------------------------------
    virtual bool validateContent
    (
        QName** const         children
      , XMLSize_t             childCount
      , unsigned int          emptyNamespaceId
      , XMLSize_t*            indexFailingChild
      , MemoryManager*  const manager = XMLPlatformUtils::fgMemoryManager
    )   const;

	virtual bool validateContentSpecial
    (
        QName** const           children
      , XMLSize_t               childCount
      , unsigned int            emptyNamespaceId
      , GrammarResolver*  const pGrammarResolver
      , XMLStringPool*    const pStringPool
      , XMLSize_t*              indexFailingChild
      , MemoryManager*    const manager = XMLPlatformUtils::fgMemoryManager
    ) const;

    virtual ContentLeafNameTypeVector* getContentLeafNameTypeVector() const ;

    virtual unsigned int getNextState(unsigned int currentState,
                                      XMLSize_t    elementIndex) const;

    virtual bool handleRepetitions( const QName* const curElem,
                                    unsigned int curState,
                                    unsigned int currentLoop,
                                    unsigned int& nextState,
                                    unsigned int& nextLoop,
                                    XMLSize_t elementIndex,
                                    SubstitutionGroupComparator * comparator) const;

    virtual void checkUniqueParticleAttribution
    (
        SchemaGrammar*    const pGrammar
      , GrammarResolver*  const pGrammarResolver
      , XMLStringPool*    const pStringPool
      , XMLValidator*     const pValidator
      , unsigned int*     const pContentSpecOrgURI
      , const XMLCh*            pComplexTypeName = 0
    ) ;

private :
    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    void buildChildList
    (
        ContentSpecNode* const                     curNode
      , ValueVectorOf<QName*>&                     toFill
      , ValueVectorOf<bool>&                       toType
    );

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    AllContentModel();
    AllContentModel(const AllContentModel&);
    AllContentModel& operator=(const AllContentModel&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fCount
    //      The count of possible children in the fChildren member.
    //
    //  fChildren
    //      The list of possible children that we have to accept. This array
    //      is allocated as large as needed in the constructor.
    //
    //  fChildOptional
    //      The corresponding list of optional state of each child in fChildren
    //      True if the child is optional (i.e. minOccurs = 0).
    //
    //  fNumRequired
    //      The number of required children in <all> (i.e. minOccurs = 1)
    //
    //  fIsMixed
    //      AllContentModel with mixed PCDATA.
    // -----------------------------------------------------------------------
    MemoryManager* fMemoryManager;
    XMLSize_t       fCount;
    QName**         fChildren;
    bool*           fChildOptional;
    unsigned int    fNumRequired;
    bool            fIsMixed;
    bool            fHasOptionalContent;
};

inline ContentLeafNameTypeVector* AllContentModel::getContentLeafNameTypeVector() const
{
	return 0;
}

inline unsigned int
AllContentModel::getNextState(unsigned int,
                              XMLSize_t) const {

    return XMLContentModel::gInvalidTrans;
}

inline bool
AllContentModel::handleRepetitions( const QName* const /*curElem*/,
                                    unsigned int /*curState*/,
                                    unsigned int /*currentLoop*/,
                                    unsigned int& /*nextState*/,
                                    unsigned int& /*nextLoop*/,
                                    XMLSize_t /*elementIndex*/,
                                    SubstitutionGroupComparator * /*comparator*/) const
{
    return true;
}

XERCES_CPP_NAMESPACE_END

#endif
