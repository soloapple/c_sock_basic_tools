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

static int n_child = 1;
extern int lenbuf;

	void *
foo(void*)
{
	printf ( "*** running thread child:%d ***\n", n_child);
	n_child++;
	return NULL;
}

	void
max_thread()
{
	pthread_t thread;
	int i = 0;

	while (1) {
		if (pthread_create(&thread, NULL, foo, NULL) != 0)
			return;
		i++;
		printf("i = %d\n", i);
	}
}

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
	FILE *f = fopen(file, "r+");
	if(f == NULL)
	{
		perror(file);
		return EXIT_FAILURE;
	}

	int n_read = fread(t_buf, 1, BUFSIZ, f);
	if (n_read <= 0) 
	{
		perror("fread()");
		fclose(f);
		return EXIT_FAILURE;	
	}

	return n_read;
}

/* ----- init socket , read file, and send, recv ----- */
	int 
w_mission_start(char *ip, char *port, char *t_buf, int n_read)
{
	int s_sock = 0;
	char s_buf[BUFSIZ] = {0};
	char r_buf[BUFSIZ] = {0};
	struct sockaddr_in s_net_addr;
	
	s_sock = s_net_init(&s_net_addr, ip, port);
	int res = s_net_connect(s_sock, &s_net_addr);
	if (res < 0)
		return EXIT_FAILURE;

	int send_len = 0;
	int recv_len = 0;

#ifndef M_SHORT
	for (;;)
#endif
	{
		send_len = s_net_send_by_len(s_sock, s_buf, n_read);
		if(send_len <= 0)
		{
			perror("send()");
			goto EXIT;
		}

		recv_len = s_net_recv_by_len(s_sock, r_buf);
		if(recv_len <= 0)
		{
			perror("recv()");
			goto EXIT;
		}
	}

EXIT:
	close(s_sock);

	return 0;
}

	int
w_short_mission_start(char *ip, char *port, char *t_buf, int n_read)
{
	int s_sock = 0;
	char s_buf[BUFSIZ] = {0};
	char r_buf[BUFSIZ] = {0};
	struct sockaddr_in s_net_addr;

	s_sock = s_net_init(&s_net_addr, ip, port);
	int res = s_net_connect(s_sock, &s_net_addr);
	if (res < 0)
		return EXIT_FAILURE;

	int send_len = 0;
	int recv_len = 0;

	{
		send_len = s_net_send_by_len(s_sock, s_buf, n_read);
		if(send_len <= 0)
		{
			perror("send()");
			goto EXIT;
		}

		recv_len = s_net_recv_by_len(s_sock, r_buf);
		if(recv_len <= 0)
		{
			perror("recv()");
			goto EXIT;
		}
	}

EXIT:
	close(s_sock);

	return 0;
}

	void 
c_process(char *ip, char *port, char *file, int link_num, int link_mode, int interval, int times)
{
  	assert(file);

	int status = 0;
	char t_buf[BUFSIZ] = {0};
	int n_read = w_read_file_to_buf(file, t_buf);
	if (n_read <= 0)
		return;

resend:

 	int i = 0;
    for (i = 0; i < link_num; i++)
    {
        status = fork();
        if (status == 0)
        {
			if(link_mode) 
			{
				printf("process start %d\n", getpid());
				w_mission_start(ip, port, t_buf, n_read);
			}
			else
			{
				printf("process start %d\n", getpid());
				w_short_mission_start(ip, port, t_buf, n_read);
			}

            return;
        }
		else if (status < 0)
            return;
    }	

	if (!link_mode)
	{
		while (times-- != 0)
		{
			while (c_wait_childs(NULL) > 0);
			usleep(interval);
			printf("resend\n");
			goto resend;
		}
	}
} 

	void
s_child_server(int c_fd)
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
				perror("send()");										
				goto EXIT;
			}
		}
		
		if (n_recv == 0 )
		{
			perror("0 recv()");
			goto EXIT;
		}

		if (n_recv < 0)
		{
			perror("-1 recv()");
			goto EXIT;
		}
	}

EXIT:
	puts("EXIT!");
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
	int s_len = sizeof(struct sockaddr_in);

	s_sock = s_net_init(&s_net_addr, ip, port);
	
	if (s_net_bind(s_sock, &s_net_addr) < 0)
		return ;

	if (s_net_listen(s_sock) < 0)
		return;

	for (;;) {
		c_fd = noblock_accept(s_sock, (struct sockaddr*)&s_net_addr, s_len, 10);
		if (c_fd < 0) {
			if(errno == EAGAIN||errno == EWOULDBLOCK||errno == EINTR)
				continue;
			else
				break;
		}

		if (c_fd == 0)
			continue;		

		status = fork();
		if (status == 0) {
			printf ( "[%s %d]:accept fd:%d\n", __FILE__, __LINE__, c_fd );
			close(s_sock);
			s_child_server(c_fd);
		}

		close(c_fd);
	}	
}
