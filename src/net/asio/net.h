#pragma once

class socket_base
{
  typedef int message_flags;

 public:

  enum shutdown_type {
    shutdown_received, shutdown_send, shutdown_both
  };

  enum wait_type {
    wait_read, wait_write, wait_error
  };

 protected:
  ~socket_base() {}
};