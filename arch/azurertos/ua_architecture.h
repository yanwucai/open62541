/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 */

#ifdef UA_ARCHITECTURE_AZURERTOS

#ifndef PLUGINS_ARCH_AZURERTOS_UA_ARCHITECTURE_H_
#define PLUGINS_ARCH_AZURERTOS_UA_ARCHITECTURE_H_


#include <open62541/architecture_definitions.h>


#include "nxd_bsd.h"
#include <string.h>

/* typedef INT ssize_t; */

#define OPTVAL_TYPE int
#ifdef UA_sleep_ms
void UA_sleep_ms(unsigned long ms);
#else
# define UA_sleep_ms(X) tx_thread_sleep((X) * NX_IP_PERIODIC_RATE / 1000)
#endif

#define UA_access(x,y) 0

#define UA_IPV6 0
#define UA_SOCKET INT
#define UA_INVALID_SOCKET NX_SOC_ERROR
#define UA_ERRNO nx_bsd_errno
#define UA_INTERRUPTED EINTR
#define UA_AGAIN EAGAIN
#define UA_INPROGRESS EINPROGRESS
#define UA_WOULDBLOCK EWOULDBLOCK
#define UA_ERR_CONNECTION_PROGRESS EINPROGRESS
#define UA_EAGAIN EAGAIN
#define UA_POLLIN POLLIN
#define UA_POLLOUT POLLOUT

#define UA_fd_set NX_BSD_FD_SET
#define UA_fd_isset NX_BSD_FD_ISSET



#define UA_getnameinfo(sa, salen, host, hostlen, serv, servlen, flags) \
    nx_bsd_getnameinfo(sa, (socklen_t)salen, host, (size_t)hostlen, serv, (size_t)servlen, flags)
#define UA_poll nx_bsd_poll
#define UA_send(sockfd, buf, len, flags) nx_bsd_send(sockfd, buf, (INT)(len), flags)
#define UA_recv(sockfd, buf, len, flags) nx_bsd_recv(sockfd, buf, (INT)(len), flags)
#define UA_sendto(sockfd, buf, len, flags, dest_addr, addrlen) nx_bsd_sendto(sockfd, (char*)(buf), (int)(len), flags, dest_addr, (int) (addrlen))
#define UA_recvfrom(sockfd, buf, len, flags, src_addr, addrlen) nx_bsd_recvfrom(sockfd, (char*)(buf), (int)(len), flags, src_addr, addrlen)
#define UA_recvmsg nx_bsd_recvmsg
#define UA_htonl htonl
#define UA_ntohl ntohl
#define UA_close nx_bsd_soc_close
#define UA_select(nfds, readfds, writefds, exceptfds, timeout) nx_bsd_select((INT)(nfds), readfds, writefds, exceptfds, timeout)
#define UA_shutdown(a, b)
#define UA_socket nx_bsd_socket
#define UA_bind(sock, addr, len) nx_bsd_bind(sock, addr, (INT)(len))
#define UA_listen(sockID, backlog) nx_bsd_listen(sockID, 5)
#define UA_accept(sock, addr, len) nx_bsd_accept(sock, addr, (INT *)(len))
#define UA_connect(sockfd, addr, addrlen) nx_bsd_connect(sockfd, addr, (INT)(addrlen))
#define UA_getaddrinfo nx_bsd_getaddrinfo
#define UA_getsockopt(sock, level, name, val, len) nx_bsd_getsockopt(sock, level, name, val, (INT *)(len))
#define UA_setsockopt nx_bsd_setsockopt
#define UA_ioctl(sock, cmd, res) nx_bsd_ioctl(sock, cmd, (INT *)(res))
#define UA_freeaddrinfo nx_bsd_freeaddrinfo
#define UA_getsockname(sock, addr, len) nx_bsd_getsockname(sock, addr, (INT *)(len))
#define UA_inet_pton nx_bsd_inet_pton

#if UA_IPV6
# define UA_if_nametoindex
#endif

/* Use the standard malloc */
#ifndef UA_free
# define UA_free free
# define UA_malloc malloc
# define UA_calloc calloc
# define UA_realloc realloc
#endif


#define UA_snprintf snprintf
#define UA_strncasecmp strncasecmp

#define UA_LOG_SOCKET_ERRNO_WRAP(LOG) { \
    char *errno_str = ""; \
    LOG; \
}

#define UA_LOG_SOCKET_ERRNO_GAI_WRAP UA_LOG_SOCKET_ERRNO_WRAP

#if UA_MULTITHREADING >= 100

typedef struct {
    TX_MUTEX mutex;
    int mutexCounter;
} UA_Lock;

static UA_INLINE void
UA_LOCK_INIT(UA_Lock *lock) {
    tx_mutex_create(&lock->mutex, "UA_Lock", TX_NO_INHERIT);
    lock->mutexCounter = 0;
}

static UA_INLINE void
UA_LOCK_DESTROY(UA_Lock *lock) {
    tx_mutex_delete(&lock->mutex);
}

static UA_INLINE void
UA_LOCK(UA_Lock *lock) {
    tx_mutex_get(&lock->mutex, TX_WAIT_FOREVER);
    UA_assert(++(lock->mutexCounter) == 1);
}

static UA_INLINE void
UA_UNLOCK(UA_Lock *lock) {
    UA_assert(--(lock->mutexCounter) == 0);
    tx_mutex_put(&lock->mutex);
}

static UA_INLINE void
UA_LOCK_ASSERT(UA_Lock *lock, int num) {
    UA_assert(lock->mutexCounter == num);
}
#else
#define UA_LOCK_INIT(lock)
#define UA_LOCK_DESTROY(lock)
#define UA_LOCK(lock)
#define UA_UNLOCK(lock)
#define UA_LOCK_ASSERT(lock, num)
#endif


#ifdef NX_BSD_ENABLE_NATIVE_API

#define errno nx_bsd_errno
#define timeval nx_bsd_timeval
#define pollfd nx_bsd_pollfd
#define fd_set nx_bsd_fd_set
#define sockaddr nx_bsd_sockaddr
#define sockaddr_storage nx_bsd_sockaddr_storage
#define socklen_t nx_bsd_socklen_t
#define sockaddr_in nx_bsd_sockaddr_in
#define addrinfo nx_bsd_addrinfo
#define sockaddr_ll nx_bsd_sockaddr_ll

#define in_addr nx_bsd_in_addr
#define ip_mreq nx_bsd_ip_mreq
#define in6_addr nx_bsd_in6_addr
#define packet_mreq nx_bsd_packet_mreq
#define ether_header nx_bsd_ether_header
#define iovec nx_bsd_iovec
#define msghdr nx_bsd_msghdr
#define ifreq nx_bsd_ifreq

#undef FD_ZERO
#define FD_ZERO NX_BSD_FD_ZERO

#endif


#include <open62541/architecture_functions.h>



#endif /* PLUGINS_ARCH_AZURERTOS_UA_ARCHITECTURE_H_ */

#endif /* UA_ARCHITECTURE_AZURERTOS */
