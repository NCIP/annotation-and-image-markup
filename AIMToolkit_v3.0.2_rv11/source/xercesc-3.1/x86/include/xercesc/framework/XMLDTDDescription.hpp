/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLDTDDescription.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLDTDDESCRIPTION_HPP)
#define XERCESC_INCLUDE_GUARD_XMLDTDDESCRIPTION_HPP

#include <xercesc/framework/XMLGrammarDescription.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLPARSER_EXPORT XMLDTDDescription : public XMLGrammarDescription
{
public :
    // -----------------------------------------------------------------------
    /** @name Virtual destructor for derived classes */
    // -----------------------------------------------------------------------
    //@{
    /**
      * virtual destructor
      *
      */
    virtual ~XMLDTDDescription();
    //@}

    // -----------------------------------------------------------------------
    /** @name Implementation of Grammar Description Interface */
    // -----------------------------------------------------------------------
    //@{     
    /**
      * getGrammarType
      *
      */
    virtual Grammar::GrammarType   getGrammarType() const
    {
        return Grammar::DTDGrammarType;
    }
    //@}

    // -----------------------------------------------------------------------
    /** @name The DTDDescription Interface */
    // -----------------------------------------------------------------------
    //@{      
    /**
      * Getter
      *
      */
    virtual const XMLCh*          getRootName() const = 0;
    virtual const XMLCh*          getSystemId() const {return 0;};

    /**
      * Setter
      *
      */
    virtual void                  setRootName(const XMLCh* const) = 0;
    virtual void                  setSystemId(const XMLCh* const) {};
    //@}
    
    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLDTDDescription)

protected :
    // -----------------------------------------------------------------------
    /**  Hidden Constructors */
    // -----------------------------------------------------------------------
    //@{
    XMLDTDDescription(MemoryManager* const memMgr = XMLPlatformUtils::fgMemoryManager);
    //@}

private :
    // -----------------------------------------------------------------------
    /** name  Unimplemented copy constructor and operator= */
    // -----------------------------------------------------------------------
    //@{
    XMLDTDDescription(const XMLDTDDescription& );
    XMLDTDDescription& operator=(const XMLDTDDescription& );
    //@}

};


XERCES_CPP_NAMESPACE_END

#endif
