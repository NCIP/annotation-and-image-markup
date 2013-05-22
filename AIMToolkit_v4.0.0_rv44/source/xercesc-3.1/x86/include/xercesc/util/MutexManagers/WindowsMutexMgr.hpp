/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: WindowsMutexMgr.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_WINDOWSMUTEXMGR_HPP)
#define XERCESC_INCLUDE_GUARD_WINDOWSMUTEXMGR_HPP

#include <xercesc/util/XMLMutexMgr.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/*
	The mutex manager to use on MS Windows platforms
*/
class WindowsMutexMgr : public XMLMutexMgr
{
    public:
        WindowsMutexMgr();
        virtual ~WindowsMutexMgr();

		// Mutex operations
		virtual XMLMutexHandle	create(MemoryManager* const manager);
		virtual void			destroy(XMLMutexHandle mtx, MemoryManager* const manager);
		virtual void			lock(XMLMutexHandle mtx);
		virtual void			unlock(XMLMutexHandle mtx);
};

XERCES_CPP_NAMESPACE_END


#endif

