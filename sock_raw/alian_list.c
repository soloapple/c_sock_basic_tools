/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: alian_list.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��01��01�� 21ʱ49��59��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��01��01��                  build this moudle  
 *****************************************************************************/
#include <stdio.h>

#define TPACKET_ALIGNMENT   16
#define TPACKET_ALIGN(x)    (((x)+TPACKET_ALIGNMENT-1)&~(TPACKET_ALIGNMENT-1))

int main()
{
	printf ( "%d\n", TPACKET_ALIGN(28) );
	printf ( "%d\n", ~(15));
	printf ( "%d\n", 43&(-16) );

	return 0;
} 
