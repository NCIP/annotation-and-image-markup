/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XPathMatcherStack.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XPATHMATCHERSTACK_HPP)
#define XERCESC_INCLUDE_GUARD_XPATHMATCHERSTACK_HPP


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/XPathMatcher.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class VALIDATORS_EXPORT XPathMatcherStack : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
    XPathMatcherStack(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
	~XPathMatcherStack();

	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XPathMatcher* getMatcherAt(const XMLSize_t index) const;
    XMLSize_t     getMatcherCount() const;
    XMLSize_t     size() const;

	// -----------------------------------------------------------------------
    //  Access methods
    // -----------------------------------------------------------------------
    void addMatcher(XPathMatcher* const matcher);

	// -----------------------------------------------------------------------
    //  Stack methods
    // -----------------------------------------------------------------------
    void pushContext();
    void popContext();

	// -----------------------------------------------------------------------
    //  Reset methods
    // -----------------------------------------------------------------------
    void clear();

private:
    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    void cleanUp();

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XPathMatcherStack(const XPathMatcherStack& other);
    XPathMatcherStack& operator= (const XPathMatcherStack& other);

    // -----------------------------------------------------------------------
    //  Data members
    // -----------------------------------------------------------------------
    unsigned int                fMatchersCount;
    ValueStackOf<int>*          fContextStack;
    RefVectorOf<XPathMatcher>*  fMatchers;
};

// ---------------------------------------------------------------------------
//  XPathMatcherStack: Getter methods
// ---------------------------------------------------------------------------
inline XMLSize_t XPathMatcherStack::size() const {

    return fContextStack->size();
}

inline XMLSize_t XPathMatcherStack::getMatcherCount() const {

    return fMatchersCount;
}

inline XPathMatcher*
XPathMatcherStack::getMatcherAt(const XMLSize_t index) const {

    return fMatchers->elementAt(index);
}

// ---------------------------------------------------------------------------
//  XPathMatcherStack: Stack methods
// ---------------------------------------------------------------------------
inline void XPathMatcherStack::pushContext() {

    fContextStack->push(fMatchersCount);
}

inline void XPathMatcherStack::popContext() {

    fMatchersCount = fContextStack->pop();
}

// ---------------------------------------------------------------------------
//  XPathMatcherStack: Access methods
// ---------------------------------------------------------------------------
inline void XPathMatcherStack::addMatcher(XPathMatcher* const matcher) {

    if (fMatchersCount == fMatchers->size()) {

        fMatchers->addElement(matcher);
        fMatchersCount++;
    }
    else {
        fMatchers->setElementAt(matcher, fMatchersCount++);
    }
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file XPathMatcherStack.hpp
  */

