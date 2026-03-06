#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <poll.h>

typedef int socket_type;
const int invalid_socket = -1;
const int socket_error_retval = -1;
const int max_addr_v4_str_len = INET_ADDRSTRLEN;

#if defined(INET6_ADDRSTRLEN)
const int max_addr_v6_str_len = INET6_ADDRSTRLEN + 1 + IF_NAMESIZE;
#else 
const int max_addr_v6_str_len = 256;
#endif // defined(INET6_ADDRSTRLEN)

typedef sockaddr_in sockaddr_in4_type;
typedef in6_addr in6_addr_type;
typedef int ioctl_arg_type;
typedef ssize_t signed_size_type;
