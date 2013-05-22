/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLRefInfo.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLREFINFO_HPP)
#define XERCESC_INCLUDE_GUARD_XMLREFINFO_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#include <xercesc/internal/XSerializable.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 *  This class provides a simple means to track ID Ref usage. Since id/idref
 *  semantics are part of XML 1.0, any validator will likely to be able to
 *  track them. Instances of this class represent a reference and two markers,
 *  one for its being declared and another for its being used. When the
 *  document is done, one can look at each instance and, if used but not
 *  declared, its an error.
 *
 *  The getKey() method allows it to support keyed collection semantics. It
 *  returns the referenced name, so these objects will be stored via the hash
 *  of the name. This name will either be a standard QName if namespaces are
 *  not enabled/supported by the validator, or it will be in the form
 *  {url}name if namespace processing is enabled.
 */
class XMLPARSER_EXPORT XMLRefInfo : public XSerializable, public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    /** @name Constructor */
    //@{
    XMLRefInfo
    (
        const   XMLCh* const   refName
        , const bool           fDeclared = false
        , const bool           fUsed = false
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    //@}

    /** @name Destructor */
    //@{
    ~XMLRefInfo();
    //@}


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getDeclared() const;
    const XMLCh* getRefName() const;
    bool getUsed() const;


    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setDeclared(const bool newValue);
    void setUsed(const bool newValue);

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLRefInfo)

    XMLRefInfo
    (
      MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLRefInfo(const XMLRefInfo&);
    XMLRefInfo& operator=(XMLRefInfo&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fDeclared
    //      The name was declared somewhere as an ID attribute.
    //
    //  fRefName
    //      The name of the ref that this object represents. This is not a
    //      name of the attribute, but of the value of an ID or IDREF attr
    //      in content.
    //
    //  fUsed
    //      The name was used somewhere in an IDREF/IDREFS attribute. If this
    //      is true, but fDeclared is false, then the ref does not refer to
    //      a declared ID.
    // -----------------------------------------------------------------------
    bool        fDeclared;
    bool        fUsed;
    XMLCh*      fRefName;
    MemoryManager* fMemoryManager;
};


// ---------------------------------------------------------------------------
//  XMLRefInfo: Constructors and Destructor
// ---------------------------------------------------------------------------
inline XMLRefInfo::XMLRefInfo( const XMLCh* const   refName
                             , const bool           declared
                             , const bool           used
                             , MemoryManager* const manager) :
    fDeclared(declared)
    , fUsed(used)
    , fRefName(0)
    , fMemoryManager(manager)
{
    fRefName = XMLString::replicate(refName, fMemoryManager);
}

inline XMLRefInfo::~XMLRefInfo()
{
    fMemoryManager->deallocate(fRefName);
}


// ---------------------------------------------------------------------------
//  XMLRefInfo: Getter methods
// ---------------------------------------------------------------------------
inline bool XMLRefInfo::getDeclared() const
{
    return fDeclared;
}

inline const XMLCh* XMLRefInfo::getRefName() const
{
    return fRefName;
}

inline bool XMLRefInfo::getUsed() const
{
    return fUsed;
}


// ---------------------------------------------------------------------------
//  XMLRefInfo: Setter methods
// ---------------------------------------------------------------------------
inline void XMLRefInfo::setDeclared(const bool newValue)
{
    fDeclared = newValue;
}

inline void XMLRefInfo::setUsed(const bool newValue)
{
    fUsed = newValue;
}

XERCES_CPP_NAMESPACE_END

#endif
