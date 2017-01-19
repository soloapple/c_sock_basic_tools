/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: grap_raw_link_pgk.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2016��12��26�� 15ʱ21��28��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2016��12��26��                  build this moudle  
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
#include "/revive/git/c_sock_basic_tools/include/colorpt.h"

typedef struct _iphdr //����IP�ײ� 
{ 
    unsigned char h_verlen; //4λ�ײ�����+4λIP�汾�� 
    unsigned char tos; //8λ��������TOS 
    unsigned short total_len; //16λ�ܳ��ȣ��ֽڣ� 
    unsigned short ident; //16λ��ʶ 
    unsigned short frag_and_flags; //3λ��־λ 
    unsigned char ttl; //8λ����ʱ�� TTL 
    unsigned char proto; //8λЭ�� (TCP, UDP ������) 
    unsigned short checksum; //16λIP�ײ�У��� 
    unsigned int sourceIP; //32λԴIP��ַ 
    unsigned int destIP; //32λĿ��IP��ַ 
}IP_HEADER; 

typedef struct _udphdr //����UDP�ײ�
{
    unsigned short uh_sport;    //16λԴ�˿�
    unsigned short uh_dport;    //16λĿ�Ķ˿�
    unsigned int uh_len;//16λUDP������
    unsigned int uh_sum;//16λУ���
}UDP_HEADER;

typedef struct _tcphdr //����TCP�ײ� 
{ 
    unsigned short th_sport; //16λԴ�˿� 
    unsigned short th_dport; //16λĿ�Ķ˿� 
    unsigned int th_seq; //32λ���к� 
    unsigned int th_ack; //32λȷ�Ϻ� 
    unsigned char th_lenres;//4λ�ײ�����/6λ������ 
    unsigned char th_flag; //6λ��־λ
    unsigned short th_win; //16λ���ڴ�С
    unsigned short th_sum; //16λУ���
    unsigned short th_urp; //16λ��������ƫ����
}TCP_HEADER; 

typedef struct _icmphdr {  
    unsigned char  icmp_type;  
    unsigned char icmp_code; /* type sub code */  
    unsigned short icmp_cksum;  
    unsigned short icmp_id;  
    unsigned short icmp_seq;  
    /* This is not the std header, but we reserve space for time */  
    unsigned short icmp_timestamp;  
}ICMP_HEADER;

void 
analyseTCP(TCP_HEADER *tcp)
{
    LOGD("TCP -----\n");
    LOGN("Source port: %u\n", ntohs(tcp->th_sport));
    LOGN("Dest port: %u\n", ntohs(tcp->th_dport));
}

void 
analyseUDP(UDP_HEADER *udp)
{
    LOGD("UDP -----\n");
    LOGN("Source port: %u\n", ntohs(udp->uh_sport));
    LOGN("Dest port: %u\n", ntohs(udp->uh_dport));
}

void 
analyseICMP(ICMP_HEADER *icmp)
{
    LOGD("ICMP -----\n");
    LOGN("type: %u\n", icmp->icmp_type);
    LOGN("sub code: %u\n", icmp->icmp_code);
}

int analyData(char *data);
int rawSocket();
int setPromisc(char *,int *);
int count=0;

int check_data_proto(char *buf);

int 
main(int argc,char **argv)
{
    if(argc!=2)
    {
        LOGE("please enter the ecterface\n");
        exit(1);
    }

    int sock;
//    int msgsock;
    char buf[8192];
//    struct ifreq ifr;
    int rval;

    sock = rawSocket();
//    setPromisc(argv[1], &sock);
    memset(buf, 0, sizeof(buf));

    socklen_t len = sizeof(struct sockaddr);
    struct sockaddr_in rcvaddr;

    for (;;)
    {
        rval=recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&rcvaddr, &len);
//        rval = recv(sock, buf, sizeof(buf), 0);
        if(rval > 0)
        {
//            LOGN("Get %d bytes\n",rval);
//            analyData(buf);
			check_data_proto(buf + 14);
        }
    }

    return 0;
}

