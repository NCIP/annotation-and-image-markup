/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_HELPERS_SOCKET_BUFFER_HEADER_
#define DCMTK_LOG4CPLUS_HELPERS_SOCKET_BUFFER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/lloguser.h"


namespace dcmtk {
namespace log4cplus {
    namespace helpers {

        /**
         *
         */
        class DCMTK_LOG4CPLUS_EXPORT SocketBuffer : protected LogLogUser
        {
        public:
            SocketBuffer(size_t max);
            SocketBuffer(const SocketBuffer& rhs);
            ~SocketBuffer();

            SocketBuffer& operator=(const SocketBuffer& rhs);

            char *getBuffer() const { return buffer; }
            size_t getMaxSize() const { return maxsize; }
            size_t getSize() const { return size; }
            void setSize(size_t s) { size = s; }
            size_t getPos() const { return pos; }

            unsigned char readByte();
            unsigned short readShort();
            unsigned int readInt();
            tstring readString(unsigned char sizeOfChar);

            void appendByte(unsigned char val);
            void appendShort(unsigned short val);
            void appendInt(unsigned int val);
            void appendSize_t(size_t val);
            void appendString(const tstring& str);
            void appendBuffer(const SocketBuffer& buffer);

        private:
          // Methods
            void copy(const SocketBuffer& rhs);

          // Data
            size_t maxsize;
            size_t size;
            size_t pos;
            char *buffer;
        };

    } // end namespace helpers
} // end namespace log4cplus
} // end namespace dcmtk

#endif // DCMTK_LOG4CPLUS_HELPERS_SOCKET_HEADER_

