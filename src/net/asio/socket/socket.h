#pragma once

#include <cstddef>

#include "net/asio/socket/reactive_socket_service.h"

#include "net/asio/error_code.h"
#include "net/asio/async_result.h"
#include "net/asio/io_object_impl.h"

template<typename Protocol, typename Executor>
class basic_socket : public socket_base
{
private:

  class initiate_async_connect;
  class initiate_async_wait;

public:
  
  typedef Executor executor_type;
  typedef Protocol protocol_type;
  typedef Protocol::endpoint endpoint_type;

  explicit basic_socket(const executor_type& ex) : {}

protected:
  ~basic_socket() {}

  io_object_impl<reactive_socket_service<Protocol>, Executor> impl_;
};

template<typename Protocol, typename Executor>
class basic_datagram_socket : public basic_socket<Protocol, Executor>
{
 private:

  class initiate_async_send;
  class initiate_async_send_to;
  class initiate_async_receive;
  class initiate_async_receive_from;
  
 public:

  typedef Executor executor_type;

  template<typename Executor1>
  struct rebind_executor
  {
    typedef basic_datagram_socket<Protocol, Executor1> other;
  };

  typedef Protocol protocol_type;
  typedef typename Protocol::endpoint endpoint_type;

  explicit basic_datagram_socket(const executor_type& ex, const endpoint_type& endpoint)
      : basic_socket<Protocol, Executor>(ex, endpoint) {
    
  }

  ~basic_datagram_socket() {}

  template<typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers) {
    std::error_code ec;
    std::size_t s = this->impl_.get_service().send(
      this->impl
    )
  }
  
  template<typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers) {

  }

 private:
  
};
