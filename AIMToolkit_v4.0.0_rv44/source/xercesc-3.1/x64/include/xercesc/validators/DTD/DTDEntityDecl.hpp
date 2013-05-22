/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DTDEntityDecl.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DTDENTITYDECL_HPP)
#define XERCESC_INCLUDE_GUARD_DTDENTITYDECL_HPP

#include <xercesc/framework/XMLEntityDecl.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This is a derivative of the abstract version of an entity decl in the
//  framework directory. We just need to provide implementation of a couple
//  of methods.
//
class VALIDATORS_EXPORT DTDEntityDecl : public XMLEntityDecl
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    DTDEntityDecl(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    DTDEntityDecl
    (
        const   XMLCh* const   entName
        , const bool           fromIntSubset = false
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    DTDEntityDecl
    (
        const   XMLCh* const   entName
        , const XMLCh* const   value
        , const bool           fromIntSubset = false
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    DTDEntityDecl
    (
        const   XMLCh* const    entName
        , const XMLCh           value
        , const bool            fromIntSubset = false
        , const bool            specialChar = false
    );
    ~DTDEntityDecl();


    // -----------------------------------------------------------------------
    //  Implementation of the virtual XMLEntityDecl interface
    // -----------------------------------------------------------------------
    virtual bool getDeclaredInIntSubset() const;
    virtual bool getIsParameter() const;
    virtual bool getIsSpecialChar() const;


    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setDeclaredInIntSubset(const bool newValue);
    void setIsParameter(const bool newValue);
    void setIsSpecialChar(const bool newValue);

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(DTDEntityDecl)

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DTDEntityDecl(const DTDEntityDecl&);
    DTDEntityDecl& operator=(DTDEntityDecl&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fDeclaredInIntSubset
    //      Indicates whether the entity was declared in the internal subset
    //      or not. If not, it cannot be referred to from a standalone
    //      document.
    //
    //  fIsParameter
    //      Indicates whether this is a parameter entity or a general entity.
    //
    //  fIsSpecialChar
    //      This indicates that its one of the special character entities,
    //      e.g. lt or gt or amp. We need to know this because there are
    //      places where only a numeric char ref or special char ref is valid
    //      and all others are ignored or illegal.
    // -----------------------------------------------------------------------
    bool    fDeclaredInIntSubset;
    bool    fIsParameter;
    bool    fIsSpecialChar;
};


// ---------------------------------------------------------------------------
//  DTDEntityDecl: Constructors and Destructor
// ---------------------------------------------------------------------------
inline DTDEntityDecl::DTDEntityDecl(MemoryManager* const manager) :

    XMLEntityDecl(manager)
    , fDeclaredInIntSubset(false)
    , fIsParameter(false)
    , fIsSpecialChar(false)
{
}

inline DTDEntityDecl::DTDEntityDecl( const XMLCh* const   entName
                                   , const bool           fromIntSubset
                                   , MemoryManager* const manager) :

    XMLEntityDecl(entName, manager)
    , fDeclaredInIntSubset(fromIntSubset)
    , fIsParameter(false)
    , fIsSpecialChar(false)
{
}

inline DTDEntityDecl::DTDEntityDecl( const XMLCh* const   entName
                                   , const XMLCh* const   value
                                   , const bool           fromIntSubset
                                   , MemoryManager* const manager) :
    XMLEntityDecl(entName, value, manager)
    , fDeclaredInIntSubset(fromIntSubset)
    , fIsParameter(false)
    , fIsSpecialChar(false)
{
}

inline DTDEntityDecl::DTDEntityDecl(const   XMLCh* const    entName
                                    , const XMLCh           value
                                    , const bool            fromIntSubset
                                    , const bool            specialChar) :
    XMLEntityDecl(entName, value, XMLPlatformUtils::fgMemoryManager)
    , fDeclaredInIntSubset(fromIntSubset)
    , fIsParameter(false)
    , fIsSpecialChar(specialChar)
{
}

inline DTDEntityDecl::~DTDEntityDecl()
{
}


// ---------------------------------------------------------------------------
//  DTDEntityDecl: Getter methods
// ---------------------------------------------------------------------------
inline bool DTDEntityDecl::getDeclaredInIntSubset() const
{
    return fDeclaredInIntSubset;
}

inline bool DTDEntityDecl::getIsParameter() const
{
    return fIsParameter;
}

inline bool DTDEntityDecl::getIsSpecialChar() const
{
    return fIsSpecialChar;
}


// ---------------------------------------------------------------------------
//  DTDEntityDecl: Setter methods
// ---------------------------------------------------------------------------
inline void DTDEntityDecl::setDeclaredInIntSubset(const bool newValue)
{
    fDeclaredInIntSubset = newValue;
}

inline void DTDEntityDecl::setIsParameter(const bool newValue)
{
    fIsParameter = newValue;
}

inline void DTDEntityDecl::setIsSpecialChar(const bool newValue)
{
    fIsSpecialChar = newValue;
}

XERCES_CPP_NAMESPACE_END

#endif
