/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: getopt_long.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月01日 11时32分30秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月01日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int cpu;
int mem;
int file;

char* const short_options = "hc:m:f:";
struct option long_options[] = 
{
	{"cpu", required_argument, 0, 'c'},
	{"mem", required_argument, 0, 'm'},
	{"file", required_argument, 0, 'f'},
	{"help", no_argument, 0, 'h'},
	{0, 0, 0, 0},
};

void
Usage(int argc, char *argv[])
{
	printf ( "usage:%s [cpu_over_load_per]\n", argv[0] );
}

void 
pars_args(int argc, char *argv[])
{
	char c;
	char *opt_arg;

	while ( (c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1 )
	{
		switch (c)
		{
			case 'h':
				Usage(argc, argv);
				break;
			case 'c':
				opt_arg = optarg;
				printf("cpu is:%s!\n", opt_arg);
				cpu = atoi(opt_arg);
				break;
			case 'm':
				opt_arg = optarg;
				printf("mem is:%s!\n", opt_arg);
				mem = atoi(opt_arg);
				break;
			case 'f':
				opt_arg = optarg;
				printf("file is:%s!\n", opt_arg);
				file = atoi(opt_arg);
				break;
		}
	}			
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		Usage(argc, argv);
		return 0;
	}

	pars_args(argc, argv);	

	exit(1);
}
