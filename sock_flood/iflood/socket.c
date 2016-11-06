/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: data.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/18/16 19:37:06
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/18/16                  build this moudle  
 ***************************************************************************************/

#include "socket.h"

/* ----- trans from socket addr to x.x.x.x  ----- */
	char *
s_net_ntoa(char *buf, size_t bufsize, struct in_addr a)
{
	unsigned int ip = ntohl(a.s_addr);

	snprintf(buf, bufsize, "%d.%d.%d.%d",
			(ip & 0xff000000) >> 24,
			(ip & 0x00ff0000) >> 16,
			(ip & 0x0000ff00) >> 8,
			(ip & 0x000000ff));
	return buf;
}

/* ----- trans from "x.x.x.x" to int ----- */
	int
s_inet_aton(char *buf, struct in_addr *a)
{
	return inet_aton(buf, a);
}


char *
inet_ultoa(unsigned int u, char * s)
{
    static char ss[20];

    if (s == NULL)
        s = ss;
    sprintf(s, "%d.%d.%d.%d",
            (unsigned int)(u>>24)&0xff, (unsigned int)(u>>16)&0xff,
            (unsigned int)(u>>8)&0xff, (unsigned int)u&0xff);
    return s;
}

int 
inet_atoul(const char * s)
{
    int i;
    int u[4];
    unsigned int rv;

    if(sscanf(s, "%d.%d.%d.%d", &u[0], &u[1], &u[2], &u[3]) == 4) {
        for (i = 0, rv = 0; i < 4; i++) {
            rv <<= 8;
            rv |= u[i] & 0xff;
        }
        return rv;
    } else
        return 0xffffffff;
}


/* ----- interface ----- */
int 
s_net_init(struct sockaddr_in *s_net_addr, char *s_ip, char *s_port)
{
	int s_sock;
    s_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (s_sock < 0)
    {
		printf ( "socket\n" );
        return false;
    }

	int reuse = 1;
  	if (setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) == false) 
		return false;

    memset(s_net_addr, 0x00, sizeof(struct sockaddr_in));
    s_net_addr->sin_family = AF_INET;
	s_net_addr->sin_addr.s_addr = inet_addr(s_ip);
    s_net_addr->sin_port = htons(atoi(s_port));

	return s_sock;
}


/* ----- only set timeout ----- */
void	
s_net_set_tout(int s_sock)
{
	struct timeval timeout = {120, 0};

	setsockopt(s_sock, SOL_SOCKET,SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));
	setsockopt(s_sock, SOL_SOCKET,SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
}

/* ----- connect ----- */
int
s_net_connect(int s_sock, struct sockaddr_in *s_net_addr)
{   
    socklen_t s_net_len = sizeof(struct sockaddr_in);
	if ((connect(s_sock, (struct sockaddr*)s_net_addr, s_net_len)) < 0)
	{
		perror("connect");
		return false;
	}

	return true;
}


/* ----- accept  ----- */
int
s_net_accept(int l_sock, struct sockaddr_in *c_addr)
{
	socklen_t s_len = sizeof(struct sockaddr_in);
	int c_sock = accept(l_sock, (struct sockaddr*)c_addr, &s_len);
	if (c_sock < 0)
		perror("accept()");
	
	return c_sock;
}


int 
s_net_recv_by_len(int s_sock, char *r_buf)
{
	unsigned int n_total = 0;
	unsigned int n_read = 0;

	if ( (n_read = recv(s_sock, r_buf, 4, 0)) <= 0)
    {
		perror("irecv()");
		return false;
    }

	memcpy(&n_total, r_buf, 4);
	//printf("[%s %d]: recv total %d\n", __FILE__, __LINE__, n_total);
		
	if ( (n_read = s_net_recv(s_sock, r_buf, n_total)) <= 0)
    {
		perror("irecv()");
		return false;
    }
	
	//printf("[%s %d]: recv nread %d\n", __FILE__, __LINE__, n_read);

	return n_read+4;	
}


/* ----- recv ----- */
int
s_net_recv(int s_sock, char *r_buf, int len)
{
    unsigned int nread = 0;
    unsigned int nleft = len;
    char   *ptr = r_buf;

    while (nleft > 0)
    {
        if ( (nread = recv(s_sock, ptr, nleft, 0)) <= 0)
        {
			perror("irecv()");
            return false;
        }

        nleft -= nread;
        ptr += nread;

	//	printf("[%s %d]: s_net_recv %d\n", __FILE__, __LINE__, nread);
    }

	//printf("[%s %d]: final in net recv %d\n", __FILE__, __LINE__, len-nleft);
    return len - nleft;
}


int 
s_net_send_by_len(int s_sock, char *t_buf, int len)
{
	char s_buf[BUFSIZ] = {0};

	int n_read = (len < BUFSIZ-4 ? len : BUFSIZ-4);
	memcpy(s_buf, &n_read, 4);
	memcpy(s_buf + 4, t_buf, n_read);

	//printf("[%s %d]: send nread %d\n", __FILE__, __LINE__, n_read);

	return s_net_send(s_sock, s_buf, n_read + 4);
}


/* ----- send  ----- */
int
s_net_send(int s_sock, char *s_buf, int len)
{
	int ret = 0;
    unsigned int nsend = 0;
    unsigned int total = len;

    while (len > 0) {
        if ((ret = send(s_sock, (void*)((unsigned long)s_buf + nsend), total - nsend, 0)) < 0) {
            if (errno != EPIPE)
                printf("Send() error: [%d] %s", errno, strerror(errno));
            return -1;
        }
        nsend += ret;
        len -= nsend;
    }
    return nsend;
}


/* ----- set nonblock  ----- */
int
s_set_nonblock(int s_sock)
{
    int opts = fcntl(s_sock, F_GETFL);
    if(opts < 0)
    {
        perror("fcntl(sock,GETFL)");
        return false;
    }

    opts = opts | O_NONBLOCK;
    if(fcntl(s_sock, F_SETFL, opts) < 0)
    {
        perror("fcntl(sock,SETFL,opts)");
        return false;
    }

	return true;
}

int 
s_net_bind(int s_sock, struct sockaddr_in *s_net_addr) 
{
	if (bind(s_sock, (struct sockaddr*)s_net_addr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("bind()");
		return false;
	}

	return true;
}

int 
s_net_listen(int s_sock)
{
	int ret = listen(s_sock, SOMAXCONN);
	return ret;
}

int 
s_net_accept(int s_sock, struct sockaddr* s)
{
	socklen_t s_len = sizeof(struct sockaddr_in);
	int ret = accept( s_sock, s, &s_len);
	return ret;
}

int 
noblock_accept(int fd, struct sockaddr* paddr, int addrlen, const int time_out)
{
    int    ret;
    int    newfd;
    fd_set rfds;
    struct timeval tv;

    if (s_set_nonblock(fd) < 0)
        return false;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    tv.tv_sec = time_out;
    tv.tv_usec = 0;

    ret = select(fd+1, &rfds, NULL, NULL, &tv);
    if (ret <= 0)
        return ret;

    if (FD_ISSET(fd, &rfds)) {
        newfd = accept(fd, paddr, (unsigned int*)&addrlen);
        return newfd;
    }

    return 0;
}

