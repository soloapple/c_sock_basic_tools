/***************************************************************************************
 *   Copyright (C), 2006-2015, Legendsec Technology Co., Ltd.
 *
 *    Filename: epoll_send_https.c
 * Description: 
 *     Version: 1.0
 *     Created: solo-apple   07/17/15 22:17:17
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              solo-apple   07/17/15                  build this moudle  
 ***************************************************************************************/

#include "syshead.h"


#include <stdio.h>   
#include <sys/types.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <arpa/inet.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>

#define BUFFER_SIZE 4096
#define MAX_EVENTS 50000
//#define SOCKET_NUM 1000
#define SOCKET_NUM 2


char sendbuf[] = "POST /sqltest/selServlet HTTP/1.1\r\nHost: 10.60.159.4\r\nConnection: keep-alive\r\nContent-Length: 10\r\nAccept: */*\r\nOrigin: http://10.60.159.4\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36\r\nContent-Type: application/x-www-form-urlencoded; charset=UTF-8\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: zh-CN,zh;q=0.8\r\nCookie: JSESSIONID=CB73BE891B3C27B1390652D4E25641D4\r\n\r\nusername=a";  

int main(int argc, char * argv[])   
{
	if (argc <= 2)
	{
		printf("usage: %s ip port\n", basename(argv[0]));
		return 1;
	}
	//const char *ip = "10.60.159.4";
	//int port = 80;
	const char* ip = argv[1];
	int port = atoi(argv[2]);

    int sockfd[SOCKET_NUM];
    int len;   
    struct sockaddr_in my_addr;   
    struct sockaddr_in server_address;
    int sin_size;   

	char recvbuf[BUFFER_SIZE];
	bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;         // host byte order
	inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);     // short, network byte order
	
	printf("%s\n", sendbuf);

	int epoll_fd;
	epoll_fd=epoll_create(MAX_EVENTS);
	if(epoll_fd==-1)
	{
		perror("epoll_create failed");
		exit(EXIT_FAILURE);
	}

puts("-----------1");

	struct timeval start, end;
	gettimeofday( &start, NULL );
	
	int flags = 0;
	int j; 
	for(j=0; j<SOCKET_NUM; j++)
	{
		if ((sockfd[j]=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)   
		{     
			perror("socket");   
			return 1;   
		}   

		flags = fcntl(socket[j], F_GETFL, 0);
		fcntl(socket[j], F_SETFL, flags|O_NONBLOCK);
//puts("-----------2");

puts("-----------3");
char IPdotdec[20];
inet_ntop(AF_INET, (void *)&server_address.sin_addr.s_addr, IPdotdec, 16);
printf("%s %d\n", IPdotdec, ntohs(server_address.sin_port));

		if (connect(sockfd[j], (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
		{
			printf("connection failed, errno: %d, j: %d\n", errno, j);
			perror("connection failed");
			close(sockfd[j]);	

			return 1;
		}	

		struct epoll_event ev;
		ev.events=EPOLLIN;
		ev.data.fd = sockfd[j];
		
		if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd[j], &ev)==-1)
		{
			perror("epll_ctl:server_sockfd register failed");
			exit(EXIT_FAILURE);
		}

		len = send(sockfd[j], sendbuf, sizeof(sendbuf)-1,0);
		printf("j: %d, nsend: %d\n", j, len);
	}

	printf("j: %d\n", j);

   	struct epoll_event events[MAX_EVENTS];
	int nfds;
	int counts = 0;
	printf("receiving......\n");
    while(counts < 1000)
	{
		nfds=epoll_wait(epoll_fd,events,MAX_EVENTS,-1);
		printf("nfds: %d\n", nfds);
		if(nfds==-1)
		{
			perror("start epoll_wait failed");
			exit(EXIT_FAILURE);
		}
		int i;
		for(i=0;i<nfds;i++)
		{
			if (events[i].events & EPOLLIN)
			{
				len=recv(events[i].data.fd, recvbuf, BUFFER_SIZE, 0);
				if(len<0)
				{
					perror("receive from client failed");
					exit(EXIT_FAILURE);
				}

				printf("receive from client %d:%s\n",events[i].data.fd, recvbuf);
				counts++;
			}
			else
			{

			}
		}
	}
	
	gettimeofday( &end, NULL );
	int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
	printf("time: %d us\n", timeuse);


	return 0;   
}  
