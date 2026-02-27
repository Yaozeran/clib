/* Copyright (c) 2026 Yao Zeran 
 * 
 * Implemented based on the lib cereal, refer to 
 *   https://github.com/USCiLab/cereal for more details */
 
#ifndef SERDES_SERDES_OPS_H
#define SERDES_SERDES_OPS_H

#include <cstdlib>
#include <utility>
#include <cstdint>

#include <array>
#include <string>

#include "concepts.h"
#include "serializer.h"
#include "deserializer.h"

namespace serdes
{

template<typename T>
struct binary_data {
  
  typedef T data_type;

  /* cannot implicitly convert const ptr to void* , use pt */
  using storage_type = std::conditional_t<
    std::is_const_v<std::remove_pointer_t<std::remove_reference_t<T>>>,
    const void*, void*>;
  
  storage_type data_;
  uint64_t size_;

  binary_data(data_type&& d, uint64_t s) : data_(std::forward<data_type>(d)), size_(s) {}

}; // struct binary_data

template<class T>
inline binary_data<T> make_binary_data(T&& data, size_t size) {
  return {std::forward<T>(data), size};
}

template<typename T>
struct size_tag {

  typedef T size_type;
  using storage_type = std::conditional_t<std::is_lvalue_reference_v<T>, T, std::decay_t<T>>;

  storage_type size_;

  size_tag(size_type&& sz) : size_(std::forward<size_type>(sz)) {}

  size_tag& operator=(const size_tag&) = delete;

}; // struct size_tag

template<class T>
inline size_tag<T> make_size_tag(T sz) {
  return {std::forward<T>(sz)};
}

/* arithmetic type */

template<arithmetic T>
inline void serialize(const T& v, byte_serializer& ser) {
  ser.write(std::addressof(v), sizeof(v));
}

template<arithmetic T>
inline void deserialize(T& v, byte_deserializer& des) {
  des.read(std::addressof(v), sizeof(v));
}

/* binary data type */

template<typename T>
void serialize(const binary_data<T>& bd, byte_serializer& ser) {
  ser.write(bd.data_, static_cast<std::streamsize>(bd.size_));
}

template<typename T>
void deserialize(binary_data<T>& bd, byte_deserializer& des) {
  des.read(bd.data_, static_cast<std::streamsize>(bd.size_));
}

/* size tag type */

template<typename T>
void serialize(const size_tag<T>& tag, byte_serializer& ser) {
  ser(tag.size_);
}

template<typename T>
void deserialize(size_tag<T>& tag, byte_deserializer& des) {
  des(tag.size_);
}

/* array type */

template<typename T, size_t len, class serializer>
requires serializable_with<binary_data<const T*>, serializer>
inline void serialize(const std::array<T, len> &arr, serializer &ser) {
  ser( make_binary_data(arr.data(), len * sizeof(T)) );
}

template<typename T, size_t len, class deserializer>
requires deserializable_with<binary_data<T>, deserializer>
inline void deserialize(std::array<T, len> &arr, deserializer &des) {
  des( make_binary_data(arr.data(), len * sizeof(T)) );
}

/* string types */

template<class char_t, class traits, class alloc, class serializer>
requires serializable_with<binary_data<const char_t*>, serializer>
inline void serialize(const std::basic_string<char_t, traits, alloc> &str, serializer &ser) {
  ser( make_size_tag(str.size()) );
  ser( make_binary_data(str.data(), str.size() * sizeof(char_t)) );
}

template<class char_t, class traits, class alloc, class deserializer>
requires deserializable_with<binary_data<char_t*>, deserializer>
inline void deserialize(std::basic_string<char_t, traits, alloc> &str, deserializer &des) {
  size_t sz;
  size_tag<size_t> tag = make_size_tag(sz);
  des( tag );
  str.resize(tag.size_);
  des( make_binary_data(const_cast<char_t*>(str.data()), str.size() * sizeof(char_t)) );
}

} // namespace serdes

#endif // SERDES_SERDES_OPS_H