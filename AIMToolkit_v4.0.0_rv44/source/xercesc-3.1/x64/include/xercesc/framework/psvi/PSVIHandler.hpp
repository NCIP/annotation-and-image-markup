/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

 /*
 * $Id: PSVIHandler.hpp 676796 2008-07-15 05:04:13Z dbertoni $
 */

#if !defined(XERCESC_INCLUDE_GUARD_PSVIHANDLER_HPP)
#define XERCESC_INCLUDE_GUARD_PSVIHANDLER_HPP


XERCES_CPP_NAMESPACE_BEGIN


class PSVIElement;
class PSVIAttributeList;


/**
  * This abstract class provides the interface for the scanner to return
  * PSVI information to the application.
  *
  */
class XMLPARSER_EXPORT PSVIHandler
{
public:
    // -----------------------------------------------------------------------
    //  Constructors are hidden, just the virtual destructor is exposed
    // -----------------------------------------------------------------------
    /** @name Destructor */
    //@{
    virtual ~PSVIHandler()
    {
    }
    //@}

    /** @name The PSVI handler interface */
    //@{
    /** Receive notification of the PSVI properties of an element.
      * The scanner will issue this call after the XMLDocumentHandler
      * endElement call.  Since the scanner will issue the psviAttributes
      * call immediately after reading the start tag of an element, all element
      * content will be effectively bracketed by these two calls.
      * @param  localName The name of the element whose end tag was just
      *                     parsed.
      * @param  uri       The namespace to which the element is bound
      * @param  elementInfo    Object containing the element's PSVI properties
      */
    virtual void handleElementPSVI
    (
        const   XMLCh* const            localName 
        , const XMLCh* const            uri
        ,       PSVIElement *           elementInfo
    ) = 0;

    /** 
      * Receive notification of partial PSVI properties of an element.
      * This callback is made right after the psviAttributes
      * call for non-empty element. 
      *
      *  The PSVIElement passed in has all fields properly set and it
      *  can be safely accessed the same way as the one passed in handleElementPSVI.
      *  However, fields listed below always have default values.
      *
      *  getValidity()	              PSVIItem::VALIDITY_NOTKNOWN
      *  getValidationAttemped()      PSVIItem::VALIDATION_NONE
      *  getMemberTypeDefinition()    0
      *  getSchemaNormalizedValue()   0
      *  getCanonicalRepresentation() 0
      *  getNotationDeclaration()     0
      *
      *
      * @param  localName    The name of the element upon which start tag 
      *                      these attributes were encountered.
      * @param  uri          The namespace to which the element is bound
      * @param  elementInfo  Object containing the element's partial PSVI properties
      */
    virtual void handlePartialElementPSVI
    (
          const XMLCh*        const localName 
        , const XMLCh*        const uri
        ,       PSVIElement *       elementInfo
    );

    /**
      * Enables PSVI information about attributes to be passed back to the
      * application.  This callback will be made on *all*
      * elements; on elements with no attributes, the final parameter will
      * be null.
      * @param  localName The name of the element upon which start tag 
      *          these attributes were encountered.
      * @param  uri       The namespace to which the element is bound
      * @param  psviAttributes   Object containing the attributes' PSVI properties
      *          with information to identify them.
      */
    virtual void handleAttributesPSVI
    (
        const   XMLCh* const            localName 
        , const XMLCh* const            uri
        ,       PSVIAttributeList *     psviAttributes
    ) = 0;


    //@}



protected :
    // -----------------------------------------------------------------------
    //  Hidden Constructors
    // -----------------------------------------------------------------------
    PSVIHandler()
    {
    }


private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    PSVIHandler(const PSVIHandler&);
    PSVIHandler& operator=(const PSVIHandler&);
};

inline void PSVIHandler::handlePartialElementPSVI(const XMLCh*        const /*localName*/
                                                , const XMLCh*        const /*uri*/
                                                ,       PSVIElement *       /*elementInfo*/
                                                 )
{
}

XERCES_CPP_NAMESPACE_END

#endif
