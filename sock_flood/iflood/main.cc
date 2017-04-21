/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: main.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/16/16 01:03:38
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/16/16                  build this moudle  
 ***************************************************************************************/
#ifndef  MAIN_INCLUDE
#define  MAIN_INCLUDE

#include "headers.h"

char *l_opt_arg;
char *const short_options = "p:i:f:c:shm:t:n:l:";
char *DFT_PORT = "8000";
char *DFT_IP = "0.0.0.0";

/* ----- 1: client , 0: server ----- */
int cs_mode;
int mode = 1;
int nums = 1;

int interval = 100000;
int times = 1;
int lenbuf = BUFSIZ;

struct option long_options[] =
{
	{"client", 1, NULL, 'c'},      
	{"server", 0, NULL, 's'},      
	{"port", 1, NULL, 'p'},      
	{"file", 1, NULL, 'f'},      
	{"nums", 1, NULL, 'n'},      
	{"mode", 1, NULL, 'm'},
	{"lenbuf", 1, NULL, 'l'},
	{"interval", 1, NULL, 'i'},
	{"times", 1, NULL, 't'},
	{"help", 0, NULL, 'h'},      
	{0, 0, 0, 0},      
};

void usage(int argc, char *argv[])
{
	printf( 
			"Usage: client or server\n"
			"Client: iflood -c ip -f file [ -p port -n nums -m 1(long)|0(short)\n -t times -i interval ]\n"
			"Server: iflood -s [ -p port ]\n"
			"\n\n"
			"Client/Server:\n"
			" p, --port	server port, default value is 8000\n"
			"\n\n"
			"Client specific:\n"
			" c, --client	start as client\n"
			" f, --file	file to send, largest size if 8k. only use by client\n"
			" n, --nums	the num of client process that connect to server. default nums is 1\n"
			" i, --interval	in short mode, the interval time between two send times. unit is um. default is 100000 \n"
			" t, --times	in short mode, the times that connect and send data to server. default is 1\n"
			" l, --len	set send and recv buf size, default is 8k.\n"
			" m, --mode	arg can be 1 or 0, represent long link or short link. default mode is long.\n"
			"\n\n"
			"Server specific:\n"
			" s, --server	start as server, listening on ip 0.0.0.0\n"
			"\n\n"
			"Miscellaneous:\n"
			" h, --help	display the help and exit\n"
	);

	exit(0);
}

const char *style = STYLE;
//const char *cstyle = CSTYLE;
const char *cstyle = "NULL";


/* 
 * Name:  quit_sys
 * Description:  
 */ 
void
quit_sys( ) 
{
	quit_sock_array();	

	return;
}    

/* 
 * Name:  sig_quit
 * Description:  
 */ 
void	
sig_quit(int signal) 
{
	switch ( signal ) 
	{
		case SIGINT:	
		case SIGSEGV:	
		case SIGILL:	
			quit_sys();	
			break;
	}

	return;
}    

int main(int argc, char *argv[])      
{      
	char *ip = DFT_IP;
	char *port = DFT_PORT;
	char *file = NULL;

	int c;      
	while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1)      
	{
		switch (c)
		{
			case 'i':
				interval = atoi(optarg);
				break;
			case 'p':
				port = strdup(optarg);
				break;
			case 'f':
				file = strdup(optarg);
				break;
			case 'c':
				cs_mode = 1;
				ip = strdup(optarg);
				break;
			case 's':
				cs_mode = 0;
				break;
			case 'n':
				nums = atoi(optarg);
				break;
			case 't':
				times = atoi(optarg);
				break;
			case 'm':
				mode = atoi(optarg);
				break;
			case 'l':
				lenbuf = atoi(optarg);
				break;
			case 'h':
				usage(argc, argv);	
				break;

			default:
				usage(argc, argv);	
				break;
		}
	}

	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, sig_quit);
	signal(SIGSEGV, sig_quit);
	signal(SIGILL, sig_quit);

	if (cs_mode)
	{
		if((mode != 0) && (mode != 1))
			usage(argc, argv);

		if((nums < 0) || (nums > 100000))
			usage(argc, argv);

		if ( !strcmp(cstyle, "fdarray") )
		{
			LOGD("CLIENT[ARRAY MODE] connect to server %s %s \n", ip, port)
			c_process_fdarray(ip, port, file, nums, mode, interval, times);
		}
		else
		{
			LOGD("CLIENT[PROCESS MODE] connect to server %s %s \n", ip, port)
			c_process(ip, port, file, nums, mode, interval, times);
		}
	}
	else
	{
		if ( !strcmp(style, "epoll") )
		{
			LOGDP("SERVER[EPOLL MODE] LISTENING ON %s!\n", port);
			s_process_epoll(ip, port);
		}
		else
		{
			LOGDP("SERVER[PPOCESS MODE] LISTENING ON %s\n", port);
			s_process(ip, port);
		}
	}
		
	return 0;
}

#endif   
