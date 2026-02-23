#pragma once

#include <cstddef>
#include <memory>

inline void* align(size_t alignment, size_t size, void*& ptr, size_t& space) 
{
  return std::align(alignment, size, ptr, space);
}

template<typename T, typename Alloc, typename... Args>
T* allocate_obj(const Alloc& a, Args&&... args)
{
  typename std::allocator_traits<Alloc>::template rebind_alloc<T> alloc(a);
  T* raw = std::allocator_traits<decltype(alloc)>::allocate(alloc, 1);
#if !defined(NO_EXCEPTIONS)
  try
#endif 
  {
    return new (raw) T(static_cast<Args&&>(args)...);
  }
#if !defined(NO_EXCEPTIONS)
  catch(...)
  {
    std::allocator_traits<decltype(alloc)>::deallocate(alloc, raw, 1);
    throw;
  }
#endif
}

template<typename Alloc, typename T>
T* deallocate_obj(const Alloc& a, T* ptr)
{
  typename std::allocator_traits<Alloc>::template rebind_alloc(T) alloc(a);
  std::allocator_traits<decltype(alloc)>::destroy(alloc, ptr);
  std::allocator_traits<decltype(alloc)>::deallocate(alloc, ptr, 1); 
}

