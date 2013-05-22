/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSFacet.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSFACET_HPP)
#define XERCESC_INCLUDE_GUARD_XSFACET_HPP

#include <xercesc/framework/psvi/XSSimpleTypeDefinition.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This represents all Schema Facet components with the exception 
 * of Enumeration and Pattern Facets, which are represented by the 
 * XSMultiValueFacet interface.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAnnotation;

class XMLPARSER_EXPORT XSFacet : public XSObject
{
public:

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  facetKind
      * @param  lexicalValue
      * @param  isFixed
      * @param  annot
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSFacet
    (
        XSSimpleTypeDefinition::FACET facetKind
        , const XMLCh* const          lexicalValue
        , bool                        isFixed
        , XSAnnotation* const         annot
        , XSModel* const              xsModel
        , MemoryManager* const        manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSFacet();
    //@}

    //---------------------
    /** @name XSFacet methods */

    //@{

    /**
     * @return An indication as to the facet's type; see <code>XSSimpleTypeDefinition::FACET</code>
     */
    XSSimpleTypeDefinition::FACET getFacetKind() const;

    /**
     * @return Returns a value of a constraining facet. 
     */
    const XMLCh *getLexicalFacetValue() const;

    /**
     * Check whether a facet value is fixed. 
     */
    bool isFixed() const;

    /**
     * @return an annotation
     */
    XSAnnotation *getAnnotation() const;

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{

    //@}
private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSFacet(const XSFacet&);
    XSFacet & operator=(const XSFacet &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XSSimpleTypeDefinition::FACET fFacetKind;
    bool                          fIsFixed;
    const XMLCh*                  fLexicalValue;
    XSAnnotation*                 fAnnotation;
};

inline XSSimpleTypeDefinition::FACET XSFacet::getFacetKind() const
{   
    return fFacetKind;
}

inline const XMLCh* XSFacet::getLexicalFacetValue() const
{
    return fLexicalValue;    
}

inline bool XSFacet::isFixed() const
{
    return fIsFixed;
}

inline XSAnnotation* XSFacet::getAnnotation() const
{
    return fAnnotation;
}


XERCES_CPP_NAMESPACE_END

#endif
