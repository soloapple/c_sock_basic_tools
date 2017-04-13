#ifndef COMMON_H
#define COMMON_H

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <netinet/tcp.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

#define MEM_REPLACE(pstr, len, src, dst) do { \
	memreplace(pstr, len, src, strlen(src), dst, strlen(dst)); \
} while (0)

/* error output */
void  err_sys(const char *fmt, ...);
void  err_msg(const char *fmt, ...);
void  err_debug(const char *fmt, ...);

/* daemon */
int   daemon_init(const char *pname, int level);

/* sys app */
int   setlimit();
int   x_getpid(const char *pid, char *argv[]);
int   x_writepid(const char *pid);
int   x_rvpid(const char *pid);
int   Pthread_create(pthread_t *td, const pthread_attr_t *attr,
		void *(*start)(void *), void *arg);
void  *Calloc(int nsize, int size);

/* common tool */
int   memreplace(char **pstr, int *len, char *src, int nsrc, 
		char *dst, int ndst);
int   memreplace_one(char **pstr, int *len, char *src, int nsrc,
		char *dst, int ndst);
void  putbuf(unsigned char *buf, int len);
int   replacekey(char **buffer, int *buflen, char *srckey, char *srcvalue,
		char *dstkey, char *dstvalue);

/* network operating */
int   is_ip_valid(const char *ipstr);
int   is_port_use(u16 port);
u32   ip_aton(char *sip);
char *ip_ntoa(u32 sip, char *rvip);

int   Select(int nfds, fd_set *rfds, fd_set *wfds, fd_set *efds,
		struct timeval *tout);
int   setsockattr_u(int s);
int   setsockattr_t(int s);
int   Setsockopt(int sock, int level, int optname);
int   Bind(int sockfd, struct sockaddr *addr, int socklen);
int   Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
int   Connect(int s, struct sockaddr *addr, socklen_t addrlen);
int   sendn(int s, const void *buf, size_t len);
void  init_sockaddr(struct sockaddr_in *sockaddr, u32 ip, u16 port);
int   setnonblock(int sockfd);
int   Recv(int s, void *buf, size_t len, int flags);
int   Recvfrom(int s, void *buf, size_t len, int flags,
		struct sockaddr *from, socklen_t *fromlen);
int   Sendto(int s, const void *buf, size_t len, int flags,
		const struct sockaddr *to, socklen_t tolen);

u16   getsockport(int sockfd);
u16   getpeerport(int sockfd);
u32   getsockip(int sockfd);
u32   getpeerip(int sockfd);

/* use port pool */
int   pp_init(u16 initport, u16 total);
void  pp_destroy();
u16   pp_getidle_rand();
u16   pp_getidle_odd();
u16   pp_getidle_even();
void  pp_setidle(const u16 port);

/* ip pool */
void  ipp_init();
void  ipp_destroy();
int   ipp_add(u32 ip);
u32   ipp_getidle();
void  ipp_setidle(u32 ip);

/* argument parsing */
void  ferry_usage(char *argv[]);
void  ferry_parse_arg(int argc, char *argv[]);

#endif // ~COMMON_H
