/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSAnnotation.hpp 672273 2008-06-27 13:57:00Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSANNOTATION_HPP)
#define XERCESC_INCLUDE_GUARD_XSANNOTATION_HPP

#include <xercesc/framework/psvi/XSObject.hpp>
#include <xercesc/internal/XSerializable.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Annotation
 * component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.
 */

// forward declarations
class DOMNode;
class ContentHandler;

class XMLPARSER_EXPORT XSAnnotation : public XSerializable, public XSObject
{
public:

    // TargetType
    enum ANNOTATION_TARGET {
	    /**
	     * The object type is <code>org.w3c.dom.Element</code>.
	     */
	    W3C_DOM_ELEMENT           = 1,
	    /**
	     * The object type is <code>org.w3c.dom.Document</code>.
	     */
	    W3C_DOM_DOCUMENT          = 2
    };

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor
      *
      * @param  contents    The string that is to be the content of this XSAnnotation
      * @param  manager     The configurable memory manager
      */
    XSAnnotation
    (
        const XMLCh* const contents
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSAnnotation();
    //@}

    //---------------------
    /** @name XSAnnotation methods */

    //@{

    /**
     * Write contents of the annotation to the specified DOM object. In-scope
     * namespace declarations for <code>annotation</code> element are added as
     * attribute nodes of the serialized <code>annotation</code>.
     * @param node  A target pointer to the annotation target object, i.e.
     * either <code>DOMDocument</code> or <code>DOMElement</code> cast as
     * <code>DOMNode</code>.
     * @param targetType  A target type.
     */

    void writeAnnotation(DOMNode* node, ANNOTATION_TARGET targetType);

    /**
     * Write contents of the annotation to the specified object.
     * The corresponding events for all in-scope namespace declarations are
     * sent via the specified document handler.
     * @param handler  A target pointer to the annotation target object, i.e.
     *   <code>ContentHandler</code>.
     */
    void writeAnnotation(ContentHandler* handler);

    /**
     * A text representation of annotation.
     */
    const XMLCh *getAnnotationString() const;
    XMLCh *getAnnotationString();

    //@}

    //----------------------------------
    /** methods needed by implementation */
    //@{
    void            setNext(XSAnnotation* const nextAnnotation);
    XSAnnotation*   getNext();
    //@}

    //-----------------------------
    /** Getter */
    //@{
    inline void           getLineCol(XMLFileLoc& line, XMLFileLoc& col)  const;
    inline const XMLCh*   getSystemId()                    const;
    //@}

    //-----------------------------
    /** Setter */
    //@{
    inline void           setLineCol(XMLFileLoc line, XMLFileLoc col);
           void           setSystemId(const XMLCh* const systemId);
    //@}

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XSAnnotation)
    XSAnnotation(MemoryManager* const manager);

private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSAnnotation(const XSAnnotation&);
    XSAnnotation & operator=(const XSAnnotation &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XMLCh*        fContents;
    XSAnnotation* fNext;

private:

    XMLCh*        fSystemId;
    XMLFileLoc    fLine;
    XMLFileLoc    fCol;

};

inline const XMLCh *XSAnnotation::getAnnotationString() const
{
    return fContents;
}

inline XMLCh *XSAnnotation::getAnnotationString()
{
    return fContents;
}

inline void XSAnnotation::getLineCol(XMLFileLoc& line, XMLFileLoc& col) const
{
    line = fLine;
    col  = fCol;
}

inline const XMLCh* XSAnnotation::getSystemId() const
{
    return fSystemId;
}

inline void XSAnnotation::setLineCol(XMLFileLoc line, XMLFileLoc col)
{
    fLine = line;
    fCol  = col;
}

XERCES_CPP_NAMESPACE_END

#endif
