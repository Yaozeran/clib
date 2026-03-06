/* Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#pragma once

#include "asio/error_code.h"

namespace asio
{

namespace error
{

enum basic_errors {
  
  access_denied = EACCES,

  bad_descriptor = EBADF,

  not_socket = ENOTSOCK,

  invalid_argument = EINVAL,

};

enum addrinfo_errors {

};

enum misc_errors {

};

inline void clear(asio::error_code& ec) {
  ec.assign(0, ec.category());
}

inline const asio::error_category& get_system_category() { return system_category(); }

  namespace detail
  {
  std::error_condition error_number_to_condition(int ev)
  {
    switch (ev)
    {
    case access_denied:
      return std::errc::permission_denied;
    case address_family_not_supported:
      return std::errc::address_family_not_supported;
    case address_in_use:
      return std::errc::address_in_use;
    case already_connected:
      return std::errc::already_connected;
    case already_started:
      return std::errc::connection_already_in_progress;
    case broken_pipe:
      return std::errc::broken_pipe;
    case connection_aborted:
      return std::errc::connection_aborted;
    case connection_refused:
      return std::errc::connection_refused;
    case connection_reset:
      return std::errc::connection_reset;
    case bad_descriptor:
      return std::errc::bad_file_descriptor;
    case fault:
      return std::errc::bad_address;
    case host_unreachable:
      return std::errc::host_unreachable;
    case in_progress:
      return std::errc::operation_in_progress;
    case interrupted:
      return std::errc::interrupted;
    case invalid_argument:
      return std::errc::invalid_argument;
    case message_size:
      return std::errc::message_size;
    case name_too_long:
      return std::errc::filename_too_long;
    case network_down:
      return std::errc::network_down;
    case network_reset:
      return std::errc::network_reset;
    case network_unreachable:
      return std::errc::network_unreachable;
    case no_descriptors:
      return std::errc::too_many_files_open;
    case no_buffer_space:
      return std::errc::no_buffer_space;
    case no_memory:
      return std::errc::not_enough_memory;
    case no_permission:
      return std::errc::operation_not_permitted;
    case no_protocol_option:
      return std::errc::no_protocol_option;
    case no_such_device:
      return std::errc::no_such_device;
    case not_connected:
      return std::errc::not_connected;
    case not_socket:
      return std::errc::not_a_socket;
    case operation_aborted:
      return std::errc::operation_canceled;
    case operation_not_supported:
      return std::errc::operation_not_supported;
    case shut_down:
      return std::error_condition(ev, asio::system_category());
    case timed_out:
      return std::errc::timed_out;
    case try_again:
      return std::errc::resource_unavailable_try_again;
    default:
      if (ev == would_block)
        return std::errc::operation_would_block;
      return std::error_condition(ev, asio::system_category());
    }
  }
  } // namespace detail


} // namespace error

namespace error
{

inline std::error_code make_error_code(basic_errors e) {
  return std::error_code(static_cast<int>(e), get_system_category());
}

} // namespace error

} // namespace asio

namespace std
{

template<> struct is_error_code_enum<asio::error::basic_errors> {
  static const bool value = true;
};

} // namespace std