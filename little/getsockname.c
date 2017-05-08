/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: getsockname.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月06日 05时53分32秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月06日                  build this moudle  
 *****************************************************************************/

#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include <arpa/inet.h>  
#include <netdb.h>  

#define PORT 7778  
#define MAXDATASIZE 1024  

int 
main()  
{  
	struct sockaddr_in user_addr,my_addr;  
	char my_ip[13];  
	int socket_fd;  
	int so_broadcast=1;  
	char buf[MAXDATASIZE];  

	socklen_t size;  

	my_addr.sin_family=AF_INET;  
	my_addr.sin_port=htons(PORT);  
	my_addr.sin_addr.s_addr=inet_addr("255.255.255.255");  

	user_addr.sin_family=AF_INET;  
	user_addr.sin_port=htons(PORT);  
	user_addr.sin_addr.s_addr=htonl(INADDR_ANY);  


	if((socket_fd=(socket(AF_INET,SOCK_DGRAM,0)))==-1) {  
		perror("socket");  
		exit(1);  
	}  

	setsockopt(socket_fd,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast));

	if((bind(socket_fd,(struct sockaddr *)&user_addr, sizeof(struct sockaddr)))==-1) {  
		perror("bind");  
		exit(1);  
	}  

	strcpy(buf,"broadcast test");  
	sendto(socket_fd,buf,strlen(buf),0,(struct sockaddr *)&my_addr,sizeof(my_addr));  

	size=sizeof(user_addr);  
	recvfrom(socket_fd,buf,MAXDATASIZE,0,(struct sockaddr *)&user_addr,&size);  

	strcpy(my_ip, inet_ntoa(user_addr.sin_addr));  
	printf("my_ip:%s\n",inet_ntoa(user_addr.sin_addr));  
	
	return 0;
}  
