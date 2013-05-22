/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_HELPERS_SOCKET_HEADER_
#define DCMTK_LOG4CPLUS_HELPERS_SOCKET_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/sockbuff.h"
#if defined(_WIN32)
#include <winsock.h>
#endif

namespace dcmtk {
namespace log4cplus {
    namespace helpers {

        enum SocketState { ok,
                           not_opened,
                           bad_address,
                           connection_failed,
                           broken_pipe,
                           invalid_access_mode,
                           message_truncated
                         };

#if !defined(_WIN32)
        typedef int SOCKET_TYPE;
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#else
        typedef SOCKET SOCKET_TYPE;
#endif

        class DCMTK_LOG4CPLUS_EXPORT AbstractSocket {
        public:
          // ctor and dtor
            AbstractSocket();
            AbstractSocket(SOCKET_TYPE sock, SocketState state, int err);
            AbstractSocket(const AbstractSocket&);
            virtual ~AbstractSocket() = 0;

          // methods
            /// Close socket
            virtual void close();
            virtual bool isOpen() const;

            AbstractSocket& operator=(const AbstractSocket& rhs);

        protected:
          // Methods
            virtual void copy(const AbstractSocket& rhs);

          // Data
            SOCKET_TYPE sock;
            SocketState state;
            int err;
        };



        /**
         * This class implements client sockets (also called just "sockets").
         * A socket is an endpoint for communication between two machines.
         */
        class DCMTK_LOG4CPLUS_EXPORT Socket : public AbstractSocket {
        public:
          // ctor and dtor
            Socket();
            Socket(SOCKET_TYPE sock, SocketState state, int err);
            Socket(const tstring& address, int port);
            virtual ~Socket();

          // methods
            virtual bool read(SocketBuffer& buffer);
            virtual bool write(const SocketBuffer& buffer);
        };



        /**
         * This class implements server sockets. A server socket waits for
         * requests to come in over the network. It performs some operation
         * based on that request, and then possibly returns a result to the
         * requester.
         */
        class DCMTK_LOG4CPLUS_EXPORT ServerSocket : public AbstractSocket {
        public:
          // ctor and dtor
            ServerSocket(int port);
            virtual ~ServerSocket();

            Socket accept();
        };


        DCMTK_LOG4CPLUS_EXPORT SOCKET_TYPE openSocket(unsigned short port, SocketState& state);
        DCMTK_LOG4CPLUS_EXPORT SOCKET_TYPE connectSocket(const tstring& hostn,
                                                   unsigned short port, SocketState& state);
        DCMTK_LOG4CPLUS_EXPORT SOCKET_TYPE acceptSocket(SOCKET_TYPE sock, SocketState& state);
        DCMTK_LOG4CPLUS_EXPORT int closeSocket(SOCKET_TYPE sock);

        DCMTK_LOG4CPLUS_EXPORT long read(SOCKET_TYPE sock, SocketBuffer& buffer);
        DCMTK_LOG4CPLUS_EXPORT long write(SOCKET_TYPE sock, const SocketBuffer& buffer);

        DCMTK_LOG4CPLUS_EXPORT tstring getHostname (bool fqdn);

    } // end namespace helpers
} // end namespace log4cplus
} // end namespace dcmtk

#endif // DCMTK_LOG4CPLUS_HELPERS_SOCKET_HEADER_
