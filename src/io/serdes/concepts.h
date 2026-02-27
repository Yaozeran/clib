/* Copyright (c) 2026 Yao Zeran 
 * 
 * Implemented based on the lib cereal, refer to 
 *   https://github.com/USCiLab/cereal for more details */

#ifndef SERDES_CONCEPTS_H
#define SERDES_CONCEPTS_H

#include <concepts>

#include "access.h"

namespace serdes
{

template<typename T, class cserdes>
concept has_member_serdes_method = requires(T& cls, cserdes& s) {
  serdes::access::member_serdes_method(cls, s);
};

template<typename T, class cserdes>
concept has_non_member_serdes_method = requires(T& obj, cserdes& s) {
  serdes_method(obj, s);
};

template<typename T, class cserdes>
concept has_non_member_serialize_method = requires(T& obj, cserdes& s) {
  serialize(obj, s);
};

template<typename T, class cserdes>
concept has_non_member_deserialize_method = requires(T& obj, cserdes& s) {
  deserialize(obj, s);
};

template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template<typename T, typename cser>
concept serializable_with = requires(const T& obj, cser& ser) {
  ser( obj );
};

template<typename T, typename cdes>
concept deserializable_with = requires(const T& obj, cdes& des) {
  des( obj );
};

} // namespace serdes

#endif // SERDES_CONCEPTS_H