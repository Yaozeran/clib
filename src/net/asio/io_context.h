#pragma once

#include <chrono>

#include "execution_context.h"

namespace detail
{
typedef schedular io_context_impl;
} /* namespace detail */

struct io_context_bits {
  static constexpr uintptr_t blocking_never = 1;
  static constexpr uintptr_t relationship_continuation = 2;
  static constexpr uintptr_t outstanding_work_tracked = 3;
  static constexpr uintptr_t runtime_bits = 4;
};

class io_context : public execution_context
{
  typedef std::size_t count_type;
 public:

  template<typename Allocator, uintptr_t Bits>
  class basic_executor_type;
  template<typename Allocator, uintptr_t Bits>
  friend class basic_executor_type;
  typedef basic_executor_type<std::allocator<void>, 0> executor_type;

  class service;
  class strand;

  inline io_context() {

  }
  explicit inline io_context(int concurrency_hint) {

  }
  explicit io_context(const execution_context::service_maker& initial_services) {

  }
  template<typename Allocator>
  io_context(std::allocator_arg_t, const Allocator& a) {

  }
  template<typename Allocator>
  io_context(std::allocator_arg_t, const Allocator& a, int concurrency_hint) {

  }
  template<typename Allocator>
  io_context(std::allocator_arg_t, const Allocator& a, const service_maker& initial_services) {

  }

  inline ~io_context();

  executor_type get_executor() noexcept {

  }

  inline count_type run() {

  }

  template<typename Rep, typename Period>
  std::size_t run_for(const std::chrono::duration<Rep, Period>& rel_time) {

  }

  template<typename Clock, typename Duration>
  std::size_t run_until(const std::chrono::time_point<Clock, Duration>& abs_time) {

  }

  inline count_type run_one() {

  }

  template<typename Rep, typename Period>
  std::size_t run_one_for(const std::chrono::duration<Rep, Period>& rel_time) {

  }

  template<typename Clock, typename Duration>
  std::size_t run_one_until(const std::chrono::time_point<Clock, Duration>& abs_time) {

  }

  inline count_type poll();

  inline count_type poll_one();

  inline void stop() {

  }

  inline bool stopped() const { return; }

  inline void restart() {

  }

 private:
  io_context(const io_context&) = delete;
  io_context& operator=(const io_context&) = delete;

  template<typename Service>
  friend Service& use_service(io_context& ioc);

  impl_type& impl_;
};

template<typename Func, typename ExecutionContext>
inline void post(Func func, ExecutionContext ctx)
{
  
}

template<typename Func, typename ExecutionContext>
inline void write(Func func, ExecutionContext ctx)
{

}