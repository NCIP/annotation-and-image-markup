/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: SubstitutionGroupComparator.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_SUBSTITUTIONGROUPCOMPARATOR_HPP)
#define XERCESC_INCLUDE_GUARD_SUBSTITUTIONGROUPCOMPARATOR_HPP

#include <xercesc/util/StringPool.hpp>
#include <xercesc/util/QName.hpp>
#include <xercesc/validators/common/GrammarResolver.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class SchemaGrammar;

class VALIDATORS_EXPORT SubstitutionGroupComparator : public XMemory
{
public:

    // -----------------------------------------------------------------------
    //  Public Constructor
    // -----------------------------------------------------------------------
    /** @name Constructor. */
    //@{

    SubstitutionGroupComparator(GrammarResolver*  const pGrammarResolver
                              , XMLStringPool*    const pStringPool);


    //@}

    // -----------------------------------------------------------------------
    //  Public Destructor
    // -----------------------------------------------------------------------
    /** @name Destructor. */
    //@{

    ~SubstitutionGroupComparator();

    //@}

    // -----------------------------------------------------------------------
    // Validation methods
    // -----------------------------------------------------------------------
    /** @name Validation Function */
    //@{

    /**
	   * Checks that the "anElement" is within the substitution group.
	   *
	   * @param  anElement   QName of the element
	   *
	   * @param  exemplar     QName of the head element in the group
	   */
    bool isEquivalentTo(const QName* const anElement
                      , const QName* const exemplar);
	 //@}

    /*
     * check whether one element or any element in its substitution group
     * is allowed by a given wildcard uri
     *
     * @param pGrammar the grammar where the wildcard is declared
     * @param element  the QName of a given element
     * @param wuri     the uri of the wildcard
     * @param wother   whether the uri is from ##other, so wuri is excluded
     *
     * @return whether the element is allowed by the wildcard
     */
    bool isAllowedByWildcard(SchemaGrammar* const pGrammar, QName* const element, unsigned int wuri, bool wother);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    SubstitutionGroupComparator();
    SubstitutionGroupComparator(const SubstitutionGroupComparator&);
    SubstitutionGroupComparator& operator=(const SubstitutionGroupComparator&);
    
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //
    // -----------------------------------------------------------------------
    GrammarResolver     *fGrammarResolver;
    XMLStringPool       *fStringPool;
};


// ---------------------------------------------------------------------------
//  SubstitutionGroupComparator: Getters
// ---------------------------------------------------------------------------
inline SubstitutionGroupComparator::SubstitutionGroupComparator(GrammarResolver*  const pGrammarResolver
                                                              , XMLStringPool*    const pStringPool)
:fGrammarResolver(pGrammarResolver)
,fStringPool(pStringPool)
{}

inline SubstitutionGroupComparator::~SubstitutionGroupComparator()
{}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file SubstitutionGroupComparator.hpp
  */

