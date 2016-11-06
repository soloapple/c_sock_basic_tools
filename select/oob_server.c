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


#define MYPORT 4000
#define BACKLOG 10
int new_fd = -1;
void sig_urg(int signo);

int main()
{
	int sockfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	int n ;
	char buff[100] ;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	if (bind(sockfd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

	signal(SIGURG, sig_urg);
	if(fcntl(sockfd, F_SETOWN, getpid())==-1)
	{
		perror("fcntl");
		exit(1);
	}

	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{
			perror("accept");
			continue;
		}
		fcntl(new_fd,F_SETOWN,getpid());
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		//if (!fork())
		if (1)
		{
			while(1)
			{
				if((n=recv(new_fd,buff,sizeof(buff)-1,0)) == 0)
				{
					printf("received EOF\n");
					break;
				}
				buff[n] ='\0';
				printf("Recv %d bytes: %s\n", n, buff);
			}
		}
		close(new_fd);
	}
	while(waitpid(-1,NULL,WNOHANG) > 0);

	return 0;
}

void sig_urg(int signo)
{
	int n;
	char buff[100];
	printf("SIGURG received\n");
	//printf("in sig_urg(),new_fd = %d\n",new_fd);
	//while((n = recv(new_fd,buff,sizeof(buff)-1,MSG_OOB)) == -1);
	n = recv(new_fd,buff,sizeof(buff)-1,MSG_OOB);
	if(n>0)
	{
		buff[n]='\0';
		printf("recv %d OOB byte: %s\n",n,buff);
	}
	else
	{
		perror("recv");
	}

}
