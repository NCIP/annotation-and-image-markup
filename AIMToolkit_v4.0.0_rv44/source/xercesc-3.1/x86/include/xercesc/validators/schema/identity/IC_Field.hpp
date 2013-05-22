/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: IC_Field.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_IC_FIELD_HPP)
#define XERCESC_INCLUDE_GUARD_IC_FIELD_HPP


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/XPathMatcher.hpp>

#include <xercesc/internal/XSerializable.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class ValueStore;
class FieldActivator;


class VALIDATORS_EXPORT IC_Field : public XSerializable, public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    IC_Field(XercesXPath* const xpath,
             IdentityConstraint* const identityConstraint);
	~IC_Field();

    // -----------------------------------------------------------------------
    //  operators
    // -----------------------------------------------------------------------
    bool operator== (const IC_Field& other) const;
    bool operator!= (const IC_Field& other) const;

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XercesXPath* getXPath() const { return fXPath; }
    IdentityConstraint* getIdentityConstraint() const { return fIdentityConstraint; }

    // -----------------------------------------------------------------------
    //  Factory methods
    // -----------------------------------------------------------------------
    XPathMatcher* createMatcher
    (
        FieldActivator* const fieldActivator
        , ValueStore* const valueStore
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(IC_Field)

    IC_Field(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    IC_Field(const IC_Field& other);
    IC_Field& operator= (const IC_Field& other);

    // -----------------------------------------------------------------------
    //  Data members
    // -----------------------------------------------------------------------
    XercesXPath*        fXPath;
    IdentityConstraint* fIdentityConstraint;
};


class VALIDATORS_EXPORT FieldMatcher : public XPathMatcher
{
public:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    ~FieldMatcher() {}

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    ValueStore* getValueStore() const { return fValueStore; }
    IC_Field*   getField() const { return fField; }

    // -----------------------------------------------------------------------
    //  Virtual methods
    // -----------------------------------------------------------------------
    void matched(const XMLCh* const content, DatatypeValidator* const dv,
                 const bool isNil);

private:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    FieldMatcher(XercesXPath* const anXPath,
                 IC_Field* const aField,
                 ValueStore* const valueStore,
                 FieldActivator* const fieldActivator,
                 MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    FieldMatcher(const FieldMatcher& other);
    FieldMatcher& operator= (const FieldMatcher& other);

    // -----------------------------------------------------------------------
    //  Friends
    // -----------------------------------------------------------------------
    friend class IC_Field;

    // -----------------------------------------------------------------------
    //  Data members
    // -----------------------------------------------------------------------
    ValueStore*     fValueStore;
    IC_Field*       fField;
    FieldActivator* fFieldActivator;
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file IC_Field.hpp
  */

