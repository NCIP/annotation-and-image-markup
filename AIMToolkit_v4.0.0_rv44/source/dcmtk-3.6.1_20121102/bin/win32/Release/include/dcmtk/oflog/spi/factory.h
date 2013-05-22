/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_SPI_FACTORY_HEADER_
#define DCMTK_LOG4CPLUS_SPI_FACTORY_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/layout.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/property.h"
#include "dcmtk/oflog/helpers/threads.h"
#include "dcmtk/oflog/spi/filter.h"
#include "dcmtk/oflog/spi/objreg.h"
//#include <map>
//#include <memory>
//#include <vector>


namespace dcmtk {
namespace log4cplus {
    namespace spi {

        /**
         * This is the base class for all factories.
         */
        class DCMTK_LOG4CPLUS_EXPORT BaseFactory {
        public:
            virtual ~BaseFactory() = 0;

            /**
             * Returns the typename of the objects this factory creates.
             */
            virtual tstring getTypeName() = 0;
        };


        /**
         * This abstract class defines the "Factory" interface to create "Appender"
         * objects.
         */
        class DCMTK_LOG4CPLUS_EXPORT AppenderFactory : public BaseFactory {
        public:
            typedef Appender ProductType;
            typedef SharedAppenderPtr ProductPtr;

            AppenderFactory();
            virtual ~AppenderFactory() = 0;

            /**
             * Create an "Appender" object.
             */
            virtual SharedAppenderPtr createObject(const helpers::Properties& props, tstring& error) = 0;
        };



        /**
         * This abstract class defines the "Factory" interface to create "Layout"
         * objects.
         */
        class DCMTK_LOG4CPLUS_EXPORT LayoutFactory : public BaseFactory {
        public:
            typedef Layout ProductType;
            typedef OFauto_ptr<Layout> ProductPtr;

            LayoutFactory();
            virtual ~LayoutFactory() = 0;

            /**
             * Create a "Layout" object.
             */
            virtual OFauto_ptr<Layout> createObject(const helpers::Properties& props, tstring& error) = 0;
        };



        /**
         * This abstract class defines the "Factory" interface to create "Appender"
         * objects.
         */
        class DCMTK_LOG4CPLUS_EXPORT FilterFactory : public BaseFactory {
        public:
            typedef Filter ProductType;
            typedef FilterPtr ProductPtr;

            FilterFactory();
            virtual ~FilterFactory() = 0;

            /**
             * Create a "Filter" object.
             */
            virtual FilterPtr createObject(const helpers::Properties& props, tstring& error) = 0;
        };



        /**
         * This template class is used as a "Factory Registry".  Objects are
         * "entered" into the registry with a "name" using the
         * <code>put()</code> method.  (The registry then owns the object.)
         * These object can then be retrieved using the <code>get()</code>
         * method.
         *
         * <b>Note:</b>  This class is Thread-safe.
         */
        template<class T>
        class DCMTK_LOG4CPLUS_EXPORT FactoryRegistry : private ObjectRegistryBase {
        public:
            typedef T product_type;

            virtual ~FactoryRegistry() {
                clear();
            }

          // public methods
            /**
             * Used to enter an object into the registry.  (The registry now
             *  owns <code>object</code>.)
             */
            bool put(OFauto_ptr<T> object) {
                 bool putValResult = putVal(object->getTypeName(), object.get());
                 object.release();
                 return putValResult;
            }

            /**
             * Used to retrieve an object from the registry.  (The registry
             * owns the returned pointer.)
             */
            T* get(const tstring& name) const {
                return OFstatic_cast(T*, getVal(name));
            }

        protected:
            virtual void deleteObject(void *object) const {
                delete OFstatic_cast(T*, object);
            }
        };


        typedef FactoryRegistry<AppenderFactory> AppenderFactoryRegistry;
        typedef FactoryRegistry<LayoutFactory> LayoutFactoryRegistry;
        typedef FactoryRegistry<FilterFactory> FilterFactoryRegistry;


        /**
         * Returns the "singleton" <code>AppenderFactoryRegistry</code>.
         */
        DCMTK_LOG4CPLUS_EXPORT AppenderFactoryRegistry& getAppenderFactoryRegistry();

        /**
         * Returns the "singleton" <code>LayoutFactoryRegistry</code>.
         */
        DCMTK_LOG4CPLUS_EXPORT LayoutFactoryRegistry& getLayoutFactoryRegistry();

        /**
         * Returns the "singleton" <code>FilterFactoryRegistry</code>.
         */
        DCMTK_LOG4CPLUS_EXPORT FilterFactoryRegistry& getFilterFactoryRegistry();

    }
}
} // end namespace dcmtk


#endif // DCMTK_LOG4CPLUS_SPI_FACTORY_HEADER_

