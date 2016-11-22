/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: epoll.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   11/22/16 04:50:09
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/22/16                  build this moudle  
 *****************************************************************************/
#include "headers.h"

void 
addfd(int epollfd, int fd, bool enable_et)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN|EPOLLERR;
	if (enable_et)
	{
		event.events |= EPOLLET;
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	s_set_nonblock(fd);
}

void 
del_sock(int epollfd, int fd)
{
	close(fd);
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}

void 
s_process_epoll(char *ip, char *port)
{
	int s_sock;
	int epollfd;
	int number;
	int n_recv;
	int n_send;
	int i = 0;
	int n = 0;
	socklen_t s_len;

	struct sockaddr_in s_net_addr;
	char buf[8192];
	
	s_len = sizeof(struct sockaddr_in);
	s_sock = s_net_init(&s_net_addr, ip, port);
	
	if ( s_net_bind(s_sock, &s_net_addr) < 0 )
		return ;

	if ( s_net_listen(s_sock) < 0 )
		return;

	epoll_event events[MAX_EVENT_NUMBER];
	epollfd = epoll_create(5);
	if ( epollfd == -1 )
	{
		LOGE("create epoll fd failed\n");
		exit(0);
	}
	addfd(epollfd, s_sock, false);

	for ( ;; )
	{
		number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		{
			if ( number < 0 )
			{
				LOGE("epoll failed!\n");
				break;
			}
		}

		for ( i=0; i<number; i++ )
		{
			int sockfd = events[i].data.fd;
			if ( sockfd == s_sock )	
			{
				struct sockaddr_in conn_addr;
				int connfd = accept(s_sock, (struct sockaddr*)&conn_addr, &s_len);
				char addr_p[16];
				inet_ntop(AF_INET, &(conn_addr.sin_addr),
					addr_p, (socklen_t)sizeof(addr_p));
					LOGDP("Accept Client[%d] ip:%s Port:%d\n", 
					n++, addr_p, conn_addr.sin_port);

				addfd(epollfd, connfd, false);
			}
			else if ( events[i].events & EPOLLIN )
			{
				n_recv = s_net_recv_by_len(sockfd, buf);
				if ( n_recv > 0 ) 
				{
					n_send = s_net_send_by_len(sockfd, buf, n_recv);
					if (n_send < 0)
					{
						struct sockaddr_in sa; 
						socklen_t len;
						if(!getpeername(sockfd, (struct sockaddr *)&sa, &len))
						{   
							char cmd[1024];
							snprintf(cmd, 1024, "send data to ip: %s, port :%d failed!\n",
									inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
							LOGD("%s\n", cmd);
						}	
					
						del_sock(epollfd, sockfd);
						continue;
					}
				}

				if ( n_recv == 0 )
				{
					struct sockaddr_in sa;

					socklen_t len;
					if(!getpeername(sockfd, (struct sockaddr *)&sa, &len))
					{   
						char cmd[1024];
						snprintf(cmd, 1024, "client ip: %s, port :%d closed socket\n",
								inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
						LOGD("%s", cmd);
					}	

					del_sock(epollfd, sockfd);
					continue;
				}

				if ( n_recv < 0 )
				{
					if ( (errno == EAGAIN) 
							|| (errno == EWOULDBLOCK) 
							)
						continue;

					del_sock(epollfd, sockfd);
					continue;
				}
			}
			else if ( events[i].events & EPOLLERR )
			{
				del_sock(epollfd, sockfd);
				continue;
			}
		}
	}

	close(epollfd);
	return;
}
