#pragma once

#include "src/net/common.h"
#include "src/net/memory.h"

class service_registry;

class execution_context
{
 public: 

  template<typename T> class allocator;
  class id : private noncopyable
  {
   public: 
    id() {}
  };
  class service;
  class service_maker;

 public:

  inline execution_context()
  {

  }
  template<typename Allocator>
  execution_context(std::allocator_arg_t, const Allocator& alloc)
  {

  }
  explicit inline execution_context(const service_maker& initial_services)
  {

  }
  template<typename Allocator>
  execution_context(std::allocator_arg_t, const Allocator& a, 
      const service_maker& initial_services)
  {

  }
  
 protected:
  
  inline void shutdown();

  inline void destroy();

 public:
  
  enum fork_event
  {
    fork_prepare, fork_parent, fork_child
  };
    
  inline void notify_fork(fork_event event);

 private:
  
  class allocator_impl_base
  {
   public: 
    virtual void destory() = 0;
    virtual void* allocate(size_t size, size_t align) = 0;
    virtual void deallocate(void* ptr, size_t size, size_t align) = 0;
   protected:
    virtual inline ~allocator_impl_base();
  };
  template<typename Allocator> class allocator_impl;

  explicit inline execution_context(allocator_impl_base* alloc);
  inline execution_context(allocator_impl_base* alloc, 
      const service_maker& initial_services)
  {

  }

  struct auto_allocator_ptr
  {
    allocator_impl_base* ptr_;
    ~auto_allocator_ptr();
  } allocator_;
  
  service_registry* service_registry_;
};

template<typename T>
class execution_context::allocator
{
  typedef T value_type;

 public:

  template<typename U>
  struct rebind
  {
    typedef allocator<U> other;
  };

  explicit constexpr allocator(execution_context& e) noexcept
      : impl_(e.alloctor_.ptr_)
  {
  }

};

class execution_context::service : private noncopyable
{
 public:
  execution_context& context();
 protected: 
  inline service(execution_context& owner);
  virtual inline ~service();
 private:
  virtual void shutdown() = 0;
  virtual inline void nofity_fork(execution_context::fork_event event);
};

class service_already_exists : public std::logic_error
{
 public:
  inline service_already_exists();
};

class invalid_service_owner : public std::logic_error
{
 public:
  inline invalid_service_owner();
};

template<typename 