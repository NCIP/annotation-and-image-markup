/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLDTDDescriptionImpl.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLDTDDESCRIPTIONIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_XMLDTDDESCRIPTIONIMPL_HPP

#include <xercesc/framework/XMLDTDDescription.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLPARSER_EXPORT XMLDTDDescriptionImpl : public XMLDTDDescription
{
public :
    // -----------------------------------------------------------------------
    /** @name constructor and destructor */
    // -----------------------------------------------------------------------
    //@{
    XMLDTDDescriptionImpl(
                          const XMLCh* const   systemId 
                        , MemoryManager* const memMgr
                          );

    ~XMLDTDDescriptionImpl();
    //@}

    // -----------------------------------------------------------------------
    /** @name Implementation of GrammarDescription Interface */
    // -----------------------------------------------------------------------
    //@{
    /**
      * getGrammarKey
      *
      */
    virtual const XMLCh*           getGrammarKey() const ;
    //@}

    // -----------------------------------------------------------------------
    /** @name Implementation of DTDDescription Interface */
    // -----------------------------------------------------------------------
    //@{
    /**
      * Getter
      *
      */
    virtual const XMLCh*          getRootName() const;
    virtual const XMLCh*          getSystemId() const;

    /**
      * Setter
      *
      */
    virtual void                  setRootName(const XMLCh* const);
    virtual void                  setSystemId(const XMLCh* const);
    //@}
    
    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLDTDDescriptionImpl)

    XMLDTDDescriptionImpl(MemoryManager* const memMgr = XMLPlatformUtils::fgMemoryManager);

private :
    // -----------------------------------------------------------------------
    /** name  Unimplemented copy constructor and operator= */
    // -----------------------------------------------------------------------
    //@{
    XMLDTDDescriptionImpl(const XMLDTDDescriptionImpl& );
    XMLDTDDescriptionImpl& operator=(const XMLDTDDescriptionImpl& );
    //@}

    // -----------------------------------------------------------------------
    //
    // fSystemId:
    //     SYSTEM ID of the grammar
    //
    // fRootName: 
    //      root name of the grammar
    //
    // -----------------------------------------------------------------------

    const XMLCh*      fSystemId;
    const XMLCh*      fRootName;    

};


XERCES_CPP_NAMESPACE_END

#endif
