#pragma once

#include <type_traits>

#include "io_context.h"

template<typename IoObjectService, typename Executor = io_context::executor_type>
class io_object_impl
{
  typedef IoObjectService service_type;
  typedef typename service_type::implementation_type implementation_type;
  typedef Executor executor_type;

  explicit io_object_impl(int, const executor_type& ex) : service_(), excutor_(ex) {

  }

  ~io_object_impl() {
    service_->destroy(implementation_);
  }

private:
  
  template<typename T>
  static execution_context& get_context(const T& t, std::enable_if_t<!execution::is_executor<T>::value>* = 0) {
    return t.context();
  }

  io_object_impl(const io_object_impl&) = delete;
  io_object_impl& operator=(const io_object_impl&) = delete;

  service_type* service_;
  implmentation_type* implementation_;
  executor_type* executor_;
};