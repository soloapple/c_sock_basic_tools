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

#define die(msg) do { LOGE(msg); exit(EXIT_FAILURE); } while (0)
#define PORT "4242"
#define NUM_CHILDREN 3
#define MAXLEN 1024

int readline(int fd, char *buf, int maxlen);
int recvdata(int fd, char *buf, int maxlen);

int 
main(int argc, char **argv)
{
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
		die("Couldn't create a socket\n");
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(int)) == -1) 
	{
		die("Couldn't setsockopt\n");
	}

	if (getaddrinfo(NULL, PORT, NULL, &ai) != 0) 
	{ 
		die("Couldn't get address\n");
	}

	if (bind(sockfd, ai->ai_addr, ai->ai_addrlen) != 0) 
	{
		die("Couldn't bind socket to address\n");
	}

	freeaddrinfo(ai);

	if (listen(sockfd, 10) == -1) 
	{
		die("Couldn't make socket listen\n");
	}

	LOGD("One new connection is coming!\n");

	for (i = 0; i < NUM_CHILDREN; i++) 
	{
		cpid = fork();
		if (cpid == -1) 
		{
			die("Couldn't fork\n");
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
					die("Couldn't accept a connection\n");
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
	close(sockfd);
	LOGD("Close server socket.\n");
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