void 
analyseIP(IP_HEADER *ip)
{
    unsigned char* p = (unsigned char*)&ip->sourceIP;
    LOGN("Source IP\t: %u.%u.%u.%u\n",p[0],p[1],p[2],p[3]);
    p = (unsigned char*)&ip->destIP;
    LOGN("Destination IP\t: %u.%u.%u.%u\n",p[0],p[1],p[2],p[3]);
}

int
check_data_proto(char *buf)
{
    IP_HEADER *ip;

	ip = ( IP_HEADER *)(buf+14);
    size_t iplen =  (ip->h_verlen&0x0f)*4;
	if (ip->proto == IPPROTO_TCP)
	{
	    analyData(buf);
		return 0;
	    analyseIP(ip);
		TCP_HEADER *tcp = (TCP_HEADER *)(buf +iplen);
		analyseTCP(tcp);
	}
	else if (ip->proto == IPPROTO_UDP)
	{
		return 0;
	    analyseIP(ip);
		UDP_HEADER *udp = (UDP_HEADER *)(buf + iplen);
		analyseUDP(udp);
	}
	else if (ip->proto == IPPROTO_ICMP)
	{
	    analyseIP(ip);
		ICMP_HEADER *icmp = (ICMP_HEADER *)(buf + iplen);
		analyseICMP(icmp);
	}
	else if (ip->proto == IPPROTO_IGMP)
	{
//		LOGN("IGMP----\n");
	}
	else
	{
//		LOGN("other protocol!\n");
	}        

	return 0;
}

int 
analyData(char *data)
{
    struct iphdr *ip;
    struct tcphdr *tcp;
//    struct ether_header *ether;

//    ether=(struct ether_header*)data;//�������Ǵ�������·��ץȡ�ģ���ô���������̫��֡ͷ
//    LOGN("shu ju bao lei xing xie yi:%d\n",ether->ether_type);
//    ip=(struct iphdr*)(data+sizeof(struct ether_header));
    ip=(struct iphdr*)data;
    count++;
	
//	char sip[16];
//	strcpy(sip, inet_ntoa(*((struct in_addr*)&ip->saddr)));
//	if ( strcmp(sip, "10.0.0.41") == 0)
//		return 0;

    LOGN("Protocol::%d\n",ip->protocol);
    LOGN("Source IP::%s\n",inet_ntoa(*((struct in_addr*)&ip->saddr)));
	LOGN("Dest IP::%s\n",inet_ntoa(*((struct in_addr*)&ip->daddr)));

    tcp=(struct tcphdr*)(data+sizeof(*ip));

    LOGN("Source Port::%d\n",ntohs(tcp->source));
    LOGN("Dest Port::%d\n",ntohs(tcp->dest));
    LOGN("Already get %d package\n",count);
    LOGN("\n");

    return 1;
}

int 
rawSocket()//����ԭʼ�׽���
{
    int sock;
//    sock=socket(PF_INET,SOCK_RAW,IPPROTO_UDP);//IP��ץȡ
//    sock=socket(PF_INET,SOCK_RAW,IPPROTO_TCP);//IP��ץȡ
//    sock = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_IP));//������·��ץȡ
    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));//������·��ץȡ
    if(sock<0)
    {
        LOGE("create raw socket failed::%s\n",strerror(errno));
        exit(1);
    }
    
    LOGD("raw socket ::%d created successful\n",sock);
    return sock;
}

int 
setPromisc(char *enterface,int *sock)//����eth0�Ļ���ģʽ
{
    struct ifreq ifr;
    strcpy(ifr.ifr_name, "net1");
    ifr.ifr_flags=IFF_UP|IFF_PROMISC|IFF_BROADCAST|IFF_RUNNING;
    if (ioctl(*sock, SIOCSIFFLAGS, &ifr) == -1)//���û���ģʽ
    {
        LOGE("set 'eth0' to promisc model failed\n");
        exit(1);
    }

    LOGD("set '%s' to promisc successed\n",enterface);
    return 1;
}
