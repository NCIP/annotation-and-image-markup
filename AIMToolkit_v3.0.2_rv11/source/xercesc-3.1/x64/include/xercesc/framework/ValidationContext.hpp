/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ValidationContext.hpp 729944 2008-12-29 17:03:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_VALIDATION_CONTEXT_HPP)
#define XERCESC_INCLUDE_GUARD_VALIDATION_CONTEXT_HPP

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/RefHashTableOf.hpp>
#include <xercesc/util/NameIdPool.hpp>
#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLRefInfo;
class DTDEntityDecl;
class DatatypeValidator;
class ElemStack;
class NamespaceScope;
class XMLScanner;

class XMLPARSER_EXPORT ValidationContext : public XMemory
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
    virtual ~ValidationContext(){};
    //@}

    // -----------------------------------------------------------------------
    /** @name The ValidationContext Interface */
    // -----------------------------------------------------------------------
    //@{

    /**
      * IDRefList
      *
      */
    virtual RefHashTableOf<XMLRefInfo>*  getIdRefList() const = 0;

    virtual void                         setIdRefList(RefHashTableOf<XMLRefInfo>* const) = 0;

    virtual void                         clearIdRefList() = 0;

    virtual void                         addId(const XMLCh * const ) = 0;

    virtual void                         addIdRef(const XMLCh * const ) = 0;

    virtual void                         toCheckIdRefList(bool) = 0;

    /**
      * EntityDeclPool
      *
      */
    virtual const NameIdPool<DTDEntityDecl>* getEntityDeclPool() const = 0;

    virtual const NameIdPool<DTDEntityDecl>* setEntityDeclPool(const NameIdPool<DTDEntityDecl>* const) = 0;    
           
    virtual void                             checkEntity(const XMLCh * const ) const = 0 ;

    /**
      * Union datatype handling
      *
      */

    virtual DatatypeValidator * getValidatingMemberType() const = 0 ;
    virtual void setValidatingMemberType(DatatypeValidator * validatingMemberType) = 0 ;

    /**
      * QName datatype handling
      * Create default implementations for source code compatibility
      */
    virtual bool isPrefixUnknown(XMLCh* /* prefix */) { return true; };
    virtual void setElemStack(ElemStack* /* elemStack */) {};
    virtual const XMLCh* getURIForPrefix(XMLCh* /*prefix */) { return 0; };
    virtual void setScanner(XMLScanner* /* scanner */) { };
    virtual void setNamespaceScope(NamespaceScope* /* nsStack */) { };

    //@}

   
protected :
    // -----------------------------------------------------------------------
    /**  Hidden Constructors */
    // -----------------------------------------------------------------------
    //@{
    ValidationContext(MemoryManager* const memMgr = XMLPlatformUtils::fgMemoryManager)
    :fMemoryManager(memMgr)
    {
    };
    //@}

    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fMemoryManager
    //      Pluggable memory manager for dynamic allocation/deallocation.
    // -----------------------------------------------------------------------
    MemoryManager*                    fMemoryManager;

private :
    // -----------------------------------------------------------------------
    /** name  Unimplemented copy constructor and operator= */
    // -----------------------------------------------------------------------
    //@{
    ValidationContext(const ValidationContext& );
    ValidationContext& operator=(const ValidationContext& );
    //@}

};

XERCES_CPP_NAMESPACE_END

#endif

