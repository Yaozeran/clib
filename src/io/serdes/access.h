/* Copyright (c) 2026 Yao Zeran 
 * 
 * Implemented based on the lib cereal, refer to 
 *   https://github.com/USCiLab/cereal for more details */

#ifndef SERDES_ACCESS_H
#define SERDES_ACCESS_H

#include <type_traits>

namespace serdes
{

class access
{
public:
 
  /* This method will call the "serdes_method" defined in the target object class
   * */
  template<typename T, class cserdes>
  inline static auto 
  member_serdes_method(T& cls, cserdes &serdes) -> decltype(cls.serdes_method(serdes)) {
    return cls.serdes_method(serdes);
  }

};

} // namespace serdes

#endif // SERDES_ACCESS_H