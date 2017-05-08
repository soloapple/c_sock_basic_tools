/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: udp_conn.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月06日 07时06分47秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月06日                  build this moudle  
 *****************************************************************************/
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h>

using namespace std;

int main()
{
	int sockClient,nMsgLen,nReady;
	char szRecv[1024],szSend[1024],szMsg[1024];
	struct sockaddr_in addrServer, addrCli, addrLocal;
	socklen_t addrLen;
	fd_set setHold,setTest;
	char my_ip[1024];

	sockClient=socket(AF_INET,SOCK_DGRAM,0);
	addrLen=sizeof(struct sockaddr_in);
	bzero(&addrServer,sizeof(addrServer));
	addrServer.sin_family=AF_INET;
	addrServer.sin_addr.s_addr=inet_addr("172.24.141.29");
	addrServer.sin_port=htons(8000);

#ifdef NEEDBIND
	addrLocal.sin_family=AF_INET;
	addrLocal.sin_addr.s_addr=htonl(INADDR_ANY);
	addrLocal.sin_port=htons(9000);
	if(bind(sockClient,(struct sockaddr*)&addrLocal,sizeof(addrLocal))==-1)
	{
		perror("error in binding");
		exit(2);
	}
#endif

	if(connect(sockClient,(struct sockaddr*)&addrServer,sizeof(addrServer))==-1)
	{
		perror("error in connecting");
		exit(1);
	}

	socklen_t len_sock_cli = sizeof(addrCli);	
	getsockname(sockClient, (struct sockaddr*)&addrCli, &len_sock_cli);
	
	strcpy(my_ip, inet_ntoa(addrCli.sin_addr));  
	printf("my_ip:%s\n",inet_ntoa(addrCli.sin_addr));  
}
