/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

 /*
 * $Id: MemoryManager.hpp 673975 2008-07-04 09:23:56Z borisk $
 */


#if !defined(XERCESC_INCLUDE_GUARD_MEMORYMANAGER_HPP)
#define XERCESC_INCLUDE_GUARD_MEMORYMANAGER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <stdlib.h>


XERCES_CPP_NAMESPACE_BEGIN


/**
 *  Configurable memory manager
 *
 *  <p>This interface allows outside applications to plug in their own memory
 *  manager to be used by Xerces for memory allocation/deallocation.</p>
 */
class XMLPARSER_EXPORT MemoryManager
{
public:
    // -----------------------------------------------------------------------
    //  Constructors are hidden, only the virtual destructor is exposed
    // -----------------------------------------------------------------------

    /** @name Destructor */
    //@{

    /**
      * Default destructor
      */
    virtual ~MemoryManager()
    {
    }
    //@}


    /**
      * This method is called to obtain the memory manager that should be
      * used to allocate memory used in exceptions. If the same memory
      * manager can be used, simply return 'this' from this function.
      * Note, however, that if there is a possibility that an exception
      * thrown can outlive the memory manager (for example, because the
      * memory manager object is allocated on the stack or is managed by
      * a stack-bound object), it is recommended that you return
      * XMLPlatformUtils::fgMemoryManager.
      *
      * @return A pointer to the memory manager
      */
    virtual MemoryManager* getExceptionMemoryManager() = 0;


    // -----------------------------------------------------------------------
    //  The virtual memory manager interface
    // -----------------------------------------------------------------------
    /** @name The pure virtual methods in this interface. */
    //@{

    /**
      * This method allocates requested memory.
      *
      * @param size The requested memory size
      *
      * @return A pointer to the allocated memory
      */
    virtual void* allocate(XMLSize_t size) = 0;

    /**
      * This method deallocates memory
      *
      * @param p The pointer to the allocated memory to be deleted
      */
    virtual void deallocate(void* p) = 0;

    //@}


protected :
    // -----------------------------------------------------------------------
    //  Hidden Constructors
    // -----------------------------------------------------------------------
    /** @name Constructor */
    //@{

    /**
      * Protected default constructor
      */
    MemoryManager()
    {
    }
    //@}



private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    MemoryManager(const MemoryManager&);
    MemoryManager& operator=(const MemoryManager&);
};

XERCES_CPP_NAMESPACE_END

#endif
