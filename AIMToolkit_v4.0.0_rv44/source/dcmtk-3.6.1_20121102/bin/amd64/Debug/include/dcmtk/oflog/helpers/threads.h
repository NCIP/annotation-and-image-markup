/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_THREADS_HEADER_
#define DCMTK__LOG4CPLUS_THREADS_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/pointer.h"


namespace dcmtk { namespace log4cplus { namespace thread {

/**
 * This is used to lock a mutex.  The dtor unlocks the mutex.
 */
class Guard
{
public:
    /** "locks" <code>mutex</code>. */
    Guard(DCMTK_LOG4CPLUS_MUTEX_PTR_DECLARE mutex)
        : _mutex (mutex)
    {
        DCMTK_LOG4CPLUS_MUTEX_LOCK( _mutex );
    }

    /** "unlocks" <code>mutex</code>. */
    ~Guard()
    {
        DCMTK_LOG4CPLUS_MUTEX_UNLOCK( _mutex );
    }

private:
    DCMTK_LOG4CPLUS_MUTEX_PTR_DECLARE _mutex;

    // disable copy
    Guard(const Guard&);
    Guard& operator=(const Guard&);
};


#ifndef DCMTK_LOG4CPLUS_SINGLE_THREADED

DCMTK_LOG4CPLUS_EXPORT void blockAllSignals();
DCMTK_LOG4CPLUS_EXPORT tstring getCurrentThreadName();


struct ThreadStart;


/**
 * There are many cross-platform C++ Threading libraries.  The goal of
 * this class is not to replace (or match in functionality) those
 * libraries.  The goal of this class is to provide a simple Threading
 * class with basic functionality.
 */
class DCMTK_LOG4CPLUS_EXPORT AbstractThread
    : public virtual dcmtk::log4cplus::helpers::SharedObject
{
public:
    AbstractThread();
    bool isRunning() const { return running; }
    DCMTK_LOG4CPLUS_THREAD_KEY_TYPE getThreadId() const;
    DCMTK_LOG4CPLUS_THREAD_HANDLE_TYPE getThreadHandle () const;
    virtual void start();
    void join () const;

protected:
    // Force objects to be constructed on the heap
    virtual ~AbstractThread();
    virtual void run() = 0;

private:
    bool running;

    // Friends.
    friend struct ThreadStart;

#  ifdef DCMTK_LOG4CPLUS_USE_PTHREADS
    pthread_t handle;

#  elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    HANDLE handle;
    unsigned thread_id;

#  endif

    // Disallow copying of instances of this class.
    AbstractThread(const AbstractThread&);
    AbstractThread& operator=(const AbstractThread&);
};

typedef helpers::SharedObjectPtr<AbstractThread> AbstractThreadPtr;


#endif // DCMTK_LOG4CPLUS_SINGLE_THREADED


} } } // namespace dcmtk { namespace log4cplus { namespace thread {


#endif // DCMTK__LOG4CPLUS_THREADS_HEADER_

