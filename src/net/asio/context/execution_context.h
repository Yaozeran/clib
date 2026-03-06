#pragma once

#include "asio/common.h"
#include "asio/memory.h"

namespace asio
{

class execution_context;
class io_context;

template<typename Service>
Service& use_service(execution_context&);

template<typename Service>
Service& use_service(io_context&);

template<typename Service>
void add_service(execution_context&, Service*);

  namespace detail
  {
  class service_registry;    
  } // namespace detail

class execution_context : private noncopyable
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

  inline execution_context() : execution_context(
    detail::allocate_object<allocator_impl<std::allocator<void>>>(std::allocator<void>(), std::allocator<void>()))) {
  }
  template<typename Allocator>
  execution_context(std::allocator_arg_t, const Allocator& alloc) {

  }
  explicit inline execution_context(const service_maker& initial_services) {

  }
  template<typename Allocator>
  execution_context(std::allocator_arg_t, const Allocator& a, const service_maker& initial_services) {

  }
  
protected:
  
  inline void shutdown();

  inline void destroy();

public:
  
  enum fork_event {
    fork_prepare, fork_parent, fork_child
  };
    
  inline void notify_fork(fork_event event);

private:
  
  class allocator_impl_base;

  template<typename Allocator> class allocator_impl;

  explicit inline execution_context(allocator_impl_base* alloc) {

  }
  
  inline execution_context(allocator_impl_base* alloc, const service_maker& initial_services) {

  }

  struct auto_allocator_ptr {
    allocator_impl_base* ptr_;
    ~auto_allocator_ptr();
  } allocator_;
  
  detail::service_registry* service_registry_;

}; // class execution_context

class execution_context::allocator_impl_base
{
public: 

  virtual void destory() = 0;

  virtual void* allocate(size_t size, size_t align) = 0;

  virtual void deallocate(void* ptr, size_t size, size_t align) = 0;

protected:

  virtual inline ~allocator_impl_base();

}; // class execution_context::allocator_impl_base

template<typename Allocator> 
class execution_context::allocator_impl : public execution_context::allocator_impl_base
{
public:

  allocator_impl(const Allocator& alloc) : allocator_(alloc) {}

  void destroy();

  void* allocate(size_t size, size_t align) {
    typename std::allocator_traits<Allocator>::template rebind_alloc<unsigned char> alloc(allocator_);
    std::size_t space = size + align - 1;
    unsigned char* base = std::allocator_traits<decltype(alloc)>::allocate(
      alloc, space + sizeof(std::ptrdiff_t);
    )
    void* p = base;
    if (detail::align(align, size, p, space)) {
      std::ptrdiff_t off = static_cast<unsigned char*>(p) - base;
    }
  }

  void deallocate(void* ptr, size_t size, size_t align) {
    
  }

private: 

  Allocator allocator_;

}; // template<typename Allocator> class execution_context::allocator_impl;


template<typename T>
class execution_context::allocator
{
  typedef T value_type;

public:

  template<typename U>
  struct rebind {
    typedef allocator<U> other;
  };

  explicit constexpr allocator(execution_context& e) noexcept : impl_(e.alloctor_.ptr_) { }

  template<typename U>
  constexpr allocator(const allocator<U>& a) noexcept : impl_(a.impl_) { }

  constexpr bool operator==(const allocator& other) const noexcept {
    return impl_ == other.impl_;
  }

  constexpr bool operator!=(const allocator& other) const noexcept {
    return impl_ != other.impl_;
  }

  T* allocate(std::size_t n) const {
    return static_cast<T*>(impl_->allocate(sizeof(T) * n, alignof(T)));
  }

  void deallocate(T* p, std::size_t n) const {
    impl_->deallocate(p, sizeof(T) * n, alignof(T));
  }

private:

  template<typename> 
  friend class execution_context::allocator;

  allocator_impl_base* impl_;

}; // class execution_context::allocator

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

  namespace detail
  {

  template<typename Type>
  class service_id : public execution_context::id
  {

  };

  template<typename Type>
  class execution_context_service_base : public execution_context::service
  {
  public:

    static service_id<Type> id;
  
    execution_context_service_base(execution_context& e) : execution_context::service(e) { }
  };

  template<typename Type>
  service_id<Type> execution_context_service_base<Type>::id;

  } // namespace detail


} // namespace asio