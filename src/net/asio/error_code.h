#pragma once

#include <system_error>

inline std::error_condition error_number_to_condition(int ev) {

}

namespace detail
{
 
class system_category : public std::error_category
{
 public: 
  const char* name() const noexcept {
    return "asio.system";
  }
  std::string message(int value) const {

  }
 private:
  static const char* strerror_result(int, const char* s) { return s; }
  static const char* strerror_result(const char* s, const char*) { return s; }
};
 
} /* namespace detail */

extern inline const std::error_category& system_category() {
  static detail::system_category instance;
  return instance; 
}