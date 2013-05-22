/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIOBJCOU_H
#define DIOBJCOU_H

#include "dcmtk/config/osconfig.h"

#ifdef WITH_THREADS
#include "dcmtk/ofstd/ofthread.h"
#endif

#include "dcmtk/dcmimgle/didefine.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class to count number of instances (objects created from a certain class).
 *  used to manage more than one reference to an object in a secure way.
 */
class DCMTK_DCMIMGLE_EXPORT DiObjectCounter
{

 public:

    /** add a reference.
     *  Increase the internal counter by 1.
     */
    inline void addReference()
    {
#ifdef WITH_THREADS
        theMutex.lock();
#endif
        ++Counter;
#ifdef WITH_THREADS
        theMutex.unlock();
#endif
    }

    /** remove a reference.
     *  Decrease the internal counter by 1 and delete the object only if the counter is zero.
     */
    inline void removeReference()
    {
#ifdef WITH_THREADS
        theMutex.lock();
#endif
        if (--Counter == 0)
        {
#ifdef WITH_THREADS
            theMutex.unlock();
#endif
            delete this;
#ifdef WITH_THREADS
        } else {
            theMutex.unlock();
#endif
        }
    }


 protected:

    /** constructor.
     *  Internal counter is initialized with 1.
     */
    DiObjectCounter()
      : Counter(1)
#ifdef WITH_THREADS
       ,theMutex()
#endif
    {
    }

    /** destructor
     */
    virtual ~DiObjectCounter()
    {
    }


 private:

    /// internal counter
    unsigned long Counter;

#ifdef WITH_THREADS
    /** if compiled for multi-thread operation, the Mutex protecting
     *  access to the value of this object.
     */
    OFMutex theMutex;
#endif
};


#endif
