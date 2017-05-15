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
	//发送字符串消息*
	struct Msg msg;
	struct Intmsg imsg;	
	for(i=0;i<10;i++)
	{
		msg.type=1;
		bzero(msg.data,sizeof(msg.data));
		sprintf(msg.data, "消息:%d", i);
		r=msgsnd(msgid, &msg, strlen(msg.data), 0);
		printf("message send:%d\n",r);		
	}	
	//发送整数消息
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
	//得到消息队列
	key_t key=ftok(".",200);
	int msgid=msgget(key,0);
	//得到消息	
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


