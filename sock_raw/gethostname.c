/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: gethostname.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2016年12月30日 20时39分27秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2016年12月30日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

#define NET_ADDR_STR_LEN 16     //16个字节，用于存放点分十进制IP地址的字符串长度

int main(int argc,char **argv)
{
	struct hostent *host;   //存放主机信息
	char addr_p[NET_ADDR_STR_LEN]; //用于存放点分十进制IP地址的字符串
	int i;
	if((host = gethostent()) == NULL)
	{
		perror("fail to get host's information\n");
		exit(1);
	}

	printf("hostName: %s\n" , host->h_name);
	for(i = 0 ; host->h_aliases[i] != NULL;i++)
	{
		printf("%s\n" , host->h_aliases[i]);     //主机别名列表，可以又很多，以二维数组形式存储   h_aliases[0] 为主机IP
	}

	if(host->h_addrtype == AF_INET)      //判断IP类型是否是ipv4
	{
		printf("at_inet\n");
	}
	else
	{
		printf("unix_inet\n");
	}
	printf("len%d\n",host->h_length);    //地址长度

	for(i = 0 ; host->h_addr_list[i] != NULL ; i++)
	{
		//该地址以二进制形式存储，转换为字符串的形式
		printf("%s\n",inet_ntop(host->h_addrtype,host->h_addr_list[i],addr_p,NET_ADDR_STR_LEN));      //打印主机IP地址
	}
	return 0;
}
