/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: msg_key.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/26/16 18:29:12
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/26/16                  build this moudle  
 ***************************************************************************************/
#include "msg_key.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct Msg
{
	long type;
	char data[50];
};

struct Intmsg
{
	long type;
	int  data;
};

void 
send_msg()
{
	key_t key=ftok(".",200);
	int r, i;
	int msgid=msgget(key,IPC_CREAT|IPC_EXCL|0666);
	//�����ַ�����Ϣ*
	struct Msg msg;
	struct Intmsg imsg;	
	for(i=0;i<10;i++)
	{
		msg.type=1;
		bzero(msg.data,sizeof(msg.data));
		sprintf(msg.data, "��Ϣ:%d", i);
		r=msgsnd(msgid, &msg, strlen(msg.data), 0);
		printf("message send:%d\n",r);		
	}	
	//����������Ϣ
	for(i=0;i<10;i++)
	{
		imsg.type=2;
		imsg.data=i;		
		r=msgsnd(msgid, &imsg, sizeof(imsg.data), 0);
		printf("has send:%d, %d\n",r, i);		
	}
}

void 
recv_msg()
{
	//�õ���Ϣ����
	key_t key=ftok(".",200);
	int msgid=msgget(key,0);
	//�õ���Ϣ	
	struct Msg msg;
	while(1)
	{
		printf ( "recv now!\n" );
		memset(msg.data, 0x00, 50);
		size_t size=msgrcv(msgid,&msg,sizeof(msg.data),1,0);
		msg.data[size]=0;
		printf("msg is:%s\n",msg.data);
	}
}


