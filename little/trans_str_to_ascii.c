/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: trans_str_to_ascii.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月29日 00时45分51秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月29日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int ui;
const char str_demo[] = "\\\"HmEvNl_\\\"\\u89e3\\u4e91\\u98de";

#define	xfree(p) 			\
do {						\
	if (p) {				\
		free(p);			\
		p = NULL; 			\
	}						\
} while (0)

char *
trans_ascii_to_str(const char *src) 
{
	ui asc_char;
	int i, j, transflag;
	int len_src = strlen(src);

	char *dst = (char *)calloc(len_src, 1);
	if ( dst == NULL )
		return NULL;

	for ( i = 0, j = 0, transflag = 0; i < len_src; i++ )	
	{
		if ( src[i] == '\\' )
		{
			transflag = 1;
			continue;	
		}	

		if ( src[i] == 'u' && transflag )
		{
			if ( (i+4) >= len_src )
			{
				xfree(dst);
				return NULL;
			}

			sscanf( src+i+1, "%04x", &asc_char);
			if ( asc_char > 0xff )
			{
				dst[j++] = ((char*)&asc_char)[1];
			}

			dst[j++] = ((char*)&asc_char)[0];
			i = i + 4;
			continue;
		}

		dst[j++] = src[i];
		transflag = 0;
	}

	return dst;
}    

int
main(int argc, char *argv[])
{
	char *dst = trans_ascii_to_str(str_demo);
	printf ( "%s\n", dst );

	return 0;
}
