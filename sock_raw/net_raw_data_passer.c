/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: net_raw_data_passer.c
 * Description: recv data from raw sock, then send it.
 *				queue and hash will be add later.
 *				it implements route function.
 *
 *     Version: 1.0
 *     Created: soloapple   2016年12月29日 10时07分04秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2016年12月29日          build this moudle  
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

#include "xutils.h"
#include "/revive/git/c_sock_basic_tools/include/colorpt.h"

const char *src_port = "4242";

#define IP_TCP_HDR_SIZE sizeof(struct iphdr) + sizeof(struct tcphdr)
#define buf_size 8192

int local_sock;
int target_sock;
int next_sock;
struct sockaddr_in *target;	
struct sockaddr_in *next;	
char *send_buff;
char *send_buff_head;
char *hostname;

int fd_recv;
int fd_send;
char *dev_recv;
char *dev_send;
struct sockaddr_ll sa_recv;
struct sockaddr_ll sa_send;

typedef struct _iphdr //定义IP首部 
{ 
    unsigned char h_verlen; //4位首部长度+4位IP版本号 
    unsigned char tos; //8位服务类型TOS 
    unsigned short total_len; //16位总长度（字节） 
    unsigned short ident; //16位标识 
    unsigned short frag_and_flags; //3位标志位 
    unsigned char ttl; //8位生存时间 TTL 
    unsigned char proto; //8位协议 (TCP, UDP 或其他) 
    unsigned short checksum; //16位IP首部校验和 
    unsigned int sourceIP; //32位源IP地址 
    unsigned int destIP; //32位目的IP地址 
}IP_HEADER; 

typedef struct _udphdr //定义UDP首部
{
    unsigned short uh_sport;    //16位源端口
    unsigned short uh_dport;    //16位目的端口
    unsigned int uh_len;//16位UDP包长度
    unsigned int uh_sum;//16位校验和
}UDP_HEADER;

typedef struct _tcphdr //定义TCP首部 
{ 
    unsigned short th_sport; //16位源端口 
    unsigned short th_dport; //16位目的端口 
    unsigned int th_seq; //32位序列号 
    unsigned int th_ack; //32位确认号 
    unsigned char th_lenres;//4位首部长度/6位保留字 
    unsigned char th_flag; //6位标志位
    unsigned short th_win; //16位窗口大小
    unsigned short th_sum; //16位校验和
    unsigned short th_urp; //16位紧急数据偏移量
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

struct ring {
	int tp_size;                /* use memory size(block_size*block_count) */
	int tp_frame;               /* every frame size of struct tpacket_req */
	int tp_frame_count;         /* the total frame */

	int recv_sd;                /* recv data socket fd */
	int send_sd;                /* send data socket fd */

	char *tx_ring;              /* point to send mmap */
	char *rx_ring;              /* point to recv mmap */

	int txring_offset;          /* header offset that default value is zero */
	int rxring_offset;          /* header offset that default value is zero */

	struct sockaddr_ll sl_recv; /* bind recv network interface */
	struct sockaddr_ll sl_send; /* bind send network interface */
} rg;


void sys_exit()
{
	/* clear socket fd */
	if (rg.recv_sd)
		close(rg.recv_sd);

	if (rg.send_sd)
		close(rg.send_sd);

	/* clear mmap ring */
	if (rg.rx_ring)
		munmap(rg.rx_ring, rg.tp_size);

	if (rg.tx_ring)
		munmap(rg.tx_ring, rg.tp_size);

	exit(0);
}




typedef struct arglist
{
		
}al;

int set_promisc(char *interface, int *sock);

void 
analyseTCP(TCP_HEADER *tcp)
{
    LOGD("TCP -----\n");
    LOGN("Source port: %u\n", ntohs(tcp->th_sport));
    LOGN("Dest port: %u\n", ntohs(tcp->th_dport));
	puts("");
}

void 
analyseUDP(UDP_HEADER *udp)
{
    LOGD("UDP -----\n");
    LOGN("Source port: %u\n", ntohs(udp->uh_sport));
    LOGN("Dest port: %u\n", ntohs(udp->uh_dport));
	puts("");
}

void 
analyseICMP(ICMP_HEADER *icmp)
{
    LOGD("ICMP -----\n");
    LOGN("type: %u\n", icmp->icmp_type);
    LOGN("sub code: %u\n", icmp->icmp_code);
	puts("");
}

int analyseData(char *data, char *source_verify_ip, char *dest_verify_ip, int source_port, int dest_port);
int count=0;

int check_data_proto(char *buf);


/*    
 * sock=socket(PF_INET,SOCK_RAW,IPPROTO_UDP);//IP层抓取
 * sock=socket(PF_INET,SOCK_RAW,IPPROTO_TCP);//IP层抓取
 * sock = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_IP));//数据链路层抓取
 */
int
init_client_sock(char *interface)
{
	local_sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));
	if (local_sock < 0)
	{
		LOGE("create raw socket failed::%s\n", strerror(errno));
		return -1;
	}

	if ( set_promisc(interface, &local_sock) < 0)
		return -1;

	return 0;
}

