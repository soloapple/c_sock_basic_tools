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
void
prt_char(char c)
{
	if (isprint(c))
		printf("%c", c);
	else
		printf(" ");
}

void
prt_hex(char c)
{
	if (isprint(c))
		printf(" %02x ", c);
	else
		printf(" %02x ", c);
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

	for ( i=0; i<len; i++ )
	{
		if ( (((i+1)%16) == 1) )
			printf(" %08x ", i);

		prt_hex(buf[i]);

		if ( (((i+1)%8) == 0) && (((i+1)%16) != 0) )
			printf(" -- ");

		if ( (((i+1)%16) == 0) )
		{
			line_num = get_line_head_num(i);
			j = 16 * line_num;

			printf("     ");
			for( x=0; x<16; x++, j++ )
			{
				prt_char(buf[j]);
			}
			puts("");
		}
	}
}


int
main(int argc, char *argv[])
{
	if ( argc != 2 )
		printf("USAGE: %s string", argv[0]);

	char *s = argv[1];
	print_hex(s, 48);
	
	return 0;
}
