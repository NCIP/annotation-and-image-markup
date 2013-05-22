/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLGrammarDescription.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLGRAMMARDESCRIPTION_HPP)
#define XERCESC_INCLUDE_GUARD_XMLGRAMMARDESCRIPTION_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/validators/common/Grammar.hpp>

#include <xercesc/internal/XSerializable.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLPARSER_EXPORT XMLGrammarDescription : public XSerializable, public XMemory
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
    virtual ~XMLGrammarDescription();
    //@}

    // -----------------------------------------------------------------------
    /** @name The Grammar Description Interface */
    // -----------------------------------------------------------------------
    //@{     
    /**
      * getGrammarType
      *
      */
    virtual Grammar::GrammarType   getGrammarType() const = 0;
    
    /**
      * getGrammarKey
      *
      */
    virtual const XMLCh*           getGrammarKey() const = 0;    
    //@}
    
    inline MemoryManager*          getMemoryManager() const;

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLGrammarDescription)

protected :
    // -----------------------------------------------------------------------
    /**  Hidden Constructors */
    // -----------------------------------------------------------------------
    //@{
    XMLGrammarDescription(MemoryManager* const memMgr = XMLPlatformUtils::fgMemoryManager);
    //@}

private :
    // -----------------------------------------------------------------------
    /** name  Unimplemented copy constructor and operator= */
    // -----------------------------------------------------------------------
    //@{
    XMLGrammarDescription(const XMLGrammarDescription& );
    XMLGrammarDescription& operator=(const XMLGrammarDescription& );
    //@}

    // -----------------------------------------------------------------------
    //
    // fMemMgr: plugged-in (or defaulted-in) memory manager, 
    //          not owned 
    //          no reset after initialization
	//          allow derivatives to access directly
    //
    // -----------------------------------------------------------------------    
    MemoryManager* const  fMemMgr;     
};

inline MemoryManager* XMLGrammarDescription::getMemoryManager() const
{
    return fMemMgr;
}

XERCES_CPP_NAMESPACE_END

#endif
