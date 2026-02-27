/* Copyright (c) 2026 Yao Zeran 
 * 
 * Implemented based on the lib cereal, refer to 
 *   https://github.com/USCiLab/cereal for more details */

#ifndef SERDES_SERIALIZER_H
#define SERDES_SERIALIZER_H

#include <sstream>
#include <iostream>

#include "access.h"
#include "concepts.h"

namespace serdes
{

/* Base class: serialize an object into an output stream. 
 * */
template<class serializer_impl>
class serializer_base
{
public:
  
  serializer_base(serializer_impl* const derived) : self_(derived) {}
  
  template<typename... Ts> 
  inline serializer_base& operator() (Ts&&... objs) {
    self_->process(std::forward<Ts>(objs)...);
    return *self_;
  }

private:

  serializer_impl* self_;

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
  serializer_impl& process_impl(const T& obj) {
    access::member_serdes_method(const_cast<T&>(obj), *self_);
    return *self_;
  }

  template<typename T>
  requires has_non_member_serdes_method<T, decltype(*self_)> 
  serializer_impl& process_impl(const T& obj) {
    serdes_method(const_cast<T&>(obj), *self_);
    return *self_;
  }

  template<typename T>
  requires has_non_member_serialize_method<T, decltype(*self_)>
  serializer_impl& process_impl(const T& obj) {
    serialize(const_cast<T&>(obj), *self_);
    return *self_;
  }
};

/* A serializer to produce a byte stream from an object 
 * */
class byte_serializer : public serializer_base<byte_serializer>
{
public: 

  byte_serializer(std::ostream &s) : serializer_base<byte_serializer>(this), stream_(s) {}

  ~byte_serializer() noexcept = default;

  void write(const void* data, std::streamsize size) {
    auto const written_size = stream_.rdbuf()->sputn(reinterpret_cast<const char*>(data), size);
    if(written_size != size) {/* todo */};
  }

private:

  std::ostream& stream_;

}; // class byte_serializer

} // namespace cser

#endif // SERIALIZER_H