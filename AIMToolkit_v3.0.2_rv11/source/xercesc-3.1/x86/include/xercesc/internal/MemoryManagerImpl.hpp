/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: MemoryManagerImpl.hpp 673975 2008-07-04 09:23:56Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_MEMORYMANAGERIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_MEMORYMANAGERIMPL_HPP

#include <xercesc/framework/MemoryManager.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * Configurable memory manager
  *
  * <p>This is Xerces default implementation of the memory
  *    manager interface, which will be instantiated and used
  *    in the absence of an application's memory manager.
  * </p>
  */

class XMLUTIL_EXPORT MemoryManagerImpl : public MemoryManager
{
public:

    /** @name Constructor */
    //@{

    /**
      * Default constructor
      */
    MemoryManagerImpl()
    {
    }
    //@}

    /** @name Destructor */
    //@{

    /**
      * Default destructor
      */
    virtual ~MemoryManagerImpl()
    {
    }
    //@}


    /**
      * This method is called to obtain the memory manager that should be
      * used to allocate memory used in exceptions.
      *
      * @return A pointer to the memory manager
      */
    virtual MemoryManager* getExceptionMemoryManager();


    /** @name The virtual methods in MemoryManager */
    //@{

    /**
      * This method allocates requested memory.
      *
      * @param size The requested memory size
      *
      * @return A pointer to the allocated memory
      */
    virtual void* allocate(XMLSize_t size);

    /**
      * This method deallocates memory
      *
      * @param p The pointer to the allocated memory to be deleted
      */
    virtual void deallocate(void* p);

    //@}

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    MemoryManagerImpl(const MemoryManagerImpl&);
    MemoryManagerImpl& operator=(const MemoryManagerImpl&);

};

XERCES_CPP_NAMESPACE_END

#endif
