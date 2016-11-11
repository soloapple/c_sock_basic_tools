/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: socket.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/18/16 19:32:42
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/18/16                  build this moudle
 ***************************************************************************************/


#ifndef  socket_INCLUDE
#define  socket_INCLUDE

#include "system.h"
#include "color_print.h"


char *s_net_ntoa(char *buf, size_t bufsize, struct in_addr a);
int s_inet_aton(char *buf, struct in_addr *a);
int s_net_init(struct sockaddr_in *s_net_addr, char *s_ip, char *s_port);
void s_net_set_tout(int s_sock);

int s_net_connect(int s_sock, struct sockaddr_in *s_net_addr);
int s_net_recv(int s_sock, char *r_buf, int len);
int s_net_send(int s_sock, char *s_buf, int len);
int s_net_listen(int s_sock);
int s_net_accept(int s_sock);
int s_net_bind(int s_sock, struct sockaddr_in *s_net_addr);
int s_net_send_by_len(int s_sock, char *t_buf, int len);
int s_net_recv_by_len(int s_sock, char *r_buf);

char *inet_ultoa(unsigned int u, char * s);
int inet_atoul(const char * s);
int noblock_accept(int fd, struct sockaddr_in* paddr, int addrlen, const int time_out);

#endif   /* ----- #ifndef socket_INC  ----- */















