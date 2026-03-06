#pragma once

#include <cstddef>

#include "net/reactor/reactor.h"
#include "net/execution_context.h"

#include "net/socket/socket_types.h"
#include "net/socket/socket_ops.h"
#include "net/socket/socket_base.h"

#include "net/error_code.h"

namespace asio
{

} // namespace asio


class reactive_socket_service_base
{
public:

  struct base_impl_type {
    socket_type socket_;
    socket_ops::state_type state_;
    reactor::per_descriptor_data reactor_data_;
  };

  inline reactive_socket_service_base(execution_context& context) {

  }

  inline void base_shutdown() {

  }

  inline void construct(base_impl_type& impl) {
    impl.socket_ = invalid_socket;
    impl.state_ = 0;
    impl.reactor_data_ = reactor::per_descriptor_data();
  }

  bool is_open(const base_impl_type& impl) const { return impl.socket_ != invalid_socket; }

  std::error_code close(base_impl_type& impl, std::error_code& ec) {

  }

  std::size_t available(const base_impl_type& impl, std::error_code& ec) { 
    return socket_ops::available(impl.socket_, ec); 
  }

  std::error_code wait(base_impl_type& impl, socket_base::wait_type& w, std::error_code& ec) {
    switch (w) {
    case socket_base::wait_read:
      socket_ops::poll_read(impl.socket_, impl.state_, -1, ec);
      break;
    case socket_base::wait_write:
      socket_ops::poll_write(impl.socket_, impl.state_, -1, ec);
      break;
    case socket_base::wait_error:
      socket_ops::poll_error(impl.socket_, impl.state_, -1, ec);
      break;
    default:
      ec = error::invalid_argument;
      break;
    }
    return ec;
  }

  template<typename Handler, typename IoExecutor>
  void async_wait(base_impl_type& impl, socket_base::wait_type w, Handler& handler, const IoExecutor& io_ex) {
    bool is_continuation = is_continuation(handler); // todo
    typedef reactive_wait_op<Handler, IoExecutor> op;

    typename op::ptr p = { addressof(handler), op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, handler, io_ex);

    int op_type;
    switch (w)
    {
    case socket_base::wait_read:
      op_type = reactor::read_op;
      break;
    case socket_base::wait_write:
      op_type = reactor::write_op;
      break;
    case socket_base::wait_error:
      op_type = reactor::except_op;
      break;
    default:
      
    }
  }
};