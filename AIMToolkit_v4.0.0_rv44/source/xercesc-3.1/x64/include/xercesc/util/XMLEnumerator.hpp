/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLEnumerator.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLENUMERATOR_HPP)
#define XERCESC_INCLUDE_GUARD_XMLENUMERATOR_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

template <class TElem> class XMLEnumerator
{
public :
    // -----------------------------------------------------------------------
    //  Destructor
    // -----------------------------------------------------------------------
    virtual ~XMLEnumerator() {};

    // -----------------------------------------------------------------------
    //  XMLEnumerator interface
    // -----------------------------------------------------------------------
    virtual bool hasMoreElements() const = 0;
    virtual TElem& nextElement() = 0;
    virtual void Reset() = 0;

    XMLEnumerator() {}
    XMLEnumerator(const XMLEnumerator<TElem>&) {}

private:
	// -----------------------------------------------------------------------
    //  Unimplemented operators
    // -----------------------------------------------------------------------
    XMLEnumerator<TElem>& operator=(const XMLEnumerator<TElem>&);    
};

XERCES_CPP_NAMESPACE_END

#endif
