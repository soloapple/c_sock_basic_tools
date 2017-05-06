/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: hex_print.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/01/16 16:33:47
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/01/16                  build this moudle  
 ***************************************************************************************/
#include "hex_print.h"
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
	int i,j,x;
	int line_num;
	int time = 16;
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
	for( x=0; x<(len%16); x++, j++ )
	{
		prt_char(buf[j]);
	}
	puts("");
}

char *	
hex_print ( char *pstr )
{
	if (pstr == NULL )
	{
		LOGN("String is empty!\n");
		return;
	}

	print_hex(pstr, strlen(pstr));
	
	return 0;
}
