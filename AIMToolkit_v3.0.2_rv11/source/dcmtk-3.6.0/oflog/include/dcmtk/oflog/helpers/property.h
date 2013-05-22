/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef LOG4CPLUS_HELPERS_PROPERTY_HEADER_
#define LOG4CPLUS_HELPERS_PROPERTY_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/tstring.h"
//#include <map>
#include "dcmtk/ofstd/ofmap.h"
//#include <vector>
#include "dcmtk/ofstd/oflist.h"

#if (defined(__MWERKS__) && defined(__MACOS__))
using STD_NAMESPACE size_t;
#endif


namespace log4cplus {
    namespace helpers {

        class LOG4CPLUS_EXPORT Properties {
        public:
            Properties();
            explicit Properties(log4cplus::tistream& input);
            explicit Properties(const log4cplus::tstring& inputFile);
            virtual ~Properties();

          // constants
            static const tchar PROPERTIES_COMMENT_CHAR;

          // methods
            /**
             * Tests to see if <code>key</code> can be found in this map.
             */
            bool exists(const log4cplus::tstring& key) const {
                return data.find(key) != data.end();
            }


            /**
             * Returns the number of entries in this map.
             */
            size_t size() const {
                return data.size();
            }

            /**
             * Searches for the property with the specified key in this property
             * list. If the key is not found in this property list, the default
             * property list, and its defaults, recursively, are then checked.
             * The method returns <code>null</code> if the property is not found.
             */
            log4cplus::tstring getProperty(const log4cplus::tstring& key) const;

            /**
             * Searches for the property with the specified key in this property
             * list. If the key is not found in this property list, the default
             * property list, and its defaults, recursively, are then checked.
             * The method returns the default value argument if the property is
             * not found.
             */
            log4cplus::tstring getProperty(const log4cplus::tstring& key,
                                           const log4cplus::tstring& defaultVal) const;

            /**
             * Returns all the keys in this property list.
             */
            OFList<log4cplus::tstring> propertyNames() const;

            /**
             * Inserts <code>value</code> into this map indexed by <code>key</code>.
             */
            void setProperty(const log4cplus::tstring& key, const log4cplus::tstring& value);

            /**
             * Removed the property index by <code>key</code> from this map.
             */
            bool removeProperty(const log4cplus::tstring& key);

            /**
             * Returns a subset of the "properties" whose keys start with
             * "prefix".  The returned "properties" have "prefix" trimmed from
             * their keys.
             */
            Properties getPropertySubset(const log4cplus::tstring& prefix) const;

        protected:
          // Types
//            LOG4CPLUS_EXPIMP_TEMPLATE template class LOG4CPLUS_EXPORT STD_NAMESPACE map<log4cplus::tstring, log4cplus::tstring>;
            typedef OFMap<log4cplus::tstring, log4cplus::tstring> StringMap;

          // Methods
            void init(log4cplus::tistream& input);

          // Data
            StringMap data;
        };
    } // end namespace helpers

}


#endif // LOG4CPLUS_HELPERS_PROPERTY_HEADER_

