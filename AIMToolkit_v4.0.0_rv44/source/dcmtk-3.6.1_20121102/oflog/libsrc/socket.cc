/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/helpers/socket.h"
#include "dcmtk/oflog/helpers/loglog.h"


using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;

#if !defined(_WIN32)
//#  include <unistd.h>
#  define INCLUDE_UNISTD
//#  include <errno.h>
#  define INCLUDE_CERRNO
#  include "dcmtk/ofstd/ofstdinc.h"
#  define GET_LAST_ERROR errno
#else
#  define GET_LAST_ERROR WSAGetLastError()
#endif



//////////////////////////////////////////////////////////////////////////////
// AbstractSocket ctors and dtor
//////////////////////////////////////////////////////////////////////////////

AbstractSocket::AbstractSocket()
: sock(INVALID_SOCKET),
  state(not_opened),
  err(0)
{
}



AbstractSocket::AbstractSocket(SOCKET_TYPE sock_, SocketState state_, int err_)
: sock(sock_),
  state(state_),
  err(err_)
{
}



AbstractSocket::AbstractSocket(const AbstractSocket& rhs)
{
    copy(rhs);
}


AbstractSocket::~AbstractSocket()
{
    close();
}



//////////////////////////////////////////////////////////////////////////////
// AbstractSocket methods
//////////////////////////////////////////////////////////////////////////////

void
AbstractSocket::close()
{
    if(sock != INVALID_SOCKET) {
        closeSocket(sock);
        sock = INVALID_SOCKET;
    }
}



bool
AbstractSocket::isOpen() const
{
    return sock != INVALID_SOCKET;
}




AbstractSocket&
AbstractSocket::operator=(const AbstractSocket& rhs)
{
    if(&rhs != this) {
        close();
        copy(rhs);
    }

    return *this;
}



void
AbstractSocket::copy(const AbstractSocket& r)
{
    AbstractSocket& rhs = OFconst_cast(AbstractSocket&, r);
    sock = rhs.sock;
    state = rhs.state;
    err = rhs.err;
    rhs.sock = INVALID_SOCKET;
    rhs.state = not_opened;
    rhs.err = 0;
}



//////////////////////////////////////////////////////////////////////////////
// Socket ctors and dtor
//////////////////////////////////////////////////////////////////////////////

Socket::Socket()
: AbstractSocket()
{
}



Socket::Socket(const tstring& address, int port)
: AbstractSocket()
{
    sock = connectSocket(address, port, state);
    if(sock == INVALID_SOCKET) {
        err = errno;
    }
}


Socket::Socket(SOCKET_TYPE sock_, SocketState state_, int err_)
: AbstractSocket(sock_, state_, err_)
{
}



Socket::~Socket()
{
}





//////////////////////////////////////////////////////////////////////////////
// Socket methods
//////////////////////////////////////////////////////////////////////////////

bool
Socket::read(SocketBuffer& buffer)
{
    long retval = helpers::read(sock, buffer);
    if(retval <= 0) {
        close();
    }
    else {
        buffer.setSize(retval);
    }

    return (retval > 0);
}



bool
Socket::write(const SocketBuffer& buffer)
{
    long retval = helpers::write(sock, buffer);
    if(retval <= 0) {
        close();
    }

    return (retval > 0);
}




//////////////////////////////////////////////////////////////////////////////
// ServerSocket ctor and dtor
//////////////////////////////////////////////////////////////////////////////

ServerSocket::ServerSocket(int port)
{
    sock = openSocket(port, state);
    if(sock == INVALID_SOCKET) {
        err = errno;
    }
}



ServerSocket::~ServerSocket()
{
}



//////////////////////////////////////////////////////////////////////////////
// ServerSocket methods
//////////////////////////////////////////////////////////////////////////////

Socket
ServerSocket::accept()
{
    SocketState state_;
    SOCKET_TYPE clientSock = acceptSocket(sock, state_);
    return Socket(clientSock, state_, 0);
}


