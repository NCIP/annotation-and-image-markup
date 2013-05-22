/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_SPI_OBJECT_REGISTRY_HEADER_
#define DCMTK_LOG4CPLUS_SPI_OBJECT_REGISTRY_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/threads.h"
#include "dcmtk/ofstd/oflist.h"
#include "dcmtk/ofstd/ofmap.h"
//#include <map>
//#include <memory>
//#include <vector>


namespace dcmtk {
namespace log4cplus {
    namespace spi {

        /**
         * This is the base class used to implement the functionality required
         * by the ObjectRegistry template class.
         */
        class DCMTK_LOG4CPLUS_EXPORT ObjectRegistryBase {
        public:
          // public methods
            /**
             * Tests to see whether or not an object is bound in the
             * registry as <code>name</code>.
             */
            bool exists(const tstring& name) const;

            /**
             * Returns the names of all registered objects.
             */
            OFList<tstring> getAllNames() const;

        protected:
          // Ctor and Dtor
            ObjectRegistryBase();
            virtual ~ObjectRegistryBase();

          // protected methods
            /**
             * Used to enter an object into the registry.  (The registry now
             * owns <code>object</code>.)
             */
            bool putVal(const tstring& name, void* object);

            /**
             * Used to retrieve an object from the registry.  (The registry
             * owns the returned pointer.)
             */
            void* getVal(const tstring& name) const;

            /**
             * Deletes <code>object</code>.
             */
            virtual void deleteObject(void *object) const = 0;

            /**
             * Deletes all objects from this registry.
             */
            virtual void clear();

          // Types
            typedef OFMap<tstring, void*> ObjectMap;

          // Data
            DCMTK_LOG4CPLUS_MUTEX_PTR_DECLARE mutex;
            ObjectMap data;
        };

    }
}
} // end namespace dcmtk


#endif // DCMTK_LOG4CPLUS_SPI_OBJECT_REGISTRY_HEADER_

