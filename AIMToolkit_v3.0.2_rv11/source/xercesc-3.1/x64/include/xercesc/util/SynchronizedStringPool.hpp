/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: SynchronizedStringPool.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_SYNCHRONIZEDSTRINGPOOL_HPP)
#define XERCESC_INCLUDE_GUARD_SYNCHRONIZEDSTRINGPOOL_HPP

#include <xercesc/framework/MemoryManager.hpp>
#include <xercesc/util/StringPool.hpp>
#include <xercesc/util/Mutexes.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This class provides a synchronized string pool implementation.
//  This will necessarily be slower than the regular XMLStringPool, so it
//  should only be used when updates need to be made in a thread-safe
//  way.  Updates will be made on datastructures local to this object;
//  all queries that don't involve mutation will first be directed at
//  the XMLStringPool implementation with which this object is
//  constructed.
class XMLUTIL_EXPORT XMLSynchronizedStringPool : public XMLStringPool
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XMLSynchronizedStringPool
    (
        const XMLStringPool *  constPool
        , const unsigned int   modulus = 109
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    virtual ~XMLSynchronizedStringPool();


    // -----------------------------------------------------------------------
    //  Pool management methods
    // -----------------------------------------------------------------------
    virtual unsigned int addOrFind(const XMLCh* const newString);
    virtual bool exists(const XMLCh* const newString) const;
    virtual bool exists(const unsigned int id) const;
    virtual void flushAll();
    virtual unsigned int getId(const XMLCh* const toFind) const;
    virtual const XMLCh* getValueForId(const unsigned int id) const;
    virtual unsigned int getStringCount() const;


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLSynchronizedStringPool(const XMLSynchronizedStringPool&);
    XMLSynchronizedStringPool& operator=(const XMLSynchronizedStringPool&);


    // -----------------------------------------------------------------------
    // private data members
    //  fConstPool
    //      the pool whose immutability we're protecting
    // fMutex
    //      mutex to permit synchronous updates of our StringPool
    const XMLStringPool* fConstPool;
    XMLMutex             fMutex;
};

XERCES_CPP_NAMESPACE_END

#endif
