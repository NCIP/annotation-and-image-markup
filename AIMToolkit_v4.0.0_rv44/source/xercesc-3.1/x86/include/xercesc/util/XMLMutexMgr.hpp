/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLMutexMgr.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLMUTEXMGR_HPP)
#define XERCESC_INCLUDE_GUARD_XMLMUTEXMGR_HPP

#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

typedef void* XMLMutexHandle;

//	Abstract class for mutex implementation.
//  This is be used to allow multiple mutex handling implementations.
class XMLMutexMgr : public XMemory
{
    public:
        XMLMutexMgr() {}
        virtual ~XMLMutexMgr() {}

		// Mutex operations
		virtual XMLMutexHandle	create(MemoryManager* const manager) = 0;
		virtual void			destroy(XMLMutexHandle mtx, MemoryManager* const manager) = 0;
		virtual void			lock(XMLMutexHandle mtx) = 0;
		virtual void			unlock(XMLMutexHandle mtx) = 0;
};

XERCES_CPP_NAMESPACE_END


#endif

