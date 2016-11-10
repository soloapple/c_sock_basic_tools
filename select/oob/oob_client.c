/***************************************************************************************
 *   Copyright (C), 2006-2015, Legendsec Technology Co., Ltd.
 *
 *    Filename: oob_client.c

 * Description: 
 *     Version: 1.0
 *     Created: Liujfa   06/18/15 03:14:07
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              Liujfa   06/18/15                  build this moudle  
 ***************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../include/color_print.h"

#define PORT 4000
#define MAXDATASIZE 100

int 
send_data(int sockfd, char *data, int flag)
{
	int len;

	len = send(sockfd, data, strlen(data), flag);
	if ( len == -1 )
	{
		LOGE("send failed\n");
		close(sockfd);

		exit(0);
	}

	if ( flag == MSG_OOB )
	{
		LOGD("Send %d byte of OOB data:%s\n", strlen(data),data);
	}
	else if ( flag == 0 )
	{
		LOGD("Send %d byte of common data:%s\n", strlen(data),data);
	}

	sleep(2);
	return 0;
}

int main(int argc, char *argv[])
{
	int sockfd,numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr;

	if (argc != 3)
	{
		LOGE("Usage: client ip port\n");
		exit(0);
	}

	if ((he=gethostbyname(argv[1])) == NULL)
	{
		LOGE("Gethostbyname failed!\n");
		exit(0);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		LOGE("create socket failed!\n");
		exit(0);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(atoi(argv[2]));
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

	if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{
		LOGE("connect socket failed!\n");
		exit(0);
	}

	send_data(sockfd, "123", 0);
	send_data(sockfd, "4", MSG_OOB);
	send_data(sockfd, "56", 0);
	send_data(sockfd, "7", MSG_OOB);
	send_data(sockfd, "89", MSG_OOB);
	send_data(sockfd, "ABC", MSG_OOB);
	send_data(sockfd, "abc", MSG_OOB);

	return 0;
}
