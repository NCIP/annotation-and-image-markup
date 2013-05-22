/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/ofstd/ofcast.h"

//! @file
//! This file contains implementations of synchronization
//! primitives using the Win32 API. It does not contain any include
//! guards because it is only a fragment to be included by
//! syncprims.h.

namespace dcmtk { namespace log4cplus { namespace thread {


#define DCMTK_LOG4CPLUS_THROW_RTE(msg) \
    do { detail::syncprims_throw_exception (msg, __FILE__, __LINE__); } while (0)

//
//
//

inline
Mutex::Mutex ()
{
    InitializeCriticalSection (&cs);
}


inline
Mutex::~Mutex ()
{
    DeleteCriticalSection (&cs);
}


inline
void
Mutex::lock () const
{
    EnterCriticalSection (&cs);
}


inline
void
Mutex::unlock () const
{
    LeaveCriticalSection (&cs);
}


//
//
//

inline
Semaphore::Semaphore (unsigned max, unsigned initial)
{
    sem = CreateSemaphore (0, initial, max, 0);
    if (! sem)
        DCMTK_LOG4CPLUS_THROW_RTE ("Semaphore::Semaphore");
}


inline
Semaphore::~Semaphore ()
{
    try
    {
        if (! CloseHandle (sem))
            DCMTK_LOG4CPLUS_THROW_RTE ("Semaphore::~Semaphore");
    }
    catch (...)
    { }
}


inline
void
Semaphore::unlock () const
{
    DWORD ret = ReleaseSemaphore (sem, 1, 0);
    if (! ret)
         DCMTK_LOG4CPLUS_THROW_RTE ("Semaphore::unlock");
}


inline
void
Semaphore::lock () const
{
    DWORD ret = WaitForSingleObject (sem, INFINITE);
    if (ret != WAIT_OBJECT_0)
        DCMTK_LOG4CPLUS_THROW_RTE ("Semaphore::lock");
}


//
//
//

inline
ManualResetEvent::ManualResetEvent (bool sig)
{
    ev = CreateEvent (0, true, sig, 0);
    if (! ev)
        DCMTK_LOG4CPLUS_THROW_RTE ("ManualResetEvent::ManualResetEvent");
}


inline
ManualResetEvent::~ManualResetEvent ()
{
    try
    {
        if (! CloseHandle (ev))
            DCMTK_LOG4CPLUS_THROW_RTE ("ManualResetEvent::~ManualResetEvent");
    }
    catch (...)
    { }
}


inline
void
ManualResetEvent::signal () const
{
    if (! SetEvent (ev))
        DCMTK_LOG4CPLUS_THROW_RTE ("ManualResetEVent::signal");
}


inline
void
ManualResetEvent::wait () const
{
    DWORD ret = WaitForSingleObject (ev, INFINITE);
    if (ret != WAIT_OBJECT_0)
        DCMTK_LOG4CPLUS_THROW_RTE ("ManualResetEvent::wait");
}


inline
bool
ManualResetEvent::timed_wait (unsigned long msec) const
{
    DWORD ret = WaitForSingleObject (ev, OFstatic_cast(DWORD, msec));
    switch(ret)
    {
    case WAIT_OBJECT_0:
        return true;

    case WAIT_TIMEOUT:
        return false;

    default:
        DCMTK_LOG4CPLUS_THROW_RTE ("ManualResetEvent::timed_wait");
        // Silence warnings about not returning any value from function
        // returning bool.
        return false;
    }
}


inline
void
ManualResetEvent::reset () const
{
    if (! ResetEvent (ev))
        DCMTK_LOG4CPLUS_THROW_RTE ("ManualResetEvent::reset");
}


#undef DCMTK_LOG4CPLUS_THROW_RTE


} } } // namespace dcmtk { namespace log4cplus { namespace thread {
