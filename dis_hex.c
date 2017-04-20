/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: dis_hex.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月20日 05时45分38秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月20日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <getopt.h>

char *file = NULL;
char *pstr = NULL;

char *const short_options = "f:s:h";
struct option long_options[] =
{
	{"file", 1, NULL, 'f'},      
	{"str", 1, NULL, 's'},      
	{"help", 0, NULL, 'h'},      
	{0, 0, 0, 0},
};

void
prt_char(char c)
{
	if (isprint(c))
		printf("%c", c);
	else
		printf("*");
}

void
prt_hex(char c)
{
	if (isprint(c))
		printf(" %02x ", c);
	else
		printf(" ** ");
}

int
get_line_head_num(int i)
{
	int j;
	j = (i/16);

	return j;
}

void
print_hex(char *buf, int len)
{
	int i;
	int j;
	int line_num;
	int time = 16;
	int x;
	int n_polish;
	bool show_mid = false;

	int last_line = get_line_head_num(len);
	int last_head = last_line * 16;

	for ( i=0; i<len; i++ )
	{
		if ( (((i+1)%16) == 1) )
			printf(" %08x ", i);

		prt_hex(buf[i]);

		if ( (((i+1)%8) == 0) && (((i+1)%16) != 0) )
			printf(" -- ");

		if ( (((i+1)%16) == 0) )
		{
			j = get_line_head_num(i) * 16;

			printf("     ");
			for( x=0; x<16; x++, j++ )
			{
				prt_char(buf[j]);
			}
			puts("");
		}
	}

	/* print last line hex. */
	n_polish = len;
	if ( (n_polish%16) < 8 )	
	{
		show_mid = true;
	}

	while ( (n_polish % 16) != 0 )
	{
		if ( (((n_polish)%8) == 0) && show_mid )
			printf(" -- ");

		printf(" ** ");
		n_polish++;
	}

	/* print last line str. */
	j = last_head;
	printf("     ");
	for( x=0; x<16; x++, j++ )
	{
		prt_char(buf[j]);
	}
	puts("");
}

int 
read_conf(char *file, char **p, size_t fsize)
{
	FILE *fp = fopen(file, "r+");
	if ( fp == NULL )
	{
		printf ( "file is null\n" );
		return -1;
	}

	int n = fread(*p, 1, fsize, fp);

	return n;
}


/* 
 * Name:  usage
 * Description:  
 */ 
void
usage(int argc, char *argv[]) 
{
	printf( 
			"USAGE: exec -f filename|-s string.\n\n"
			" h, --help	display the help and exit.\n"
			" f, filename, file to display to hex.\n"
			" s, string to display.\n"
	);
}    

void
parse_arg(int argc, char *argv[])
{
	int c;      
	while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1)      
	{
		switch (c)
		{
			case 'f':
				file = strdup(optarg);
				break;
			
			case 's':
				pstr = strdup(optarg);
				break;
			
			case 'h':
				usage(argc, argv);	
				break;
		
			default:
				usage(argc, argv);	
				break;
		}
	}
}

size_t
get_file_size(char *path)  
{  
	size_t filesize = -1;      
	struct stat statbuff;  
	if(stat(path, &statbuff) < 0){  
		return filesize;  
	}else{  
		filesize = statbuff.st_size;  
	}  
	return filesize;  
}  

int
main(int argc, char *argv[])
{
	parse_arg(argc, argv);

	if (file != NULL)
	{
		size_t fsize = get_file_size(file);
		char *p = (char*)calloc(fsize, 1);
		read_conf(file, &p, fsize);
		print_hex(p, fsize);

		free(p);
	}

	if (pstr != NULL)
	{
		print_hex(pstr, strlen(pstr));
	}
	
	return 0;
}
