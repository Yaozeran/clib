#pragma once

#include "asio/socket/socket_types.h"
#include "asio/socket/socket_option.h"

class socket_base
{
public:

  enum shutdown_type {
    shutdown_receive = SHUT_RD,
    shutdown_send = SHUT_WR,
    shutdown_both = SHUT_RDWR
  };

  enum wait_type {
    wait_read, wait_write, wait_error
  };

  typedef int message_flags;

  typedef socket_option::boolean<SOL_SOCKET, SO_BROADCAST> broadcast;

protected:

  ~socket_base() { }
};