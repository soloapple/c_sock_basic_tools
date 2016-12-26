/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: grap_raw_link_pgk.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2016年12月26日 15时21分28秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2016年12月26日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int analyData(char *data);
int rawSocket();
int setPromisc(char *,int *);
int count=0;

int 
main(int argc,char **argv)
{
    if(argc!=2)
    {
        perror("please enter the ecterface");
        exit(1);
    }

    int sock;
    int msgsock;
    struct sockaddr_in rcvaddr;
    char buf[9216];
    struct ifreq ifr;
    socklen_t len;
    int rval;

    sock=rawSocket();
    setPromisc(argv[1],&sock);
    len=sizeof(struct sockaddr);
    memset(buf,0,sizeof(buf));

    for (;;)
    {
        rval=recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&rcvaddr, &len);
        if(rval>0)
        {
//            printf("Get %d bytes\n",rval);
            analyData(buf);
        }
    }

    return 0;
}

int 
analyData(char *data)
{
    struct iphdr *ip;
    struct tcphdr *tcp;
    struct ether_header *ether;

//    ether=(struct ether_header*)data;//若数据是从数据链路曾抓取的，那么就有这个以太网帧头
//    printf("shu ju bao lei xing xie yi:%d\n",ether->ether_type);
//    ip=(struct iphdr*)(data+sizeof(struct ether_header));
    ip=(struct iphdr*)data;
    count++;
	
	char sip[16];
	strcpy(sip, inet_ntoa(*((struct in_addr*)&ip->saddr)));
	if ( ! strcmp (sip, "172.24.128.42"))
	{
		return 0;
	}

    printf("Protocol::%d\n",ip->protocol);
    printf("Source IP::%s\n",inet_ntoa(*((struct in_addr*)&ip->saddr)));
	printf("Dest IP::%s\n",inet_ntoa(*((struct in_addr*)&ip->daddr)));

    tcp=(struct tcphdr*)(data+sizeof(*ip));

    printf("Source Port::%d\n",ntohs(tcp->source));
    printf("Dest Port::%d\n",ntohs(tcp->dest));
    printf("Already get %d package\n",count);
    printf("\n");

    return 1;
}

int 
rawSocket()//创建原始套接字
{
    int sock;
//    sock=socket(PF_INET,SOCK_RAW,IPPROTO_UDP);//IP层抓取
//    sock=socket(PF_INET,SOCK_RAW,IPPROTO_TCP);//IP层抓取
    sock=socket(PF_PACKET,SOCK_RAW,ETH_P_IP);//数据链路层抓取
    if(sock<0)
    {
        printf("create raw socket failed::%s\n",strerror(errno));
        exit(1);
    }
    
    printf("raw socket ::%d created successful\n",sock);
    return sock;
}

int 
setPromisc(char *enterface,int *sock)//设置eth0的混乱模式
{
    struct ifreq ifr;
    strcpy(ifr.ifr_name,"eth0");
    ifr.ifr_flags=IFF_UP|IFF_PROMISC|IFF_BROADCAST|IFF_RUNNING;
    if(ioctl(*sock,SIOCSIFFLAGS,&ifr)==-1)//设置混乱模式
    {
        perror("set 'eth0' to promisc model failed\n");
        exit(1);
    }

    printf("set '%s' to promisc successed\n",enterface);
    return 1;
}
