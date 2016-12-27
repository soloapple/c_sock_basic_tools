/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: stand_tcp_client.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2016年12月27日 09时27分52秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2016年12月27日                  build this moudle  
 *****************************************************************************/
#include "syshead.h"
#define    RES_LENGTH  10240 //接受字符的最大长度
int     connect_socket(char * server,int serverPort);
int     send_msg(int sockfd,char * sendBuff);
char *  recv_msg(int sockfd);
int     close_socket(int sockfd);

const char *local_ip = "127.0.0.1";

int main(int argc, char ** argv)
{
	LOGN("TCP CLIENT\n");

	int   sockfd=0;
	char  sendMsg[30]="abc.org\r\n\r";
	char* res;
	int   port = 4242;
	char  ip[128] = {0};

	strncpy(ip, local_ip, strlen(local_ip));
	if (argc > 2)
	{
		strncpy(ip, argv[1], strlen(argv[1]));
		port = atoi(argv[2]);
		LOGN("Input IP: %s, port : %d\n", ip, port);
	}
	else if (argc > 1)
	{	
		port = atoi(argv[1]);
		LOGN("Input port : %d\n", port);
	}

	sockfd = connect_socket(ip, port);
	send_msg(sockfd,sendMsg);
	res = recv_msg(sockfd); 
//	printf(res);

	free(res);
	close_socket(sockfd);
	return 0;
}

int    
connect_socket(char *server, int serverPort)
{
	int sockfd = 0;
	struct	sockaddr_in addr;
	struct	hostent * phost;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		LOGE("Init socket error!");
		return -1;
	}

	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(serverPort);
	addr.sin_addr.s_addr = inet_addr(server);
	
	if(addr.sin_addr.s_addr == INADDR_NONE)
	{
		phost = (struct hostent*)gethostbyname(server);
		if (phost == NULL)
		{
			LOGE("Init socket s_addr error!");
			return -1;
		}
		addr.sin_addr.s_addr =((struct in_addr*)phost->h_addr)->s_addr;
	}

	if (connect(sockfd,(struct sockaddr*)&addr, sizeof(addr))<0)
	{
		LOGE("Connect server fail!");
		return -1;
	}

	return sockfd;
}

int 
send_msg(int sockfd, char *sendBuff)
{
	int sendSize = 0;
	if ((sendSize = send(sockfd, sendBuff, strlen(sendBuff), 0)) <= 0)
	{
		LOGE("Send msg error!\n");
		return -1;
	}
	
	LOGN("Now Send Buffer:%s\n", sendBuff);
	return sendSize;
}

char* 
recv_msg(int sockfd)
{
	char *response;
	int flag = 0;
	int recLenth = 0;
	response = (char *)calloc(RES_LENGTH, 1);
	
	for(;;)
	{
		if ((recLenth = recv(sockfd, response+flag, RES_LENGTH-flag, 0)) == -1 )
		{
			free(response);
			LOGE("Return value : %d\n", recLenth);
			return NULL;
		}
		else if(recLenth==0)
		{
			LOGN("Server Closed!\n");
			break;
		}
		else
		{
			LOGN("LEN: %d DATA: %s\n", recLenth, response + flag);
			flag += recLenth;
			recLenth = 0;
		}
	}

	response[flag]='\0';
	return response;
}

int 
close_socket(int sockfd)
{
	close(sockfd);
	return 0;
}


