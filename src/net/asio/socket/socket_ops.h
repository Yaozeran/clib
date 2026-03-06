#pragma once

#include <cstddef>

#include "net/socket/socket_types.h"

#include "net/error.h"
#include "net/error_code.h"

namespace socket_ops
{

enum {

  user_set_non_blocking = 1,

  internal_non_blocking = 2,

  non_blocking = user_set_non_blocking | internal_non_blocking,

  enable_connection_aborted = 4,

  user_set_linger = 8,

  stream_oriented = 16,

  datagram_oriented = 32,

  possible_dup = 64,

  reset_edge_on_partial_read = 128

}; // enum

typedef unsigned char state_type;

inline void clear_last_error() {
#if defined(WINDOWS) || defined(__CYGWIN__)
#else
  errno = 0;
#endif
}

inline void get_last_error(std::error_code& ec, bool is_error_condition) {
  if (!is_error_condition) {
    error::clear(ec);
  } else {
#if defined(WINDOWS) || defined(__CYGWIN__)
#else 
    ec = std::error_code(errno, error::get_system_category());
#endif
  }
}

std::size_t available(socket_type s, std::error_code& ec) {
  if (s == invalid_socket) {
    ec = error::bad_descriptor;
    return 0;
  }
  ioctl_arg_type value = 0;
#if defined(WINDOWS) || defined(__CYGWIN__)
  int result = ::ioctlsocket(s, FIONREAD, &value);
#else 
  int result = ::ioctl(s, FIONREAD, &value);
#endif
  get_last_error(ec, result < 0);
#if defined(ENOTTY)
  if (ec.value() == ENOTTY) ec = error::not_socket;
#endif 
  return ec ? static_cast<size_t>(0) : static_cast<size_t>(value);
}

typedef iovec buf;

signed_size_type recv(socket_type s, buf* bufs, size_t count, int flags, std::error_code& ec) {
  msghdr msg = msghdr();
  msg.msg_iov = bufs;
  msg.msg_iovlen = static_cast<int>(count);
  signed_size_type result = ::recvmsg(s, &msg, flags);
  get_last_error(ec, result < 0);
  return result;
}

int poll_read(socket_type s, state_type state, int msec, std::error_code& ec) {
  if (s == invalid_socket) {
    ec = error::bad_descriptor;
    return socket_error_retval;
  }
#if defined(ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
#else
  pollfd fds;
  fds.fd = s;
  fds.events = POLLIN;
  fds.revents = 0;
  int timeout = (state & user_set_non_blocking) ? 0 : msec;
  int result = ::poll(&fds, 1, timeout);
#endif
}

} // namespace socket_ops