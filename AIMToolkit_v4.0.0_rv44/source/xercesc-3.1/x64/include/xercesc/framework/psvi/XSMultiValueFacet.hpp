/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSMultiValueFacet.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSMULTIVALUEFACET_HPP)
#define XERCESC_INCLUDE_GUARD_XSMULTIVALUEFACET_HPP

#include <xercesc/framework/psvi/XSObject.hpp>
#include <xercesc/framework/psvi/XSSimpleTypeDefinition.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class represents all Schema Facets which may possess multiple
 * lexical values/annotations (i.e., Pattern and Enumeration facets).
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAnnotation;

class XMLPARSER_EXPORT XSMultiValueFacet : public XSObject
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
      * @param  lexicalValues
      * @param  isFixed
      * @param  headAnnot
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSMultiValueFacet
    (
        XSSimpleTypeDefinition::FACET facetKind
        , StringList*                 lexicalValues
        , bool                        isFixed
        , XSAnnotation* const         headAnnot
        , XSModel* const              xsModel
        , MemoryManager* const        manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSMultiValueFacet();
    //@}

    //---------------------
    /** @name XSMultiValueFacet methods */

    //@{

    /**
     * @return An indication as to the facet's type; see <code>XSSimpleTypeDefinition::FACET</code>
     */
    XSSimpleTypeDefinition::FACET getFacetKind() const;

    /**
     * @return Returns the values of a constraining facet. 
     */
    StringList *getLexicalFacetValues();   

    /**
     * Check whether a facet value is fixed. 
     */
    bool isFixed() const;

    /**
     * @return the annotations belonging to this facet's values
     */
    XSAnnotationList *getAnnotations();

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{

    //@}
private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSMultiValueFacet(const XSMultiValueFacet&);
    XSMultiValueFacet & operator=(const XSMultiValueFacet &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XSSimpleTypeDefinition::FACET fFacetKind;
    bool                          fIsFixed;
    StringList*                   fLexicalValues;  // not owned by this class
    XSAnnotationList*             fXSAnnotationList;
};


inline XSSimpleTypeDefinition::FACET XSMultiValueFacet::getFacetKind() const
{
    return fFacetKind;
}

inline bool XSMultiValueFacet::isFixed() const
{
    return fIsFixed;
}

inline StringList *XSMultiValueFacet::getLexicalFacetValues()
{
    return fLexicalValues; 
}

inline XSAnnotationList *XSMultiValueFacet::getAnnotations()
{
    return fXSAnnotationList;
}


XERCES_CPP_NAMESPACE_END

#endif
