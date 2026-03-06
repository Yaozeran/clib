#pragma once

#include "asio/config.h"
#if defined(ASIO_WINDOWS) || defined(__CYGWIN__)
# include <winerror.h>
#elif defined(ASIO_WINDOWS_RUNTIME)
# include <windows.h>
#else 
# include <cerrno>
# include <cstring>
# include <string>
#endif // defined(ASIO_WINDOWS) || defined(__CYGWIN__)
#include <system_error>

#include "asio/socket/socket_types.h"

namespace asio
{

typedef std::error_category error_category;
typedef std::error_code error_code;

namespace error
{
  
  namespace detail
  {
  inline std::error_condition error_number_to_condition(int ev);
  } // namespace detail

} // namespace error

  namespace detail
  {
  
  class system_category : public std::error_category
  {
  public: 

    const char* name() const noexcept {
      return "asio.system";
    }

    std::string message(int value) const {
#if defined(ASIO_WINDOWS_RUNTIME) || defined(ASIO_WINDOWS_APP)

#elif defined(ASIO_WINDOWS) || defined(__CYGWIN__)

#else

# if !defined(__sun)
      if (value == ECANCELED) {
        return "Operation aborted.";
      }
# endif // !defined(__sun)
# if defined(__sun) || defined(__QNX__) || defined(__SYMBIAN32__)
      using namespace std;
      return strerror(value);
# else 
      char buf[256] = "";
      using namespace std;
      return strerror_result(strerror_r(value, buf, sizeof(buf)), buf);
# endif

#endif // defined(ASIO_WINDOWS_RUNTIME) || defined(ASIO_WINDOWS_APP)
    }

    std::error_condition default_error_condition(int ev) const noexcept {
      return error::detail::error_number_to_condition(ev);
    }

  private:
    /* glibc's variant of strerror_r */
    static const char* strerror_result(int, const char* s) { return s; }
    /* posix version */
    static const char* strerror_result(const char* s, const char*) { return s; }
  };
  
  } // namespace detail

extern inline const std::error_category& system_category() {
  static detail::system_category instance;
  return instance; 
}

} // namespace asio