int
init_server_sock(struct sockaddr_in *addr, int *sock, const char *next_addr, const char *next_port)
{
	const int flag = 1;

//	addr = calloc(sizeof(struct sockaddr_in), 1);
	addr->sin_family = AF_INET;
	addr->sin_port = htons(atoi(next_port));

	if (inet_aton(next_addr, &addr->sin_addr) == 0) 
	{
		LOGE("inet aton net fail\n");
		return -1;
	}


	if ((*sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) 
	{
		LOGE("create server socket error!\n");
		return -1;
	}

	/* 
	 * @parameter specification : IP_HDRINCL
	 * fill IP header data yourself, otherwise it will be set automatic. 
	 */
	if (setsockopt(*sock, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) < 0) 
	{
		LOGE("setsockopt fail \n");
		return -1;
	}

	return *sock;
}

unsigned short 
check_sum(unsigned short *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	short answer = 0;

	while (nleft > 1) 
	{
		sum += *w++;
		nleft -=2;
	}

	if (nleft == 1) 
	{
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return answer;
}

void 
build_iphdr(struct sockaddr_in *target, char *buffer, int len_pkg, int len_data)
{
	struct iphdr *ip = (struct iphdr *)(buffer);
	ip->version = 4;
	ip->ihl = 5;
	ip->tos = 0;
	ip->tot_len = htons(len_pkg);
	ip->id = 0;
	ip->frag_off = 0;
	ip->ttl = 255;
	ip->protocol = IPPROTO_TCP;
	ip->check = 0;
	ip->saddr = random();
	ip->daddr = target->sin_addr.s_addr;

	ip->check = check_sum((unsigned short *)ip, sizeof(struct iphdr) + len_data);
}

void 
build_tcphdr(struct sockaddr_in *target, const char *src_port, 
		char *buffer, char *data, int len_data)
{
	struct tcphdr *tcp = (struct tcphdr *)(buffer);
	tcp->source = htons(atoi(src_port));
	tcp->dest = target->sin_port;
	tcp->seq = random();
	tcp->doff = 5;
	tcp->syn = 1;
	buffer += sizeof(struct tcphdr);
	if (len_data != 0)
		memcpy(buffer, data, len_data);
	tcp->check = check_sum((unsigned short *)tcp, sizeof(struct tcphdr) + len_data); 
}

void
send_data_to_next(char *data, int len_data)
{
	int len_pkg;
	char *send_pkg;	
	char *send_pkg_head;

	len_pkg = IP_TCP_HDR_SIZE + len_data;
	send_pkg = calloc(len_pkg, 1);
	send_pkg_head = send_pkg;
	build_iphdr(target, send_pkg, len_pkg, len_data);
	send_pkg += sizeof(struct iphdr);
	build_tcphdr(target, src_port, send_pkg, data, len_data);

//	sendto(target_sock, send_pkg_head, len_pkg, 0,
//			(struct sockaddr *)target, sizeof(struct sockaddr_in));

	sendto(next_sock, send_pkg_head, len_pkg, 0,
			(struct sockaddr *)next, sizeof(struct sockaddr_in));

	free(send_pkg_head);
	//    free(target);
}

int
recv_data(char *buf)
{
	int rval;
   
	rval = recv(local_sock, buf, buf_size, 0);
	return rval;
}

int 
analyseData(char *data, char *source_verify_ip, char *dest_verify_ip, int source_port, int dest_port)
{
//	data = data + 14;
    struct iphdr *ip;
    struct tcphdr *tcp;
//  struct ether_header *ether;

//  ether=(struct ether_header*)data;//若数据是从数据链路曾抓取的，那么就有这个以太网帧头
//  LOGN("shu ju bao lei xing xie yi:%d\n",ether->ether_type);
//  ip=(struct iphdr*)(data+sizeof(struct ether_header));
    ip = (struct iphdr*)data;
    count++;

	char sip[16];
	char dip[16];
	strcpy(sip, inet_ntoa(*((struct in_addr*)&ip->saddr)));
	strcpy(dip, inet_ntoa(*((struct in_addr*)&ip->daddr)));

	if (source_verify_ip != NULL)
	{	
		if (strcmp(sip, source_verify_ip) != 0)
			return -1;
	}

	if (dest_verify_ip != NULL)
	{
		if (strcmp(dip, dest_verify_ip) != 0)
			return -1;
	}
	
	tcp = (struct tcphdr*)(data + sizeof(struct iphdr));

	if (source_port != 0)
	{
		if (ntohs(tcp->source) != source_port)
			return -1;
	}

	if (dest_port != 0)
	{
		if (ntohs(tcp->dest) != dest_port)
			return -1;
	}
    
//	output_str_to_hex((unsigned char*)data, 128);

	LOGN("***************************************\n");
	LOGN("Source IP: %s, Dest IP: %s\n", sip, dip);
    LOGN("Source Port::%d\n",ntohs(tcp->source));
    LOGN("Dest Port::%d\n",ntohs(tcp->dest));
    LOGN("Already get %d package\n", count);
	LOGN("***************************************\n");
    puts("");

    return 1;
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
	buf = buf + 14;
    IP_HEADER *ip;
	ip = ( IP_HEADER *)(buf);
    size_t iplen =  (ip->h_verlen&0x0f)*4;
	if (ip->proto == IPPROTO_TCP)
	{
		output_str_to_hex((unsigned char*)buf, 256);
		analyseIP(ip);
		TCP_HEADER *tcp = (TCP_HEADER *)(buf +iplen);
		analyseTCP(tcp);
	}
	else if (ip->proto == IPPROTO_UDP)
	{
		output_str_to_hex((unsigned char*)buf, 256);
		analyseIP(ip);
		UDP_HEADER *udp = (UDP_HEADER *)(buf + iplen);
		analyseUDP(udp);
	}
	else if (ip->proto == IPPROTO_ICMP)
	{
		output_str_to_hex((unsigned char*)buf, 256);
		analyseIP(ip);
		ICMP_HEADER *icmp = (ICMP_HEADER *)(buf + iplen);
		analyseICMP(icmp);
	}
	else if (ip->proto == IPPROTO_IGMP)
	{
		LOGN("IGMP----\n");
	}
	else
	{
		LOGN("other protocol!\n");
	}        

	return 0;
}

int 
check_data_in_rule(char *data)
{
	data = data + 14;
    IP_HEADER *ip_hdr;

	ip_hdr = (IP_HEADER *)(data);
	if (ip_hdr->proto == IPPROTO_TCP)
	{
		return analyseData(data, "172.24.128.50", NULL, 0, 4242);
	}

    return -1;
}

int 
set_promisc(char *interface, int *sock)
{
    struct ifreq ifr;
    strcpy(ifr.ifr_name, interface);
    ifr.ifr_flags=IFF_UP|IFF_PROMISC|IFF_BROADCAST|IFF_RUNNING;
    if (ioctl(*sock, SIOCSIFFLAGS, &ifr) == -1)
    {
        LOGE("set '%s' to promisc model failed\n", interface);
		return -1;
    }

    LOGD("set '%s' to promisc successed\n", interface);
    return 1;
}

const char *target_addr;
const char *target_port;
const char *next_addr;
const char *next_port;  

int
init_args(int argc, char **argv)
{
	if (argc != 6)
	{
		LOGN("Usage: %s interface(eth0) targetIP targetPort nextIP nextPort\n", argv[0]);
		return 0;
	}

	target_addr = argv[2];
	target_port = argv[3];
	next_addr = argv[4];
	next_port = argv[5];

	return 0;
}

int inet_set_so_rbuffsize(int sd, int bufsize)
{
	int ret;

	ret = setsockopt(sd, SOL_SOCKET, /*SO_RCVBUF*/SO_RCVBUFFORCE, 
			(char *)&bufsize, sizeof(int));
	if (ret < 0)
		printf("setsockopt():SO_RCVBUFFORCE failed, errno=%d\n", errno);

	return ret;
}

int inet_set_so_wbuffsize(int sd, int bufsize)
{
	int ret;

	ret = setsockopt(sd, SOL_SOCKET, /*SO_SNDBUF*/SO_SNDBUFFORCE, 
			(char *)&bufsize, sizeof(int));
	if (ret < 0)
		printf("setsockopt():SO_SNDBUFFORCE failed, errno=%d\n", errno);

	return ret;
}



int inet_setsockopt_rw_buffsize(int sd, int bufsize)
{
	int ret;

	ret = inet_set_so_rbuffsize(sd, bufsize);
	if (ret < 0)
		return ret;

	ret = inet_set_so_wbuffsize(sd, bufsize);
	if (ret < 0)
		return ret;

	return ret;
}

int 
init_sock_addr(int sd, struct sockaddr_ll *sa, char *ni, int da)
{
	int ret;
	struct ifreq s_ifr; /* points to one interface returned from ioctl */
	int i_ifindex;

	/* clear structure */
	memset(&s_ifr, 0, sizeof(struct ifreq));
	memset(sa, 0, sizeof(struct sockaddr_ll));

	/* initialize interface struct */
	strncpy(s_ifr.ifr_name, ni, sizeof(s_ifr.ifr_name));

	/* get the broad cast address */
	ret = ioctl(sd, SIOCGIFINDEX, &s_ifr);
	if (ret == -1)
		RETURN_ERROR(-1, "ioctl network interface failed.\n");

	/* update with interface index */
	i_ifindex = s_ifr.ifr_ifindex;

	/* set sockaddr info */
	sa->sll_family = PF_PACKET;
	sa->sll_protocol = htons(ETH_P_IP);
	sa->sll_ifindex = i_ifindex;

	if (da) {
		/* set default mac address header */
		//char dstaddr[ETH_ALEN] = {0x00,0x22,0x46,0x10,0xDE,0x15};
		//memcpy(&(sa->sll_addr), dstaddr, ETH_ALEN);
		
		sa->sll_halen = ETH_ALEN;
		memset(&(sa->sll_addr), 0xff, ETH_ALEN);
	}

	if (!da) {
		/* listen mode that bind port */
		ret = bind(sd, (struct sockaddr *)sa, sizeof(struct sockaddr_ll));
		if (ret < 0)
			RETURN_ERROR(-1, "bind network interface failed.\n");
	}

	return 0;
}

int init_sock_ring()
{
	int ret;
	struct tpacket_req req;

	req.tp_block_size = al.block_size;
	req.tp_block_nr = al.block_count;
	req.tp_frame_size = al.block_size/2;
	req.tp_frame_nr = al.block_count*2;

	rg.tp_size = al.block_size * al.block_count;
	rg.tp_frame = al.block_size / 2;
	rg.tp_frame_count = rg.tp_size / rg.tp_frame;

	ret = setsockopt(fd_recv, SOL_PACKET, PACKET_RX_RING, 
			(void *)&req, sizeof(req));
	if (ret < 0) 
		RETURN_ERROR(-1, "set PACKET_RX_RING failed.\n");

	ret = setsockopt(fd_send, SOL_PACKET, PACKET_TX_RING, 
			(void *)&req, sizeof(req));
	if (ret < 0)
		RETURN_ERROR(-1, "set PACKET_TX_RING failed.\n");

	rg.rx_ring = (char *)mmap(0, rg.tp_size, PROT_READ|PROT_WRITE, MAP_SHARED, 
			fd_recv, 0);
	if (rg.rx_ring == MAP_FAILED)
		RETURN_ERROR(-1, "create RX_RING mmap failed.\n");

	rg.tx_ring = (char *)mmap(0, rg.tp_size, PROT_READ|PROT_WRITE, MAP_SHARED, 
			fd_send, 0);
	if (rg.rx_ring == MAP_FAILED)
		RETURN_ERROR(-1, "create TX_RING mmap failed.\n");

	return 0;
}

int 
init_packet_socket()
{
	int ret;

	/* open recv packet socket */
	fd_recv = socket(PF_PACKET, /*SOCK_DGRAM*/SOCK_RAW, htons(ETH_P_IP));;
	if (fd_recv < 0)
		return -1;

	ret = init_sock_addr(fd_recv, &sa_recv, dev_recv, 0);
	if (ret < 0)
		return ret;

	/* open send packet socket */
	fd_send = socket(PF_PACKET, /*SOCK_DGRAM*/SOCK_RAW, htons(ETH_P_IP));;
	if (fd_send < 0) 
		return -1;

	/* set send packet socket buf size */
	ret = inet_setsockopt_rw_buffsize(fd_send, 4096);
	if (ret < 0)
		RETURN_ERROR(-1, "set send packet socket buf size failed.\n");

	ret = init_sock_addr(fd_send, &sa_send, dev_send, 1);
	if (ret < 0)
		return ret;

	/* set packet socket ring mmap */
	if (init_sock_ring() < 0)
		return -1;

	return 0;
}

int 
main(int argc,char **argv)
{
//	init_args(argc, argv);

//	if (init_client_sock(argv[1]) < 0)
//		return -1;
		
	if (init_packet_socket() < 0)
		return -1;

	next = calloc(sizeof(struct sockaddr_in), 1);
	if (init_server_sock(next, &next_sock, next_addr, next_port) < 0)
		return -1;

	target = calloc(sizeof(struct sockaddr_in), 1);
	if (init_server_sock(target, &target_sock, target_addr, target_port) < 0)
		return -1;

	char *buf = (char*)calloc(buf_size, 1);
	int rval;
	int ret;

	for (;;)
	{
		rval = recv_data(buf);
		if (rval > 0)
		{
			/* 
			 * Data should put to queue by normal.
			 * Now send it directly for convenience. 
			 * Just temporary.  
			 */
			ret = check_data_in_rule(buf);
			if (ret > 0)
			{
				output_str_to_hex((unsigned char*)buf, rval);
//				buf = buf + 14 + sizeof(IP_HEADER) + sizeof(TCP_HEADER) + 20;
//				rval = rval - 14 - sizeof(IP_HEADER) - sizeof(TCP_HEADER) - 20;

				ret = sendto(fd_send, buf, rval, 0,
					(struct sockaddr *)next, sizeof(struct sockaddr_in));

				LOGN("send len to next: %d\n", ret);
//				send_data_to_next(buf, rval);
			}
        }
    }

	free(buf);
    return 0;
}

