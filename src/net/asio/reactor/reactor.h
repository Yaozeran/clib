#pragma once

#include "config.h"

#if defined(HAS_IOCP) || defined(WINDOWS_RUNTIME)
# include "null_reactor.h"
#elif defined(HAS_IO_URING_AS_DEFAULT)
# include "null_reactor.h"
#elif defined(HAS_EPOLL)
# include "epoll_reactor.h"
#elif defined(HAS_KQUEUE)
# include "reactor/kqueue_reactor.h"
typedef kqueue_reactor reactor;
#elif defined(HAS_DEV_POLL)
# include "dev_poll_reactor.h"
#else
# include "select_reactor.h"
#endif