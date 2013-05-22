/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: SAX2XMLFilter.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_SAX2XMLFILTER_HPP)
#define XERCESC_INCLUDE_GUARD_SAX2XMLFILTER_HPP

#include <xercesc/sax2/SAX2XMLReader.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class SAX2_EXPORT SAX2XMLFilter : public SAX2XMLReader
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors and Destructor */
    //@{
    /** The default constructor */
    SAX2XMLFilter()
    {
    }
    /** The destructor */
    virtual ~SAX2XMLFilter()
    {
    }
    //@}

    //-----------------------------------------------------------------------
    // The XMLFilter interface
    //-----------------------------------------------------------------------
    /** @name Implementation of SAX 2.0 XMLFilter interface's. */
    //@{

    /**
      * This method returns the parent XMLReader object.
      *
      * @return A pointer to the parent XMLReader object.
      */
    virtual SAX2XMLReader* getParent() const = 0 ;

    /**
      * Sets the parent XMLReader object; parse requests will be forwarded to this
      * object, and callback notifications coming from it will be postprocessed
      *
      * @param parent The new XMLReader parent.
      * @see SAX2XMLReader#SAX2XMLReader
      */
    virtual void setParent(SAX2XMLReader* parent) = 0;

    //@}

private :
    /* The copy constructor, you cannot call this directly */
    SAX2XMLFilter(const SAX2XMLFilter&);

    /* The assignment operator, you cannot call this directly */
    SAX2XMLFilter& operator=(const SAX2XMLFilter&);

};

XERCES_CPP_NAMESPACE_END

#endif
