/* Copyright (c) 2026 Yao Zeran 
 * 
 * Implemented based on the lib cereal, refer to 
 *   https://github.com/USCiLab/cereal for more details */
 
#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <iostream>

#include "access.h"
#include "concepts.h"

namespace serdes
{

/* Base class: read a serialized stream into an obj.
 * */
template<class deserializer_impl>
class deserializer_base
{
public:

  deserializer_base(deserializer_impl* const derived) : self_(derived) {}
  
  template<typename... Ts> 
  inline deserializer_base& operator() (Ts&& ... objs) {
    self_->process(std::forward<Ts>(objs)...);
    return *self_;
  }

private:

  deserializer_impl* self_;

  template<typename F, typename... Ts>
  inline void process(F&& first, Ts&&... others) {
    self_->process(std::forward<F>(first));
    self_->process(std::forward<Ts>(others)...);
  }
  
  template<typename T>
  inline void process(T&& obj) {
    self_->process_impl(obj);
  }

  template<typename T> 
  requires has_member_serdes_method<T, decltype(*self_)> 
  deserializer_impl& process_impl(T& obj) {
    access::member_serdes_method(obj, *self_);
    return *self_;
  }

  template<typename T>
  requires has_non_member_serdes_method<T, decltype(*self_)> 
  deserializer_impl& process_impl(T& obj) {
    serdes_method(obj, *self_);
    return *self_;
  }

  template<typename T>
  requires has_non_member_deserialize_method<T, decltype(*self_)> 
  deserializer_impl& process_impl(T& obj) {
    deserialize(obj, *self_);
    return *self_;
  }

};

class byte_deserializer : public deserializer_base<byte_deserializer>
{
public:
  
  byte_deserializer(std::istream &s) : deserializer_base<byte_deserializer>(this), stream_(s) {}
  
  ~byte_deserializer() noexcept = default;

  void read(void* data, std::streamsize size) {
    auto const read_size = stream_.rdbuf()->sgetn(reinterpret_cast<char*>(data),size);
    if(read_size != size) { 
      std::cout << "failed to read " + std::to_string(size) + " bytes from input stream! read " 
        << std::to_string(read_size) << std::endl;
    }
  }

private:

  std::istream& stream_;

}; // class byte_deserializer

} // namespace serdes

#endif // DESERIALIZER_H