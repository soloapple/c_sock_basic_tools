/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: fdarray.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   11/22/16 10:57:22
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/22/16                  build this moudle  
 *****************************************************************************/
#include "headers.h"
list <int> cli_sock_fd_array;

void
quit_sock_array()
{
	if ( cli_sock_fd_array.empty() )
		exit(0);

	LOGD("array is not empty, cleaning!\n");
	list<int>::iterator it;
	for ( it=cli_sock_fd_array.begin();
			it!=cli_sock_fd_array.end();
			)	
	{
		LOGE("close socket id:%d\n", (*it));
		close(*it);
		it++;
	}

	cli_sock_fd_array.clear();

	exit(0);
}

int
init_sock_array(int link_num)
{
	int i;

	for ( i=0; i<link_num; i++ ) 
	{
		int sockfd = socket(PF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			LOGE("create socket failed!\n");
			return -1;
		}

		int reuse = 1;
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) == false) 
		{
			LOGE( "Set sockopt failed!\n");
			return -1;
		}

		cli_sock_fd_array.push_back(sockfd);
	}

	return 0;
}

int
init_sock_addr(struct sockaddr_in *s_net_addr, char *s_ip, char *s_port)
{
    memset(s_net_addr, 0x00, sizeof(struct sockaddr_in));
    s_net_addr->sin_family = AF_INET;
	s_net_addr->sin_addr.s_addr = inet_addr(s_ip);
    s_net_addr->sin_port = htons(atoi(s_port));

	return 0;
}		

/* 
 * Name:  conn_sock_array
 * Description:  if connect failed, erase it, continue others.
 */ 
void
conn_sock_array(struct sockaddr_in *s_net_addr) 
{
	int res;
//	int reconn_time;

	list<int>::iterator it;
	for ( it=cli_sock_fd_array.begin();
			it!=cli_sock_fd_array.end();
			)	
	{	
		res = s_net_connect(*it, s_net_addr);
		if ( res < 0 )
		{		
			LOGE("sock fd [%d] connect failed, erase!\n", *it);
			close(*it);
			cli_sock_fd_array.erase(it++);
			continue;
		}
		else
		{
			LOGE("sock fd [%d] connect success!\n", *it);
			it++;
		}
	}

	return;
}    

/* 
 * Name:  send_sock_data
 * Description:  
 */ 
int
send_sock_data(char *t_buf, int n_read) 
{
	int send_len;
	int recv_len;
	char s_buf[BUFSIZ] = {0};
	char r_buf[BUFSIZ] = {0};

	list<int>::iterator it;
	for ( it=cli_sock_fd_array.begin();
			it!=cli_sock_fd_array.end();
			)	
	{	
		send_len = s_net_send_by_len(*it, s_buf, n_read);
		if ( send_len <= 0 )
		{
			LOGE("client send data failed!\n");
			close(*it);
			cli_sock_fd_array.erase(it++);	
		}

		recv_len = s_net_recv_by_len(*it, r_buf);
		if ( recv_len <= 0 )
		{
			LOGE("client recv data failed!\n");
			close(*it);
			it = cli_sock_fd_array.erase(it++);	
		}

		if ( cli_sock_fd_array.empty() )
		{
			LOGE("socket array is empty!\n");
			return -1;
		}

		it++;
	}

	return 0;
}    

/* 
 * prepare socket fds, 
 * num is given by args.
 * then connect and send data to server one by one. 
 */
void 
c_process_fdarray(char *ip, char *port, char *file, 
		int link_num, int link_mode, int interval, int times)
{
	int ret;
	int n_read = 0;
	struct sockaddr_in s_net_addr;
	char t_buf[BUFSIZ] = {0};

	n_read = w_read_file_to_buf(file, t_buf);
	if ( n_read <= 0 )
		return;
	
	init_sock_addr(&s_net_addr, ip, port);

	ret = init_sock_array(link_num);
	if ( ret < 0 )
		goto end;

	conn_sock_array(&s_net_addr);
	if ( cli_sock_fd_array.empty() )
	{
		LOGE("connect failed, fd array is empty!\n");
		goto end;
	}

	for (;;)	
	{
		if ( (ret = send_sock_data(t_buf, n_read)) < 0 )
			break;
	}

end:
	quit_sock_array();
	return;
}
