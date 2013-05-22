/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XercesElementWildcard.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XERCESELEMENTWILDCARD_HPP)
#define XERCESC_INCLUDE_GUARD_XERCESELEMENTWILDCARD_HPP

#include <xercesc/util/QName.hpp>
#include <xercesc/validators/common/ContentSpecNode.hpp>
#include <xercesc/validators/schema/SubstitutionGroupComparator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward declarations
// ---------------------------------------------------------------------------
class SchemaGrammar;


class VALIDATORS_EXPORT XercesElementWildcard
{

public :

    // -----------------------------------------------------------------------
    //  Class static methods
    // -----------------------------------------------------------------------
    /*
     * check whether two elements are in conflict
     */
    static bool conflict(SchemaGrammar* const         pGrammar,
                         ContentSpecNode::NodeTypes   type1,
                         QName*                       q1,
                         ContentSpecNode::NodeTypes   type2,
                         QName*                       q2,
                         SubstitutionGroupComparator* comparator);

private:

    // -----------------------------------------------------------------------
    //  private helper methods
    // -----------------------------------------------------------------------
    static bool uriInWildcard(SchemaGrammar* const         pGrammar,
                              QName*                       qname,
                              unsigned int                 wildcard,
                              ContentSpecNode::NodeTypes   wtype,
                              SubstitutionGroupComparator* comparator);

    static bool wildcardIntersect(ContentSpecNode::NodeTypes t1,
                                  unsigned int               w1,
                                  ContentSpecNode::NodeTypes t2,
                                  unsigned int               w2);

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XercesElementWildcard();
    ~XercesElementWildcard();
};

XERCES_CPP_NAMESPACE_END

#endif // XERCESELEMENTWILDCARD_HPP

