/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: stand_tcp_server.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2016年12月27日 09时29分14秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2016年12月27日                  build this moudle  
 *****************************************************************************/
#include "syshead.h"
 #define _XOPEN_SOURCE 600

#define PORT "4242"
#define NUM_CHILDREN 3
#define MAXLEN 1024

int readline(int fd, char *buf, int maxlen);
int recvdata(int fd, char *buf, int maxlen);

int 
main(int argc, char **argv)
{
	char err_buf[128];
	int i, n, sockfd, clientfd;
	int yes = 1;  

	struct addrinfo *ai;
	struct sockaddr_in *client;
	socklen_t client_t;
	pid_t cpid;

	char line[MAXLEN];
	char cpid_s[32];
	char welcome[32];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{
		LOGE("%s", strerror(errno));
		goto E0;
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(int)) == -1) 
	{
		LOGE("%s", strerror(errno));
		goto E1;
	}

	if (getaddrinfo(NULL, PORT, NULL, &ai) != 0) 
	{ 
		LOGE("%s", strerror(errno));
		goto E1;
	}

	if (bind(sockfd, ai->ai_addr, ai->ai_addrlen) != 0) 
	{
		LOGE("%s", strerror(errno));
		goto E1;
	}

	freeaddrinfo(ai);

	if (listen(sockfd, 10) == -1) 
	{
		LOGE("%s", strerror(errno));
		goto E1;
	}

	for (i = 0; i < NUM_CHILDREN; i++) 
	{
		cpid = fork();
		if (cpid == -1) 
		{
			LOGE("%s", strerror(errno));
			goto E1;
		}
		if (cpid == 0) 
		{
			for (;;) 
			{ 
				client_t = sizeof client;
				LOGD("Waiting new connection!\n");
				clientfd = accept(sockfd, (struct sockaddr *)&client, &client_t);
				if (clientfd == -1) 
				{
					LOGE("%s", strerror(errno));
					goto E1;
				}

				bzero(cpid_s, 32);
				bzero(welcome, 32);
				sprintf(cpid_s, "%d", getpid());
				sprintf(welcome, "Child %s echo>\n", cpid_s);
				send(clientfd, welcome, strlen(welcome), 0);

				/* n = readline(clientfd, line, MAXLEN);
				if (n == -1) {
					die("Couldn't read line from connection");
				}                                                 */
			
				n = recvdata(clientfd, line, MAXLEN);
				LOGD("recieve data: %s\n", line);
				send(clientfd, line, n, 0);

				LOGN("Close client socket.\n");
				close(clientfd);
			}
		}
	}

	while (waitpid(-1, NULL, 0) > 0);
E1:
	close(sockfd);
	LOGD("Close server socket.\n");
E0:
	return 0;
}
  
int
readline(int fd, char *buf, int maxlen)
{
	int n, rc;
	char c;
	for (n = 1; n < maxlen; n++) {
		if ((rc = read(fd, &c, 1)) == 1) {
			*buf++ = c;
			if (c == '\n')
				break;
		} else if (rc == 0) {
			if (n == 1)
				return 0;
			else
				break;
		} else
			return -1;
	}
	*buf = '\0';
	
	return n;
}

int
recvdata(int fd, char *buf, int maxlen)
{
	return recv(fd, buf, maxlen, 0);
}
