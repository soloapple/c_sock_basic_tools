/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: gethostname.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2016��12��30�� 20ʱ39��27��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2016��12��30��                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

#define NET_ADDR_STR_LEN 16     //16���ֽڣ����ڴ�ŵ��ʮ����IP��ַ���ַ�������

int main(int argc,char **argv)
{
	struct hostent *host;   //���������Ϣ
	char addr_p[NET_ADDR_STR_LEN]; //���ڴ�ŵ��ʮ����IP��ַ���ַ���
	int i;
	if((host = gethostent()) == NULL)
	{
		perror("fail to get host's information\n");
		exit(1);
	}

	printf("hostName: %s\n" , host->h_name);
	for(i = 0 ; host->h_aliases[i] != NULL;i++)
	{
		printf("%s\n" , host->h_aliases[i]);     //���������б������ֺܶ࣬�Զ�ά������ʽ�洢   h_aliases[0] Ϊ����IP
	}

	if(host->h_addrtype == AF_INET)      //�ж�IP�����Ƿ���ipv4
	{
		printf("at_inet\n");
	}
	else
	{
		printf("unix_inet\n");
	}
	printf("len%d\n",host->h_length);    //��ַ����

	for(i = 0 ; host->h_addr_list[i] != NULL ; i++)
	{
		//�õ�ַ�Զ�������ʽ�洢��ת��Ϊ�ַ�������ʽ
		printf("%s\n",inet_ntop(host->h_addrtype,host->h_addr_list[i],addr_p,NET_ADDR_STR_LEN));      //��ӡ����IP��ַ
	}
	return 0;
}
