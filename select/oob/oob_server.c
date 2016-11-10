/***************************************************************************************
 *   Copyright (C), 2006-2015, Legendsec Technology Co., Ltd.
 *
 *    Filename: oob_server.c
 * Description: 
 *     Version: 1.0
 *     Created: Liujfa   06/18/15 03:46:02
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              Liujfa   06/18/15                  build this moudle  
 ***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "../include/color_print.h"

#define MYPORT 4000
#define BACKLOG 10

int new_fd = -1;
void sig_urg(int signo);

void
show_socket_listen_info(char **ip, int port)
{
	LOGN("+--------------------------------------+\n");
	LOGN("+ FUNCTION:    %-24s+\n", "oob data recv");
	LOGN("+ Listen IP:   %-24s+\n", *ip);
	LOGN("+ Listen Port: %-24d+\n", port);
	LOGN("+--------------------------------------+\n");
}

int main()
{
	int sockfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	int n ;
	char buff[100];
	char *ip = NULL;
	char *s_ip = (char*)malloc(16);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		LOGE("Create Socket failed");
		exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);

	inet_ntop(AF_INET, &(my_addr.sin_addr), s_ip, (socklen_t)sizeof(s_ip));

	show_socket_listen_info(&s_ip, htons(my_addr.sin_port));

	if (bind(sockfd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
	{
		LOGE("Bind Socket Error");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1)
	{
		LOGE("Listen Socket Error");
		exit(1);
	}

	signal(SIGURG, sig_urg);
	if(fcntl(sockfd, F_SETOWN, getpid())==-1)
	{
		LOGE("Fcntl Socket Error");
		exit(1);
	}
	
	sin_size = sizeof(struct sockaddr_in);

	while(1)
	{
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{
			perror("accept");
			continue;
		}

		fcntl(new_fd,F_SETOWN,getpid());

		char client_ip[16] = {0};
		inet_ntop(AF_INET, &their_addr.sin_addr, client_ip, (socklen_t)sizeof(client_ip));
		LOGW("client _ip:%s\n", client_ip );	

		for (;;)
		{
			if ( (n = recv(new_fd, buff, sizeof(buff)-1, 0)) == 0 )
			{
				LOGE("received EOF\n");
				break;
			}

			buff[n] ='\0';
			LOGDP("Recv %d bytes: %s\n", n, buff);
		}

		close(new_fd);

	}

	while(waitpid(-1,NULL,WNOHANG) > 0);

	free(s_ip);

	return 0;
}

void sig_urg(int signo)
{
	int n;
	char buff[100];
	LOGDP("SIGURG received\n");

	n = recv(new_fd, buff, sizeof(buff)-1, MSG_OOB);
	if(n>0)
	{
		buff[n]='\0';
		LOGDP("Recv %d OOB byte: %s\n",n,buff);
	}
	else
	{
		LOGE("Recv OOB");
	}
}
