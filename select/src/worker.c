/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: worker.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/26/16 12:49:50
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/26/16                  build this moudle  
 ***************************************************************************************/

#include "worker.h"
#include "socket.h"

int 
c_wait_childs(int *status)
{
	int ret;

	while(((ret = wait(status)) == -1) && (errno == EINTR));
		return ret;
}

int 
w_read_file_to_buf(char *file, char *t_buf)
{
	int n_read = 0;

	FILE *f = fopen(file, "r+");
	if(f == NULL)
	{
		LOGE("%s IS NOT EXIST", file);
		goto end;
	}

	n_read = fread(t_buf, 1, BUFSIZ, f);
	if (n_read <= 0) 
	{
		LOGE("READ %s FAILED", file);
		goto end;	
	}

end:
	if ( f != NULL )
		fclose(f);

	return n_read;
}

void
w_mission_start(char *ip, char *port, char *t_buf, int n_read)
{
	int s_sock = 0;
	char s_buf[BUFSIZ] = {0};
	char r_buf[BUFSIZ] = {0};
	struct sockaddr_in s_net_addr;

	int res;

	int send_len = 0;
	int recv_len = 0;
	
	s_sock = s_net_init(&s_net_addr, ip, port);
	res = s_net_connect(s_sock, &s_net_addr);
	if ( res < 0 )
		goto EXIT_LONG;


	for (;;)
	{
		send_len = s_net_send_by_len(s_sock, s_buf, n_read);
		if(send_len <= 0)
			goto EXIT_LONG;

		recv_len = s_net_recv_by_len(s_sock, r_buf);
		if(recv_len <= 0)
			goto EXIT_LONG;
	}

EXIT_LONG:
	close(s_sock);

	return;
}

void 
w_short_mission_start(char *ip, char *port, char *t_buf, int n_read)
{
	int s_sock = 0;
	char s_buf[BUFSIZ] = {0};
	char r_buf[BUFSIZ] = {0};
	struct sockaddr_in s_net_addr;

	int send_len = 0;
	int recv_len = 0;

	s_sock = s_net_init(&s_net_addr, ip, port);
	int res = s_net_connect(s_sock, &s_net_addr);
	if (res < 0)
		goto EXIT_SHORT;

	send_len = s_net_send_by_len(s_sock, s_buf, n_read);
	if(send_len <= 0)
		goto EXIT_SHORT;

	recv_len = s_net_recv_by_len(s_sock, r_buf);
	if(recv_len <= 0)
		goto EXIT_SHORT;

EXIT_SHORT:
	LOGDP("CHILD PROCEDURE QUIT!\n");
	close(s_sock);

	return;
}

void 
c_process(char *ip, char *port, char *file, int link_num, int link_mode, int interval, int times)
{
 	int i = 0;
	int status = 0;
	char t_buf[BUFSIZ] = {0};
	int n_read = w_read_file_to_buf(file, t_buf);
	if (n_read <= 0)
		return;

resend:

    for (i = 0; i < link_num; i++)
    {
        status = fork();
        if ( status == 0 )
        {
			if( link_mode == LONG_MODE ) 
			{
				LOGD("Long Mode process[%d] start!\n", getpid());
				w_mission_start(ip, port, t_buf, n_read);
			}
			else
			{
				LOGD("Short Mode process[%d] start!\n", getpid());
				w_short_mission_start(ip, port, t_buf, n_read);
			}

            return;
        }
		else if (status < 0)
		{
			LOGEP("Fork failed!");
            return;
		}
    }	

	if ( link_mode == SHORT_MODE )
	{
		while ( times-- != 1 )
		{
			while (c_wait_childs(NULL) > 0);
				usleep(interval);
			goto resend;
		}
	}
} 

	void
s_child_server(int c_fd, struct sockaddr_in *paddr)
{
	int n_recv = 0;
	int n_send = 0;
	char buf[BUFSIZ] = {0};

	s_net_set_tout(c_fd);

	for(;;)
	{
		n_recv = s_net_recv_by_len(c_fd, buf);
		if (n_recv > 0) 
		{
			n_send = s_net_send_by_len(c_fd, buf, n_recv);
			if (n_send < 0)
			{
				char addr_p[16];
				inet_ntop(AF_INET, &(paddr->sin_addr),
					addr_p, (socklen_t)sizeof(addr_p));
				LOGWP("Send data to ip:%s Port:%d error\n", 
					addr_p, paddr->sin_port );

				break;
			}
		}
		
		if (n_recv == 0 )
		{
			char addr_p[16];
			inet_ntop(AF_INET, &(paddr->sin_addr),
				addr_p, (socklen_t)sizeof(addr_p));
			LOGDP( "Closed Client ip:%s Port:%d\n", 
				addr_p, paddr->sin_port );

			break;
		}

		if (n_recv < 0)
		{
			char addr_p[16];
			inet_ntop(AF_INET, &(paddr->sin_addr),
				addr_p, (socklen_t)sizeof(addr_p));
			LOGWP( "abnormal close Client ip:%s Port:%d\n", 
				addr_p, paddr->sin_port );

			break;
		}
	}

EXIT_CHLD:
	close(c_fd);
	exit(0);
}

	void 
s_process(char *ip, char *port)
{
	int s_sock = 0;
	int c_fd;	
	int status;
	struct sockaddr_in s_net_addr;
	struct sockaddr_in c_net_addr;

	int n = 0;

	int s_len = sizeof(struct sockaddr_in);

	s_sock = s_net_init(&s_net_addr, ip, port);
	
	if ( s_net_bind(s_sock, &s_net_addr) < 0 )
		return ;

	if ( s_net_listen(s_sock) < 0 )
		return;

	for (;;) {
		c_fd = noblock_accept(s_sock, &c_net_addr, s_len, 10);
		if ( c_fd < 0 ) {
			if(errno == EAGAIN||errno == EWOULDBLOCK||errno == EINTR)
				continue;
			else
				break;
		}

		if ( c_fd == 0 )
			continue;		

		status = fork();
		if ( status == 0 ) {
			close(s_sock);
			s_child_server(c_fd, &c_net_addr);
		}

		n++;
		LOGDP("[%d] Process\n", n);
		close(c_fd);
	}	
}
