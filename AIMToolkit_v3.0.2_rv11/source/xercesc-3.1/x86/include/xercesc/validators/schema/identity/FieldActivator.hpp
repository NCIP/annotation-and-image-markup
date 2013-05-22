/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: FieldActivator.hpp 679340 2008-07-24 10:28:29Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_FIELDACTIVATOR_HPP)
#define XERCESC_INCLUDE_GUARD_FIELDACTIVATOR_HPP

/**
  * This class is responsible for activating fields within a specific scope;
  * the caller merely requests the fields to be activated.
  */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/ValueHashTableOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class IdentityConstraint;
class XPathMatcher;
class ValueStoreCache;
class IC_Field;
class XPathMatcherStack;


class VALIDATORS_EXPORT FieldActivator : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    FieldActivator(ValueStoreCache* const valueStoreCache,
                   XPathMatcherStack* const matcherStack,
                   MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
	FieldActivator(const FieldActivator& other);
	~FieldActivator();

    // -----------------------------------------------------------------------
    //  Operator methods
    // -----------------------------------------------------------------------
    FieldActivator& operator =(const FieldActivator& other);

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getMayMatch(IC_Field* const field);

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setValueStoreCache(ValueStoreCache* const other);
    void setMatcherStack(XPathMatcherStack* const matcherStack);
    void setMayMatch(IC_Field* const field, bool value);

	// -----------------------------------------------------------------------
    //  Activation methods
    // -----------------------------------------------------------------------
    /**
      * Start the value scope for the specified identity constraint. This
      * method is called when the selector matches in order to initialize
      * the value store.
      */
    void startValueScopeFor(const IdentityConstraint* const ic, const int initialDepth);

    /**
      * Request to activate the specified field. This method returns the
      * matcher for the field.
      */
    XPathMatcher* activateField(IC_Field* const field, const int initialDepth);

    /**
      * Ends the value scope for the specified identity constraint.
      */
    void endValueScopeFor(const IdentityConstraint* const ic, const int initialDepth);

private:
    // -----------------------------------------------------------------------
    //  Data
    // -----------------------------------------------------------------------
    ValueStoreCache*                   fValueStoreCache;
    XPathMatcherStack*                 fMatcherStack;
    ValueHashTableOf<bool, PtrHasher>* fMayMatch;
    MemoryManager*                     fMemoryManager;
};


// ---------------------------------------------------------------------------
//  FieldActivator: Getter methods
// ---------------------------------------------------------------------------
inline bool FieldActivator::getMayMatch(IC_Field* const field) {

    return fMayMatch->get(field);
}

// ---------------------------------------------------------------------------
//  FieldActivator: Setter methods
// ---------------------------------------------------------------------------
inline void FieldActivator::setValueStoreCache(ValueStoreCache* const other) {

    fValueStoreCache = other;
}

inline void
FieldActivator::setMatcherStack(XPathMatcherStack* const matcherStack) {

    fMatcherStack = matcherStack;
}

inline void FieldActivator::setMayMatch(IC_Field* const field, bool value) {

    fMayMatch->put(field, value);
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file FieldActivator.hpp
  */
